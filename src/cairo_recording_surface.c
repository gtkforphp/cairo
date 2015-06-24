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
  | Author: Michael Maclean <mgdm@php.net>                               |
  +----------------------------------------------------------------------+
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_cairo.h"
#include "zend_exceptions.h"

#ifdef CAIRO_HAS_RECORDING_SURFACE

zend_class_entry *cairo_ce_cairorecordingsurface;

ZEND_BEGIN_ARG_INFO(CairoRecordingSurface___construct_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, content)
	ZEND_ARG_INFO(0, extents)
ZEND_END_ARG_INFO()

static double php_cairo_get_double_from_array(zval *val, const char *name) {
	zval **tmp;

	if (zend_hash_find(Z_ARRVAL_P(val), name, strlen(name) + 1, (void **)&tmp) == SUCCESS) {
		if (Z_TYPE_PP(tmp) != IS_DOUBLE) {
			convert_to_double(*tmp);
		} 

		return Z_DVAL_PP(tmp);
	} else {
		zend_error(E_WARNING, "Key '%s' does not exist", name);
	}
	return 0;
}

static cairo_rectangle_t *php_cairo_make_rectangle(zval *val) {
	cairo_rectangle_t *rectangle = ecalloc(1, sizeof(cairo_rectangle_t));

	rectangle->x = php_cairo_get_double_from_array(val, "x");
	rectangle->y = php_cairo_get_double_from_array(val, "y");
	rectangle->width = php_cairo_get_double_from_array(val, "width");
	rectangle->height = php_cairo_get_double_from_array(val, "height");
	return rectangle;
}

/* {{{ proto CairoRecordingSurface __construct(int content, array extents)
       Returns new CairoRecordingSurface */
PHP_METHOD(CairoRecordingSurface, __construct)
{
	long content;
	cairo_surface_object *surface_object;
	zval *extents = NULL;
	cairo_rectangle_t *rectangle = NULL;

	PHP_CAIRO_ERROR_HANDLING(TRUE)
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l|a", &content, &extents) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(TRUE)
		return;
	}

	if (extents != NULL) {
		rectangle = php_cairo_make_rectangle(extents);
	}
	PHP_CAIRO_RESTORE_ERRORS(TRUE)

	surface_object = (cairo_surface_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
	surface_object->surface = cairo_recording_surface_create(content, rectangle);

	if (rectangle != NULL) {
		efree(rectangle);
	}

	php_cairo_throw_exception(cairo_surface_status(surface_object->surface) TSRMLS_CC);
}
/* }}} */

/* {{{ proto CairoRecordingSurface cairo_recording_surface_create(int content, array extents)
       Returns new CairoRecordingSurface object */
PHP_FUNCTION(cairo_recording_surface_create)
{
	long content;
	cairo_surface_object *surface_object;
	cairo_rectangle_t *rectangle;
	zval *extents;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l|a", &content, &extents) == FAILURE) {
		return;
	}

	if (extents != NULL) {
		rectangle = php_cairo_make_rectangle(extents);
	}

	object_init_ex(return_value, cairo_ce_cairorecordingsurface);
	surface_object = (cairo_surface_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	surface_object->surface = cairo_recording_surface_create(content, rectangle);
	efree(rectangle);
	php_cairo_trigger_error(cairo_surface_status(surface_object->surface) TSRMLS_CC);
}
/* }}} */

PHP_FUNCTION(cairo_recording_surface_ink_extents)
{
	zval *surface_zval;
	cairo_surface_object *surface_object;
	double x, y, width, height;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &surface_zval, cairo_ce_cairorecordingsurface) == FAILURE) {
		return;
	}
	
	surface_object = (cairo_surface_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
	cairo_recording_surface_ink_extents(surface_object->surface, &x, &y, &width, &height);
	array_init(return_value);
	add_assoc_double(return_value, "x", x);
	add_assoc_double(return_value, "y", y);
	add_assoc_double(return_value, "width", width);
	add_assoc_double(return_value, "height", height);
}

const zend_function_entry cairo_recording_surface_methods[] = {
    PHP_ME(CairoRecordingSurface, __construct, CairoRecordingSurface___construct_args, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME_MAPPING(inkExtents, cairo_recording_surface_ink_extents, NULL, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};


/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(cairo_recording_surface)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "CairoRecordingSurface", cairo_recording_surface_methods);
	cairo_ce_cairorecordingsurface = zend_register_internal_class_ex(&ce, cairo_ce_cairosurface, "CairoSurface" TSRMLS_CC);
	cairo_ce_cairorecordingsurface->create_object = cairo_surface_object_new;

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
