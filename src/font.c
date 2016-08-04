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


zend_class_entry *ce_cairo_fontslant;
zend_class_entry *ce_cairo_fontweight;
zend_class_entry *ce_cairo_toyfontface;

/* ----------------------------------------------------------------
    Cairo\CairoToyFontFace Class API
------------------------------------------------------------------*/

ZEND_BEGIN_ARG_INFO_EX(CairoToyFontFace___construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_INFO(0, family)
	ZEND_ARG_INFO(0, slant)
	ZEND_ARG_INFO(0, weight)
ZEND_END_ARG_INFO()

/* {{{ proto void __construct(string family, long slant, long weight)
       Creates a font face from a triplet of family, slant, and weight. These font 
	   faces are used in implementation of the the "toy" font API.*/
PHP_METHOD(CairoToyFontFace, __construct)
{
	char *family;
        size_t family_len;
	zend_long slant = CAIRO_FONT_SLANT_NORMAL, weight = CAIRO_FONT_WEIGHT_NORMAL;
	cairo_font_face_object *fontface_object;

	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|ll", &family, &family_len, &slant, &weight) == FAILURE) {
            return;
	}
        
        fontface_object = Z_CAIRO_FONT_FACE_P(getThis());
	if(!fontface_object) {
            return;
        }
        
	fontface_object->font_face = cairo_toy_font_face_create((const char *)family, slant, weight);
	php_cairo_throw_exception(cairo_font_face_status(fontface_object->font_face));
}


/* {{{ proto string CairoToyFontFace->getFamily()
        Gets the family name of a toy font. */
PHP_METHOD(CairoToyFontFace, getFamily)
{
	cairo_font_face_object *font_face_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }

        font_face_object = Z_CAIRO_FONT_FACE_P(getThis());
	if(!font_face_object) {
            return;
        }
        
	RETURN_STRING(cairo_toy_font_face_get_family(font_face_object->font_face));
}
/* }}} */

/* {{{ proto long CairoToyFontFace->getSlant()
        Gets the slant of a toy font. */
PHP_METHOD(CairoToyFontFace, getSlant)
{
	cairo_font_face_object *font_face_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }

        font_face_object = Z_CAIRO_FONT_FACE_P(getThis());
	if(!font_face_object) {
            return;
        }
        
        object_init_ex(return_value, ce_cairo_fontslant);
        php_eos_datastructures_set_enum_value(return_value, cairo_toy_font_face_get_slant(font_face_object->font_face));
}
/* }}} */

/* {{{ proto long CairoToyFontFace->getWeight()
        Gets the weight of a toy font. */
PHP_METHOD(CairoToyFontFace, getWeight)
{
	cairo_font_face_object *font_face_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }

        font_face_object = Z_CAIRO_FONT_FACE_P(getThis());
	if(!font_face_object) {
            return;
        }
        
        object_init_ex(return_value, ce_cairo_fontweight);
        php_eos_datastructures_set_enum_value(return_value, cairo_toy_font_face_get_weight(font_face_object->font_face));
}
/* }}} */

/* ----------------------------------------------------------------
    Cairo\CairoToyFontFace Definition and registration
------------------------------------------------------------------*/

/* {{{ cairo_toy_font_face_methods */
const zend_function_entry cairo_toy_font_face_methods[] = {
	PHP_ME(CairoToyFontFace, __construct, CairoToyFontFace___construct_args, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(CairoToyFontFace, getFamily, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CairoToyFontFace, getSlant, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CairoToyFontFace, getWeight, NULL, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};
/* }}} */

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(cairo_font)
{
	zend_class_entry toyfont_ce, fontslant_ce, fontweight_ce;

        //INIT_NS_CLASS_ENTRY(toyfont_ce, CAIRO_NAMESPACE, "ToyFontFace", cairo_toy_font_face_methods);
        INIT_NS_CLASS_ENTRY(toyfont_ce, CAIRO_NAMESPACE, ZEND_NS_NAME("FontFace", "Toy"), cairo_toy_font_face_methods);
	ce_cairo_toyfontface = zend_register_internal_class_ex(&toyfont_ce, ce_cairo_fontface);
	ce_cairo_toyfontface->create_object = cairo_font_face_create_object;
        
        /* FontSlant */
        INIT_NS_CLASS_ENTRY(fontslant_ce, CAIRO_NAMESPACE, "FontSlant", NULL);
        ce_cairo_fontslant = zend_register_internal_class_ex(&fontslant_ce, php_eos_datastructures_get_enum_ce());
        ce_cairo_fontslant->ce_flags |= ZEND_ACC_FINAL;
        
        #define CAIRO_FONTSLANT_DECLARE_ENUM(name) \
            zend_declare_class_constant_long(ce_cairo_fontslant, #name, \
            sizeof(#name)-1, CAIRO_FONT_SLANT_## name);

        CAIRO_FONTSLANT_DECLARE_ENUM(NORMAL);
        CAIRO_FONTSLANT_DECLARE_ENUM(ITALIC);
        CAIRO_FONTSLANT_DECLARE_ENUM(OBLIQUE);
        
        /* FontWeight */
        INIT_NS_CLASS_ENTRY(fontweight_ce, CAIRO_NAMESPACE, "FontWeight", NULL);
        ce_cairo_fontweight = zend_register_internal_class_ex(&fontweight_ce, php_eos_datastructures_get_enum_ce());
        ce_cairo_fontweight->ce_flags |= ZEND_ACC_FINAL;
        
        #define CAIRO_FONTWEIGHT_DECLARE_ENUM(name) \
            zend_declare_class_constant_long(ce_cairo_fontweight, #name, \
            sizeof(#name)-1, CAIRO_FONT_WEIGHT_## name);
            
        CAIRO_FONTWEIGHT_DECLARE_ENUM(NORMAL);
        CAIRO_FONTWEIGHT_DECLARE_ENUM(BOLD);
}
/* }}} */

