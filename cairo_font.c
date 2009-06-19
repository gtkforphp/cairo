/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2009 The PHP Group                                |
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

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "zend_exceptions.h"
#include "php_cairo.h"

zend_class_entry *cairo_ce_cairofontface;
zend_class_entry *cairo_ce_cairofonttype;
zend_class_entry *cairo_ce_cairofontoptions;
zend_class_entry *cairo_ce_fontslant;
zend_class_entry *cairo_ce_fontweight;
zend_class_entry *cairo_ce_hintstyle;
zend_class_entry *cairo_ce_hintmetrics;

ZEND_BEGIN_ARG_INFO_EX(CairoFontOptions_fontoptions_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_OBJ_INFO(0, other, CairoFontOptions, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(CairoFontOptions_setLong_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_INFO(0, long_value)
ZEND_END_ARG_INFO()

/* {{{ proto void contruct()
   CairoFontFace CANNOT be extended in userspace, this will throw an exception on use */
PHP_METHOD(CairoFontFace, __construct)
{
	zend_throw_exception(cairo_ce_cairoexception, "CairoFontFace cannot be constructed", 0 TSRMLS_CC);
}
/* }}} */

/* {{{ proto long cairo_font_face_status(CairoFontFace object)
   proto long CairoFontFace::status()
   Returns the current integer status of the CairoFontFace */
PHP_FUNCTION(cairo_font_face_status)
{
	zval *font_face_zval = NULL;
	cairo_fontface_object *font_face_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &font_face_zval, cairo_ce_cairofontface) == FAILURE) {
		return;
	}

	font_face_object = (cairo_fontface_object *) cairo_fontface_object_get(font_face_zval TSRMLS_CC);
	RETURN_LONG(cairo_font_face_status(font_face_object->font_face));
}
/* }}} */

/* {{{ proto long cairo_font_face_get_type(CairoFontFace object)
   proto long CairoFontFace::getType()
   Returns the current integer type of the CairoFontFace backend */
PHP_FUNCTION(cairo_font_face_get_type)
{
	zval *font_face_zval = NULL;
	cairo_fontface_object *font_face_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &font_face_zval, cairo_ce_cairofontface) == FAILURE) {
		return;
	}

	font_face_object = (cairo_fontface_object *) cairo_fontface_object_get(font_face_zval TSRMLS_CC);
	RETURN_LONG(cairo_font_face_get_type(font_face_object->font_face));
}
/* }}} */

/* {{{ cairo_font_face_methods[] */
const zend_function_entry cairo_font_face_methods[] = {
	PHP_ME_MAPPING(status, cairo_font_face_status, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(getType, cairo_font_face_get_type, NULL, ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};
/* }}} */

/* {{{ cairo_fontface_object_destroy 
 */
static void cairo_fontface_object_destroy(void *object TSRMLS_DC)
{
	cairo_fontface_object *font_face = (cairo_fontface_object *)object;
	zend_hash_destroy(font_face->std.properties);
	FREE_HASHTABLE(font_face->std.properties);
	if(font_face->font_face){
		cairo_font_face_destroy(font_face->font_face);
	}

	/* if this was created with cairo_quartz_font_face_create_for_cgfont
	we may have a font ref to free up 
#ifdef CAIRO_HAS_QUARTZ_FONT
	if (font_face->quartzref != NULL)
		CFRelease(font_face->quartzref);
#endif*/
	efree(object);
}

/* }}} */

/* {{{ cairo_fontface_object_new 
 */
zend_object_value cairo_fontface_object_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	cairo_fontface_object *font_face;
	zval *temp;

	font_face = emalloc(sizeof(cairo_fontface_object));
	memset(font_face,0,sizeof(cairo_fontface_object));

	font_face->std.ce = ce;

	ALLOC_HASHTABLE(font_face->std.properties);
	zend_hash_init(font_face->std.properties, 0, NULL, ZVAL_PTR_DTOR, 0);
	zend_hash_copy(font_face->std.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref,(void *) &temp, sizeof(zval *));
	retval.handle = zend_objects_store_put(font_face, NULL, (zend_objects_free_object_storage_t)cairo_fontface_object_destroy, NULL TSRMLS_CC);
	retval.handlers = zend_get_std_object_handlers();
	return retval;
}

/* }}} */

/* {{{ cairo_fontoptions_object_destroy
 */

static void cairo_fontoptions_object_destroy(void *object TSRMLS_DC)
{
	cairo_fontoptions_object *font_options = (cairo_fontoptions_object *)object;
	zend_hash_destroy(font_options->std.properties);
	FREE_HASHTABLE(font_options->std.properties);
	if(font_options->font_options) {
		cairo_font_options_destroy(font_options->font_options);
	}

	efree(object);
}

/* }}} */

/* {{{ cairo_fontoptions_object_new 
 */

static zend_object_value cairo_fontoptions_object_new(zend_class_entry *ce TSRMLS_DC) 
{
	zend_object_value retval;
	cairo_fontoptions_object *fontoptions;
	zval *temp;

	fontoptions = ecalloc(1, sizeof(cairo_fontoptions_object));
	fontoptions->font_options = NULL;
	fontoptions->std.ce = ce;

	ALLOC_HASHTABLE(fontoptions->std.properties);
	zend_hash_init(fontoptions->std.properties, 0, NULL, ZVAL_PTR_DTOR, 0);
	zend_hash_copy(fontoptions->std.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref,(void *) &temp, sizeof(zval *));
	retval.handle = zend_objects_store_put(fontoptions, NULL, (zend_objects_free_object_storage_t)cairo_fontoptions_object_destroy, NULL TSRMLS_CC);
	retval.handlers = zend_get_std_object_handlers();
	return retval;
}

/* }}} */

/* {{{ proto void __contruct(void) 
       Creates a new CairoFontOptions object with all options initialized to default values.
   */
PHP_METHOD(CairoFontOptions, __construct)
{
	cairo_fontoptions_object *fontoptions_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	fontoptions_object = (cairo_fontoptions_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
	fontoptions_object->font_options = cairo_font_options_create();

	php_cairo_throw_exception(cairo_font_options_status(fontoptions_object->font_options) TSRMLS_CC);
}
 
/* }}} */

/* {{{ proto void cairo_font_options_create(void)
       Creates a new CairoFontOptions object with all options initialized to default values.
   */
PHP_FUNCTION(cairo_font_options_create)
{
	cairo_fontoptions_object *fontoptions_object;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	object_init_ex(return_value, cairo_ce_cairofontoptions);
	fontoptions_object = (cairo_fontoptions_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	fontoptions_object->font_options = cairo_font_options_create();

	php_cairo_trigger_error(cairo_font_options_status(fontoptions_object->font_options) TSRMLS_CC);
}
 
/* }}} */

/* {{{ proto void cairo_font_options_status(CairoFontOptions options)
       proto void CairoFontOptions::status(void)
	   Checks whether an error has previously occurred for this font options object
	   */
PHP_FUNCTION(cairo_font_options_status) 
{
	zval *font_options_zval = NULL;
	cairo_fontoptions_object *font_options_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &font_options_zval, cairo_ce_cairofontoptions) == FAILURE) {
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	font_options_object = (cairo_fontoptions_object *) cairo_fontoptions_object_get(font_options_zval TSRMLS_CC);
	RETURN_LONG(cairo_font_options_status(font_options_object->font_options));
}

/* }}} */

/* {{{ proto void cairo_font_options_merge(CairoFontOptions options, CairoFontOptions other)
       proto void CairoFontOptions::merge(CairoFontOptions other)
	   Merges non-default options from other into options, replacing existing values.
	   */
PHP_FUNCTION(cairo_font_options_merge)
{
	zval *options_zval = NULL, *other_zval = NULL;
	cairo_fontoptions_object *options_object, *other_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "OO", 
				&options_zval, cairo_ce_cairofontoptions, &other_zval, cairo_ce_cairofontoptions) == FAILURE) {
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	options_object = (cairo_fontoptions_object *) cairo_fontoptions_object_get(options_zval TSRMLS_CC);
	other_object = (cairo_fontoptions_object *) cairo_fontoptions_object_get(options_zval TSRMLS_CC);
	
	cairo_font_options_merge(options_object->font_options, other_object->font_options);
	PHP_CAIRO_ERROR(cairo_font_options_status(options_object->font_options));
}

/* }}} */


/* {{{ proto void cairo_font_options_hash(CairoFontOptions options)
       proto void CairoFontOptions::hash(void)
	   Compute a hash for the font options object
	   */
PHP_FUNCTION(cairo_font_options_hash) 
{
	zval *font_options_zval = NULL;
	cairo_fontoptions_object *font_options_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &font_options_zval, cairo_ce_cairofontoptions) == FAILURE) {
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	font_options_object = (cairo_fontoptions_object *) cairo_fontoptions_object_get(font_options_zval TSRMLS_CC);
	RETURN_LONG(cairo_font_options_hash(font_options_object->font_options));
}

/* }}} */


/* {{{ proto void cairo_font_options_equal(CairoFontOptions options, CairoFontOptions other)
       proto void CairoFontOptions::equal(CairoFontOptions other)
	   Compares two font options objects for equality.
	   */
PHP_FUNCTION(cairo_font_options_equal)
{
	zval *options_zval = NULL, *other_zval = NULL;
	cairo_fontoptions_object *options_object, *other_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "OO", 
				&options_zval, cairo_ce_cairofontoptions, &other_zval, cairo_ce_cairofontoptions) == FAILURE) {
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	options_object = (cairo_fontoptions_object *) cairo_fontoptions_object_get(options_zval TSRMLS_CC);
	other_object = (cairo_fontoptions_object *) cairo_fontoptions_object_get(options_zval TSRMLS_CC);
	
	RETURN_BOOL(cairo_font_options_equal(options_object->font_options, other_object->font_options));
}

/* }}} */

/* {{{ proto void cairo_font_options_set_antialias(CairoFontOptions options)
       proto void CairoFontOptions::set_antialias(void)
	   Sets the antialiasing mode for the font options object.
	   */
PHP_FUNCTION(cairo_font_options_set_antialias) 
{
	int antialias = 0;
	zval *font_options_zval = NULL;
	cairo_fontoptions_object *font_options_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ol", &font_options_zval, cairo_ce_cairofontoptions, &antialias) == FAILURE) {
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	font_options_object = (cairo_fontoptions_object *) cairo_fontoptions_object_get(font_options_zval TSRMLS_CC);
	cairo_font_options_set_antialias(font_options_object->font_options, antialias);
	PHP_CAIRO_ERROR(cairo_font_options_status(font_options_object->font_options));
}

/* }}} */

/* {{{ proto void cairo_font_options_get_antialias(CairoFontOptions options)
       proto void CairoFontOptions::get_antialias(void)
	   Gets the antialiasing mode for the font options object.
	   */
PHP_FUNCTION(cairo_font_options_get_antialias) 
{
	zval *font_options_zval = NULL;
	cairo_fontoptions_object *font_options_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &font_options_zval, cairo_ce_cairofontoptions) == FAILURE) {
		return;
	}

	font_options_object = (cairo_fontoptions_object *) cairo_fontoptions_object_get(font_options_zval TSRMLS_CC);
	RETURN_LONG(cairo_font_options_get_antialias(font_options_object->font_options));
}

/* }}} */


/* {{{ proto void cairo_font_options_set_subpixel_order(CairoFontOptions options)
       proto void CairoFontOptions::set_subpixel_order(void)
	   Sets the subpixel order for the font options object.
	   */
PHP_FUNCTION(cairo_font_options_set_subpixel_order) 
{
	int subpixel_order = 0;
	zval *font_options_zval = NULL;
	cairo_fontoptions_object *font_options_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ol", &font_options_zval, cairo_ce_cairofontoptions, &subpixel_order) == FAILURE) {
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	font_options_object = (cairo_fontoptions_object *) cairo_fontoptions_object_get(font_options_zval TSRMLS_CC);
	cairo_font_options_set_subpixel_order(font_options_object->font_options, subpixel_order);
	PHP_CAIRO_ERROR(cairo_font_options_status(font_options_object->font_options));
}

/* }}} */

/* {{{ proto void cairo_font_options_get_subpixel_order(CairoFontOptions options)
       proto void CairoFontOptions::get_subpixel_order(void)
	   Gets the subpixel order for the font options object.
	   */
PHP_FUNCTION(cairo_font_options_get_subpixel_order) 
{
	zval *font_options_zval = NULL;
	cairo_fontoptions_object *font_options_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &font_options_zval, cairo_ce_cairofontoptions) == FAILURE) {
		return;
	}

	font_options_object = (cairo_fontoptions_object *) cairo_fontoptions_object_get(font_options_zval TSRMLS_CC);
	RETURN_LONG(cairo_font_options_get_subpixel_order(font_options_object->font_options));
}

/* }}} */

/* {{{ proto void cairo_font_options_set_hint_style(CairoFontOptions options)
       proto void CairoFontOptions::set_hint_style(void)
	   Sets the hint style for font outlines for the font options object.
	   */
PHP_FUNCTION(cairo_font_options_set_hint_style) 
{
	int hint_style = 0;
	zval *font_options_zval = NULL;
	cairo_fontoptions_object *font_options_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ol", &font_options_zval, cairo_ce_cairofontoptions, &hint_style) == FAILURE) {
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	font_options_object = (cairo_fontoptions_object *) cairo_fontoptions_object_get(font_options_zval TSRMLS_CC);
	cairo_font_options_set_hint_style(font_options_object->font_options, hint_style);
	PHP_CAIRO_ERROR(cairo_font_options_status(font_options_object->font_options));
}

/* }}} */

/* {{{ proto void cairo_font_options_get_hint_style(CairoFontOptions options)
       proto void CairoFontOptions::get_hint_style(void)
	   Gets the hint style for font outlines for the font options object.
	   */
PHP_FUNCTION(cairo_font_options_get_hint_style) 
{
	zval *font_options_zval = NULL;
	cairo_fontoptions_object *font_options_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &font_options_zval, cairo_ce_cairofontoptions) == FAILURE) {
		return;
	}

	font_options_object = (cairo_fontoptions_object *) cairo_fontoptions_object_get(font_options_zval TSRMLS_CC);
	RETURN_LONG(cairo_font_options_get_hint_style(font_options_object->font_options));
}

/* }}} */

/* {{{ proto void cairo_font_options_set_hint_metrics(CairoFontOptions options)
       proto void CairoFontOptions::set_hint_metrics(void)
	   Sets the metrics hinting mode for the font options object.
	   */
PHP_FUNCTION(cairo_font_options_set_hint_metrics) 
{
	int hint_metrics = 0;
	zval *font_options_zval = NULL;
	cairo_fontoptions_object *font_options_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ol", &font_options_zval, cairo_ce_cairofontoptions, &hint_metrics) == FAILURE) {
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	font_options_object = (cairo_fontoptions_object *) cairo_fontoptions_object_get(font_options_zval TSRMLS_CC);
	cairo_font_options_set_hint_metrics(font_options_object->font_options, hint_metrics);
	PHP_CAIRO_ERROR(cairo_font_options_status(font_options_object->font_options));
}

/* }}} */

/* {{{ proto void cairo_font_options_get_hint_metrics(CairoFontOptions options)
       proto void CairoFontOptions::get_hint_metrics(void)
	   Gets the metrics hinting mode for the font options object.
	   */
PHP_FUNCTION(cairo_font_options_get_hint_metrics) 
{
	zval *font_options_zval = NULL;
	cairo_fontoptions_object *font_options_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &font_options_zval, cairo_ce_cairofontoptions) == FAILURE) {
		return;
	}

	font_options_object = (cairo_fontoptions_object *) cairo_fontoptions_object_get(font_options_zval TSRMLS_CC);
	RETURN_LONG(cairo_font_options_get_hint_metrics(font_options_object->font_options));
}

/* }}} */

const zend_function_entry cairo_font_options_methods[] = {
	PHP_ME(CairoFontOptions, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME_MAPPING(status, cairo_font_options_status, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(merge, cairo_font_options_merge, CairoFontOptions_fontoptions_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(hash, cairo_font_options_hash, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(equal, cairo_font_options_equal, CairoFontOptions_fontoptions_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(setAntialias, cairo_font_options_set_antialias, CairoFontOptions_setLong_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(getAntialias, cairo_font_options_get_antialias, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(setSubpixelOrder, cairo_font_options_set_subpixel_order, CairoFontOptions_setLong_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(getSubpixelOrder, cairo_font_options_get_subpixel_order, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(setHintStyle, cairo_font_options_set_hint_style, CairoFontOptions_setLong_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(getHintStyle, cairo_font_options_get_hint_style, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(setHintMetrics, cairo_font_options_set_hint_metrics, CairoFontOptions_setLong_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(getHintMetrics, cairo_font_options_get_hint_metrics, NULL, ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};

/* }}} */

/* Helper Functions */
PHP_CAIRO_API zend_class_entry * php_cairo_get_fontface_ce()
{
	return cairo_ce_cairofontface;
}

PHP_CAIRO_API zend_class_entry * php_cairo_get_fontoptions_ce()
{
	return cairo_ce_cairofontoptions;
}

/* These is a wrapper around cairo_font_options_copy to "re-export" it out
so extensions using php cairo don't have to explicitly link against cairo */
PHP_CAIRO_API cairo_font_options_t * php_cairo_font_options_copy(const cairo_font_options_t *fo)
{
	return cairo_font_options_copy(fo);
}

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(cairo_font)
{
	zend_class_entry fontface_ce;
	zend_class_entry fontoptions_ce;
	zend_class_entry fonttype_ce;
	zend_class_entry fontslant_ce;
	zend_class_entry fontweight_ce;
	zend_class_entry hintstyle_ce;
	zend_class_entry hintmetrics_ce;

	INIT_CLASS_ENTRY(fontface_ce, "CairoFontFace", cairo_font_face_methods);
	cairo_ce_cairofontface = zend_register_internal_class(&fontface_ce TSRMLS_CC);
	cairo_ce_cairofontface->create_object = cairo_fontface_object_new;
	cairo_ce_cairofontface->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS;

	INIT_CLASS_ENTRY(fontoptions_ce, "CairoFontOptions", cairo_font_options_methods);
	cairo_ce_cairofontoptions = zend_register_internal_class(&fontoptions_ce TSRMLS_CC);
	cairo_ce_cairofontoptions->create_object = cairo_fontoptions_object_new;

	INIT_CLASS_ENTRY(fonttype_ce, "CairoFontType", NULL);
	cairo_ce_cairofonttype = zend_register_internal_class(&fonttype_ce TSRMLS_CC);
	cairo_ce_cairofonttype->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS | ZEND_ACC_FINAL_CLASS;

	#define REGISTER_CAIRO_FONTTYPE_LONG_CONST(const_name, value) \
	zend_declare_class_constant_long(cairo_ce_cairofonttype, const_name, sizeof(const_name)-1, (long)value TSRMLS_CC); \
	REGISTER_LONG_CONSTANT(#value,  value,  CONST_CS | CONST_PERSISTENT);

	REGISTER_CAIRO_FONTTYPE_LONG_CONST("TOY", CAIRO_FONT_TYPE_TOY);
	REGISTER_CAIRO_FONTTYPE_LONG_CONST("FT", CAIRO_FONT_TYPE_FT);
	REGISTER_CAIRO_FONTTYPE_LONG_CONST("WIN32", CAIRO_FONT_TYPE_WIN32);
#ifdef CAIRO_FONT_TYPE_QUARTZ
	REGISTER_CAIRO_FONTTYPE_LONG_CONST("QUARTZ", CAIRO_FONT_TYPE_QUARTZ);
#endif
#ifdef CAIRO_FONT_TYPE_USER
	REGISTER_CAIRO_FONTTYPE_LONG_CONST("USER", CAIRO_FONT_TYPE_USER);
#endif

    INIT_CLASS_ENTRY(fontslant_ce, "CairoFontSlant", NULL);
    cairo_ce_fontslant = zend_register_internal_class(&fontslant_ce TSRMLS_CC);
    cairo_ce_fontslant->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS | ZEND_ACC_FINAL_CLASS;

    #define REGISTER_CAIRO_FONTSLANT_LONG_CONST(const_name, value) \
    zend_declare_class_constant_long(cairo_ce_fontslant, const_name, sizeof(const_name)-1, (long)value TSRMLS_CC); \
    REGISTER_LONG_CONSTANT(#value,  value,  CONST_CS | CONST_PERSISTENT);

    REGISTER_CAIRO_FONTSLANT_LONG_CONST("NORMAL", CAIRO_FONT_SLANT_NORMAL);
    REGISTER_CAIRO_FONTSLANT_LONG_CONST("ITALIC", CAIRO_FONT_SLANT_ITALIC);
    REGISTER_CAIRO_FONTSLANT_LONG_CONST("OBLIQUE", CAIRO_FONT_SLANT_OBLIQUE);

    INIT_CLASS_ENTRY(fontweight_ce, "CairoFontWeight", NULL);
    cairo_ce_fontweight = zend_register_internal_class(&fontweight_ce TSRMLS_CC);
    cairo_ce_fontweight->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS | ZEND_ACC_FINAL_CLASS;

    #define REGISTER_CAIRO_FONTWEIGHT_LONG_CONST(const_name, value) \
    zend_declare_class_constant_long(cairo_ce_fontweight, const_name, sizeof(const_name)-1, (long)value TSRMLS_CC); \
    REGISTER_LONG_CONSTANT(#value,  value,  CONST_CS | CONST_PERSISTENT);

    REGISTER_CAIRO_FONTWEIGHT_LONG_CONST("NORMAL", CAIRO_FONT_WEIGHT_NORMAL);
    REGISTER_CAIRO_FONTWEIGHT_LONG_CONST("BOLD", CAIRO_FONT_WEIGHT_BOLD);


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

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
