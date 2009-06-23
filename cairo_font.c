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
zend_class_entry *cairo_ce_fontslant;
zend_class_entry *cairo_ce_fontweight;

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
	cairo_font_face_object *font_face_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &font_face_zval, cairo_ce_cairofontface) == FAILURE) {
		return;
	}

	font_face_object = (cairo_font_face_object *) cairo_font_face_object_get(font_face_zval TSRMLS_CC);
	RETURN_LONG(cairo_font_face_status(font_face_object->font_face));
}
/* }}} */

/* {{{ proto long cairo_font_face_get_type(CairoFontFace object)
   proto long CairoFontFace::getType()
   Returns the current integer type of the CairoFontFace backend */
PHP_FUNCTION(cairo_font_face_get_type)
{
	zval *font_face_zval = NULL;
	cairo_font_face_object *font_face_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &font_face_zval, cairo_ce_cairofontface) == FAILURE) {
		return;
	}

	font_face_object = (cairo_font_face_object *) cairo_font_face_object_get(font_face_zval TSRMLS_CC);
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

/* {{{ cairo_font_face_object_destroy 
 */
static void cairo_font_face_object_destroy(void *object TSRMLS_DC)
{
	cairo_font_face_object *font_face = (cairo_font_face_object *)object;
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

/* {{{ cairo_font_face_object_new 
 */
zend_object_value cairo_font_face_object_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	cairo_font_face_object *font_face;
	zval *temp;

	font_face = emalloc(sizeof(cairo_font_face_object));
	memset(font_face,0,sizeof(cairo_font_face_object));

	font_face->std.ce = ce;

	ALLOC_HASHTABLE(font_face->std.properties);
	zend_hash_init(font_face->std.properties, 0, NULL, ZVAL_PTR_DTOR, 0);
	zend_hash_copy(font_face->std.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref,(void *) &temp, sizeof(zval *));
	retval.handle = zend_objects_store_put(font_face, NULL, (zend_objects_free_object_storage_t)cairo_font_face_object_destroy, NULL TSRMLS_CC);
	retval.handlers = zend_get_std_object_handlers();
	return retval;
}

/* }}} */

/* Helper Functions */
PHP_CAIRO_API zend_class_entry * php_cairo_get_fontface_ce()
{
	return cairo_ce_cairofontface;
}

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(cairo_font)
{
	zend_class_entry fontface_ce;
	zend_class_entry fonttype_ce;
	zend_class_entry fontslant_ce;
	zend_class_entry fontweight_ce;

	INIT_CLASS_ENTRY(fontface_ce, "CairoFontFace", cairo_font_face_methods);
	cairo_ce_cairofontface = zend_register_internal_class(&fontface_ce TSRMLS_CC);
	cairo_ce_cairofontface->create_object = cairo_font_face_object_new;
	cairo_ce_cairofontface->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS;

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
