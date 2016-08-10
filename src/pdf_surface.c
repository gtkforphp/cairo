/*
  +----------------------------------------------------------------------+
  | For PHP Version 7                                                    |
  +----------------------------------------------------------------------+
  | Copyright (c) 2015 Elizabeth M Smith                                 |
  +----------------------------------------------------------------------+
  | http://www.opensource.org/licenses/mit-license.php  MIT License      |
  | Also available in LICENSE                                            |
  +----------------------------------------------------------------------+
  | Author: Elizabeth M Smith <auroraeosrose@gmail.com>                  |
  +----------------------------------------------------------------------+
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <cairo.h>
#include <php.h>
#include <zend_exceptions.h>

#include <ext/eos_datastructures/php_eos_datastructures_api.h>

#include "php_cairo.h"
#include "php_cairo_internal.h"

#if CAIRO_HAS_PDF_SURFACE
#include <cairo-pdf.h>

zend_class_entry *ce_cairo_pdfsurface;

/* ----------------------------------------------------------------
    Cairo\Surface\Pdf Class API
------------------------------------------------------------------*/

ZEND_BEGIN_ARG_INFO(CairoPdfSurface___construct_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, file)
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

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "zdd", &stream_zval, &width, &height) == FAILURE) {
		return;
	}

	surface_object = Z_CAIRO_SURFACE_P(getThis());
	if(!surface_object) {
            return;
        }

	/* special case - a NULL file is like an "in memory" PDF */
	if(Z_TYPE_P(stream_zval) == IS_NULL) {
		surface_object->surface = cairo_pdf_surface_create(NULL, width, height);
	/* Otherwise it can be a filename or a PHP stream */
	} else {
		if(Z_TYPE_P(stream_zval) == IS_STRING) {
			stream = php_stream_open_wrapper(Z_STRVAL_P(stream_zval), "w+b", REPORT_ERRORS, NULL);
			owned_stream = 1;
		} else if(Z_TYPE_P(stream_zval) == IS_RESOURCE)  {
			php_stream_from_zval(stream, stream_zval);	
		} else {
			zend_throw_exception(ce_cairo_exception, "Cairo\\Surface\\Pdf::__construct() expects parameter 1 to be null, a string, or a stream resource", 0 TSRMLS_CC);
			return;
		}

		/* Pack TSRMLS info and stream into struct*/
		closure = ecalloc(1, sizeof(stream_closure));
		closure->stream = stream;
		closure->owned_stream = owned_stream;

		surface_object->closure = closure;
		surface_object->surface = cairo_pdf_surface_create_for_stream(php_cairo_write_func, (void *)closure, width, height);
	}

	php_cairo_throw_exception(cairo_surface_status(surface_object->surface) TSRMLS_CC);
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoPdfSurface_setSize_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, width)
	ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()

/* {{{ proto void CairoPdfSurface->setSize(, double width, double height)
       Changes the size of a PDF surface for the current (and subsequent) pages.
       This should be called before any drawing takes place on the surface */
PHP_METHOD(CairoPdfSurface, setSize)
{
	double width = 0.0, height = 0.0;
	cairo_surface_object *surface_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "dd", &width, &height) == FAILURE) {
		return;
	}
        
        surface_object = Z_CAIRO_SURFACE_P(getThis());
	if(!surface_object) {
            return;
        }

	cairo_pdf_surface_set_size(surface_object->surface, width, height);
	php_cairo_throw_exception(cairo_surface_status(surface_object->surface));
}
/* }}} */


/* ----------------------------------------------------------------
    Cairo\Surface\Pdf Definition and registration
------------------------------------------------------------------*/

/* {{{ cairo_pdf_surface_methods[] */
const zend_function_entry cairo_pdf_surface_methods[] = {
	PHP_ME(CairoPdfSurface, __construct, CairoPdfSurface___construct_args, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(CairoPdfSurface, setSize, CairoPdfSurface_setSize_args, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};
/* }}} */

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(cairo_pdf_surface)
{
	zend_class_entry ce;

        INIT_NS_CLASS_ENTRY(ce, CAIRO_NAMESPACE, ZEND_NS_NAME("Surface", "Pdf"), cairo_pdf_surface_methods);
	ce_cairo_pdfsurface = zend_register_internal_class_ex(&ce, ce_cairo_surface);
	ce_cairo_pdfsurface->create_object = cairo_surface_create_object;

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

