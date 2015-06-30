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

zend_class_entry *ce_cairo_exception;
zend_class_entry *ce_cairo_status;

/* ----------------------------------------------------------------
    Cairo C API
------------------------------------------------------------------*/

void php_cairo_throw_exception(cairo_status_t status)
{
	char * error_message;

	if (status == CAIRO_STATUS_SUCCESS) {
		return;
	}

	error_message = estrdup(cairo_status_to_string(status));
	zend_throw_exception(ce_cairo_exception, error_message, status);
	efree(error_message);
	return;
}

/* ----------------------------------------------------------------
    Cairo\Status Class API
------------------------------------------------------------------*/

ZEND_BEGIN_ARG_INFO(CairoStatus_getStatusMessage_args, ZEND_SEND_BY_VAL)
ZEND_END_ARG_INFO()

/* {{{ proto string CairoStatus->getStatusMessage
       Translates the current enums value to it's cairo status message value */
PHP_METHOD(CairoStatus, getStatusMessage)
{
	long status = 0;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}

	status = php_eosdatastructures_get_enum_value(getThis());

	RETURN_STRING(cairo_status_to_string(status));
}
/* }}} */

/* ----------------------------------------------------------------
    Cairo\Status and Cairo\Exception Definition and registration
------------------------------------------------------------------*/

/* {{{ cairo_status_methods[] */
const zend_function_entry cairo_status_methods[] = {
	PHP_ME(CairoStatus, getStatusMessage, CairoStatus_getStatusMessage_args, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};
/* }}} */

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(cairo_exception)
{
	zend_class_entry ce, status_ce;

	INIT_NS_CLASS_ENTRY(ce,  CAIRO_NAMESPACE, "Exception", NULL);
	ce_cairo_exception = zend_register_internal_class_ex(&ce, zend_exception_get_default());

	INIT_NS_CLASS_ENTRY(status_ce,  CAIRO_NAMESPACE, "Status", cairo_status_methods);
	ce_cairo_status = zend_register_internal_class_ex(&status_ce, php_eos_datastructures_get_enum_ce());
	ce_cairo_status->ce_flags |= ZEND_ACC_FINAL;

	#define CAIRO_STATUS_DECLARE_ENUM(name) \
		zend_declare_class_constant_long(ce_cairo_status, #name, \
		sizeof(#name)-1, CAIRO_STATUS_## name);

	CAIRO_STATUS_DECLARE_ENUM(SUCCESS);
	CAIRO_STATUS_DECLARE_ENUM(NO_MEMORY);
	CAIRO_STATUS_DECLARE_ENUM(INVALID_RESTORE);
	CAIRO_STATUS_DECLARE_ENUM(INVALID_POP_GROUP);
	CAIRO_STATUS_DECLARE_ENUM(NO_CURRENT_POINT);
	CAIRO_STATUS_DECLARE_ENUM(INVALID_MATRIX);
	CAIRO_STATUS_DECLARE_ENUM(INVALID_STATUS);
	CAIRO_STATUS_DECLARE_ENUM(NULL_POINTER);
	CAIRO_STATUS_DECLARE_ENUM(INVALID_STRING);
	CAIRO_STATUS_DECLARE_ENUM(INVALID_PATH_DATA);
	CAIRO_STATUS_DECLARE_ENUM(READ_ERROR);
	CAIRO_STATUS_DECLARE_ENUM(WRITE_ERROR);
	CAIRO_STATUS_DECLARE_ENUM(SURFACE_FINISHED);
	CAIRO_STATUS_DECLARE_ENUM(SURFACE_TYPE_MISMATCH);
	CAIRO_STATUS_DECLARE_ENUM(PATTERN_TYPE_MISMATCH);
	CAIRO_STATUS_DECLARE_ENUM(INVALID_CONTENT);
	CAIRO_STATUS_DECLARE_ENUM(INVALID_FORMAT);
	CAIRO_STATUS_DECLARE_ENUM(INVALID_VISUAL);
	CAIRO_STATUS_DECLARE_ENUM(FILE_NOT_FOUND);
	CAIRO_STATUS_DECLARE_ENUM(INVALID_DASH);
	CAIRO_STATUS_DECLARE_ENUM(INVALID_DSC_COMMENT);
	CAIRO_STATUS_DECLARE_ENUM(INVALID_INDEX);
	CAIRO_STATUS_DECLARE_ENUM(CLIP_NOT_REPRESENTABLE);
	CAIRO_STATUS_DECLARE_ENUM(TEMP_FILE_ERROR);
	CAIRO_STATUS_DECLARE_ENUM(INVALID_STRIDE);
	CAIRO_STATUS_DECLARE_ENUM(FONT_TYPE_MISMATCH);
	CAIRO_STATUS_DECLARE_ENUM(USER_FONT_IMMUTABLE);
	CAIRO_STATUS_DECLARE_ENUM(USER_FONT_ERROR);
	CAIRO_STATUS_DECLARE_ENUM(NEGATIVE_COUNT);
	CAIRO_STATUS_DECLARE_ENUM(INVALID_CLUSTERS);
	CAIRO_STATUS_DECLARE_ENUM(INVALID_SLANT);
	CAIRO_STATUS_DECLARE_ENUM(INVALID_WEIGHT);
	CAIRO_STATUS_DECLARE_ENUM(INVALID_SIZE);
	CAIRO_STATUS_DECLARE_ENUM(USER_FONT_NOT_IMPLEMENTED);
	CAIRO_STATUS_DECLARE_ENUM(DEVICE_TYPE_MISMATCH);
	CAIRO_STATUS_DECLARE_ENUM(DEVICE_ERROR);
	CAIRO_STATUS_DECLARE_ENUM(INVALID_MESH_CONSTRUCTION);
	CAIRO_STATUS_DECLARE_ENUM(DEVICE_FINISHED);

#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 14, 0)
	CAIRO_STATUS_DECLARE_ENUM(JBIG2_GLOBAL_MISSING);
#endif

	CAIRO_STATUS_DECLARE_ENUM(LAST_STATUS);

	return SUCCESS;
}
/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
