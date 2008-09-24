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

#if CAIRO_HAS_XLIB_SURFACE
#include <cairo-xlib.h>
/* {{{ Class CairoXlibSurface */

static zend_class_entry * CairoXlibSurface_ce_ptr = NULL;
static zend_object_handlers CairoXlibSurface_handlers;
/* {{{ Methods */


/* {{{ proto void construct()
   */
PHP_METHOD(CairoXlibSurface, __construct)
{
	zval * _this_zval;
	cairo_surface_object *curr;


	if (ZEND_NUM_ARGS()>0)	{
		WRONG_PARAM_COUNT;
	}

	_this_zval = getThis();
	curr = (cairo_surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);

	php_error(E_WARNING, "Cannot Be Initialized"); RETURN_FALSE;

}
/* }}} __construct */



/* {{{ proto int getDepth()
   */
PHP_METHOD(CairoXlibSurface, getDepth)
{

	zval * _this_zval = NULL;
	cairo_surface_object *curr;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoXlibSurface_ce_ptr) == FAILURE) {
		return;
	}

	curr = (cairo_surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);

	RETURN_LONG(cairo_xlib_surface_get_depth(curr->surface));

}
/* }}} getDepth */



/* {{{ proto int getHeight()
   */
PHP_METHOD(CairoXlibSurface, getHeight)
{

	zval * _this_zval = NULL;
	cairo_surface_object *curr;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoXlibSurface_ce_ptr) == FAILURE) {
		return;
	}

	curr = (cairo_surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	RETURN_LONG(cairo_xlib_surface_get_height(curr->surface));
	
}
/* }}} getHeight */



/* {{{ proto int getWidth()
   */
PHP_METHOD(CairoXlibSurface, getWidth)
{

	zval * _this_zval = NULL;
	cairo_surface_object *curr;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoXlibSurface_ce_ptr) == FAILURE) {
		return;
	}

	curr = (cairo_surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	RETURN_LONG(cairo_xlib_surface_get_width(curr->surface));
		
}
/* }}} getWidth */


static zend_function_entry CairoXlibSurface_methods[] = {
	PHP_ME(CairoXlibSurface, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(CairoXlibSurface, getDepth, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CairoXlibSurface, getHeight, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CairoXlibSurface, getWidth, NULL, ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

/* }}} Methods */

static zend_object_value CairoXlibSurface_object_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	retval = CairoSurface_object_new(ce TSRMLS_CC);
	retval.handlers = &CairoXlibSurface_handlers;
	return retval;
}

void class_init_CairoXlibSurface(TSRMLS_D)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "CairoXlibSurface", CairoXlibSurface_methods);
	CairoXlibSurface_ce_ptr = zend_register_internal_class_ex(&ce, CairoSurface_ce_ptr, "CairoSurface" TSRMLS_CC);
	CairoXlibSurface_ce_ptr->create_object = CairoXlibSurface_object_new;
	memcpy(&CairoXlibSurface_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

}

/* }}} Class CairoXlibSurface */

/* Helper Function - used in CairoSurface, NOT EXPORTED */
zend_class_entry *  get_CairoXlibSurface_ce_ptr()
{
	return CairoXlibSurface_ce_ptr;
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