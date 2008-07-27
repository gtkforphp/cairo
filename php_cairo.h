/*
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,	  |
   | that is bundled with this package in the file LICENSE, and is		  |
   | available through the world-wide-web at the following url:			  |
   | http://www.php.net/license/3_01.txt.								  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to		  |
   | license@php.net so we can mail you a copy immediately.				  |
   +----------------------------------------------------------------------+
   | Authors: Akshat Gupta <g.akshat@gmail.com>							  |
   +----------------------------------------------------------------------+
*/

/* $ Id: $ */ 

#define PHP_CAIRO_VERSION "1.01"

#ifndef PHP_CAIRO_H
#define PHP_CAIRO_H

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>

#ifdef HAVE_CAIRO

#include <php_ini.h>
#include <SAPI.h>
#include <ext/standard/info.h>
#include <Zend/zend_extensions.h>
#ifdef	__cplusplus
} /* extern "C" */

#endif
#ifdef	__cplusplus
extern "C" {
#endif

extern zend_module_entry cairo_module_entry;
#define phpext_cairo_ptr &cairo_module_entry

#ifdef PHP_WIN32
#define PHP_CAIRO_API __declspec(dllexport)
#else
#define PHP_CAIRO_API
#endif

PHP_MINIT_FUNCTION(cairo);
PHP_MINFO_FUNCTION(cairo);

#ifdef ZTS
#include "TSRM.h"
#endif

#define FREE_RESOURCE(resource) zend_list_delete(Z_LVAL_P(resource))

#define PROP_GET_LONG(name)    Z_LVAL_P(zend_read_property(_this_ce, _this_zval, #name, strlen(#name), 1 TSRMLS_CC))
#define PROP_SET_LONG(name, l) zend_update_property_long(_this_ce, _this_zval, #name, strlen(#name), l TSRMLS_CC)

#define PROP_GET_DOUBLE(name)	 Z_DVAL_P(zend_read_property(_this_ce, _this_zval, #name, strlen(#name), 1 TSRMLS_CC))
#define PROP_SET_DOUBLE(name, d) zend_update_property_double(_this_ce, _this_zval, #name, strlen(#name), d TSRMLS_CC)

#define PROP_GET_STRING(name)	 Z_STRVAL_P(zend_read_property(_this_ce, _this_zval, #name, strlen(#name), 1 TSRMLS_CC))
#define PROP_GET_STRLEN(name)	 Z_STRLEN_P(zend_read_property(_this_ce, _this_zval, #name, strlen(#name), 1 TSRMLS_CC))
#define PROP_SET_STRING(name, s) zend_update_property_string(_this_ce, _this_zval, #name, strlen(#name), s TSRMLS_CC)
#define PROP_SET_STRINGL(name, s, l) zend_update_property_stringl(_this_ce, _this_zval, #name, strlen(#name), s, l TSRMLS_CC)


PHP_FUNCTION(cairo_version);
ZEND_BEGIN_ARG_INFO_EX(cairo_version_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_FUNCTION(cairo_version_string);
ZEND_BEGIN_ARG_INFO_EX(cairo_version_string_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_FUNCTION(cairo_available_surfaces);
ZEND_BEGIN_ARG_INFO_EX(cairo_available_surfaces_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()








#ifdef	__cplusplus
} /* extern "C" */
#endif

#endif /* PHP_HAVE_CAIRO */

#endif /* PHP_CAIRO_H */

/* {{{ Proto's */


/* }}} */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw = 4 ts = 4 fdm = marker
 * vim<600: noet sw = 4 ts = 4
 */
