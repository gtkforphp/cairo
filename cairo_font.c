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

zend_class_entry *cairo_ce_cairofontslant;
zend_class_entry *cairo_ce_cairofontweight;
zend_class_entry *cairo_ce_cairotoyfontface;

ZEND_BEGIN_ARG_INFO_EX(CairoToyFontFace___construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_INFO(0, family)
	ZEND_ARG_INFO(0, slant)
	ZEND_ARG_INFO(0, weight)
ZEND_END_ARG_INFO()

#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 8, 0)
/* Toy font face support */

/* {{{ proto void cairo_toy_font_face_create(string family, long slant, long weight)
       Creates a font face from a triplet of family, slant, and weight. These font 
	   faces are used in implementation of the the "toy" font API. 
*/
PHP_FUNCTION(cairo_toy_font_face_create)
{
	char *family;
	int family_len;
   	long slant = CAIRO_FONT_SLANT_NORMAL, weight = CAIRO_FONT_WEIGHT_NORMAL;
	cairo_font_face_object *fontface_object;

	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|ll", 
				&family, &family_len, 
				&slant, &weight) == FAILURE) {
		return;
	}

	object_init_ex(return_value, cairo_ce_cairotoyfontface);
	fontface_object = (cairo_font_face_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	fontface_object->font_face = cairo_toy_font_face_create((const char *)family, slant, weight);
	php_cairo_trigger_error(cairo_font_face_status(fontface_object->font_face) TSRMLS_CC);
}

/* {{{ proto void __construct(string family, long slant, long weight)
       Creates a font face from a triplet of family, slant, and weight. These font 
	   faces are used in implementation of the the "toy" font API. 
*/
PHP_METHOD(CairoToyFontFace, __construct)
{
	char *family;
	long family_len, slant = CAIRO_FONT_SLANT_NORMAL, weight = CAIRO_FONT_WEIGHT_NORMAL;
	cairo_font_face_object *fontface_object;

	PHP_CAIRO_ERROR_HANDLING(TRUE)
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|ll", 
				&family, &family_len, 
				&slant, &weight) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(TRUE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(TRUE)

	fontface_object = (cairo_font_face_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
	fontface_object->font_face = cairo_toy_font_face_create((const char *)family, slant, weight);
	php_cairo_throw_exception(cairo_font_face_status(fontface_object->font_face) TSRMLS_CC);
}

/* {{{ proto string cairo_toy_font_face_get_family(CairoToyFontFace object)
 	   proto string CairoToyFontFace->getFamily()
	   Gets the family name of a toy font. */
PHP_FUNCTION(cairo_toy_font_face_get_family)
{
	zval *toy_font_face_zval = NULL;
	cairo_font_face_object *font_face_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &toy_font_face_zval, cairo_ce_cairotoyfontface) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	font_face_object = (cairo_font_face_object *) cairo_font_face_object_get(toy_font_face_zval TSRMLS_CC);
	RETURN_STRING(cairo_toy_font_face_get_family(font_face_object->font_face), 1);
}
/* }}} */

/* {{{ proto long cairo_toy_font_face_get_slant(CairoToyFontFace object)
 	   proto long CairoToyFontFace->getSlant()
	   Gets the slant of a toy font. */
PHP_FUNCTION(cairo_toy_font_face_get_slant)
{
	zval *toy_font_face_zval = NULL;
	cairo_font_face_object *font_face_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &toy_font_face_zval, cairo_ce_cairotoyfontface) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	font_face_object = (cairo_font_face_object *) cairo_font_face_object_get(toy_font_face_zval TSRMLS_CC);
	RETURN_LONG(cairo_toy_font_face_get_slant(font_face_object->font_face));
}
/* }}} */

/* {{{ proto long cairo_toy_font_face_get_weight(CairoToyFontFace object)
 	   proto long CairoToyFontFace->getWeight()
	   Gets the weight of a toy font. */
PHP_FUNCTION(cairo_toy_font_face_get_weight)
{
	zval *toy_font_face_zval = NULL;
	cairo_font_face_object *font_face_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &toy_font_face_zval, cairo_ce_cairotoyfontface) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	font_face_object = (cairo_font_face_object *) cairo_font_face_object_get(toy_font_face_zval TSRMLS_CC);
	RETURN_LONG(cairo_toy_font_face_get_weight(font_face_object->font_face));
}
/* }}} */

#endif

/* {{{ cairo_toy_font_face_methods */
const zend_function_entry cairo_toy_font_face_methods[] = {
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 8, 0)
	PHP_ME(CairoToyFontFace, __construct, CairoToyFontFace___construct_args, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME_MAPPING(getFamily, cairo_toy_font_face_get_family, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(getSlant, cairo_toy_font_face_get_slant, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(getWeight, cairo_toy_font_face_get_weight, NULL, ZEND_ACC_PUBLIC)
#endif
	{ NULL, NULL, NULL }
};
/* }}} */

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(cairo_font)
{
	zend_class_entry toyfont_ce;
	zend_class_entry fontslant_ce;
	zend_class_entry fontweight_ce;

	INIT_CLASS_ENTRY(toyfont_ce, "CairoToyFontFace", cairo_toy_font_face_methods);
	cairo_ce_cairotoyfontface = zend_register_internal_class_ex(&toyfont_ce, cairo_ce_cairofontface, "CairoFontFace" TSRMLS_CC);
	cairo_ce_cairotoyfontface->create_object = cairo_font_face_object_new;

    INIT_CLASS_ENTRY(fontslant_ce, "CairoFontSlant", NULL);
    cairo_ce_cairofontslant = zend_register_internal_class(&fontslant_ce TSRMLS_CC);
    cairo_ce_cairofontslant->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS | ZEND_ACC_FINAL_CLASS;

    #define REGISTER_CAIRO_FONTSLANT_LONG_CONST(const_name, value) \
    zend_declare_class_constant_long(cairo_ce_cairofontslant, const_name, sizeof(const_name)-1, (long)value TSRMLS_CC); \
    REGISTER_LONG_CONSTANT(#value,  value,  CONST_CS | CONST_PERSISTENT);

    REGISTER_CAIRO_FONTSLANT_LONG_CONST("NORMAL", CAIRO_FONT_SLANT_NORMAL);
    REGISTER_CAIRO_FONTSLANT_LONG_CONST("ITALIC", CAIRO_FONT_SLANT_ITALIC);
    REGISTER_CAIRO_FONTSLANT_LONG_CONST("OBLIQUE", CAIRO_FONT_SLANT_OBLIQUE);

    INIT_CLASS_ENTRY(fontweight_ce, "CairoFontWeight", NULL);
    cairo_ce_cairofontweight = zend_register_internal_class(&fontweight_ce TSRMLS_CC);
    cairo_ce_cairofontweight->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS | ZEND_ACC_FINAL_CLASS;

    #define REGISTER_CAIRO_FONTWEIGHT_LONG_CONST(const_name, value) \
    zend_declare_class_constant_long(cairo_ce_cairofontweight, const_name, sizeof(const_name)-1, (long)value TSRMLS_CC); \
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
