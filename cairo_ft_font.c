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

/*
cairo_font_face_t*  cairo_ft_font_face_create_for_ft_face
														(FT_Face face,
														 int load_flags);
cairo_font_face_t*  cairo_ft_font_face_create_for_pattern
														(FcPattern *pattern);
void				cairo_ft_font_options_substitute	(const cairo_font_options_t *options,
														 FcPattern *pattern);
FT_Face			 cairo_ft_scaled_font_lock_face	  (cairo_scaled_font_t *scaled_font);
void				cairo_ft_scaled_font_unlock_face	(cairo_scaled_font_t *scaled_font); */

zend_class_entry *cairo_ce_cairoftfont;

ZEND_BEGIN_ARG_INFO_EX(CairoFtFontFace_createForFtFace_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_INFO(0, face)
	ZEND_ARG_INFO(0, load_flags)
ZEND_END_ARG_INFO()


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

const zend_function_entry cairo_ft_font_methods[] = {
	PHP_ME_MAPPING(createForFtFace, cairo_ft_font_face_create_for_ft_face, CairoFtFontFace_createForFtFace_args, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	{NULL, NULL, NULL}
};

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(cairo_ft_font)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "CairoFtFontFace", cairo_ft_font_methods);
	cairo_ce_cairoftfont = zend_register_internal_class_ex(&ce, cairo_ce_cairofontface, "CairoFontFace" TSRMLS_CC);
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
