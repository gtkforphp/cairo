/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2014 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Elizabeth Smith <auroraeosrose@php.net>                      |
  |         Michael Maclean <mgdm@php.net>                               |
  +----------------------------------------------------------------------+
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_cairo.h"
#include "zend_exceptions.h"

#if CAIRO_HAS_PDF_SURFACE
#include <cairo-pdf.h>

zend_class_entry *cairo_ce_cairopdfsurface;

ZEND_BEGIN_ARG_INFO(CairoPdfSurface___construct_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, file)
	ZEND_ARG_INFO(0, width)
	ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoPdfSurface_setSize_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, width)
	ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()


/* {{{ proto void __construct(string|resource file, float width, float height) 
       Creates a PDF surface of the specified size in points to be written to filename. */
PHP_METHOD(CairoPdfSurface, __construct)
{
	zval *stream_zval = NULL;
	stream_closure *closure;
	php_stream *stream = NULL;
	double width, height;
	zend_bool owned_stream = 0;
	cairo_surface_object *surface_object;

	PHP_CAIRO_ERROR_HANDLING(TRUE)
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zdd", &stream_zval, &width, &height) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(TRUE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(TRUE)

	surface_object = (cairo_surface_object *)zend_object_store_get_object(getThis() TSRMLS_CC);

	/* special case - a NULL file is like an "in memory" PDF */
	if(Z_TYPE_P(stream_zval) == IS_NULL) {
		surface_object->surface = cairo_pdf_surface_create(NULL, width, height);
	/* Otherwise it can be a filename or a PHP stream */
	} else {
		if(Z_TYPE_P(stream_zval) == IS_STRING) {
			stream = php_stream_open_wrapper(Z_STRVAL_P(stream_zval), "w+b", REPORT_ERRORS|ENFORCE_SAFE_MODE, NULL);
			owned_stream = 1;
		} else if(Z_TYPE_P(stream_zval) == IS_RESOURCE)  {
			php_stream_from_zval(stream, &stream_zval);	
		} else {
			zend_throw_exception(cairo_ce_cairoexception, "CairoPdfSurface::__construct() expects parameter 1 to be null, a string, or a stream resource", 0 TSRMLS_CC);
			return;
		}

		/* Pack TSRMLS info and stream into struct*/
		closure = ecalloc(1, sizeof(stream_closure));
		closure->stream = stream;
		closure->owned_stream = owned_stream;
#ifdef ZTS
		closure->TSRMLS_C = TSRMLS_C;
#endif

		surface_object->closure = closure;
		surface_object->surface = cairo_pdf_surface_create_for_stream(php_cairo_write_func, (void *)closure, width, height);
	}

	php_cairo_throw_exception(cairo_surface_status(surface_object->surface) TSRMLS_CC);
}
/* }}} */

/* {{{ proto CairoPdfSurface cairo_pdf_surface_create(string|resource file, float width, float height)
       Creates a PDF surface of the specified size in points to be written to filename. */
PHP_FUNCTION(cairo_pdf_surface_create)
{
	zval *stream_zval = NULL;
	stream_closure *closure;
	php_stream *stream = NULL;
	zend_bool owned_stream = 0;
	double width, height;
	cairo_surface_object *surface_object;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zdd", &stream_zval, &width, &height) == FAILURE) {
		return;
	}

	object_init_ex(return_value, cairo_ce_cairopdfsurface);
	surface_object = (cairo_surface_object *)zend_object_store_get_object(return_value TSRMLS_CC);

	/* special case - a NULL file is like an "in memory" PDF */
	if(Z_TYPE_P(stream_zval) == IS_NULL) {
		surface_object->surface = cairo_pdf_surface_create(NULL, width, height);
	/* Otherwise it can be a filename or a PHP stream */
	} else {
		if(Z_TYPE_P(stream_zval) == IS_STRING) {
			stream = php_stream_open_wrapper(Z_STRVAL_P(stream_zval), "w+b", REPORT_ERRORS|ENFORCE_SAFE_MODE, NULL);
			owned_stream = 1;
		} else if(Z_TYPE_P(stream_zval) == IS_RESOURCE)  {
			php_stream_from_zval(stream, &stream_zval);	
		} else {
			 zend_error(E_WARNING, "cairo_pdf_surface_create() expects parameter 1 to be null, a string, or a stream resource");
			 RETURN_NULL();
		}

		/* Pack TSRMLS info and stream into struct*/
		closure = ecalloc(1, sizeof(stream_closure));
		closure->stream = stream;
		closure->owned_stream = owned_stream;
#ifdef ZTS
		closure->TSRMLS_C = TSRMLS_C;
#endif

		surface_object->closure = closure;
		surface_object->surface = cairo_pdf_surface_create_for_stream(php_cairo_write_func, (void *)closure, width, height);
	}

	php_cairo_trigger_error(cairo_surface_status(surface_object->surface) TSRMLS_CC);
}
/* }}} */

/* {{{ proto void cairo_pdf_surface_set_size(CairoPdfSurface object, double width, double height)
       proto void CairoPdfSurface->setSize(, double width, double height)
       Changes the size of a PDF surface for the current (and subsequent) pages.
       This should be called before any drawing takes place on the surface */
PHP_FUNCTION(cairo_pdf_surface_set_size)
{
	zval *surface_zval;
	double width = 0.0, height = 0.0;
	cairo_surface_object *surface_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odd", &surface_zval, cairo_ce_cairopdfsurface, &width, &height) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	surface_object = (cairo_surface_object *)cairo_surface_object_get(surface_zval TSRMLS_CC);

	cairo_pdf_surface_set_size(surface_object->surface, width, height);
	PHP_CAIRO_ERROR(cairo_surface_status(surface_object->surface));
}
/* }}} */

/* {{{ cairo_pdf_surface_methods[] */
const zend_function_entry cairo_pdf_surface_methods[] = {
	PHP_ME(CairoPdfSurface, __construct, CairoPdfSurface___construct_args, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME_MAPPING(setSize, cairo_pdf_surface_set_size, CairoPdfSurface_setSize_args, ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};
/* }}} */

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(cairo_pdf_surface)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "CairoPdfSurface", cairo_pdf_surface_methods);
	cairo_ce_cairopdfsurface = zend_register_internal_class_ex(&ce, cairo_ce_cairosurface, "CairoSurface" TSRMLS_CC);
	cairo_ce_cairopdfsurface->create_object = cairo_surface_object_new;

	return SUCCESS;
}

#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
