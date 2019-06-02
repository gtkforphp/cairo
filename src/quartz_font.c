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

#if defined(CAIRO_HAS_QUARTZ_FONT)

#include <cairo-quartz.h>
#include <ApplicationServices/ApplicationServices.h>

	zend_class_entry *ce_cairo_quartzfont;
	zend_class_entry *ce_cairo_quartzatsufontnamecode;
	zend_class_entry *ce_cairo_quartzatsufontnameplatform;


/* {{{ proto CairoQuartzFontFace CairoQuartzFontFace::createForAtsuFontId(string font_name[, int code, int platform, int script, int language])
   Takes parameters from the user an attempts to look up an atsu font id
   If that is successful it creates a new quartz font face from the resulting Id 
   http://developer.apple.com/documentation/Carbon/Reference/ATSUI_Reference/Reference/reference.html#/apple_ref/c/func/ATSUFindFontFromName
   */
PHP_METHOD(CairoQuartzFontFace, createForAtsuFontId)
{
        ATSUFontID fontID;
        //OSStatus error;
        const char *font_name;
	int font_name_length;
	FontNameCode code = kFontFullName;
	FontPlatformCode platform = kFontNoPlatformCode;
	FontScriptCode script = kFontRomanScript;
	FontLanguageCode language = kFontNoLanguageCode;
        
	cairo_font_face_object *font_face_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "s|llll", &font_name, &font_name_length, &code, &platform, &script, &language) == FAILURE) {
		return;
	}

	ATSUFindFontFromName(font_name, font_name_length, code, platform, script, language, &fontID);

	if(fontID == kATSUInvalidFontID) {
		php_cairo_throw_exception("Atsu Font could not be retrieved");
		return;
	}

        font_face_object = Z_CAIRO_FONT_FACE_P(getThis());
        
        if(!font_face_object) {
            return;
        }
        
        object_init_ex(return_value, ce_cairo_quartzfont);

	font_face_object->font_face = cairo_quartz_font_face_create_for_atsu_font_id(fontID);
	php_cairo_throw_exception(cairo_font_face_status(font_face_object->font_face));
}

/* {{{ proto CairoQuartzFontFace CairoQuartzFontFace::createForCgfont(string font_name[, int code, int platform, int script, int language])
   Takes parameters from the user and attempts to create a ctfontref
   If that is successful it creates a new quartz font face from the resulting Id 
   http://developer.apple.com/documentation/graphicsimaging/Reference/CGFont/Reference/reference.html#/apple_ref/c/func/CGFontCreateWithFontName
   */
PHP_METHOD(CairoQuartzFontFace, createForCgfont)
{
	CFStringRef font_name;
	char * c_font_name;
        size_t c_font_name_len;
	cairo_font_face_object *font_face_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "s", &c_font_name, &c_font_name_len) == FAILURE) {
		return;
	}

	font_face_object = Z_CAIRO_FONT_FACE_P(getThis());
        
        if(!font_face_object) {
            return;
        }
        
        object_init_ex(return_value, ce_cairo_quartzfont);

	/* Create our CFStringRef for the call */
	font_name = CFStringCreateWithCString(NULL, c_font_name, kCFStringEncodingMacRoman);

	/* Try to grab our new font ref */
	font_face_object->quartzref = CGFontCreateWithFontName(font_name);

	/* We are done with our CFStringRef so we free it - the null check is so we don't crash*/
	if (font_name != NULL)
		CFRelease(font_name);

	/* Now actually do the cairo call */
	font_face_object->font_face = cairo_quartz_font_face_create_for_cgfont(font_face_object->quartzref);
	php_cairo_throw_exception(cairo_font_face_status(font_face_object->font_face));
}

/* }}} */

/* {{{ cairo_quartz_font_methods[] */
const zend_function_entry cairo_quartz_font_methods[] = {
	PHP_ME(CairoQuartzFontFace, createForCgfont, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(CairoQuartzFontFace, createForAtsuFontId, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_FE_END
};
/* }}} */

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(cairo_quartz_font)
{
        zend_class_entry quartz_font_face_ce, fontname_ce, platform_ce;
        
        INIT_NS_CLASS_ENTRY(quartz_font_face_ce, CAIRO_NAMESPACE, ZEND_NS_NAME("FontFace", "Quartz"), cairo_quartz_font_methods);
	ce_cairo_quartzfont = zend_register_internal_class_ex(&quartz_font_face_ce, ce_cairo_fontface);
        
        /* FontNameCode */
	INIT_NS_CLASS_ENTRY(fontname_ce, CAIRO_NAMESPACE, ZEND_NS_NAME("Quartz", "AtsuFontNameCode"), NULL);
	ce_cairo_quartzatsufontnamecode = zend_register_internal_class_ex(&fontname_ce, php_eos_datastructures_get_enum_ce());
	ce_cairo_quartzatsufontnamecode->ce_flags |= ZEND_ACC_FINAL;
        
        #define CAIRO_QUARTZ_FONT_CODE_DECLARE_ENUM(name) \
		zend_declare_class_constant_long(ce_cairo_quartzatsufontnamecode, #name, \
		sizeof(#name)-1, kFont## name);
        
        CAIRO_QUARTZ_FONT_CODE_DECLARE_ENUM(CopyrightName);
        CAIRO_QUARTZ_FONT_CODE_DECLARE_ENUM(FamilyName);
        CAIRO_QUARTZ_FONT_CODE_DECLARE_ENUM(StyleName);
        CAIRO_QUARTZ_FONT_CODE_DECLARE_ENUM(UniqueName);
        CAIRO_QUARTZ_FONT_CODE_DECLARE_ENUM(FullName);
        CAIRO_QUARTZ_FONT_CODE_DECLARE_ENUM(VersionName);
        CAIRO_QUARTZ_FONT_CODE_DECLARE_ENUM(PostscriptName);
        CAIRO_QUARTZ_FONT_CODE_DECLARE_ENUM(TrademarkName);
        CAIRO_QUARTZ_FONT_CODE_DECLARE_ENUM(ManufacturerName);
        CAIRO_QUARTZ_FONT_CODE_DECLARE_ENUM(DesignerName);
        CAIRO_QUARTZ_FONT_CODE_DECLARE_ENUM(DescriptionName);
        CAIRO_QUARTZ_FONT_CODE_DECLARE_ENUM(VendorURLName);
        CAIRO_QUARTZ_FONT_CODE_DECLARE_ENUM(DesignerURLName);
        CAIRO_QUARTZ_FONT_CODE_DECLARE_ENUM(LicenseDescriptionName);
        CAIRO_QUARTZ_FONT_CODE_DECLARE_ENUM(LicenseInfoURLName);

        /* PlatformCode */
        INIT_NS_CLASS_ENTRY(platform_ce, CAIRO_NAMESPACE, ZEND_NS_NAME("Quartz", "AtsuFontPlatformCode"), NULL);
	ce_cairo_quartzatsufontnameplatform = zend_register_internal_class_ex(&platform_ce, php_eos_datastructures_get_enum_ce());
	ce_cairo_quartzatsufontnameplatform->ce_flags |= ZEND_ACC_FINAL;
        
        #define CAIRO_QUARTZ_FONT_PLATFORM_DECLARE_ENUM(name) \
		zend_declare_class_constant_long(ce_cairo_quartzatsufontnameplatform, #name, \
		sizeof(#name)-1, kFont## name);

	CAIRO_QUARTZ_FONT_PLATFORM_DECLARE_ENUM(UnicodePlatform);
        CAIRO_QUARTZ_FONT_PLATFORM_DECLARE_ENUM(MacintoshPlatform);
        CAIRO_QUARTZ_FONT_PLATFORM_DECLARE_ENUM(ReservedPlatform);
        CAIRO_QUARTZ_FONT_PLATFORM_DECLARE_ENUM(MicrosoftPlatform);
        CAIRO_QUARTZ_FONT_PLATFORM_DECLARE_ENUM(CustomPlatform);

	/*	TODO: register these too - ugh
enum {
  kFontRomanScript              = 0,
  kFontJapaneseScript           = 1,
  kFontTraditionalChineseScript = 2,
  kFontChineseScript            = kFontTraditionalChineseScript,
  kFontKoreanScript             = 3,
  kFontArabicScript             = 4,
  kFontHebrewScript             = 5,
  kFontGreekScript              = 6,
  kFontCyrillicScript           = 7,
  kFontRussian                  = kFontCyrillicScript,
  kFontRSymbolScript            = 8,
  kFontDevanagariScript         = 9,
  kFontGurmukhiScript           = 10,
  kFontGujaratiScript           = 11,
  kFontOriyaScript              = 12,
  kFontBengaliScript            = 13,
  kFontTamilScript              = 14,
  kFontTeluguScript             = 15,
  kFontKannadaScript            = 16,
  kFontMalayalamScript          = 17,
  kFontSinhaleseScript          = 18,
  kFontBurmeseScript            = 19,
  kFontKhmerScript              = 20,
  kFontThaiScript               = 21,
  kFontLaotianScript            = 22,
  kFontGeorgianScript           = 23,
  kFontArmenianScript           = 24,
  kFontSimpleChineseScript      = 25,
  kFontTibetanScript            = 26,
  kFontMongolianScript          = 27,
  kFontGeezScript               = 28,
  kFontEthiopicScript           = kFontGeezScript,
  kFontAmharicScript            = kFontGeezScript,
  kFontSlavicScript             = 29,
  kFontEastEuropeanRomanScript  = kFontSlavicScript,
  kFontVietnameseScript         = 30,
  kFontExtendedArabicScript     = 31,
  kFontSindhiScript             = kFontExtendedArabicScript,
  kFontUninterpretedScript      = 32
};

enum {
  kFontEnglishLanguage          = 0,
  kFontFrenchLanguage           = 1,
  kFontGermanLanguage           = 2,
  kFontItalianLanguage          = 3,
  kFontDutchLanguage            = 4,
  kFontSwedishLanguage          = 5,
  kFontSpanishLanguage          = 6,
  kFontDanishLanguage           = 7,
  kFontPortugueseLanguage       = 8,
  kFontNorwegianLanguage        = 9,
  kFontHebrewLanguage           = 10,
  kFontJapaneseLanguage         = 11,
  kFontArabicLanguage           = 12,
  kFontFinnishLanguage          = 13,
  kFontGreekLanguage            = 14,
  kFontIcelandicLanguage        = 15,
  kFontMalteseLanguage          = 16,
  kFontTurkishLanguage          = 17,
  kFontCroatianLanguage         = 18,
  kFontTradChineseLanguage      = 19,
  kFontUrduLanguage             = 20,
  kFontHindiLanguage            = 21,
  kFontThaiLanguage             = 22,
  kFontKoreanLanguage           = 23,
  kFontLithuanianLanguage       = 24,
  kFontPolishLanguage           = 25,
  kFontHungarianLanguage        = 26,
  kFontEstonianLanguage         = 27,
  kFontLettishLanguage          = 28,
  kFontLatvianLanguage          = kFontLettishLanguage,
  kFontSaamiskLanguage          = 29,
  kFontLappishLanguage          = kFontSaamiskLanguage,
  kFontFaeroeseLanguage         = 30,
  kFontFarsiLanguage            = 31,
  kFontPersianLanguage          = kFontFarsiLanguage,
  kFontRussianLanguage          = 32,
  kFontSimpChineseLanguage      = 33,
  kFontFlemishLanguage          = 34,
  kFontIrishLanguage            = 35,
  kFontAlbanianLanguage         = 36,
  kFontRomanianLanguage         = 37,
  kFontCzechLanguage            = 38,
  kFontSlovakLanguage           = 39,
  kFontSlovenianLanguage        = 40,
  kFontYiddishLanguage          = 41,
  kFontSerbianLanguage          = 42,
  kFontMacedonianLanguage       = 43,
  kFontBulgarianLanguage        = 44,
  kFontUkrainianLanguage        = 45,
  kFontByelorussianLanguage     = 46,
  kFontUzbekLanguage            = 47,
  kFontKazakhLanguage           = 48,
  kFontAzerbaijaniLanguage      = 49,
  kFontAzerbaijanArLanguage     = 50,
  kFontArmenianLanguage         = 51,
  kFontGeorgianLanguage         = 52,
  kFontMoldavianLanguage        = 53,
  kFontKirghizLanguage          = 54,
  kFontTajikiLanguage           = 55,
  kFontTurkmenLanguage          = 56,
  kFontMongolianLanguage        = 57,
  kFontMongolianCyrLanguage     = 58,
  kFontPashtoLanguage           = 59,
  kFontKurdishLanguage          = 60,
  kFontKashmiriLanguage         = 61,
  kFontSindhiLanguage           = 62,
  kFontTibetanLanguage          = 63,
  kFontNepaliLanguage           = 64,
  kFontSanskritLanguage         = 65,
  kFontMarathiLanguage          = 66,
  kFontBengaliLanguage          = 67,
  kFontAssameseLanguage         = 68,
  kFontGujaratiLanguage         = 69,
  kFontPunjabiLanguage          = 70,
  kFontOriyaLanguage            = 71,
  kFontMalayalamLanguage        = 72,
  kFontKannadaLanguage          = 73,
  kFontTamilLanguage            = 74,
  kFontTeluguLanguage           = 75,
  kFontSinhaleseLanguage        = 76,
  kFontBurmeseLanguage          = 77,
  kFontKhmerLanguage            = 78,
  kFontLaoLanguage              = 79,
  kFontVietnameseLanguage       = 80,
  kFontIndonesianLanguage       = 81,
  kFontTagalogLanguage          = 82,
  kFontMalayRomanLanguage       = 83,
  kFontMalayArabicLanguage      = 84,
  kFontAmharicLanguage          = 85,
  kFontTigrinyaLanguage         = 86,
  kFontGallaLanguage            = 87,
  kFontOromoLanguage            = kFontGallaLanguage,
  kFontSomaliLanguage           = 88,
  kFontSwahiliLanguage          = 89,
  kFontRuandaLanguage           = 90,
  kFontRundiLanguage            = 91,
  kFontChewaLanguage            = 92,
  kFontMalagasyLanguage         = 93,
  kFontEsperantoLanguage        = 94,
  kFontWelshLanguage            = 128,
  kFontBasqueLanguage           = 129,
  kFontCatalanLanguage          = 130,
  kFontLatinLanguage            = 131,
  kFontQuechuaLanguage          = 132,
  kFontGuaraniLanguage          = 133,
  kFontAymaraLanguage           = 134,
  kFontTatarLanguage            = 135,
  kFontUighurLanguage           = 136,
  kFontDzongkhaLanguage         = 137,
  kFontJavaneseRomLanguage      = 138,
  kFontSundaneseRomLanguage     = 139
};
*/
return SUCCESS;
}
/* }}} */

#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
 
