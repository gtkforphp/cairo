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

/* {{{ Class CairoException */


/* {{{ Methods */

static zend_function_entry CairoException_methods[] = {
	{ NULL, NULL, NULL }
};

/* }}} Methods */

void class_init_CairoException(TSRMLS_D)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "CairoException", CairoException_methods);
	CairoException_ce_ptr = zend_register_internal_class_ex(&ce, zend_exception_get_default(TSRMLS_C), "Exception" TSRMLS_CC);
}

/* }}} Class CairoException */

void cairo_throw_exception(cairo_status_t status TSRMLS_DC)
{
	char * error_message;

	if (status == CAIRO_STATUS_SUCCESS) {
		return;
	}
	error_message = estrdup(cairo_status_to_string(status));
	zend_throw_exception(CairoException_ce_ptr, error_message, status TSRMLS_CC);
	return;
}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw = 4 ts = 4 fdm = marker
 * vim<600: noet sw = 4 ts = 4
 */