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


#if defined(CAIRO_HAS_WIN32_FONT) && defined(HAVE_WIN32_FONT)

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


#define LFONT_FIND_LONG(name, defaultval) \
    if ((tmp = zend_hash_str_find(Z_ARRVAL_P(font_options), #name, sizeof(#name)-1)) != NULL) { \
        if (Z_TYPE_P(tmp) != IS_LONG) \
            zend_error(E_WARNING, "cairo_win32_font_face_create() expects key '"#name"' to be of type long"); \
        else \
            lfont.##name = Z_LVAL_P(tmp); \
    } \
    else \
        lfont.##name = defaultval;
        
/** Same as before but casts return to BYTE */
#define LFONT_FIND_LONGB(name, defaultval) \
    if ((tmp = zend_hash_str_find(Z_ARRVAL_P(font_options), #name, sizeof(#name)-1)) != NULL) { \
        if (Z_TYPE_P(tmp) != IS_LONG) \
            zend_error(E_WARNING, "cairo_win32_font_face_create() expects key '"#name"' to be of type long"); \
        else \
            lfont.##name = (BYTE)Z_LVAL_P(tmp); \
    } \
    else \
        lfont.##name = (BYTE)defaultval;
            
#define LFONT_FIND_BOOL(name, defaultval) \
    if ((tmp = zend_hash_str_find(Z_ARRVAL_P(font_options), #name, sizeof(#name)-1)) != NULL) { \
        if (Z_TYPE_P(tmp) != IS_TRUE && Z_TYPE_P(tmp) != IS_FALSE) \
            zend_error(E_WARNING, "cairo_win32_font_face_create() expects key '"#name"' to be of type bool"); \
        else \
            lfont.##name = Z_TYPE_P(tmp) == IS_TRUE ? 1 : 0; \
    } \
    else \
        lfont.##name = defaultval;

zend_class_entry *ce_cairo_win32font;
/** These classes are containers for constants defined in WinGdi.h, etc. */
static zend_class_entry *ce_cairo_win32fontweight;
static zend_class_entry *ce_cairo_win32fontcharset;
/** output precision constants */
static zend_class_entry *ce_cairo_win32fontoutprec;
/** clip precision constants */
static zend_class_entry *ce_cairo_win32fontclipprec;
static zend_class_entry *ce_cairo_win32fontquality;
static zend_class_entry *ce_cairo_win32fontpitch;
static zend_class_entry *ce_cairo_win32fontfamily;
static zend_object_handlers cairo_win32_font_face_object_handlers;

/**
 * CairoWin32FontFace::__construct takes 1 optional argument
 */
ZEND_BEGIN_ARG_INFO_EX(CairoWin32FontFace_construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
    ZEND_ARG_INFO(0, font_options)
ZEND_END_ARG_INFO()

/* {{{ proto CairoWin32FontFace::__construct([array font_options])
       Creates a new font face for the Win32 backend */
PHP_METHOD(CairoWin32FontFace, __construct)
{
    cairo_font_face_object *font_face;
    LOGFONT     lfont;
    HFONT       hfont;
    zval        *font_options = NULL;
    zval        *tmp;
    //char        *font_name = NULL;          
    
    if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "|a", &font_options) == FAILURE) {
        return;
    }

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

        if ((tmp = zend_hash_str_find(Z_ARRVAL_P(font_options), "lfFaceName", sizeof("lfFaceName")-1)) != NULL) {
            if (Z_TYPE_P(tmp) != IS_STRING) {
                zend_error(E_WARNING, "cairo\\FontFace\\Win32::__construct() expects key 'lfFaceName' to be of type string");
            } else {
                lstrcpy(lfont.lfFaceName, Z_STRVAL_P(tmp));
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
    
    font_face = Z_CAIRO_FONT_FACE_P(getThis());
    font_face->font_face = cairo_win32_font_face_create_for_hfont(hfont);

    php_cairo_throw_exception(cairo_font_face_status(font_face->font_face));
}
/* }}} */

/* ----------------------------------------------------------------
    Cairo\Win32FontFace Definition and registration
------------------------------------------------------------------*/

const zend_function_entry cairo_win32_font_methods[] = {
    PHP_ME(CairoWin32FontFace, __construct, CairoWin32FontFace_construct_args, \
        ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    ZEND_FE_END
};

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
    
    INIT_NS_CLASS_ENTRY(ce, CAIRO_NAMESPACE, ZEND_NS_NAME("FontFace", "Win32"), cairo_win32_font_methods);
    ce_cairo_win32font = zend_register_internal_class_ex(&ce, ce_cairo_fontface);
    
    #define CAIRO_WIN32_DECLARE_ENUM(ce, const_name, const_value) \
        zend_declare_class_constant_long(ce_cairo_win32font##ce, #const_name, sizeof(#const_name)-1, (long)const_value);
    
    INIT_NS_CLASS_ENTRY(ce_cairowin32fontweight, CAIRO_NAMESPACE, ZEND_NS_NAME("FontFace", ZEND_NS_NAME("Win32", "FontWeight")), NULL);
    ce_cairo_win32fontweight = zend_register_internal_class_ex(&ce_cairowin32fontweight, php_eos_datastructures_get_enum_ce());
    ce_cairo_win32fontweight->ce_flags |= ZEND_ACC_FINAL;
    CAIRO_WIN32_DECLARE_ENUM(weight, "NORMAL", "CAIRO_WIN32_FONT_WEIGHT_NORMAL");
    CAIRO_WIN32_DECLARE_ENUM(weight, "DONTCARE", "CAIRO_WIN32_FONT_WEIGHT_DONTCARE");
    CAIRO_WIN32_DECLARE_ENUM(weight, "THIN", "CAIRO_WIN32_FONT_WEIGHT_THIN");
    CAIRO_WIN32_DECLARE_ENUM(weight, "EXTRALIGHT", "CAIRO_WIN32_FONT_WEIGHT_EXTRALIGHT");
    CAIRO_WIN32_DECLARE_ENUM(weight, "ULTRALIGHT", "CAIRO_WIN32_FONT_WEIGHT_ULTRALIGHT");
    CAIRO_WIN32_DECLARE_ENUM(weight, "LIGHT", "CAIRO_WIN32_FONT_WEIGHT_LIGHT");
    CAIRO_WIN32_DECLARE_ENUM(weight, "REGULAR", "CAIRO_WIN32_FONT_WEIGHT_REGULAR");
    CAIRO_WIN32_DECLARE_ENUM(weight, "MEDIUM", "CAIRO_WIN32_FONT_WEIGHT_MEDIUM");
    CAIRO_WIN32_DECLARE_ENUM(weight, "SEMIBOLD", "CAIRO_WIN32_FONT_WEIGHT_SEMIBOLD");
    CAIRO_WIN32_DECLARE_ENUM(weight, "DEMIBOLD", "CAIRO_WIN32_FONT_WEIGHT_DEMIBOLD");
    CAIRO_WIN32_DECLARE_ENUM(weight, "BOLD", "CAIRO_WIN32_FONT_WEIGHT_BOLD");
    CAIRO_WIN32_DECLARE_ENUM(weight, "EXTRABOLD", "CAIRO_WIN32_FONT_WEIGHT_EXTRABOLD");
    CAIRO_WIN32_DECLARE_ENUM(weight, "ULTRABOLD", "CAIRO_WIN32_FONT_WEIGHT_ULTRABOLD");
    CAIRO_WIN32_DECLARE_ENUM(weight, "HEAVY", "CAIRO_WIN32_FONT_WEIGHT_HEAVY");
    CAIRO_WIN32_DECLARE_ENUM(weight, "BLACK", "CAIRO_WIN32_FONT_WEIGHT_BLACK");

    INIT_NS_CLASS_ENTRY(ce_cairowin32fontcharset, CAIRO_NAMESPACE, ZEND_NS_NAME("FontFace", ZEND_NS_NAME("Win32", "FontCharset")), NULL);
    ce_cairo_win32fontcharset = zend_register_internal_class_ex(&ce_cairowin32fontcharset, php_eos_datastructures_get_enum_ce());
    ce_cairo_win32fontcharset->ce_flags |= ZEND_ACC_FINAL;
    CAIRO_WIN32_DECLARE_ENUM(charset, "ANSI", ANSI_CHARSET, "CAIRO_WIN32_FONT_CHARSET_ANSI");
    CAIRO_WIN32_DECLARE_ENUM(charset, "BALTIC", BALTIC_CHARSET, "CAIRO_WIN32_FONT_CHARSET_BALTIC");
    CAIRO_WIN32_DECLARE_ENUM(charset, "CHINESEBIG5", CHINESEBIG5_CHARSET, "CAIRO_WIN32_FONT_CHARSET_CHINESEBIG5");
    CAIRO_WIN32_DECLARE_ENUM(charset, "DEFAULT", DEFAULT_CHARSET, "CAIRO_WIN32_FONT_CHARSET_DEFAULT");
    CAIRO_WIN32_DECLARE_ENUM(charset, "EASTEUROPE", EASTEUROPE_CHARSET, "CAIRO_WIN32_FONT_CHARSET_EASTEUROPE");
    CAIRO_WIN32_DECLARE_ENUM(charset, "GB2312", GB2312_CHARSET, "CAIRO_WIN32_FONT_CHARSET_GB2312");
    CAIRO_WIN32_DECLARE_ENUM(charset, "GREEK", GREEK_CHARSET, "CAIRO_WIN32_FONT_CHARSET_GREEK");
    CAIRO_WIN32_DECLARE_ENUM(charset, "HANGUL", HANGUL_CHARSET, "CAIRO_WIN32_FONT_CHARSET_HANGUL");
    CAIRO_WIN32_DECLARE_ENUM(charset, "MAC", MAC_CHARSET, "CAIRO_WIN32_FONT_CHARSET_MAC");
    CAIRO_WIN32_DECLARE_ENUM(charset, "OEM", OEM_CHARSET, "CAIRO_WIN32_FONT_CHARSET_OEM");
    CAIRO_WIN32_DECLARE_ENUM(charset, "RUSSIAN", RUSSIAN_CHARSET, "CAIRO_WIN32_FONT_CHARSET_RUSSIAN");
    CAIRO_WIN32_DECLARE_ENUM(charset, "SHIFTJIS", SHIFTJIS_CHARSET, "CAIRO_WIN32_FONT_CHARSET_SHIFTJIS");
    CAIRO_WIN32_DECLARE_ENUM(charset, "SYMBOL", SYMBOL_CHARSET, "CAIRO_WIN32_FONT_CHARSET_SYMBOL");
    CAIRO_WIN32_DECLARE_ENUM(charset, "TURKISH", TURKISH_CHARSET, "CAIRO_WIN32_FONT_CHARSET_TURKISH");
    CAIRO_WIN32_DECLARE_ENUM(charset, "VIETNAMESE", VIETNAMESE_CHARSET, "CAIRO_WIN32_FONT_CHARSET_VIETNAMESE");
#if(WINVER >= 0x0400)
    CAIRO_WIN32_DECLARE_ENUM(charset, "JOHAB", JOHAB_CHARSET, "CAIRO_WIN32_FONT_CHARSET_JOHAB");
    CAIRO_WIN32_DECLARE_ENUM(charset, "ARABIC", ARABIC_CHARSET, "CAIRO_WIN32_FONT_CHARSET_ARABIC");
    CAIRO_WIN32_DECLARE_ENUM(charset, "HEBREW", HEBREW_CHARSET, "CAIRO_WIN32_FONT_CHARSET_HEBREW");
    CAIRO_WIN32_DECLARE_ENUM(charset, "THAI", THAI_CHARSET, "CAIRO_WIN32_FONT_CHARSET_THAI");
#endif /** WINVER */

    INIT_NS_CLASS_ENTRY(ce_cairowin32fontoutprec, CAIRO_NAMESPACE, ZEND_NS_NAME("FontFace", ZEND_NS_NAME("Win32", "FontOutputPrecision")), NULL);
    ce_cairo_win32fontoutprec = zend_register_internal_class_ex(&ce_cairowin32fontoutprec, php_eos_datastructures_get_enum_ce());
    ce_cairo_win32fontoutprec->ce_flags |= ZEND_ACC_FINAL;
    CAIRO_WIN32_DECLARE_ENUM(outprec, "CHARACTER", OUT_CHARACTER_PRECIS, "CAIRO_WIN32_FONT_OUT_PRECISION_CHARACTER");
    CAIRO_WIN32_DECLARE_ENUM(outprec, "DEFAULT", OUT_DEFAULT_PRECIS, "CAIRO_WIN32_FONT_OUT_PRECISION_DEFAULT");
    CAIRO_WIN32_DECLARE_ENUM(outprec, "DEVICE", OUT_DEVICE_PRECIS, "CAIRO_WIN32_FONT_OUT_PRECISION_DEVICE");
    CAIRO_WIN32_DECLARE_ENUM(outprec, "OUTLINE", OUT_OUTLINE_PRECIS, "CAIRO_WIN32_FONT_OUT_PRECISION_OUTLINE");
    CAIRO_WIN32_DECLARE_ENUM(outprec, "PS_ONLY", OUT_PS_ONLY_PRECIS, "CAIRO_WIN32_FONT_OUT_PRECISION_PS_ONLY");
    CAIRO_WIN32_DECLARE_ENUM(outprec, "RASTER", OUT_RASTER_PRECIS, "CAIRO_WIN32_FONT_OUT_PRECISION_RASTER");
    CAIRO_WIN32_DECLARE_ENUM(outprec, "STRING", OUT_STRING_PRECIS, "CAIRO_WIN32_FONT_OUT_PRECISION_STRING");
    CAIRO_WIN32_DECLARE_ENUM(outprec, "STROKE", OUT_STROKE_PRECIS, "CAIRO_WIN32_FONT_OUT_PRECISION_STROKE");
    CAIRO_WIN32_DECLARE_ENUM(outprec, "TT_ONLY", OUT_TT_ONLY_PRECIS, "CAIRO_WIN32_FONT_OUT_PRECISION_TT_ONLY");
    CAIRO_WIN32_DECLARE_ENUM(outprec, "TT", OUT_TT_PRECIS, "CAIRO_WIN32_FONT_OUT_PRECISION_TT");

    INIT_NS_CLASS_ENTRY(ce_cairowin32fontclipprec, CAIRO_NAMESPACE, ZEND_NS_NAME("FontFace", ZEND_NS_NAME("Win32", "FontClipPrecision")), NULL);
    ce_cairo_win32fontclipprec = zend_register_internal_class_ex(&ce_cairowin32fontclipprec, php_eos_datastructures_get_enum_ce());
    ce_cairo_win32fontclipprec->ce_flags |= ZEND_ACC_FINAL;
    CAIRO_WIN32_DECLARE_ENUM(clipprec, "CHARACTER", CLIP_CHARACTER_PRECIS, "CAIRO_WIN32_FONT_CLIP_PRECISION_CHARACTER");
    CAIRO_WIN32_DECLARE_ENUM(clipprec, "DEFAULT", CLIP_DEFAULT_PRECIS, "CAIRO_WIN32_FONT_CLIP_PRECISION_DEFAULT");
#if (_WIN32_WINNT >= _WIN32_WINNT_LONGHORN)
    CAIRO_WIN32_DECLARE_ENUM(clipprec, "DFA_DISABLE", CLIP_DFA_DISABLE, "CAIRO_WIN32_FONT_CLIP_DFA_DISABLE");
#endif /** _WIN32_WINNT >= _WIN32_WINNT_LONGHORN */
    CAIRO_WIN32_DECLARE_ENUM(clipprec, "EMBEDDED", CLIP_EMBEDDED, "CAIRO_WIN32_FONT_CLIP_PRECISION_EMBEDDED");
    CAIRO_WIN32_DECLARE_ENUM(clipprec, "LH_ANGLES", CLIP_LH_ANGLES, "CAIRO_WIN32_FONT_CLIP_PRECISION_LH_ANGLES");
    CAIRO_WIN32_DECLARE_ENUM(clipprec, "MASK", CLIP_MASK, "CAIRO_WIN32_FONT_CLIP_PRECISION_MASK");
#if (_WIN32_WINNT >= _WIN32_WINNT_LONGHORN)
    /* No idea where this is defined. */
    /* CAIRO_WIN32_DECLARE_ENUM(clipprec, "DFA_OVERRIDE", CLIP_DFA_OVERRIDE); */
#endif /** _WIN32_WINNT >= _WIN32_WINNT_LONGHORN */
    CAIRO_WIN32_DECLARE_ENUM(clipprec, "STROKE", CLIP_STROKE_PRECIS, "CAIRO_WIN32_FONT_CLIP_PRECISION_STROKE");
    CAIRO_WIN32_DECLARE_ENUM(clipprec, "TT_ALWAYS", CLIP_TT_ALWAYS, "CAIRO_WIN32_FONT_CLIP_PRECISION_TT_ALWAYS");

    INIT_NS_CLASS_ENTRY(ce_cairowin32fontquality, CAIRO_NAMESPACE, ZEND_NS_NAME("FontFace", ZEND_NS_NAME("Win32", "FontQuality")), NULL);
    ce_cairo_win32fontquality = zend_register_internal_class_ex(&ce_cairowin32fontquality, php_eos_datastructures_get_enum_ce());
    ce_cairo_win32fontquality->ce_flags |= ZEND_ACC_FINAL;
    CAIRO_WIN32_DECLARE_ENUM(quality, "ANTIALIASED", ANTIALIASED_QUALITY, "CAIRO_WIN32_FONT_QUALITY_ANTIALIASED");
    CAIRO_WIN32_DECLARE_ENUM(quality, "CLEARTYPE", CLEARTYPE_QUALITY, "CAIRO_WIN32_FONT_QUALITY_CLEARTYPE");
    CAIRO_WIN32_DECLARE_ENUM(quality, "DEFAULT", DEFAULT_QUALITY, "CAIRO_WIN32_FONT_QUALITY_DEFAULT");
    CAIRO_WIN32_DECLARE_ENUM(quality, "DRAFT", DRAFT_QUALITY, "CAIRO_WIN32_FONT_QUALITY_DRAFT");
    CAIRO_WIN32_DECLARE_ENUM(quality, "NONANTIALIASED", NONANTIALIASED_QUALITY, "CAIRO_WIN32_FONT_QUALITY_NONANTIALIASED");
    CAIRO_WIN32_DECLARE_ENUM(quality, "PROOF", PROOF_QUALITY, "CAIRO_WIN32_FONT_QUALITY_PROOF");

    INIT_NS_CLASS_ENTRY(ce_cairowin32fontpitch, CAIRO_NAMESPACE, ZEND_NS_NAME("FontFace", ZEND_NS_NAME("Win32", "FontPitch")), NULL);
    ce_cairo_win32fontpitch = zend_register_internal_class_ex(&ce_cairowin32fontpitch, php_eos_datastructures_get_enum_ce());
    ce_cairo_win32fontpitch->ce_flags |= ZEND_ACC_FINAL;
    CAIRO_WIN32_DECLARE_ENUM(pitch, "DEFAULT", DEFAULT_PITCH, "CAIRO_WIN32_FONT_PITCH_DEFAULT");
    CAIRO_WIN32_DECLARE_ENUM(pitch, "FIXED", FIXED_PITCH, "CAIRO_WIN32_FONT_PITCH_FIXED");
    CAIRO_WIN32_DECLARE_ENUM(pitch, "VARIABLE", VARIABLE_PITCH, "CAIRO_WIN32_FONT_PITCH_VARIABLE");

    INIT_NS_CLASS_ENTRY(ce_cairowin32fontfamily, CAIRO_NAMESPACE, ZEND_NS_NAME("FontFace", ZEND_NS_NAME("Win32", "FontFamily")), NULL);
    ce_cairo_win32fontfamily = zend_register_internal_class_ex(&ce_cairowin32fontfamily, php_eos_datastructures_get_enum_ce());
    ce_cairo_win32fontfamily->ce_flags |= ZEND_ACC_FINAL;
    CAIRO_WIN32_DECLARE_ENUM(family, "DECORATIVE", FF_DECORATIVE, "CAIRO_WIN32_FONT_FAMILY_DECORATIVE");
    CAIRO_WIN32_DECLARE_ENUM(family, "DONTCARE", FF_DONTCARE, "CAIRO_WIN32_FONT_FAMILY_DONTCARE");
    CAIRO_WIN32_DECLARE_ENUM(family, "MODERN", FF_MODERN, "CAIRO_WIN32_FONT_FAMILY_MODERN");
    CAIRO_WIN32_DECLARE_ENUM(family, "ROMAN", FF_ROMAN, "CAIRO_WIN32_FONT_FAMILY_ROMAN");
    CAIRO_WIN32_DECLARE_ENUM(family, "SCRIPT", FF_SCRIPT, "CAIRO_WIN32_FONT_FAMILY_SCRIPT");
    CAIRO_WIN32_DECLARE_ENUM(family, "SWISS", FF_SWISS, "CAIRO_WIN32_FONT_FAMILY_SWISS");
    
    return SUCCESS;
}

#endif /** CAIRO_HAS_WIN32_FONT */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
 