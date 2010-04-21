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
  |         Mark Skilbeck <markskilbeck@php.net>                         |
  +----------------------------------------------------------------------+
*/

/* $Id$ */
/** TODO: REGISTER_LONG_CONSTANT support in REGISTER_WIN32_LONG_CONSTANT */
/** The zend_function_entry's are in php_cairo.h and cairo.c */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <cairo.h>
#include "php.h"
#include "php_cairo.h"
#include "zend_exceptions.h"
#include "zend.h"

#ifdef CAIRO_HAS_WIN32_FONT
#include <Windows.h>
#include <Wingdi.h>
#include <cairo/cairo-win32.h>

/** Not sure why these are not being defined in Wingdi.h 
    Must investigate */
#ifndef CLEARTYPE_QUALITY
# define CLEARTYPE_QUALITY 5
#endif
#ifndef CLEARTYPE_NATURAL_QUALITY
# define CLEARTYPE_NATURAL_QUALITY 6
#endif

/** Windows has a non-existant naming-scheme for
	its constants, so we have a const_name_p (procedural)
	string to avoid messing around with const_name. 
	*/
#define REGISTER_WIN32_LONG_CONST(ce, const_name, const_value, const_name_p) \
        zend_declare_class_constant_long(cairo_ce_##ce, const_name, sizeof(const_name) - 1, (long)const_value TSRMLS_CC); \
		REGISTER_LONG_CONSTANT(const_name_p, const_value, CONST_CS | CONST_PERSISTENT);

#define LFONT_FIND_LONG(name, defaultval) \
    if (zend_hash_find(Z_ARRVAL_P(font_options), #name, sizeof(#name), (void **)&tmp) == SUCCESS) { \
        if (Z_TYPE_PP(tmp) != IS_LONG) \
            zend_error(E_WARNING, "cairo_win32_font_face_create() expects key '"#name"' to be of type long"); \
        else \
            lfont.##name = Z_LVAL_PP(tmp); \
    } \
    else \
        lfont.##name = defaultval;
        
/** Same as before but casts return to BYTE */
#define LFONT_FIND_LONGB(name, defaultval) \
    if (zend_hash_find(Z_ARRVAL_P(font_options), #name, sizeof(#name), (void **)&tmp) == SUCCESS) { \
        if (Z_TYPE_PP(tmp) != IS_LONG) \
            zend_error(E_WARNING, "cairo_win32_font_face_create() expects key '"#name"' to be of type long"); \
        else \
            lfont.##name = (BYTE)Z_LVAL_PP(tmp); \
    } \
    else \
        lfont.##name = (BYTE)defaultval;
            
#define LFONT_FIND_BOOL(name, defaultval) \
    if (zend_hash_find(Z_ARRVAL_P(font_options), #name, sizeof(#name), (void **)&tmp) == SUCCESS) { \
        if (Z_TYPE_PP(tmp) != IS_BOOL) \
            zend_error(E_WARNING, "cairo_win32_font_face_create() expects key '"#name"' to be of type bool"); \
        else \
            lfont.##name = Z_BVAL_PP(tmp); \
    } \
    else \
        lfont.##name = defaultval;

zend_class_entry *cairo_ce_cairowin32font;
/** These classes are containers for constants defined in WinGdi.h, etc. */
zend_class_entry *cairo_ce_cairowin32fontweight;
zend_class_entry *cairo_ce_cairowin32fontcharset;
/** output precision constants */
zend_class_entry *cairo_ce_cairowin32fontoutprec;
/** clip precision constants */
zend_class_entry *cairo_ce_cairowin32fontclipprec;
zend_class_entry *cairo_ce_cairowin32fontquality;
zend_class_entry *cairo_ce_cairowin32fontpitch;
zend_class_entry *cairo_ce_cairowin32fontfamily;

/**
 * CairoWin32FontFace::__construct takes 1 optional argument
 */
ZEND_BEGIN_ARG_INFO_EX(CairoWin32FontFace_construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
    ZEND_ARG_INFO(0, "font_options")
ZEND_END_ARG_INFO()


/* {{{ proto CairoWin32FontFace cairo_win32_font_face_create([array font_options])
       Creates a new font face for the Win32 backend */
PHP_FUNCTION(cairo_win32_font_face_create)
{
    cairo_win32_font_face_object *font_face;
    LOGFONT     lfont;
    HFONT       hfont;
    zval        *font_options = NULL;
    zval        **tmp;
    char        *font_name = NULL;          

    PHP_CAIRO_ERROR_HANDLING(FALSE)
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|a", &font_options) == FAILURE) {
        PHP_CAIRO_RESTORE_ERRORS(FALSE)
        return;
    }
    PHP_CAIRO_RESTORE_ERRORS(FALSE)

    if (font_options) {
        /** Find values in font_options array and set them. Otherwise set defaults */
        LFONT_FIND_LONG(lfHeight, 0);
        LFONT_FIND_LONG(lfWidth, 0);
        LFONT_FIND_LONG(lfWeight, FW_DONTCARE);
        LFONT_FIND_LONG(lfOrientation, 0);
        LFONT_FIND_BOOL(lfItalic, FALSE);
        LFONT_FIND_BOOL(lfUnderline, FALSE);
        LFONT_FIND_BOOL(lfStrikeOut, FALSE);
        LFONT_FIND_LONGB(lfCharSet, DEFAULT_CHARSET);
        LFONT_FIND_LONGB(lfOutPrecision, OUT_DEFAULT_PRECIS);
        LFONT_FIND_LONGB(lfClipPrecision, CLIP_DEFAULT_PRECIS);
        LFONT_FIND_LONGB(lfQuality, DEFAULT_QUALITY);
        LFONT_FIND_LONGB(lfPitchAndFamily, FIXED_PITCH | FF_DONTCARE);
        
        if (zend_hash_find(Z_ARRVAL_P(font_options), "lfFaceName", sizeof("lfFaceName"), (void **)&tmp) == SUCCESS) {
            if (Z_TYPE_PP(tmp) != IS_STRING) {
                zend_error(E_WARNING, "cairo_win32_font_face_create() expects key 'lfFaceName' to be of type string");
            } else {
                lstrcpy(lfont.lfFaceName, Z_STRVAL_PP(tmp));    
            }
        } else {
            lstrcpy(lfont.lfFaceName, "");
        }
        
    } else {
        /** Arbitrary defaults */
        lfont.lfHeight = 24;
        lfont.lfWidth = 12;
        lfont.lfOrientation = 0;
        lfont.lfEscapement = 0;
        lfont.lfWeight = FW_NORMAL;
        lfont.lfItalic = FALSE;
        lfont.lfUnderline = FALSE;
        lfont.lfStrikeOut = FALSE;
        lfont.lfCharSet = DEFAULT_CHARSET;
        lfont.lfOutPrecision = OUT_DEFAULT_PRECIS;
        lfont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
        lfont.lfQuality = DEFAULT_QUALITY;
        lfont.lfPitchAndFamily = FIXED_PITCH | FF_DONTCARE;
        lstrcpy(lfont.lfFaceName, "");
    }    
    
    hfont = CreateFontIndirect(&lfont);

    object_init_ex(return_value, cairo_ce_cairowin32font);
    font_face = (cairo_win32_font_face_object *)zend_object_store_get_object(return_value TSRMLS_CC);
    font_face->font_face = cairo_win32_font_face_create_for_hfont(hfont);

    PHP_CAIRO_ERROR(cairo_font_face_status(font_face->font_face));
}

/* {{{ proto CairoWin32FontFace::__construct([array font_options])
       Creates a new font face for the Win32 backend */
PHP_METHOD(CairoWin32FontFace, __construct)
{
    cairo_win32_font_face_object *font_face;
    LOGFONT     lfont;
    HFONT       hfont;
    zval        *font_options = NULL;
    zval        **tmp;
    char        *font_name = NULL;          

    PHP_CAIRO_ERROR_HANDLING(TRUE)
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|a", &font_options) == FAILURE) {
        PHP_CAIRO_RESTORE_ERRORS(TRUE)
        return;
    }
    PHP_CAIRO_RESTORE_ERRORS(TRUE)

    if (font_options) {
        /** Find values in font_options array and set them. Otherwise set defaults */
        LFONT_FIND_LONG(lfHeight, 0);
        LFONT_FIND_LONG(lfWidth, 0);
        LFONT_FIND_LONG(lfWeight, FW_DONTCARE);
        LFONT_FIND_LONG(lfOrientation, 0);
        LFONT_FIND_BOOL(lfItalic, FALSE);
        LFONT_FIND_BOOL(lfUnderline, FALSE);
        LFONT_FIND_BOOL(lfStrikeOut, FALSE);
        LFONT_FIND_LONGB(lfCharSet, DEFAULT_CHARSET);
        LFONT_FIND_LONGB(lfOutPrecision, OUT_DEFAULT_PRECIS);
        LFONT_FIND_LONGB(lfClipPrecision, CLIP_DEFAULT_PRECIS);
        LFONT_FIND_LONGB(lfQuality, DEFAULT_QUALITY);
        LFONT_FIND_LONGB(lfPitchAndFamily, FIXED_PITCH | FF_DONTCARE);

        if (zend_hash_find(Z_ARRVAL_P(font_options), "lfFaceName", sizeof("lfFaceName"), (void **)&tmp) == SUCCESS) {
            if (Z_TYPE_PP(tmp) != IS_STRING) {
                zend_error(E_WARNING, "cairo_win32_font_face_create() expects key 'lfFaceName' to be of type string");
            } else {
                lstrcpy(lfont.lfFaceName, Z_STRVAL_PP(tmp));
            }
        } else {
            lstrcpy(lfont.lfFaceName, "");
        }

    } else {
        /** Arbitrary defaults */
        lfont.lfHeight = 0;
        lfont.lfWidth = 0;
        lfont.lfOrientation = 0;
        lfont.lfEscapement = 0;
        lfont.lfWeight = FW_DONTCARE;
        lfont.lfItalic = FALSE;
        lfont.lfUnderline = TRUE;
        lfont.lfStrikeOut = FALSE;
        lfont.lfCharSet = DEFAULT_CHARSET;
        lfont.lfOutPrecision = OUT_DEFAULT_PRECIS;
        lfont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
        lfont.lfQuality = DEFAULT_QUALITY;
        lfont.lfPitchAndFamily = FIXED_PITCH | FF_DONTCARE;
        lstrcpy(lfont.lfFaceName, "");
    }    

    hfont = CreateFontIndirect(&lfont);

    font_face = (cairo_win32_font_face_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
    font_face->font_face = cairo_win32_font_face_create_for_hfont(hfont);

    php_cairo_throw_exception(cairo_font_face_status(font_face->font_face) TSRMLS_CC);
}
/* }}} */

static function_entry cairo_win32_font_methods[] = {
    PHP_ME(CairoWin32FontFace, __construct, CairoWin32FontFace_construct_args, \
        ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    {NULL, NULL, NULL}
};

static void cairo_win32_font_face_object_destroy(void *object TSRMLS_DC)
{
    cairo_win32_font_face_object *font_face = (cairo_win32_font_face_object *)object;
    /** Frees the contents of the hashtable */
    zend_hash_destroy(font_face->std.properties);
    /** Frees the hashtable itself */
    FREE_HASHTABLE(font_face->std.properties);

    if (font_face->font_face)
        cairo_font_face_destroy(font_face->font_face);

    efree(font_face);
}

/**
 * Called by init_object_ex() to create the new object.
 */
zend_object_value cairo_win32_font_face_create_new(zend_class_entry *ce TSRMLS_DC)
{
    zend_object_value retval;
    cairo_win32_font_face_object *font_face;
    zval *temp;

    font_face = ecalloc(1, sizeof(cairo_win32_font_face_object));
    font_face->std.ce = ce;

    ALLOC_HASHTABLE(font_face->std.properties);
    zend_hash_init(font_face->std.properties, 0, NULL, ZVAL_PTR_DTOR, 0);
    zend_hash_copy(
        font_face->std.properties, 
        &ce->default_properties, 
        (copy_ctor_func_t) zval_add_ref,(void *) 
        &temp, sizeof(zval *)
    );
    retval.handle = zend_objects_store_put(
        font_face, NULL, 
        (zend_objects_free_object_storage_t)cairo_win32_font_face_object_destroy, 
        NULL TSRMLS_CC
    );
    retval.handlers = zend_get_std_object_handlers();
    return retval;
}


PHP_MINIT_FUNCTION(cairo_win32_font)
{
    zend_class_entry ce;
    /** These classes are containers for constants defined in WinGdi.h, etc. */
    zend_class_entry ce_cairowin32fontweight;
    zend_class_entry ce_cairowin32fontcharset;
    zend_class_entry ce_cairowin32fontoutprec;
    zend_class_entry ce_cairowin32fontclipprec;
    zend_class_entry ce_cairowin32fontquality;
    zend_class_entry ce_cairowin32fontpitch;
    zend_class_entry ce_cairowin32fontfamily;

    INIT_CLASS_ENTRY(ce, "CairoWin32FontFace", cairo_win32_font_methods);
    cairo_ce_cairowin32font = zend_register_internal_class_ex(
        &ce, cairo_ce_cairofontface, "CairoFontFace" TSRMLS_CC);
    /** So Zend knows what function to call when a new CairoWin32FontFace
        is requested */
    cairo_ce_cairowin32font->create_object = cairo_win32_font_face_create_new;

    /** Commence BORING constant definitions! */
    INIT_CLASS_ENTRY(ce_cairowin32fontweight, "CairoWin32FontWeight", NULL);
    cairo_ce_cairowin32fontweight = zend_register_internal_class(&ce_cairowin32fontweight TSRMLS_CC);
    cairo_ce_cairowin32fontweight->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS | ZEND_ACC_FINAL_CLASS;
    REGISTER_WIN32_LONG_CONST(cairowin32fontweight, "NORMAL", FW_NORMAL, "CAIRO_WIN32_FONT_WEIGHT_NORMAL");
    REGISTER_WIN32_LONG_CONST(cairowin32fontweight, "DONTCARE", FW_DONTCARE, "CAIRO_WIN32_FONT_WEIGHT_DONTCARE");
    REGISTER_WIN32_LONG_CONST(cairowin32fontweight, "THIN", FW_THIN, "CAIRO_WIN32_FONT_WEIGHT_THIN");
    REGISTER_WIN32_LONG_CONST(cairowin32fontweight, "EXTRALIGHT", FW_EXTRALIGHT, "CAIRO_WIN32_FONT_WEIGHT_EXTRALIGHT");
    REGISTER_WIN32_LONG_CONST(cairowin32fontweight, "ULTRALIGHT", FW_ULTRALIGHT, "CAIRO_WIN32_FONT_WEIGHT_ULTRALIGHT");
    REGISTER_WIN32_LONG_CONST(cairowin32fontweight, "LIGHT", FW_LIGHT, "CAIRO_WIN32_FONT_WEIGHT_LIGHT");
    REGISTER_WIN32_LONG_CONST(cairowin32fontweight, "REGULAR", FW_REGULAR, "CAIRO_WIN32_FONT_WEIGHT_REGULAR");
    REGISTER_WIN32_LONG_CONST(cairowin32fontweight, "MEDIUM", FW_MEDIUM, "CAIRO_WIN32_FONT_WEIGHT_MEDIUM");
    REGISTER_WIN32_LONG_CONST(cairowin32fontweight, "SEMIBOLD", FW_SEMIBOLD, "CAIRO_WIN32_FONT_WEIGHT_SEMIBOLD");
    REGISTER_WIN32_LONG_CONST(cairowin32fontweight, "DEMIBOLD", FW_DEMIBOLD, "CAIRO_WIN32_FONT_WEIGHT_DEMIBOLD");
    REGISTER_WIN32_LONG_CONST(cairowin32fontweight, "BOLD", FW_BOLD, "CAIRO_WIN32_FONT_WEIGHT_BOLD");
    REGISTER_WIN32_LONG_CONST(cairowin32fontweight, "EXTRABOLD", FW_EXTRABOLD, "CAIRO_WIN32_FONT_WEIGHT_EXTRABOLD");
    REGISTER_WIN32_LONG_CONST(cairowin32fontweight, "ULTRABOLD", FW_ULTRABOLD, "CAIRO_WIN32_FONT_WEIGHT_ULTRABOLD");
    REGISTER_WIN32_LONG_CONST(cairowin32fontweight, "HEAVY", FW_HEAVY, "CAIRO_WIN32_FONT_WEIGHT_HEAVY");
    REGISTER_WIN32_LONG_CONST(cairowin32fontweight, "BLACK", FW_BLACK, "CAIRO_WIN32_FONT_WEIGHT_BLACK");

    INIT_CLASS_ENTRY(ce_cairowin32fontcharset, "CairoWin32FontCharset", NULL);
    cairo_ce_cairowin32fontcharset = zend_register_internal_class(&ce_cairowin32fontcharset TSRMLS_CC);
    cairo_ce_cairowin32fontcharset->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS | ZEND_ACC_FINAL_CLASS;
    REGISTER_WIN32_LONG_CONST(cairowin32fontcharset, "ANSI", ANSI_CHARSET, "CAIRO_WIN32_FONT_CHARSET_ANSI");
    REGISTER_WIN32_LONG_CONST(cairowin32fontcharset, "BALTIC", BALTIC_CHARSET, "CAIRO_WIN32_FONT_CHARSET_BALTIC");
    REGISTER_WIN32_LONG_CONST(cairowin32fontcharset, "CHINESEBIG5", CHINESEBIG5_CHARSET, "CAIRO_WIN32_FONT_CHARSET_CHINESEBIG5");
    REGISTER_WIN32_LONG_CONST(cairowin32fontcharset, "DEFAULT", DEFAULT_CHARSET, "CAIRO_WIN32_FONT_CHARSET_DEFAULT");
    REGISTER_WIN32_LONG_CONST(cairowin32fontcharset, "EASTEUROPE", EASTEUROPE_CHARSET, "CAIRO_WIN32_FONT_CHARSET_EASTEUROPE");
    REGISTER_WIN32_LONG_CONST(cairowin32fontcharset, "GB2312", GB2312_CHARSET, "CAIRO_WIN32_FONT_CHARSET_GB2312");
    REGISTER_WIN32_LONG_CONST(cairowin32fontcharset, "GREEK", GREEK_CHARSET, "CAIRO_WIN32_FONT_CHARSET_GREEK");
    REGISTER_WIN32_LONG_CONST(cairowin32fontcharset, "HANGUL", HANGUL_CHARSET, "CAIRO_WIN32_FONT_CHARSET_HANGUL");
    REGISTER_WIN32_LONG_CONST(cairowin32fontcharset, "MAC", MAC_CHARSET, "CAIRO_WIN32_FONT_CHARSET_MAC");
    REGISTER_WIN32_LONG_CONST(cairowin32fontcharset, "OEM", OEM_CHARSET, "CAIRO_WIN32_FONT_CHARSET_OEM");
    REGISTER_WIN32_LONG_CONST(cairowin32fontcharset, "RUSSIAN", RUSSIAN_CHARSET, "CAIRO_WIN32_FONT_CHARSET_RUSSIAN");
    REGISTER_WIN32_LONG_CONST(cairowin32fontcharset, "SHIFTJIS", SHIFTJIS_CHARSET, "CAIRO_WIN32_FONT_CHARSET_SHIFTJIS");
    REGISTER_WIN32_LONG_CONST(cairowin32fontcharset, "SYMBOL", SYMBOL_CHARSET, "CAIRO_WIN32_FONT_CHARSET_SYMBOL");
    REGISTER_WIN32_LONG_CONST(cairowin32fontcharset, "TURKISH", TURKISH_CHARSET, "CAIRO_WIN32_FONT_CHARSET_TURKISH");
    REGISTER_WIN32_LONG_CONST(cairowin32fontcharset, "VIETNAMESE", VIETNAMESE_CHARSET, "CAIRO_WIN32_FONT_CHARSET_VIETNAMESE");
#if(WINVER >= 0x0400)
    REGISTER_WIN32_LONG_CONST(cairowin32fontcharset, "JOHAB", JOHAB_CHARSET, "CAIRO_WIN32_FONT_CHARSET_JOHAB");
    REGISTER_WIN32_LONG_CONST(cairowin32fontcharset, "ARABIC", ARABIC_CHARSET, "CAIRO_WIN32_FONT_CHARSET_ARABIC");
    REGISTER_WIN32_LONG_CONST(cairowin32fontcharset, "HEBREW", HEBREW_CHARSET, "CAIRO_WIN32_FONT_CHARSET_HEBREW");
    REGISTER_WIN32_LONG_CONST(cairowin32fontcharset, "THAI", THAI_CHARSET, "CAIRO_WIN32_FONT_CHARSET_THAI");
#endif /** WINVER */

    INIT_CLASS_ENTRY(ce_cairowin32fontoutprec, "CairoWin32FontOutputPrecision", NULL);
    cairo_ce_cairowin32fontoutprec = zend_register_internal_class(&ce_cairowin32fontoutprec TSRMLS_CC);
    cairo_ce_cairowin32fontoutprec->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS | ZEND_ACC_FINAL_CLASS;
    REGISTER_WIN32_LONG_CONST(cairowin32fontoutprec, "CHARACTER", OUT_CHARACTER_PRECIS, "CAIRO_WIN32_FONT_OUT_PRECISION_CHARACTER");
    REGISTER_WIN32_LONG_CONST(cairowin32fontoutprec, "DEFAULT", OUT_DEFAULT_PRECIS, "CAIRO_WIN32_FONT_OUT_PRECISION_DEFAULT");
    REGISTER_WIN32_LONG_CONST(cairowin32fontoutprec, "DEVICE", OUT_DEVICE_PRECIS, "CAIRO_WIN32_FONT_OUT_PRECISION_DEVICE");
    REGISTER_WIN32_LONG_CONST(cairowin32fontoutprec, "OUTLINE", OUT_OUTLINE_PRECIS, "CAIRO_WIN32_FONT_OUT_PRECISION_OUTLINE");
    REGISTER_WIN32_LONG_CONST(cairowin32fontoutprec, "PS_ONLY", OUT_PS_ONLY_PRECIS, "CAIRO_WIN32_FONT_OUT_PRECISION_PS_ONLY");
    REGISTER_WIN32_LONG_CONST(cairowin32fontoutprec, "RASTER", OUT_RASTER_PRECIS, "CAIRO_WIN32_FONT_OUT_PRECISION_RASTER");
    REGISTER_WIN32_LONG_CONST(cairowin32fontoutprec, "STRING", OUT_STRING_PRECIS, "CAIRO_WIN32_FONT_OUT_PRECISION_STRING");
    REGISTER_WIN32_LONG_CONST(cairowin32fontoutprec, "STROKE", OUT_STROKE_PRECIS, "CAIRO_WIN32_FONT_OUT_PRECISION_STROKE");
    REGISTER_WIN32_LONG_CONST(cairowin32fontoutprec, "TT_ONLY", OUT_TT_ONLY_PRECIS, "CAIRO_WIN32_FONT_OUT_PRECISION_TT_ONLY");
    REGISTER_WIN32_LONG_CONST(cairowin32fontoutprec, "TT", OUT_TT_PRECIS, "CAIRO_WIN32_FONT_OUT_PRECISION_TT");

    INIT_CLASS_ENTRY(ce_cairowin32fontclipprec, "CairoWin32FontClipPrecision", NULL);
    cairo_ce_cairowin32fontclipprec = zend_register_internal_class(&ce_cairowin32fontclipprec TSRMLS_CC);
    cairo_ce_cairowin32fontclipprec->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS | ZEND_ACC_FINAL_CLASS;
    REGISTER_WIN32_LONG_CONST(cairowin32fontclipprec, "CHARACTER", CLIP_CHARACTER_PRECIS, "CAIRO_WIN32_FONT_CLIP_PRECISION_CHARACTER");
    REGISTER_WIN32_LONG_CONST(cairowin32fontclipprec, "DEFAULT", CLIP_DEFAULT_PRECIS, "CAIRO_WIN32_FONT_CLIP_PRECISION_DEFAULT");
#if (_WIN32_WINNT >= _WIN32_WINNT_LONGHORN)
    REGISTER_WIN32_LONG_CONST(cairowin32fontclipprec, "DFA_DISABLE", CLIP_DFA_DISABLE);
#endif /** _WIN32_WINNT >= _WIN32_WINNT_LONGHORN */
    REGISTER_WIN32_LONG_CONST(cairowin32fontclipprec, "EMBEDDED", CLIP_EMBEDDED, "CAIRO_WIN32_FONT_CLIP_PRECISION_EMBEDDED");
    REGISTER_WIN32_LONG_CONST(cairowin32fontclipprec, "LH_ANGLES", CLIP_LH_ANGLES, "CAIRO_WIN32_FONT_CLIP_PRECISION_LH_ANGLES");
    REGISTER_WIN32_LONG_CONST(cairowin32fontclipprec, "MASK", CLIP_MASK, "CAIRO_WIN32_FONT_CLIP_PRECISION_MASK");
#if (_WIN32_WINNT >= _WIN32_WINNT_LONGHORN)
    REGISTER_WIN32_LONG_CONST(cairowin32fontclipprec, "DFA_OVERRIDE", CLIP_DFA_OVERRIDE);
#endif /** _WIN32_WINNT >= _WIN32_WINNT_LONGHORN */
    REGISTER_WIN32_LONG_CONST(cairowin32fontclipprec, "STROKE", CLIP_STROKE_PRECIS, "CAIRO_WIN32_FONT_CLIP_PRECISION_STROKE");
    REGISTER_WIN32_LONG_CONST(cairowin32fontclipprec, "TT_ALWAYS", CLIP_TT_ALWAYS, "CAIRO_WIN32_FONT_CLIP_PRECISION_TT_ALWAYS");

    INIT_CLASS_ENTRY(ce_cairowin32fontquality, "CairoWin32FontQuality", NULL);
    cairo_ce_cairowin32fontquality = zend_register_internal_class(&ce_cairowin32fontquality TSRMLS_CC);
    cairo_ce_cairowin32fontquality->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS | ZEND_ACC_FINAL_CLASS;
    REGISTER_WIN32_LONG_CONST(cairowin32fontquality, "ANTIALIASED", ANTIALIASED_QUALITY, "CAIRO_WIN32_FONT_QUALITY_ANTIALIASED");
    REGISTER_WIN32_LONG_CONST(cairowin32fontquality, "CLEARTYPE", CLEARTYPE_QUALITY, "CAIRO_WIN32_FONT_QUALITY_CLEARTYPE");
    REGISTER_WIN32_LONG_CONST(cairowin32fontquality, "DEFAULT", DEFAULT_QUALITY, "CAIRO_WIN32_FONT_QUALITY_DEFAULT");
    REGISTER_WIN32_LONG_CONST(cairowin32fontquality, "DRAFT", DRAFT_QUALITY, "CAIRO_WIN32_FONT_QUALITY_DRAFT");
    REGISTER_WIN32_LONG_CONST(cairowin32fontquality, "NONANTIALIASED", NONANTIALIASED_QUALITY, "CAIRO_WIN32_FONT_QUALITY_NONANTIALIASED");
    REGISTER_WIN32_LONG_CONST(cairowin32fontquality, "PROOF", PROOF_QUALITY, "CAIRO_WIN32_FONT_QUALITY_PROOF");

    INIT_CLASS_ENTRY(ce_cairowin32fontpitch, "CairoWin32FontPitch", NULL);
    cairo_ce_cairowin32fontpitch = zend_register_internal_class(&ce_cairowin32fontpitch TSRMLS_CC);
    cairo_ce_cairowin32fontpitch->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS | ZEND_ACC_FINAL_CLASS;
    REGISTER_WIN32_LONG_CONST(cairowin32fontpitch, "DEFAULT", DEFAULT_PITCH, "CAIRO_WIN32_FONT_PITCH_DEFAULT");
    REGISTER_WIN32_LONG_CONST(cairowin32fontpitch, "FIXED", FIXED_PITCH, "CAIRO_WIN32_FONT_PITCH_FIXED");
    REGISTER_WIN32_LONG_CONST(cairowin32fontpitch, "VARIABLE", VARIABLE_PITCH, "CAIRO_WIN32_FONT_PITCH_VARIABLE");

    INIT_CLASS_ENTRY(ce_cairowin32fontfamily, "CairoWin32FontFamily", NULL);
    cairo_ce_cairowin32fontfamily = zend_register_internal_class(&ce_cairowin32fontfamily TSRMLS_CC);
    cairo_ce_cairowin32fontfamily->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS | ZEND_ACC_FINAL_CLASS;
    REGISTER_WIN32_LONG_CONST(cairowin32fontfamily, "DECORATIVE", FF_DECORATIVE, "CAIRO_WIN32_FONT_FAMILY_DECORATIVE");
    REGISTER_WIN32_LONG_CONST(cairowin32fontfamily, "DONTCARE", FF_DONTCARE, "CAIRO_WIN32_FONT_FAMILY_DONTCARE");
    REGISTER_WIN32_LONG_CONST(cairowin32fontfamily, "MODERN", FF_MODERN, "CAIRO_WIN32_FONT_FAMILY_MODERN");
    REGISTER_WIN32_LONG_CONST(cairowin32fontfamily, "ROMAN", FF_ROMAN, "CAIRO_WIN32_FONT_FAMILY_ROMAN");
    REGISTER_WIN32_LONG_CONST(cairowin32fontfamily, "SCRIPT", FF_SCRIPT, "CAIRO_WIN32_FONT_FAMILY_SCRIPT");
    REGISTER_WIN32_LONG_CONST(cairowin32fontfamily, "SWISS", FF_SWISS, "CAIRO_WIN32_FONT_FAMILY_SWISS");

    return SUCCESS;
}

#endif /** CAIRO_HAS_WIN32_FONT */
