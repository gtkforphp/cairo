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
  |         Akshat Gupta <g.akshat@gmail.com>                            |
  +----------------------------------------------------------------------+
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_cairo.h"
#include "zend_exceptions.h"

#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 10, 0)

zend_class_entry *cairo_ce_cairosubsurface;

/* {{{ proto CairoSubSurface __construct(int content, array extents)
       Returns new CairoSubSurface */
PHP_METHOD(CairoSubSurface, __construct)
{
	zend_throw_exception(cairo_ce_cairoexception, "CairoSubSurface cannot be constructed", 0 TSRMLS_CC);
}
/* }}} */

const zend_function_entry cairo_sub_surface_methods[] = {
    PHP_ME(CairoSubSurface, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    {NULL, NULL, NULL}
};

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(cairo_sub_surface)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "CairoSubSurface", cairo_sub_surface_methods);
	cairo_ce_cairosubsurface = zend_register_internal_class_ex(&ce, cairo_ce_cairosurface, "CairoSurface" TSRMLS_CC);
	cairo_ce_cairosubsurface->create_object = cairo_surface_object_new;

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
