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

#include <cairo.h>
#include "php.h"
#include "php_cairo.h"

#ifdef CAIRO_HAS_FT_FONT
#include <fontconfig/fontconfig.h>
#include <ft2build.h>
#include FT_FREETYPE_H

zend_class_entry *cairo_ce_cairoftfont;
zend_class_entry *cairo_ce_fcpattern;

ZEND_BEGIN_ARG_INFO_EX(CairoFtFontFace_createForFtFace_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_INFO(0, face)
	ZEND_ARG_INFO(0, load_flags)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(CairoFtFontFace_createForPattern_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_INFO(0, pattern)
ZEND_END_ARG_INFO()

/* {{{ proto void CairoFcPattern->__construct()
 */
PHP_METHOD(CairoFcPattern, __construct)
{
	cairo_fc_pattern_object *fc_pattern_object;

	PHP_CAIRO_ERROR_HANDLING(TRUE)
	if (zend_parse_parameters_none() == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(TRUE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(TRUE)

	fc_pattern_object = (cairo_fc_pattern_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
	fc_pattern_object->fc_pattern = FcPatternCreate();
}
/* }}} */

/* {{{ cairo_fc_pattern_object_destroy */
static void cairo_fc_pattern_object_destroy(void *object TSRMLS_DC)
{
	cairo_fc_pattern_object *fc_pattern = (cairo_fc_pattern_object *)object;
	zend_hash_destroy(fc_pattern->std.properties);
	FREE_HASHTABLE(fc_pattern->std.properties);
	if(fc_pattern->fc_pattern){
//		FcPatternDestroy(fc_pattern->fc_pattern);
	}
	efree(object);
}
/* }}} */

/* {{{ cairo_fc_pattern_object_new 
 */
zend_object_value cairo_fc_pattern_object_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	cairo_fc_pattern_object *fc_pattern;
	zval *temp;

	fc_pattern = ecalloc(1, sizeof(cairo_fc_pattern_object));

	fc_pattern->std.ce = ce;

	ALLOC_HASHTABLE(fc_pattern->std.properties);
	zend_hash_init(fc_pattern->std.properties, 0, NULL, ZVAL_PTR_DTOR, 0);
	zend_hash_copy(fc_pattern->std.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref,(void *) &temp, sizeof(zval *));
	retval.handle = zend_objects_store_put(fc_pattern, NULL, (zend_objects_free_object_storage_t)cairo_fc_pattern_object_destroy, NULL TSRMLS_CC);
	retval.handlers = zend_get_std_object_handlers();
	return retval;
}

/* }}} */

/* {{{ proto void cairo_ft_font_options_substitute(CairoFontOptions options, CairoFcPattern pattern)
       proto void CairoFcPattern::fontOptionsSubstitute(CairoFontOptions options)
	   Add options to a FcPattern based on a CairoFontOptions object. 
	   */
PHP_FUNCTION(cairo_ft_font_options_substitute)
{
	zval *font_options_zval, *pattern_zval;
	cairo_font_options_object *font_options_object;
	cairo_fc_pattern_object *pattern_object;

	PHP_CAIRO_ERROR_HANDLING(TRUE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &font_options_zval, cairo_ce_cairofontoptions, &pattern_zval, cairo_ce_fcpattern) == FAILURE)
	{
		PHP_CAIRO_RESTORE_ERRORS(TRUE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(TRUE)

	font_options_object = (cairo_font_options_object *)cairo_font_options_object_get(font_options_zval TSRMLS_CC);
	cairo_ft_font_options_substitute(font_options_object->font_options, pattern_object->fc_pattern);
}

/*}}} */

/* {{{ proto void CairoFtFontFace->__construct()
   CairoFtFontFace CANNOT be extended in userspace, this will throw an exception on use */
PHP_METHOD(CairoFtFontFace, __construct)
{
	zend_throw_exception(cairo_ce_cairoexception, "CairoFtFontFace cannot be constructed", 0 TSRMLS_CC);
}
/* }}} */

/* {{{ proto CairoFtFontFace cairo_ft_font_face_create_for_ft_face(string face, long load_flags)
	   proto CairoFtFontFace::createForFtFace(string face, long load_flags)
	   Creates a new font face for the FreeType font backend from a pre-opened FreeType face. */

/* FIXME: Adapt this to use streams, to handle open_basedir etc */
PHP_FUNCTION(cairo_ft_font_face_create_for_ft_face)
{
	FT_Face face = (FT_Face) NULL;
	FT_Library *ft_lib;
	long load_flags = 0;	
	char *font_name;
	int error = 0;
	long font_name_length = 0;
	zval *font_face_zval = NULL;
	cairo_font_face_object *font_face_object;
	

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|l",
				&font_name, &font_name_length, &load_flags) == FAILURE)
	{
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)
	
	ft_lib = &CAIROG(ft_lib);
	if(*ft_lib == NULL) {
		error = FT_Init_FreeType(ft_lib);
		if(error) {
			//PHP_CAIRO_ERROR("Failed to initialize FreeType library");
			return;
		}
	}

	/* FIXME: hard coding open first face, will change to allow it to be selected */
	error = FT_New_Face(*ft_lib, font_name, 0, &face);
	if(error == FT_Err_Unknown_File_Format) { 
		//PHP_CAIRO_ERROR("Unknown font file format");
		return;
	} else if ( error ) { 
		//PHP_CAIRO_ERROR("An error occurred opening the file");
		return;
	} 

	object_init_ex(return_value, cairo_ce_cairoftfont);
	font_face_object = (cairo_font_face_object *)zend_object_store_get_object(return_value TSRMLS_CC);	
	font_face_object->font_face = cairo_ft_font_face_create_for_ft_face(face, (int)load_flags);
	PHP_CAIRO_ERROR(cairo_font_face_status(font_face_object->font_face));
}

/* }}} */


/* {{{ proto array cairo_fc_pattern_search(array pattern)
	   proto array CairoFcPattern::search(array pattern)
	   Uses fontconfig to find fonts matching a particular pattern */

PHP_FUNCTION(cairo_fc_pattern_search)
{
	zval *pattern_zval = NULL, **ppzval;
	FcPattern *pattern;
	FcObjectSet *os;
	FcFontSet *fs;
	int i = 0;
	long pattern_elements = 0, num_index = 0;
	HashTable *pattern_hash = NULL;
	char *pattern_key;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|a",
				&pattern_zval) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)
	
	if(CAIROG(fc_config) == NULL) {
		CAIROG(fc_config) = FcInitLoadConfigAndFonts();
		if(!CAIROG(fc_config)) {
			zend_error(E_WARNING, "Failed to initialise fontconfig library");
			RETURN_NULL();
		}
	}

	os = FcObjectSetBuild(FC_FAMILY, FC_STYLE, FC_FILE, (char *) 0);
	pattern = FcPatternCreate();

	if (pattern_zval) {
		pattern_hash = Z_ARRVAL_P(pattern_zval);
		for(zend_hash_internal_pointer_reset(pattern_hash); 
				zend_hash_has_more_elements(pattern_hash) == SUCCESS; 
				zend_hash_move_forward(pattern_hash)) {
			if (zend_hash_get_current_data(pattern_hash, (void **)&ppzval) == FAILURE) {
				continue;
			}

			if (Z_TYPE_PP(ppzval) != IS_STRING) {
				convert_to_string(*ppzval);
			}

			if( zend_hash_get_current_key(pattern_hash, &pattern_key, &num_index, 0) == HASH_KEY_IS_STRING) {
				FcPatternAddString(pattern, pattern_key, (FcChar8 *) Z_STRVAL_PP(ppzval));
			}
		}
	}

	fs = FcFontList(CAIROG(fc_config), pattern, os);

	if(!fs) {
		RETURN_NULL();
	}

	array_init(return_value);
	for (i = 0; i < fs->nfont; i++) {
		zval *pattern_zval;
		cairo_fc_pattern_object *fc_pattern_object;

		MAKE_STD_ZVAL(pattern_zval);
		object_init_ex(pattern_zval, cairo_ce_fcpattern);
		fc_pattern_object = (cairo_fc_pattern_object *) zend_object_store_get_object(pattern_zval TSRMLS_CC);
		fc_pattern_object->fc_pattern = fs->fonts[i];

		add_next_index_zval(return_value, pattern_zval);
	}
	FcFontSetDestroy(fs);
}
/* }}} */

/* {{{ proto CairoFtFontFace cairo_ft_font_face_create_for_pattern(array pattern)
       proto CairoFtFontFace CairoFtFontFace::createForPattern(array pattern)
	   Creates a new font face for the FreeType font backend based on an FcPattern */

PHP_FUNCTION(cairo_ft_font_face_create_for_pattern)
{
	FT_Library *ft_lib;
	int error = 0;
	zval *pattern_zval = NULL;
	cairo_fc_pattern_object *pattern_object;
	cairo_font_face_object *font_face_object;
	

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O",
				&pattern_zval, cairo_ce_fcpattern) == FAILURE)
	{
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)
	
	ft_lib = &CAIROG(ft_lib);
	if(*ft_lib == NULL) {
		error = FT_Init_FreeType(ft_lib);
		if(error) {
			//PHP_CAIRO_ERROR("Failed to initialize FreeType library");
			return;
		}
	}

	pattern_object = (cairo_fc_pattern_object *)cairo_fc_pattern_object_get(pattern_zval TSRMLS_CC);

	object_init_ex(return_value, cairo_ce_cairoftfontface);
	font_face_object = (cairo_font_face_object *)zend_object_store_get_object(return_value TSRMLS_CC);	
	font_face_object->font_face = (cairo_font_face_t *)cairo_ft_face_create_for_pattern(pattern_object->fc_pattern);
	PHP_CAIRO_ERROR(cairo_font_face_status(font_face_object->font_face));
}
/* }}} */

/* {{{ cairo_fc_pattern_methods */
const zend_function_entry cairo_fc_pattern_methods[] = {
	PHP_ME(CairoFcPattern, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME_MAPPING(search, cairo_fc_pattern_search, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	{NULL, NULL, NULL}
};

/* {{{ cairo_ft_font_methods */
const zend_function_entry cairo_ft_font_methods[] = {
	PHP_ME(CairoFtFontFace, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME_MAPPING(createForFtFace, cairo_ft_font_face_create_for_ft_face, CairoFtFontFace_createForFtFace_args, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME_MAPPING(createForPattern, cairo_ft_font_face_create_for_pattern, CairoFtFontFace_createForPattern_args, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME_MAPPING(fontOptionsSubstitute, cairo_ft_font_options_substitute, NULL, ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};

/* }}} */

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(cairo_ft_font)
{
	zend_class_entry ftfont_ce;
	zend_class_entry fcpattern_ce;

	INIT_CLASS_ENTRY(fcpattern_ce, "CairoFcPattern", cairo_fc_pattern_methods);
	cairo_ce_fcpattern = zend_register_internal_class(&fcpattern_ce TSRMLS_CC);
	cairo_ce_fcpattern->create_object = cairo_fc_pattern_object_new;

	INIT_CLASS_ENTRY(ftfont_ce, "CairoFtFontFace", cairo_ft_font_methods);
	cairo_ce_cairoftfont = zend_register_internal_class_ex(&ftfont_ce, cairo_ce_cairofontface, "CairoFontFace" TSRMLS_CC);
	cairo_ce_cairoftfont->create_object = cairo_font_face_object_new;

	return SUCCESS;
}

#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
