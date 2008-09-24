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

#if CAIRO_HAS_WIN32_SURFACE
#include <cairo-win32.h>
/* {{{ Class CairoWin32Surface*/

static zend_class_entry * CairoWin32Surface_ce_ptr = NULL;
static zend_object_handlers CairoWin32Surface_handlers;

/* {{{ Methods */


/* {{{ proto void construct(int hdc)
   */
PHP_METHOD(CairoWin32Surface, __construct)
{
	zval * _this_zval;

	long hdc = 0;
	cairo_surface_object *curr;


	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &hdc) == FAILURE) {
		return;
	}

	_this_zval = getThis();
	curr = (cairo_surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	/*curr->surface = cairo_win32_surface_create(hdc, NULL); -TODO */ 
}
/* }}} __construct */


static zend_function_entry CairoWin32Surface_methods[] = {
	PHP_ME(CairoWin32Surface, __construct, NULL, /**/ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	{ NULL, NULL, NULL }
};

/* }}} Methods */

static zend_object_value CairoWin32Surface_object_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	retval = CairoSurface_object_new(ce TSRMLS_CC);
	retval.handlers = &CairoWin32Surface_handlers;
	return retval;
}

void class_init_CairoWin32Surface(TSRMLS_D)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "CairoWin32Surface", CairoWin32Surface_methods);
	CairoWin32Surface_ce_ptr = zend_register_internal_class_ex(&ce, CairoSurface_ce_ptr, "CairoSurface" TSRMLS_CC);
	CairoWin32Surface_ce_ptr->create_object = CairoWin32Surface_object_new;
	memcpy(&CairoWin32Surface_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

}

/* }}} Class CairoWin32Surface */

/* Helper Function - used in CairoSurface, NOT EXPORTED */
zend_class_entry *  get_CairoWin32Surface_ce_ptr()
{
	return CairoWin32Surface_ce_ptr;
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