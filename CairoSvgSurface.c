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

#if CAIRO_HAS_SVG_SURFACE
#include <cairo-svg.h>
/* {{{ Class CairoSVGSurface */

static zend_class_entry * CairoSVGSurface_ce_ptr = NULL;
static zend_object_handlers CairoSVGSurface_handlers;


/* {{{ Methods */
ZEND_BEGIN_ARG_INFO_EX(CairoSVGSurface____construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, wpts)
  ZEND_ARG_INFO(0, hpts)
ZEND_END_ARG_INFO()

/* {{{ proto void construct(string file, float wpts, float hpts)
   */
PHP_METHOD(CairoSVGSurface, __construct)
{
	zval * _this_zval;
	zval *zstream = NULL;
	const char * file = NULL;
	int file_len = 0;
	double wpts = 0.0;
	double hpts = 0.0;
	php_stream *stream;
	cairo_surface_object *curr;
	zval ***args, *obj;
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
			printf("error!!!");
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
		curr->surface = cairo_svg_surface_create(file, wpts, hpts);
	}
	else if(Z_TYPE_P(obj) == IS_RESOURCE)  {
		zstream = obj;
		php_stream_from_zval(stream, &zstream);	
		curr->surface = cairo_svg_surface_create_for_stream(_write_func, stream, wpts, hpts);
	}
	else {
		printf("ERROR\n");
	}

	efree(args);


}
/* }}} __construct */


static zend_function_entry CairoSVGSurface_methods[] = {
	PHP_ME(CairoSVGSurface, __construct, CairoSVGSurface____construct_args, /**/ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	{ NULL, NULL, NULL }
};

/* }}} Methods */

static zend_object_value CairoSVGSurface_object_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	retval = CairoSurface_object_new(ce TSRMLS_CC);
	retval.handlers = &CairoSVGSurface_handlers;
	return retval;
}

void class_init_CairoSVGSurface(TSRMLS_D)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "CairoSVGSurface", CairoSVGSurface_methods);
	CairoSVGSurface_ce_ptr = zend_register_internal_class_ex(&ce, CairoSurface_ce_ptr, "CairoSurface" TSRMLS_CC);
	CairoSVGSurface_ce_ptr->create_object = CairoSVGSurface_object_new;
	memcpy(&CairoSVGSurface_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

}

/* }}} Class CairoSVGSurface */

/* Helper Function - used in CairoSurface, NOT EXPORTED */
zend_class_entry *  get_CairoSvgSurface_ce_ptr()
{
	return CairoSVGSurface_ce_ptr;
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