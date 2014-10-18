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

zend_class_entry *cairo_ce_cairofontoptions;
zend_class_entry *cairo_ce_subpixelorder;
zend_class_entry *cairo_ce_hintstyle;
zend_class_entry *cairo_ce_hintmetrics;

ZEND_BEGIN_ARG_INFO(CairoFontOptions_fontoptions_args, ZEND_SEND_BY_VAL)
	/* ZEND_ARG_OBJ_INFO(0, other, CairoFontOptions, 0) - dang E_RECOVERABLE_ERROR */
	ZEND_ARG_INFO(0, other)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoFontOptions_setAntialias_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, antialias)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoFontOptions_setSubpixelOrder_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, subpixel_order)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoFontOptions_setHintStyle_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, hint_style)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoFontOptions_setHintMetrics_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, hint_metrics)
ZEND_END_ARG_INFO()
/* {{{ cairo_font_options_object_destroy
 */
static void cairo_font_options_object_destroy(void *object TSRMLS_DC)
{
	cairo_font_options_object *font_options = (cairo_font_options_object *)object;
	zend_hash_destroy(font_options->std.properties);
	FREE_HASHTABLE(font_options->std.properties);
	if(font_options->font_options) {
		cairo_font_options_destroy(font_options->font_options);
	}

	efree(object);
}
/* }}} */

/* {{{ cairo_font_options_object_new 
 */
static zend_object_value cairo_font_options_object_new(zend_class_entry *ce TSRMLS_DC) 
{
	zend_object_value retval;
	cairo_font_options_object *font_options;
#if PHP_VERSION_ID < 50399
	zval *temp;
#endif

	font_options = ecalloc(1, sizeof(cairo_font_options_object));
	font_options->font_options = NULL;
	font_options->std.ce = ce;

	ALLOC_HASHTABLE(font_options->std.properties);
	zend_hash_init(font_options->std.properties, 0, NULL, ZVAL_PTR_DTOR, 0);
#if PHP_VERSION_ID < 50399
	zend_hash_copy(font_options->std.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref,(void *) &temp, sizeof(zval *));
#else
	object_properties_init(&font_options->std, ce);
#endif
	retval.handle = zend_objects_store_put(font_options, NULL, (zend_objects_free_object_storage_t)cairo_font_options_object_destroy, NULL TSRMLS_CC);
	retval.handlers = zend_get_std_object_handlers();
	return retval;
}
/* }}} */

/* {{{ proto void __contruct(void) 
       Creates a new CairoFontOptions object with all options initialized to default values.
   */
PHP_METHOD(CairoFontOptions, __construct)
{
	cairo_font_options_object *font_options_object;

	PHP_CAIRO_ERROR_HANDLING(TRUE)
	if (zend_parse_parameters_none() == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(TRUE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(TRUE)

	font_options_object = (cairo_font_options_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
	font_options_object->font_options = cairo_font_options_create();

	php_cairo_throw_exception(cairo_font_options_status(font_options_object->font_options) TSRMLS_CC);
}
/* }}} */

/* {{{ proto void cairo_font_options_create(void)
       Creates a new CairoFontOptions object with all options initialized to default values.
   */
PHP_FUNCTION(cairo_font_options_create)
{
	cairo_font_options_object *fontoptions_object;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	object_init_ex(return_value, cairo_ce_cairofontoptions);
	fontoptions_object = (cairo_font_options_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	fontoptions_object->font_options = cairo_font_options_create();

	php_cairo_trigger_error(cairo_font_options_status(fontoptions_object->font_options) TSRMLS_CC);
}
/* }}} */

/* {{{ proto void cairo_font_options_status(CairoFontOptions options)
       proto void CairoFontOptions->status(void)
	   Checks whether an error has previously occurred for this font options object
	   */
PHP_FUNCTION(cairo_font_options_status) 
{
	zval *font_options_zval = NULL;
	cairo_font_options_object *font_options_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &font_options_zval, cairo_ce_cairofontoptions) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	font_options_object = (cairo_font_options_object *) cairo_font_options_object_get(font_options_zval TSRMLS_CC);
	RETURN_LONG(cairo_font_options_status(font_options_object->font_options));
}
/* }}} */

/* {{{ proto void cairo_font_options_merge(CairoFontOptions options, CairoFontOptions other)
       proto void CairoFontOptions->merge(CairoFontOptions other)
	   Merges non-default options from other into options, replacing existing values.
	   */
PHP_FUNCTION(cairo_font_options_merge)
{
	zval *options_zval = NULL, *other_zval = NULL;
	cairo_font_options_object *options_object, *other_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "OO", 
				&options_zval, cairo_ce_cairofontoptions, &other_zval, cairo_ce_cairofontoptions) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	options_object = (cairo_font_options_object *) cairo_font_options_object_get(options_zval TSRMLS_CC);
	other_object = (cairo_font_options_object *) cairo_font_options_object_get(options_zval TSRMLS_CC);
	
	cairo_font_options_merge(options_object->font_options, other_object->font_options);
	PHP_CAIRO_ERROR(cairo_font_options_status(options_object->font_options));
}
/* }}} */


/* {{{ proto long cairo_font_options_hash(CairoFontOptions options)
       proto long CairoFontOptions->hash(void)
	   Compute a hash for the font options object
	   */
PHP_FUNCTION(cairo_font_options_hash) 
{
	zval *font_options_zval = NULL;
	cairo_font_options_object *font_options_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &font_options_zval, cairo_ce_cairofontoptions) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	font_options_object = (cairo_font_options_object *) cairo_font_options_object_get(font_options_zval TSRMLS_CC);
	RETURN_LONG(cairo_font_options_hash(font_options_object->font_options));
}
/* }}} */


/* {{{ proto boolean cairo_font_options_equal(CairoFontOptions options, CairoFontOptions other)
       proto boolean CairoFontOptions->equal(CairoFontOptions other)
	   Compares two font options objects for equality.
	   */
PHP_FUNCTION(cairo_font_options_equal)
{
	zval *options_zval = NULL, *other_zval = NULL;
	cairo_font_options_object *options_object, *other_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "OO", 
				&options_zval, cairo_ce_cairofontoptions, &other_zval, cairo_ce_cairofontoptions) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	options_object = (cairo_font_options_object *) cairo_font_options_object_get(options_zval TSRMLS_CC);
	other_object = (cairo_font_options_object *) cairo_font_options_object_get(options_zval TSRMLS_CC);
	
	RETURN_BOOL(cairo_font_options_equal(options_object->font_options, other_object->font_options));
}
/* }}} */

/* {{{ proto void cairo_font_options_set_antialias(CairoFontOptions options)
       proto void CairoFontOptions->setAntialias(void)
	   Sets the antialiasing mode for the font options object.
	   */
PHP_FUNCTION(cairo_font_options_set_antialias) 
{
	long antialias = 0;
	zval *font_options_zval = NULL;
	cairo_font_options_object *font_options_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ol", &font_options_zval, cairo_ce_cairofontoptions, &antialias) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	font_options_object = (cairo_font_options_object *) cairo_font_options_object_get(font_options_zval TSRMLS_CC);
	cairo_font_options_set_antialias(font_options_object->font_options, antialias);
	PHP_CAIRO_ERROR(cairo_font_options_status(font_options_object->font_options));
}
/* }}} */

/* {{{ proto int cairo_font_options_get_antialias(CairoFontOptions options)
       proto int CairoFontOptions->getAntialias(void)
	   Gets the antialiasing mode for the font options object.
	   */
PHP_FUNCTION(cairo_font_options_get_antialias) 
{
	zval *font_options_zval = NULL;
	cairo_font_options_object *font_options_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &font_options_zval, cairo_ce_cairofontoptions) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	font_options_object = (cairo_font_options_object *) cairo_font_options_object_get(font_options_zval TSRMLS_CC);
	RETURN_LONG(cairo_font_options_get_antialias(font_options_object->font_options));
}
/* }}} */


/* {{{ proto void cairo_font_options_set_subpixel_order(CairoFontOptions options)
       proto void CairoFontOptions->setSubpixelOrder(void)
	   Sets the subpixel order for the font options object.
	   */
PHP_FUNCTION(cairo_font_options_set_subpixel_order) 
{
	long subpixel_order = 0;
	zval *font_options_zval = NULL;
	cairo_font_options_object *font_options_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ol", &font_options_zval, cairo_ce_cairofontoptions, &subpixel_order) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	font_options_object = (cairo_font_options_object *) cairo_font_options_object_get(font_options_zval TSRMLS_CC);
	cairo_font_options_set_subpixel_order(font_options_object->font_options, subpixel_order);
	PHP_CAIRO_ERROR(cairo_font_options_status(font_options_object->font_options));
}
/* }}} */

/* {{{ proto int cairo_font_options_get_subpixel_order(CairoFontOptions options)
       proto int CairoFontOptions->getSubpixelOrder(void)
	   Gets the subpixel order for the font options object.
	   */
PHP_FUNCTION(cairo_font_options_get_subpixel_order) 
{
	zval *font_options_zval = NULL;
	cairo_font_options_object *font_options_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &font_options_zval, cairo_ce_cairofontoptions) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	font_options_object = (cairo_font_options_object *) cairo_font_options_object_get(font_options_zval TSRMLS_CC);
	RETURN_LONG(cairo_font_options_get_subpixel_order(font_options_object->font_options));
}
/* }}} */

/* {{{ proto void cairo_font_options_set_hint_style(CairoFontOptions options)
       proto void CairoFontOptions->setHintStyle(void)
	   Sets the hint style for font outlines for the font options object.
	   */
PHP_FUNCTION(cairo_font_options_set_hint_style) 
{
	long hint_style = 0;
	zval *font_options_zval = NULL;
	cairo_font_options_object *font_options_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ol", &font_options_zval, cairo_ce_cairofontoptions, &hint_style) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	font_options_object = (cairo_font_options_object *) cairo_font_options_object_get(font_options_zval TSRMLS_CC);
	cairo_font_options_set_hint_style(font_options_object->font_options, hint_style);
	PHP_CAIRO_ERROR(cairo_font_options_status(font_options_object->font_options));
}
/* }}} */

/* {{{ proto int cairo_font_options_get_hint_style(CairoFontOptions options)
       proto int CairoFontOptions->getHintStyle(void)
	   Gets the hint style for font outlines for the font options object.
	   */
PHP_FUNCTION(cairo_font_options_get_hint_style) 
{
	zval *font_options_zval = NULL;
	cairo_font_options_object *font_options_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &font_options_zval, cairo_ce_cairofontoptions) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	font_options_object = (cairo_font_options_object *) cairo_font_options_object_get(font_options_zval TSRMLS_CC);
	RETURN_LONG(cairo_font_options_get_hint_style(font_options_object->font_options));
}
/* }}} */

/* {{{ proto void cairo_font_options_set_hint_metrics(CairoFontOptions options)
       proto void CairoFontOptions->setHintMetrics(void)
	   Sets the metrics hinting mode for the font options object.
	   */
PHP_FUNCTION(cairo_font_options_set_hint_metrics) 
{
	long hint_metrics = 0;
	zval *font_options_zval = NULL;
	cairo_font_options_object *font_options_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ol", &font_options_zval, cairo_ce_cairofontoptions, &hint_metrics) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	font_options_object = (cairo_font_options_object *) cairo_font_options_object_get(font_options_zval TSRMLS_CC);
	cairo_font_options_set_hint_metrics(font_options_object->font_options, hint_metrics);
	PHP_CAIRO_ERROR(cairo_font_options_status(font_options_object->font_options));
}
/* }}} */

/* {{{ proto int cairo_font_options_get_hint_metrics(CairoFontOptions options)
       proto int CairoFontOptions->getHintMetrics(void)
	   Gets the metrics hinting mode for the font options object.
	   */
PHP_FUNCTION(cairo_font_options_get_hint_metrics) 
{
	zval *font_options_zval = NULL;
	cairo_font_options_object *font_options_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &font_options_zval, cairo_ce_cairofontoptions) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	font_options_object = (cairo_font_options_object *) cairo_font_options_object_get(font_options_zval TSRMLS_CC);
	RETURN_LONG(cairo_font_options_get_hint_metrics(font_options_object->font_options));
}
/* }}} */

const zend_function_entry cairo_font_options_methods[] = {
	PHP_ME(CairoFontOptions, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME_MAPPING(status, cairo_font_options_status, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(merge, cairo_font_options_merge, CairoFontOptions_fontoptions_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(hash, cairo_font_options_hash, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(equal, cairo_font_options_equal, CairoFontOptions_fontoptions_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(setAntialias, cairo_font_options_set_antialias, CairoFontOptions_setAntialias_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(getAntialias, cairo_font_options_get_antialias, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(setSubpixelOrder, cairo_font_options_set_subpixel_order, CairoFontOptions_setSubpixelOrder_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(getSubpixelOrder, cairo_font_options_get_subpixel_order, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(setHintStyle, cairo_font_options_set_hint_style, CairoFontOptions_setHintStyle_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(getHintStyle, cairo_font_options_get_hint_style, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(setHintMetrics, cairo_font_options_set_hint_metrics, CairoFontOptions_setHintMetrics_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(getHintMetrics, cairo_font_options_get_hint_metrics, NULL, ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};

/* }}} */

/* Helper Functions */
PHP_CAIRO_API zend_class_entry * php_cairo_get_fontoptions_ce()
{
	return cairo_ce_cairofontoptions;
}
/* }}} */

/* These is a wrapper around cairo_font_options_copy to "re-export" it out
so extensions using php cairo don't have to explicitly link against cairo */
PHP_CAIRO_API cairo_font_options_t * php_cairo_font_options_copy(const cairo_font_options_t *fo)
{
	return cairo_font_options_copy(fo);
}
/* }}} */

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(cairo_font_options)
{
	zend_class_entry fontoptions_ce;
	zend_class_entry hintstyle_ce;
	zend_class_entry hintmetrics_ce;

	INIT_CLASS_ENTRY(fontoptions_ce, "CairoFontOptions", cairo_font_options_methods);
	cairo_ce_cairofontoptions = zend_register_internal_class(&fontoptions_ce TSRMLS_CC);
	cairo_ce_cairofontoptions->create_object = cairo_font_options_object_new;

	INIT_CLASS_ENTRY(hintstyle_ce, "CairoHintStyle", NULL);
    cairo_ce_hintstyle = zend_register_internal_class(&hintstyle_ce TSRMLS_CC);
    cairo_ce_hintstyle->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS | ZEND_ACC_FINAL_CLASS;

    #define REGISTER_CAIRO_HINTSTYLE_LONG_CONST(const_name, value) \
    zend_declare_class_constant_long(cairo_ce_hintstyle, const_name, sizeof(const_name)-1, (long)value TSRMLS_CC); \
    REGISTER_LONG_CONSTANT(#value,  value,  CONST_CS | CONST_PERSISTENT);

    REGISTER_CAIRO_HINTSTYLE_LONG_CONST("STYLE_DEFAULT", CAIRO_HINT_STYLE_DEFAULT);
    REGISTER_CAIRO_HINTSTYLE_LONG_CONST("STYLE_NONE", CAIRO_HINT_STYLE_NONE);
    REGISTER_CAIRO_HINTSTYLE_LONG_CONST("STYLE_SLIGHT", CAIRO_HINT_STYLE_SLIGHT);
    REGISTER_CAIRO_HINTSTYLE_LONG_CONST("STYLE_MEDIUM", CAIRO_HINT_STYLE_MEDIUM);
    REGISTER_CAIRO_HINTSTYLE_LONG_CONST("STYLE_FULL", CAIRO_HINT_STYLE_FULL);

    INIT_CLASS_ENTRY(hintmetrics_ce, "CairoHintMetrics", NULL);
    cairo_ce_hintmetrics = zend_register_internal_class(&hintmetrics_ce TSRMLS_CC);
    cairo_ce_hintmetrics->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS | ZEND_ACC_FINAL_CLASS;

    #define REGISTER_CAIRO_HINTMETRICS_LONG_CONST(const_name, value) \
    zend_declare_class_constant_long(cairo_ce_hintmetrics, const_name, sizeof(const_name)-1, (long)value TSRMLS_CC); \
    REGISTER_LONG_CONSTANT(#value,  value,  CONST_CS | CONST_PERSISTENT);

    REGISTER_CAIRO_HINTMETRICS_LONG_CONST("METRICS_DEFAULT", CAIRO_HINT_METRICS_DEFAULT);
    REGISTER_CAIRO_HINTMETRICS_LONG_CONST("METRICS_OFF", CAIRO_HINT_METRICS_OFF);
    REGISTER_CAIRO_HINTMETRICS_LONG_CONST("METRICS_ON", CAIRO_HINT_METRICS_ON);

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
