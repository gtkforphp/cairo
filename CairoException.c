#include "php_cairo_api.h"
#include "CairoExceptionMacro.h"
#include "php_cairo_ce_ptr.h"

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
	CairoException_ce_ptr = zend_register_internal_class_ex(&ce, zend_exception_get_default(), "Exception" TSRMLS_CC);
}

/* }}} Class CairoException */

void phpCairoCheckStatus(cairo_status_t status)
{
	zend_throw_exception(CairoException_ce_ptr, cairo_status_to_string(status));
	return;

	/*
	switch(status) {
	case CAIRO_STATUS_SUCCESS:
	return 0;
	case CAIRO_STATUS_NO_MEMORY:
	zend_throw_exception(CairoException_ce_ptr,"No memory", NULL);
	break;
	case CAIRO_STATUS_READ_ERROR:
	case CAIRO_STATUS_WRITE_ERROR:
	zend_throw_exception(CairoException_ce_ptr, cairo_status_to_string(status), NULL);
	break;
	case CAIRO_STATUS_INVALID_RESTORE:
	zend_throw_expetion(CairoException_ce_ptr, "Invalid restore", NULL);
	break;
	case CAIRO_STATUS_INVALID_POP_GROUP:
	zend_throw_exception(CairoException_ce_ptr, "Pop group error", NULL);
	break;
	} */
}


