/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2011 The PHP Group                                |
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
#include "zend_exceptions.h"

#if defined(CAIRO_HAS_FT_FONT) && defined(HAVE_FREETYPE)
#include <fontconfig/fontconfig.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <cairo/cairo-ft.h>

zend_class_entry *cairo_ce_cairoftfont;

ZEND_BEGIN_ARG_INFO_EX(CairoFtFontFace_construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_INFO(0, face)
	ZEND_ARG_INFO(0, load_flags)
ZEND_END_ARG_INFO()


/* Functions for stream handling */
static unsigned long php_cairo_ft_read_func(FT_Stream stream, unsigned long offset, unsigned char* buffer, unsigned long count) {
	stream_closure *closure;
#ifdef ZTS
	TSRMLS_D;
#endif

	closure = (stream_closure *)stream->descriptor.pointer;
#ifdef ZTS
	TSRMLS_C = closure->TSRMLS_C;
#endif
	php_stream_seek(closure->stream, offset, SEEK_SET);
	return php_stream_read(closure->stream, (char *)buffer, count);
}

void php_cairo_ft_close_stream(FT_Stream stream)
{
#ifdef ZTS
	TSRMLS_D;
#endif

	stream_closure *closure;

	closure = (stream_closure *)stream->descriptor.pointer;
#ifdef ZTS
	TSRMLS_C = closure->TSRMLS_C;
#endif
	/* Don't close the stream unless we created it */
	if(closure->owned_stream) {
		php_stream_close((php_stream *)closure->stream);		
	}
	efree(closure);
	efree(stream);
}

static zend_bool php_cairo_create_ft_font_face(cairo_ft_font_face_object *font_face_object, php_stream *stream, zend_bool owned_stream, int load_flags, zend_bool throw_exceptions TSRMLS_DC) {
	FT_Library *ft_lib;
	FT_Stream ft_stream;
	FT_Face face;
	stream_closure *closure;
	php_stream_statbuf ssbuf;
	FT_Open_Args open_args;
	int error;

	ft_lib = &CAIROG(ft_lib);
	font_face_object->ft_face = NULL;
	font_face_object->ft_stream = NULL;
	
	closure = ecalloc(1, sizeof(stream_closure));
	closure->stream = stream;
	closure->owned_stream = owned_stream;
#ifdef ZTS
	closure->TSRMLS_C = TSRMLS_C;
#endif

	ft_stream = ecalloc(1, sizeof(*ft_stream));
	ft_stream->descriptor.pointer = (void *)closure;
	ft_stream->pos = php_stream_tell(stream);
	ft_stream->size = ssbuf.sb.st_size;
	ft_stream->read = php_cairo_ft_read_func;
	/* ft_stream->close = php_cairo_ft_close_stream; */
	open_args.flags = FT_OPEN_STREAM;
	open_args.stream = ft_stream;

	error = FT_Open_Face(*ft_lib, &open_args, 0, &face);
	
	if (error) {
		if (owned_stream) {
			php_stream_close(stream);
		}
		efree(closure);
		efree(ft_stream);

		return error;
	}
	
	font_face_object->ft_stream = ft_stream;
	font_face_object->font_face = (cairo_font_face_t *)cairo_ft_font_face_create_for_ft_face(face, (int)load_flags);

	/* Set Cairo to automatically destroy the FT_Face when the cairo_font_face_t is destroyed */
	error = cairo_font_face_set_user_data (
			font_face_object->font_face, 
			&font_face_object->key,
			face, 
			(cairo_destroy_func_t) FT_Done_Face);

	if (error) {
		cairo_font_face_destroy (font_face_object->font_face);
		FT_Done_Face(face);
		return error;
	}

	return 0;
}

/* {{{ proto CairoFtFontFace cairo_ft_font_face_create(string face, long load_flags)
	   Creates a new font face for the FreeType font backend from a pre-opened FreeType face. */

/* FIXME: Adapt this to use streams, to handle open_basedir etc */
PHP_FUNCTION(cairo_ft_font_face_create)
{
	FT_Library *ft_lib;
	long load_flags = 0;
	int error = 0;
	zval *stream_zval = NULL;
	cairo_ft_font_face_object *font_face_object;

	php_stream *stream;
	php_stream_statbuf ssbuf;
	zend_bool owned_stream = 0;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z|l",
				&stream_zval, &load_flags) == FAILURE)
	{
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)
	
	ft_lib = &CAIROG(ft_lib);
	if(*ft_lib == NULL) {
		error = FT_Init_FreeType(ft_lib);
		if(error) {
			zend_error(E_WARNING, "Failed to initialize the Freetype library");
			return;
		}
	}

	if(Z_TYPE_P(stream_zval) == IS_STRING) {
		stream = php_stream_open_wrapper(Z_STRVAL_P(stream_zval), "rb", REPORT_ERRORS|ENFORCE_SAFE_MODE, NULL);
		owned_stream = 1;
	} else if(Z_TYPE_P(stream_zval) == IS_RESOURCE)  {
		php_stream_from_zval(stream, &stream_zval);	
	} else {
		zend_error(E_WARNING, "cairo_ft_font_face_create expects parameter 1 to be a string or a stream resource");
		return;
	}

	if(!stream) {
		return;
	}

	if(php_stream_stat(stream, &ssbuf) != 0) {
		zend_error(E_WARNING, "Cannot determine size of stream");
		if(owned_stream) {
			php_stream_close(stream);
		}
		return;
	}

	object_init_ex(return_value, cairo_ce_cairoftfont);
	font_face_object = (cairo_ft_font_face_object *)zend_object_store_get_object(return_value TSRMLS_CC);	
	error = php_cairo_create_ft_font_face(font_face_object, stream, owned_stream, load_flags, 0 TSRMLS_CC);

	if (error) {
		if (error == FT_Err_Unknown_File_Format) {
			zend_error(E_WARNING, "Unknown file format");
		} else {
			zend_error(E_WARNING, "Error %d occurred opening the file", error);
		} 

		RETURN_NULL();
	}

	PHP_CAIRO_ERROR(cairo_font_face_status(font_face_object->font_face));
}

/* }}} */


/* {{{ proto CairoFtFontFace::__construct(string fontFilename, long load_flags)
	   Creates a new font face for the FreeType font backend from a pre-opened FreeType face. */

/* FIXME: Adapt this to use streams, to handle open_basedir etc */
PHP_METHOD(CairoFtFontFace, __construct)
{
	FT_Library *ft_lib;
	long load_flags = 0;
	int error = 0;
	zval *stream_zval = NULL;
	cairo_ft_font_face_object *font_face_object;

	php_stream *stream;
	zend_bool owned_stream = 0;
	php_stream_statbuf ssbuf;

	PHP_CAIRO_ERROR_HANDLING(TRUE)
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z|l",
				&stream_zval, &load_flags) == FAILURE)
	{
		PHP_CAIRO_RESTORE_ERRORS(TRUE)
		return;
	}
	
	ft_lib = &CAIROG(ft_lib);
	if(*ft_lib == NULL) {
		error = FT_Init_FreeType(ft_lib);
		if(error) {
			PHP_CAIRO_RESTORE_ERRORS(TRUE)
			zend_throw_exception(cairo_ce_cairoexception, "Failed to initalise FreeType library", 0 TSRMLS_CC);
			return;
		}
	}

	if(Z_TYPE_P(stream_zval) == IS_STRING) {
		stream = php_stream_open_wrapper(Z_STRVAL_P(stream_zval), "rb", REPORT_ERRORS|ENFORCE_SAFE_MODE, NULL);
		owned_stream = 1;
	} else if(Z_TYPE_P(stream_zval) == IS_RESOURCE)  {
		php_stream_from_zval(stream, &stream_zval);	
	} else {	
		PHP_CAIRO_RESTORE_ERRORS(TRUE)
		zend_throw_exception(cairo_ce_cairoexception, "CairoFtFontFace::__construct() expects parameter 1 to be a string or a stream resource", 0 TSRMLS_CC);
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(TRUE)

	if(!stream) {
		/* If there isn't a stream, the exception should already have been thrown 
		   by php_stream_open_wrapper, so just bail */
		return;
	}


	if(php_stream_stat(stream, &ssbuf) != 0) {
		zend_throw_exception(cairo_ce_cairoexception, "Cannot determine size of stream", 0 TSRMLS_CC);
		return;
	}

	font_face_object = (cairo_ft_font_face_object *)zend_object_store_get_object(getThis() TSRMLS_CC);	
	error = php_cairo_create_ft_font_face(font_face_object, stream, owned_stream, load_flags, 1 TSRMLS_CC);

	if (error) {
		if (error == FT_Err_Unknown_File_Format) {
			zend_throw_exception(cairo_ce_cairoexception, "CairoFtFontFace::__construct(): unknown file format", error TSRMLS_CC);
			return;
		} else {
			zend_throw_exception(cairo_ce_cairoexception, "CairoFtFontFace::__construct(): An error occurred opening the file", error TSRMLS_CC);
			return;
		} 
	}

	php_cairo_throw_exception(cairo_font_face_status(font_face_object->font_face) TSRMLS_CC);
}

/* }}} */

/* {{{ cairo_ft_font_methods */
const zend_function_entry cairo_ft_font_methods[] = {
	PHP_ME(CairoFtFontFace, __construct, CairoFtFontFace_construct_args, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	{NULL, NULL, NULL}
};
/* }}} */


/* {{{ cairo_ft_font_face_object_destroy 
 */
static void cairo_ft_font_face_object_destroy(void *object TSRMLS_DC)
{
	stream_closure *closure;
	cairo_ft_font_face_object *font_face = (cairo_ft_font_face_object *)object;
	zend_hash_destroy(font_face->std.properties);
	FREE_HASHTABLE(font_face->std.properties);
	if(font_face->font_face){
		cairo_font_face_destroy(font_face->font_face);
	}

	if(font_face->ft_stream != NULL) {
		closure = (stream_closure *)font_face->ft_stream->descriptor.pointer;
		php_stream_close(closure->stream);
		efree(closure);
		efree(font_face->ft_stream);
	}

	efree(object);
}

/* }}} */

/* {{{ cairo_ft_font_face_object_new 
 */
zend_object_value cairo_ft_font_face_object_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	cairo_ft_font_face_object *font_face;
	zval *temp;

	font_face = ecalloc(1, sizeof(cairo_ft_font_face_object));
	font_face->ft_stream = NULL;

	font_face->std.ce = ce;

	ALLOC_HASHTABLE(font_face->std.properties);
	zend_hash_init(font_face->std.properties, 0, NULL, ZVAL_PTR_DTOR, 0);
#if PHP_VERSION_ID < 50399
	zend_hash_copy(font_face->std.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref,(void *) &temp, sizeof(zval *));
#else
	object_properties_init(&font_face->std, ce);
#endif
	retval.handle = zend_objects_store_put(font_face, NULL, (zend_objects_free_object_storage_t)cairo_ft_font_face_object_destroy, NULL TSRMLS_CC);
	retval.handlers = zend_get_std_object_handlers();
	return retval;
}

/* }}} */


/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(cairo_ft_font)
{
	zend_class_entry ftfont_ce;

	INIT_CLASS_ENTRY(ftfont_ce, "CairoFtFontFace", cairo_ft_font_methods);
	cairo_ce_cairoftfont = zend_register_internal_class_ex(&ftfont_ce, cairo_ce_cairofontface, "CairoFontFace" TSRMLS_CC);
	cairo_ce_cairoftfont->create_object = cairo_ft_font_face_object_new;

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
