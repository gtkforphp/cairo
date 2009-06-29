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

zend_class_entry *cairo_ce_cairofontslant;
zend_class_entry *cairo_ce_cairofontweight;
zend_class_entry *cairo_ce_cairotoyfontface;

#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 8, 0)
/* Toy font face support */
#endif

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(cairo_font)
{
	zend_class_entry toyfont_ce;
	zend_class_entry fontslant_ce;
	zend_class_entry fontweight_ce;

	
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 8, 0)
	INIT_CLASS_ENTRY(ce, "CairoToyFontFace", cairo_toy_font_face_methods);
	cairo_ce_cairotoyfontface = zend_register_internal_class_ex(&ce, cairo_ce_cairofontface, "CairoFontFace" TSRMLS_CC);
	cairo_ce_cairotoyfontface->create_object = cairo_font_face_object_new;
#endif

    INIT_CLASS_ENTRY(fontslant_ce, "CairoFontSlant", NULL);
    cairo_ce_cairofontslant = zend_register_internal_class(&fontslant_ce TSRMLS_CC);
    cairo_ce_cairofontslant->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS | ZEND_ACC_FINAL_CLASS;

    #define REGISTER_CAIRO_FONTSLANT_LONG_CONST(const_name, value) \
    zend_declare_class_constant_long(cairo_ce_fontslant, const_name, sizeof(const_name)-1, (long)value TSRMLS_CC); \
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
