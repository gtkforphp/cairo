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
#include "zend_exceptions.h"
#include "php_cairo.h"

zend_class_entry *cairo_ce_cairoexception;
zend_class_entry *cairo_ce_cairostatus;

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(cairo_error)
{
	zend_class_entry ce, status_ce;

	INIT_CLASS_ENTRY(ce, "CairoException", NULL);
	cairo_ce_cairoexception = zend_register_internal_class_ex(&ce, zend_exception_get_default(TSRMLS_C), "Exception" TSRMLS_CC);

	INIT_CLASS_ENTRY(status_ce, "CairoStatus", NULL);
	cairo_ce_cairostatus = zend_register_internal_class(&status_ce TSRMLS_CC);
	cairo_ce_cairostatus->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS | ZEND_ACC_FINAL_CLASS;

	#define REGISTER_CAIRO_STATUS_LONG_CONST(const_name, value) \
	zend_declare_class_constant_long(cairo_ce_cairostatus, const_name, sizeof(const_name)-1, (long)value TSRMLS_CC); \
	REGISTER_LONG_CONSTANT(#value,  value,  CONST_CS | CONST_PERSISTENT);

	REGISTER_CAIRO_STATUS_LONG_CONST("SUCCESS", CAIRO_STATUS_SUCCESS);
	REGISTER_CAIRO_STATUS_LONG_CONST("NO_MEMORY", CAIRO_STATUS_NO_MEMORY);
	REGISTER_CAIRO_STATUS_LONG_CONST("INVALID_RESTORE", CAIRO_STATUS_INVALID_RESTORE);
	REGISTER_CAIRO_STATUS_LONG_CONST("INVALID_POP_GROUP", CAIRO_STATUS_INVALID_POP_GROUP);
	REGISTER_CAIRO_STATUS_LONG_CONST("NO_CURRENT_POINT", CAIRO_STATUS_NO_CURRENT_POINT);
	REGISTER_CAIRO_STATUS_LONG_CONST("INVALID_MATRIX", CAIRO_STATUS_INVALID_MATRIX);
	REGISTER_CAIRO_STATUS_LONG_CONST("INVALID_STATUS", CAIRO_STATUS_INVALID_STATUS);
	REGISTER_CAIRO_STATUS_LONG_CONST("NULL_POINTER", CAIRO_STATUS_NULL_POINTER);
	REGISTER_CAIRO_STATUS_LONG_CONST("INVALID_STRING", CAIRO_STATUS_INVALID_STRING);
	REGISTER_CAIRO_STATUS_LONG_CONST("INVALID_PATH_DATA", CAIRO_STATUS_INVALID_PATH_DATA);
	REGISTER_CAIRO_STATUS_LONG_CONST("READ_ERROR", CAIRO_STATUS_READ_ERROR);
	REGISTER_CAIRO_STATUS_LONG_CONST("WRITE_ERROR", CAIRO_STATUS_WRITE_ERROR);
	REGISTER_CAIRO_STATUS_LONG_CONST("SURFACE_FINISHED", CAIRO_STATUS_SURFACE_FINISHED);
	REGISTER_CAIRO_STATUS_LONG_CONST("SURFACE_TYPE_MISMATCH", CAIRO_STATUS_SURFACE_TYPE_MISMATCH);
	REGISTER_CAIRO_STATUS_LONG_CONST("PATTERN_TYPE_MISMATCH", CAIRO_STATUS_PATTERN_TYPE_MISMATCH);
	REGISTER_CAIRO_STATUS_LONG_CONST("INVALID_CONTENT", CAIRO_STATUS_INVALID_CONTENT);
	REGISTER_CAIRO_STATUS_LONG_CONST("INVALID_FORMAT", CAIRO_STATUS_INVALID_FORMAT);
	REGISTER_CAIRO_STATUS_LONG_CONST("INVALID_VISUAL", CAIRO_STATUS_INVALID_VISUAL);
	REGISTER_CAIRO_STATUS_LONG_CONST("FILE_NOT_FOUND", CAIRO_STATUS_FILE_NOT_FOUND);
	REGISTER_CAIRO_STATUS_LONG_CONST("INVALID_DASH", CAIRO_STATUS_INVALID_DASH);
	REGISTER_CAIRO_STATUS_LONG_CONST("INVALID_DSC_COMMENT", CAIRO_STATUS_INVALID_DSC_COMMENT);

#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 4, 0)
	REGISTER_CAIRO_STATUS_LONG_CONST("INVALID_INDEX", CAIRO_STATUS_INVALID_INDEX);
	REGISTER_CAIRO_STATUS_LONG_CONST("CLIP_NOT_REPRESENTABLE", CAIRO_STATUS_CLIP_NOT_REPRESENTABLE);
#endif

#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 6, 0)
	REGISTER_CAIRO_STATUS_LONG_CONST("TEMP_FILE_ERROR", CAIRO_STATUS_TEMP_FILE_ERROR);
	REGISTER_CAIRO_STATUS_LONG_CONST("INVALID_STRIDE", CAIRO_STATUS_INVALID_STRIDE);
#endif

#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 8, 0)
	REGISTER_CAIRO_STATUS_LONG_CONST("FONT_TYPE_MISMATCH", CAIRO_STATUS_FONT_TYPE_MISMATCH);
	REGISTER_CAIRO_STATUS_LONG_CONST("USER_FONT_IMMUTABLE", CAIRO_STATUS_USER_FONT_IMMUTABLE);
	REGISTER_CAIRO_STATUS_LONG_CONST("USER_FONT_ERROR", CAIRO_STATUS_USER_FONT_ERROR);
	REGISTER_CAIRO_STATUS_LONG_CONST("NEGATIVE_COUNT", CAIRO_STATUS_NEGATIVE_COUNT);
	REGISTER_CAIRO_STATUS_LONG_CONST("INVALID_CLUSTERS", CAIRO_STATUS_INVALID_CLUSTERS);
	REGISTER_CAIRO_STATUS_LONG_CONST("INVALID_SLANT", CAIRO_STATUS_INVALID_SLANT);
	REGISTER_CAIRO_STATUS_LONG_CONST("INVALID_WEIGHT", CAIRO_STATUS_INVALID_WEIGHT);
#endif
	return SUCCESS;
}
/* }}} */

PHP_CAIRO_API void php_cairo_throw_exception(cairo_status_t status TSRMLS_DC)
{
	char * error_message;

	if (status == CAIRO_STATUS_SUCCESS) {
		return;
	}
	error_message = estrdup(cairo_status_to_string(status));
	zend_throw_exception(cairo_ce_cairoexception, error_message, status TSRMLS_CC);
	efree(error_message);
	return;
}

PHP_CAIRO_API void php_cairo_trigger_error(cairo_status_t status TSRMLS_DC)
{
	char * error_message;

	if (status == CAIRO_STATUS_SUCCESS) {
		return;
	}
	error_message = estrdup(cairo_status_to_string(status));
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "%s", error_message);
	efree(error_message);
	return;
}
/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
