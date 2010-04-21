/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2008 The PHP Group                                |
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

#include <cairo.h>

#ifdef CAIRO_HAS_QUARTZ_FONT
	zend_class_entry *cairo_ce_cairoquartzfont;
	zend_class_entry *cairo_ce_cairoquartzatsufontnamecode;
	zend_class_entry *cairo_ce_cairoquartzatsufontnameplatform;
#endif

/* Font specific Backends support */

#ifdef CAIRO_HAS_QUARTZ_FONT

/* {{{ proto CairoQuartzFontFace cairo_quartz_font_face_create_for_atsu_font_id(CairoFontFace object, string font_name[, int code, int platform, int script, int language])
   proto CairoQuartzFontFace CairoQuartzFontFace::createForAtsuFontId(string font_name[, int code, int platform, int script, int language])
   Takes parameters from the user an attempts to look up an atsu font id
   If that is successful it creates a new quartz font face from the resulting Id 
   http://developer.apple.com/documentation/Carbon/Reference/ATSUI_Reference/Reference/reference.html#/apple_ref/c/func/ATSUFindFontFromName
   */
PHP_FUNCTION(cairo_quartz_font_face_create_for_atsu_font_id)
{
    ATSUFontID fontID;
    OSStatus error;
    const char *font_name;
	int font_name_length;
	FontNameCode code = kFontFullName;
	FontPlatformCode platform = kFontNoPlatformCode;
	FontScriptCode script = kFontRomanScript;
	FontLanguageCode language = kFontNoLanguageCode;

	zval *font_face_zval = NULL;
	cairo_fontface_object *font_face_object;

	PHP_CAIRO_ERROR_HANDLING
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Os|llll", &font_face_zval, cairo_ce_cairofontface,
			&font_name, &font_name_length, &code, &platform, &script, &language) == FAILURE) {
		return;
	}

	ATSUFindFontFromName(font_name, font_name_length, code, platform, script, language, &fontID);

	if(fontID == kATSUInvalidFontID) {
		PHP_CAIRO_ERROR("Atsu Font could not be retrieved");
		return;
	}

	object_init_ex(return_value, cairo_ce_cairoquartzfont);
	font_face_object = (cairo_fontface_object *)zend_object_store_get_object(return_value TSRMLS_CC);

	font_face_object->font_face = cairo_quartz_font_face_create_for_atsu_font_id(fontID);
	PHP_CAIRO_ERROR(cairo_font_face_status(font_face_object->font_face));
}

/* {{{ proto CairoQuartzFontFace cairo_quartz_font_face_create_for_cgfont(CairoFontFace object, string font_name[, int code, int platform, int script, int language])
   proto CairoQuartzFontFace CairoQuartzFontFace::createForCgfont(string font_name[, int code, int platform, int script, int language])
   Takes parameters from the user and attempts to create a ctfontref
   If that is successful it creates a new quartz font face from the resulting Id 
   http://developer.apple.com/documentation/graphicsimaging/Reference/CGFont/Reference/reference.html#/apple_ref/c/func/CGFontCreateWithFontName
   */
PHP_FUNCTION(cairo_quartz_font_face_create_for_cgfont)
{
	CFStringRef font_name;
	char * c_font_name;

	zval *font_face_zval = NULL;
	cairo_fontface_object *font_face_object;

	PHP_CAIRO_ERROR_HANDLING
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Os", &font_face_zval, cairo_ce_cairofontface, &c_font_name) == FAILURE) {
		return;
	}

	object_init_ex(return_value, cairo_ce_cairoquartzfont);
	font_face_object = (cairo_fontface_object *)zend_object_store_get_object(return_value TSRMLS_CC);

	/* Create our CFStringRef for the call */
	font_name = CFStringCreateWithCString(NULL, c_font_name, kCFStringEncodingMacRoman);

	/* Try to grab our new font ref */
	font_face_object->quartzref = CGFontCreateWithFontName(font_name);

	/* We are done with our CFStringRef so we free it - the null check is so we don't crash*/
	if (font_name != NULL)
		CFRelease(font_name);

	/* Now actually do the cairo call */
	font_face_object->font_face = cairo_quartz_font_face_create_for_cgfont(font_face_object->quartzref);
	PHP_CAIRO_ERROR(cairo_font_face_status(font_face_object->font_face));
}

/* }}} */

/* {{{ cairo_quartz_font_methods[] */
const zend_function_entry cairo_quartz_font_methods[] = {
	PHP_ME_MAPPING(createForCgfont, cairo_quartz_font_face_create_for_cgfont, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME_MAPPING(createForAtsuiFontId, cairo_quartz_font_face_create_for_atsu_font_id, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	{NULL, NULL, NULL}
};
/* }}} */

#endif

#ifdef CAIRO_HAS_QUARTZ_FONT
	INIT_CLASS_ENTRY(ce, "CairoQuartzFontFace", cairo_quartz_font_methods);
	cairo_ce_cairoquartzfont = zend_register_internal_class_ex(&ce, cairo_ce_cairofontface, "CairoFontFace" TSRMLS_CC);
	cairo_ce_cairoquartzfont->create_object = cairo_fontface_object_new;

	INIT_CLASS_ENTRY(ce, "CairoQuartzAtsuFontNameCode", NULL);
	cairo_ce_cairoquartzatsufontnamecode = zend_register_internal_class(&ce TSRMLS_CC);
	cairo_ce_cairoquartzatsufontnamecode->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS | ZEND_ACC_FINAL_CLASS;

	zend_declare_class_constant_long(cairo_ce_cairoquartzatsufontnamecode, "CopyrightName", sizeof("CopyrightName")-1, kFontCopyrightName TSRMLS_CC);
	zend_declare_class_constant_long(cairo_ce_cairoquartzatsufontnamecode, "FamilyName", sizeof("FamilyName")-1, kFontFamilyName TSRMLS_CC);
	zend_declare_class_constant_long(cairo_ce_cairoquartzatsufontnamecode, "StyleName", sizeof("StyleName")-1, kFontStyleName TSRMLS_CC);
	zend_declare_class_constant_long(cairo_ce_cairoquartzatsufontnamecode, "UniqueName", sizeof("UniqueName")-1, kFontUniqueName TSRMLS_CC);
	zend_declare_class_constant_long(cairo_ce_cairoquartzatsufontnamecode, "FullName", sizeof("FullName")-1, kFontFullName TSRMLS_CC);
	zend_declare_class_constant_long(cairo_ce_cairoquartzatsufontnamecode, "VersionName", sizeof("VersionName")-1, kFontVersionName TSRMLS_CC);
	zend_declare_class_constant_long(cairo_ce_cairoquartzatsufontnamecode, "PostscriptName", sizeof("PostscriptName")-1, kFontPostscriptName TSRMLS_CC);
	zend_declare_class_constant_long(cairo_ce_cairoquartzatsufontnamecode, "TrademarkName", sizeof("TrademarkName")-1, kFontTrademarkName TSRMLS_CC);
	zend_declare_class_constant_long(cairo_ce_cairoquartzatsufontnamecode, "ManufacturerName", sizeof("ManufacturerName")-1, kFontManufacturerName TSRMLS_CC);
	zend_declare_class_constant_long(cairo_ce_cairoquartzatsufontnamecode, "DesignerName", sizeof("DesignerName")-1, kFontDesignerName TSRMLS_CC);
	zend_declare_class_constant_long(cairo_ce_cairoquartzatsufontnamecode, "DescriptionName", sizeof("DescriptionName")-1, kFontDescriptionName TSRMLS_CC);
	zend_declare_class_constant_long(cairo_ce_cairoquartzatsufontnamecode, "VendorURLName", sizeof("VendorURLName")-1, kFontVendorURLName TSRMLS_CC);
	zend_declare_class_constant_long(cairo_ce_cairoquartzatsufontnamecode, "DesignerURLName", sizeof("DesignerURLName")-1, kFontDesignerURLName TSRMLS_CC);
	zend_declare_class_constant_long(cairo_ce_cairoquartzatsufontnamecode, "LicenseDescriptionName", sizeof("LicenseDescriptionName")-1, kFontLicenseDescriptionName TSRMLS_CC);
	zend_declare_class_constant_long(cairo_ce_cairoquartzatsufontnamecode, "LicenseInfoURLName", sizeof("LicenseInfoURLName")-1, kFontLicenseInfoURLName TSRMLS_CC);

	INIT_CLASS_ENTRY(ce, "CairoQuartzAtsuFontNamePlatform", NULL);
	cairo_ce_cairoquartzatsufontnameplatform = zend_register_internal_class(&ce TSRMLS_CC);
	cairo_ce_cairoquartzatsufontnameplatform->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS | ZEND_ACC_FINAL_CLASS;

	zend_declare_class_constant_long(cairo_ce_cairoquartzatsufontnameplatform, "UnicodePlatform", sizeof("UnicodePlatform")-1, kFontUnicodePlatform TSRMLS_CC);
	zend_declare_class_constant_long(cairo_ce_cairoquartzatsufontnameplatform, "MacintoshPlatform", sizeof("MacintoshPlatform")-1, kFontMacintoshPlatform TSRMLS_CC);
	zend_declare_class_constant_long(cairo_ce_cairoquartzatsufontnameplatform, "ReservedPlatform", sizeof("ReservedPlatform")-1, kFontReservedPlatform TSRMLS_CC);
	zend_declare_class_constant_long(cairo_ce_cairoquartzatsufontnameplatform, "MicrosoftPlatform", sizeof("MicrosoftPlatform")-1, kFontMicrosoftPlatform TSRMLS_CC);
	zend_declare_class_constant_long(cairo_ce_cairoquartzatsufontnameplatform, "CustomPlatform", sizeof("CustomPlatform")-1, kFontCustomPlatform TSRMLS_CC);

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

#endif