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

#include "php_cairo.h"
#include "php_cairo_internal.h"

#ifdef CAIRO_HAS_RECORDING_SURFACE

zend_class_entry *ce_cairo_recordingsurface;

static double php_cairo_get_double_from_array(zval *val, const char *name) 
{
	zval *tmp;
        
        //zend_string *key = zend_string_init(name, sizeof(name)-1, 0);
	//if ((tmp = zend_hash_(Z_ARR_P(val), key)) != NULL) {
        if ((tmp = zend_hash_str_find(Z_ARR_P(val), name, sizeof(name)-1)) != NULL) {
		if (Z_TYPE_P(tmp) != IS_DOUBLE) {
			convert_to_double(tmp);
		}

		return Z_DVAL_P(tmp);
	} else {
		zend_error(E_WARNING, "Key '%s' does not exist", name);
	}
	return 0;
}

static cairo_rectangle_t *php_cairo_make_rectangle(zval *val) 
{
	cairo_rectangle_t *rectangle = ecalloc(1, sizeof(cairo_rectangle_t));

	rectangle->x = php_cairo_get_double_from_array(val, "x");
	rectangle->y = php_cairo_get_double_from_array(val, "y");
	rectangle->width = php_cairo_get_double_from_array(val, "width");
	rectangle->height = php_cairo_get_double_from_array(val, "height");
	return rectangle;
}

/* ----------------------------------------------------------------
    Cairo\Surface\Recording Class API
------------------------------------------------------------------*/

ZEND_BEGIN_ARG_INFO(CairoRecordingSurface___construct_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, content)
	ZEND_ARG_INFO(0, extents)
ZEND_END_ARG_INFO()

/* {{{ proto CairoRecordingSurface __construct(int content, array extents)
       Returns new CairoRecordingSurface */
PHP_METHOD(CairoRecordingSurface, __construct)
{
	zend_long content;
	cairo_surface_object *surface_object;
        cairo_rectangle_t *rectangle = NULL;
	zval *extents = NULL;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "l|a", &content, &extents) == FAILURE) {
		return;
	}

	if (extents != NULL) {
		rectangle = php_cairo_make_rectangle(extents);
	}
        
        surface_object = Z_CAIRO_SURFACE_P(getThis());
	if(!surface_object) {
            return;
        }
        
	surface_object->surface = cairo_recording_surface_create(content, rectangle);

	if (rectangle != NULL) {
		efree(rectangle);
	}

	php_cairo_throw_exception(cairo_surface_status(surface_object->surface));
}
/* }}} */

/* {{{ proto CairoRecordingSurface create(int content, array extents)
       Returns new CairoRecordingSurface object */
PHP_METHOD(CairoRecordingSurface, inkExtents)
{
	cairo_surface_object *surface_object;
	double x, y, width, height;
        
        if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }

        surface_object = Z_CAIRO_SURFACE_P(getThis());
	if(!surface_object) {
            return;
        }
        
	cairo_recording_surface_ink_extents(surface_object->surface, &x, &y, &width, &height);
	array_init(return_value);
	add_assoc_double(return_value, "x", x);
	add_assoc_double(return_value, "y", y);
	add_assoc_double(return_value, "width", width);
	add_assoc_double(return_value, "height", height);
}
/* }}} */

/* ----------------------------------------------------------------
    Cairo\Surface\Recording Definition and registration
------------------------------------------------------------------*/

const zend_function_entry cairo_recording_surface_methods[] = {
    PHP_ME(CairoRecordingSurface, __construct, CairoRecordingSurface___construct_args, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(CairoRecordingSurface, inkExtents, NULL, ZEND_ACC_PUBLIC)
    ZEND_FE_END
};


/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(cairo_recording_surface)
{
	zend_class_entry ce;
        
        INIT_NS_CLASS_ENTRY(ce, CAIRO_NAMESPACE, ZEND_NS_NAME("Surface", "Recording"), cairo_recording_surface_methods);
	ce_cairo_recordingsurface = zend_register_internal_class_ex(&ce, ce_cairo_surface);
	ce_cairo_recordingsurface->create_object = cairo_surface_create_object;

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
