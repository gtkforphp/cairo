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

#include <ext/eos_datastructures/php_eos_datastructures_api.h>

#include "php_cairo.h"

zend_class_entry *ce_cairo_region;
zend_class_entry *ce_cairo_rectangle;
zend_class_entry *ce_cairo_region_overlap;

static zend_object_handlers cairo_region_object_handlers;

typedef struct _cairo_region_object {
	cairo_region_t *region;
	zend_object std;
} cairo_region_object;

static inline cairo_region_object *cairo_region_fetch_object(zend_object *object)
{
	return (cairo_region_object *) ((char*)(object) - XtOffsetOf(cairo_region_object, std));
}

#define Z_CAIRO_REGION_P(zv) cairo_region_fetch_object(Z_OBJ_P(zv))

/* ----------------------------------------------------------------
    Cairo\Region Class API
------------------------------------------------------------------ */

ZEND_BEGIN_ARG_INFO_EX(CairoRegion___construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
	ZEND_ARG_INFO(0, rectangles)
ZEND_END_ARG_INFO()

/* {{{ proto void __contruct([void | Cairo\Rectangle $rect | array Cairo\Rectangle $rects)
	Creates a new region - optionally with a single or union of multiple rectangles inside */
PHP_METHOD(CairoRegion, __construct)
{
	cairo_region_object *region_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}

	region_object = Z_CAIRO_REGION_P(getThis());
	if(!region_object) {
		return;
	}

	php_cairo_throw_exception(cairo_region_status(region_object->region));
}
/* }}} */

/* ----------------------------------------------------------------
    Cairo\Region Definition and registration
------------------------------------------------------------------*/

/* {{{ cairo_region_methods[] */
const zend_function_entry cairo_region_methods[] = {
	PHP_ME(CairoRegion, __construct, CairoRegion___construct_args, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	ZEND_FE_END
};
/* }}} */

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(cairo_region)
{
	zend_class_entry 	region_ce, overlap_ce;

	memcpy(&cairo_region_object_handlers,
		   zend_get_std_object_handlers(),
		   sizeof(zend_object_handlers));

	cairo_region_object_handlers.offset = XtOffsetOf(cairo_region_object, std);
	//cairo_region_object_handlers.free_obj = cairo_region_free_obj;

	INIT_NS_CLASS_ENTRY(region_ce, CAIRO_NAMESPACE, "Region", cairo_region_methods);
	ce_cairo_region = zend_register_internal_class(&region_ce);
	//ce_cairo_region->create_object = cairo_region_create_object;

	INIT_NS_CLASS_ENTRY(overlap_ce,  CAIRO_NAMESPACE, ZEND_NS_NAME("Region", "Overlap"), NULL);
	ce_cairo_region_overlap = zend_register_internal_class_ex(&overlap_ce, php_eos_datastructures_get_enum_ce());
	ce_cairo_region_overlap->ce_flags |= ZEND_ACC_FINAL;

	#define CAIRO_OVERLAP_DECLARE_ENUM(name) \
		zend_declare_class_constant_long(ce_cairo_region_overlap, #name, \
		sizeof(#name)-1, CAIRO_REGION_OVERLAP_## name);

	CAIRO_OVERLAP_DECLARE_ENUM(IN);
	CAIRO_OVERLAP_DECLARE_ENUM(OUT);
	CAIRO_OVERLAP_DECLARE_ENUM(PART);

	return SUCCESS;
}