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

#include <cairo.h>
#include "php.h"
#include "php_cairo.h"
#include "zend_exceptions.h"

#if defined(CAIRO_HAS_FT_FONT) && defined(HAVE_FREETYPE)
#include <fontconfig/fontconfig.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <cairo-ft.h>

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

static void cairo_user_data_callback_ft_free(pecl_ft_container *ft_container) {
    if(ft_container->ft_face != NULL) {
        FT_Done_Face(ft_container->ft_face);
    }
    
    if(ft_container->ft_stream != NULL) {
        pefree(ft_container->ft_stream, TRUE);
    }
    
   	if(ft_container->ft_lib != NULL) {
		FT_Done_FreeType(ft_container->ft_lib);
	}
    
    pefree(ft_container, 1);
}

static zend_bool php_cairo_create_ft_font_face(pecl_ft_container *ft_container, cairo_ft_font_face_object *font_face_object, php_stream *stream, zend_bool owned_stream, int load_flags, zend_bool throw_exceptions TSRMLS_DC) {
	FT_Stream ft_stream;
	stream_closure *closure;
	php_stream_statbuf ssbuf;
	FT_Open_Args open_args;
	int error;

	if (php_stream_stat(stream,&ssbuf) < 0) {
		return 1;
	}
	
    ft_container->ft_face = NULL; 
    ft_container->ft_stream = NULL;

    font_face_object->closure = NULL;
    
	closure = ecalloc(1, sizeof(stream_closure));
	closure->stream = stream;
	closure->owned_stream = owned_stream;
#ifdef ZTS
	closure->TSRMLS_C = TSRMLS_C;
#endif

	ft_stream = pecalloc(1, sizeof(*ft_stream), TRUE);
	ft_stream->descriptor.pointer = (void *)closure;
	ft_stream->pos = php_stream_tell(stream);
	ft_stream->size = ssbuf.sb.st_size;
	ft_stream->read = php_cairo_ft_read_func;
	open_args.flags = FT_OPEN_STREAM;
	open_args.stream = ft_stream;

	error = FT_Open_Face(ft_container->ft_lib, &open_args, 0, &ft_container->ft_face);
	
	if (error) {
		if (owned_stream) {
			php_stream_close(stream);
		}
		efree(closure);
		pefree(ft_stream, TRUE);
        
		return error;
	} 

    font_face_object->closure = closure;
    
    ft_container->ft_stream = ft_stream;
	font_face_object->font_face = (cairo_font_face_t *)cairo_ft_font_face_create_for_ft_face(ft_container->ft_face, (int)load_flags);

	/* Set Cairo to automatically destroy the FT_Face when the cairo_font_face_t is destroyed */
	error = cairo_font_face_set_user_data (
			font_face_object->font_face, 
			&font_face_object->key,
			ft_container, 
			(cairo_destroy_func_t) cairo_user_data_callback_ft_free);

            
	if (error) {
		cairo_font_face_destroy (font_face_object->font_face);
		FT_Done_Face(ft_container->ft_face);
        pefree(ft_stream, TRUE);
		return error;
	}

	return 0;
}

/* {{{ proto CairoFtFontFace cairo_ft_font_face_create(string face, long load_flags)
	   Creates a new font face for the FreeType font backend from a pre-opened FreeType face. */
PHP_FUNCTION(cairo_ft_font_face_create)
{
	long load_flags = 0;
	int error = 0;
	zval *stream_zval = NULL;
	cairo_ft_font_face_object *font_face_object;
    pecl_ft_container *ft_container;
    
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

	if(Z_TYPE_P(stream_zval) == IS_STRING) {
		stream = php_stream_open_wrapper(Z_STRVAL_P(stream_zval), "rb", REPORT_ERRORS|ENFORCE_SAFE_MODE, NULL);
		owned_stream = 1;
	} else if(Z_TYPE_P(stream_zval) == IS_RESOURCE)  {
		php_stream_from_zval(stream, &stream_zval);	
	} else {
		zend_error(E_WARNING, "cairo_ft_font_face_create expects parameter 1 to be a string or a stream resource");
		RETURN_NULL();
	}

	if(!stream) {
		RETURN_NULL();
	}

	if(php_stream_stat(stream, &ssbuf) != 0) {
		if(owned_stream) {
			php_stream_close(stream);
		}
		zend_error(E_WARNING, "cairo_ft_font_face_create(): Cannot determine size of stream");
		RETURN_NULL();
	}

	object_init_ex(return_value, cairo_ce_cairoftfont);
	font_face_object = (cairo_ft_font_face_object *)zend_object_store_get_object(return_value TSRMLS_CC);
    
    ft_container = pecalloc(1, sizeof(pecl_ft_container), 1);
    
	error = FT_Init_FreeType(&ft_container->ft_lib);
	if(error) {
        pefree(ft_container, TRUE);
		zend_error(E_WARNING, "Failed to initialize the Freetype library");
		RETURN_NULL();
	}
	
	error = php_cairo_create_ft_font_face(ft_container, font_face_object, stream, owned_stream, load_flags, 0 TSRMLS_CC);

	if (error) {
		const char *err_string = php_cairo_get_ft_error(error TSRMLS_CC);
		zend_error(E_WARNING, "cairo_ft_font_face_create(): An error occurred opening the file: %s", err_string);
        pefree(ft_container, 1);
		RETURN_NULL();
	} 

	PHP_CAIRO_ERROR(cairo_font_face_status(font_face_object->font_face));
}

/* }}} */


/* {{{ proto CairoFtFontFace::__construct(string fontFilename, long load_flags)
	   Creates a new font face for the FreeType font backend from a pre-opened FreeType face. */
PHP_METHOD(CairoFtFontFace, __construct)
{
	long load_flags = 0;
	int error = 0;
	zval *stream_zval = NULL;
	cairo_ft_font_face_object *font_face_object;
    pecl_ft_container *ft_container;

	php_stream *stream;
	php_stream_statbuf ssbuf;
	zend_bool owned_stream = 0;

	PHP_CAIRO_ERROR_HANDLING(TRUE)
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z|l",
				&stream_zval, &load_flags) == FAILURE)
	{
		PHP_CAIRO_RESTORE_ERRORS(TRUE)
		return;
	}

	if(Z_TYPE_P(stream_zval) == IS_STRING) {
		stream = php_stream_open_wrapper(Z_STRVAL_P(stream_zval), "rb", REPORT_ERRORS|ENFORCE_SAFE_MODE, NULL);
		owned_stream = 1;
	} else if(Z_TYPE_P(stream_zval) == IS_RESOURCE)  {
		php_stream_from_zval(stream, &stream_zval);	
	} else {	
		PHP_CAIRO_RESTORE_ERRORS(TRUE)
		zend_throw_exception(cairo_ce_cairoexception, "CairoFtFontFace::__construct() expects parameter 1 to be a string or a stream resource", 0 TSRMLS_CC);
		RETURN_NULL();
	}
	PHP_CAIRO_RESTORE_ERRORS(TRUE)

	if(!stream) {
		RETURN_NULL();
	}
	
	if(php_stream_stat(stream, &ssbuf) != 0) {
        if(owned_stream) {
			php_stream_close(stream);
		}
		zend_throw_exception(cairo_ce_cairoexception, "Cannot determine size of stream", 0 TSRMLS_CC);
		return;
	}

	font_face_object = (cairo_ft_font_face_object *)zend_object_store_get_object(getThis() TSRMLS_CC);

    ft_container = pecalloc(1, sizeof(pecl_ft_container), TRUE);
    
	error = FT_Init_FreeType(&ft_container->ft_lib);
	if(error) {
        pefree(ft_container, TRUE);
		zend_throw_exception(cairo_ce_cairoexception, "Failed to initalise FreeType library", 0 TSRMLS_CC);
		RETURN_NULL();
	}
	php_printf("trying to create a font face yo");
	error = php_cairo_create_ft_font_face(ft_container, font_face_object, stream, owned_stream, load_flags, 1 TSRMLS_CC);

	if (error) {
		const char *err_string = php_cairo_get_ft_error(error TSRMLS_CC);
php_printf("creating error");
		pefree(ft_container, 1);
php_printf("container freed");
		//zend_throw_exception_ex(cairo_ce_cairoexception, error, "CairoFtFontFace::__construct(): An error occurred opening the file %s", err_string TSRMLS_CC);
php_printf("exception thrown");
		RETURN_NULL();
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
	cairo_ft_font_face_object *font_face = (cairo_ft_font_face_object *)object;
	zend_hash_destroy(font_face->std.properties);
	FREE_HASHTABLE(font_face->std.properties);

	if(font_face->font_face && cairo_font_face_get_reference_count(font_face->font_face) > 0){
		cairo_font_face_destroy(font_face->font_face);
	}

    if(font_face->closure != NULL) {
        if(font_face->closure->owned_stream) {
            php_stream_close(font_face->closure->stream);
        }
        efree(font_face->closure);
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
#if PHP_VERSION_ID < 50399
	zval *temp;
#endif

	font_face = ecalloc(1, sizeof(cairo_ft_font_face_object));
	font_face->closure = NULL;
    
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
