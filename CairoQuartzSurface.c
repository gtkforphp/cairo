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

#if CAIRO_HAS_QUARTZ_SURFACE
#include <cairo-quartz.h>
/* {{{ Class CairoQuartzSurface */

static zend_class_entry * CairoQuartzSurface_ce_ptr = NULL;
static zend_object_handlers CairoQuartzSurface_handlers;

PHP_METHOD(CairoQuartzSurface, __construct);
ZEND_BEGIN_ARG_INFO_EX(CairoQuartzSurface____construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, hpixels)
  ZEND_ARG_INFO(0, format)
ZEND_END_ARG_INFO()

/* {{{ Methods */


/* {{{ proto void construct(float wpixels, float hpixels [, int format])
   */
PHP_METHOD(CairoQuartzSurface, __construct)
{
	zend_throw_exception(CairoException_ce_ptr, "CairoQuartzSurface cannot be constructed", 0 TSRMLS_CC);
}
/* }}} __construct */


static zend_function_entry CairoQuartzSurface_methods[] = {
	PHP_ME(CairoQuartzSurface, __construct, CairoQuartzSurface____construct_args, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	{ NULL, NULL, NULL }
};

/* }}} Methods */

static zend_object_value CairoQuartzSurface_object_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	retval = CairoSurface_object_new(ce TSRMLS_CC);
	retval.handlers = &CairoQuartzSurface_handlers;
	return retval;
}

void class_init_CairoQuartzSurface(TSRMLS_D)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "CairoQuartzSurface", CairoQuartzSurface_methods);
	CairoQuartzSurface_ce_ptr = zend_register_internal_class_ex(&ce, get_CairoSurface_ce_ptr(NULL), "CairoSurface" TSRMLS_CC);
	CairoQuartzSurface_ce_ptr->create_object = CairoQuartzSurface_object_new;
	memcpy(&CairoQuartzSurface_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

}

/* }}} Class CairoQuartzSurface */

/* Helper Function - used in CairoSurface, NOT EXPORTED */
zend_class_entry *  get_CairoQuartzSurface_ce_ptr()
{
	return CairoQuartzSurface_ce_ptr;
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