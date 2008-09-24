/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2008 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Akshat Gupta <g.akshat@gmail.com>                            |
  |         Elizabeth Smith <auroraeosrose@php.net>                      |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#include "php_cairo_api.h"
#include "php_cairo_internal.h"
#include <zend_exceptions.h>

#if CAIRO_HAS_PDF_SURFACE
#include <cairo-pdf.h>
/* {{{ Class CairoPDFSurface */

static zend_class_entry * CairoPDFSurface_ce_ptr = NULL;
static zend_object_handlers CairoPDFSurface_handlers;

PHP_METHOD(CairoPDFSurface, __construct);
ZEND_BEGIN_ARG_INFO_EX(CairoPDFSurface____construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, wpts)
  ZEND_ARG_INFO(0, hpts)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoPDFSurface, setSize);
ZEND_BEGIN_ARG_INFO_EX(CairoPDFSurface__set_size_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, wpts)
  ZEND_ARG_INFO(0, hpts)
ZEND_END_ARG_INFO()

/* {{{ Methods */


/* {{{ proto void construct(string file, float wpts, float hpts)
Wow - this one needs to be FIXED
   */
PHP_METHOD(CairoPDFSurface, __construct)
{
	zval * _this_zval;
	zval *zstream = NULL;
	const char * file = NULL;
	double wpts = 0.0;
	double hpts = 0.0;
	php_stream *stream;
	zval ***args, *obj;
	cairo_surface_object *curr;
	int argc = ZEND_NUM_ARGS();
	args = (zval ***)safe_emalloc(argc, sizeof(zval *),0);
	if(ZEND_NUM_ARGS() == 0 ||
		zend_get_parameters_array_ex(argc, args) == FAILURE) {
		printf("ERROR");
		efree(args);
		WRONG_PARAM_COUNT;
	}

	obj = *(args[1]);
	switch(Z_TYPE_P(obj)) {
		case IS_DOUBLE:
			wpts = Z_DVAL_P(obj);
			break;
		case IS_LONG:
			wpts = Z_LVAL_P(obj);
			break;
		default :
			printf("Error!!!");
			return;
	}
	
	obj = *(args[2]);

	switch(Z_TYPE_P(obj)) {
		case IS_DOUBLE:
			hpts = Z_DVAL_P(obj);
			break;
		case IS_LONG:
			hpts = Z_LVAL_P(obj);
			break;
		default :
			printf("Error!!!");
			return;
	}


	_this_zval = getThis();

	curr = (cairo_surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	
	obj = *(args[0]);
	if(Z_TYPE_P(obj) == IS_STRING) {
		file = Z_STRVAL_P(obj);
		curr->surface = cairo_pdf_surface_create(file, wpts, hpts);
	}
	else if(Z_TYPE_P(obj) == IS_RESOURCE)  {
		zstream = obj;
		php_stream_from_zval(stream, &zstream);	
		curr->surface = cairo_pdf_surface_create_for_stream(_write_func, stream, wpts, hpts);
	}
	else {
		zend_throw_exception(CairoException_ce_ptr, "Error creating CairoPdfSurface", 0 TSRMLS_CC);
	}

	efree(args);
}
/* }}} __construct */



/* {{{ proto void setSize(float wptd, float hpts)
   */
PHP_METHOD(CairoPDFSurface, setSize)
{

	zval * _this_zval = NULL;
	double wpts = 0.0;
	double hpts = 0.0;
	cairo_surface_object *curr;


	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odd", &_this_zval, CairoPDFSurface_ce_ptr, &wpts, &hpts) == FAILURE) {
		return;
	}

	curr = (cairo_surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_pdf_surface_set_size(curr->surface, wpts, hpts);

}
/* }}} setSize */


static zend_function_entry CairoPDFSurface_methods[] = {
	PHP_ME(CairoPDFSurface, __construct, CairoPDFSurface____construct_args, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(CairoPDFSurface, setSize, CairoPDFSurface__set_size_args, ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

/* }}} Methods */

static zend_object_value CairoPDFSurface_object_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	retval = CairoSurface_object_new(ce TSRMLS_CC);
	retval.handlers = &CairoPDFSurface_handlers;
	return retval;
}

void class_init_CairoPDFSurface(TSRMLS_D)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "CairoPDFSurface", CairoPDFSurface_methods);
	CairoPDFSurface_ce_ptr = zend_register_internal_class_ex(&ce, CairoSurface_ce_ptr, "CairoSurface" TSRMLS_CC);
	CairoPDFSurface_ce_ptr->create_object = CairoPDFSurface_object_new;
	memcpy(&CairoPDFSurface_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

}

/* }}} Class CairoPDFSurface */

/* Helper Function - used in CairoSurface, NOT EXPORTED */
zend_class_entry *  get_CairoPdfSurface_ce_ptr()
{
	return CairoPDFSurface_ce_ptr;
}

#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw = 4 ts = 4 fdm = marker
 * vim<600: noet sw = 4 ts = 4
 */