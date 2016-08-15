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

#if defined(CAIRO_HAS_FT_FONT) && defined(HAVE_FREETYPE)

const php_cairo_ft_error php_cairo_ft_errors[] =
#include FT_ERRORS_H

#include <fontconfig/fontconfig.h>


zend_class_entry *ce_cairo_ftfont;

static zend_object_handlers cairo_ft_font_face_object_handlers; 

const char* php_cairo_get_ft_error(int error) {

	const php_cairo_ft_error *current_error = php_cairo_ft_errors;

	while (current_error->err_msg != NULL) {
		if (current_error->err_code == error) {
			return current_error->err_msg;
		}
		current_error++;
	}
	return NULL;
}


static inline cairo_ft_font_face_object *cairo_ft_font_face_fetch_object(zend_object *object)
{
    return (cairo_ft_font_face_object *) ((char*)(object) - XtOffsetOf(cairo_ft_font_face_object, std));
}

#define Z_CAIRO_FT_FONT_FACE_P(zv) cairo_ft_font_face_fetch_object(Z_OBJ_P(zv))

//static inline cairo_ft_font_face_object *cairo_ft_font_face_object_get(zval *zv)
//{
//	cairo_ft_font_face_object *object = Z_CAIRO_FT_FONT_FACE_P(zv);
//	if(object->font_face == NULL) {
//		zend_throw_exception_ex(ce_cairo_exception, 0,
//			"Internal ft_font_face object missing in %s, you must call parent::__construct in extended classes",
//			ZSTR_VAL(Z_OBJCE_P(zv)->name));
//		return NULL;
//	}
//	return object;
//}


/* Functions for stream handling */
static unsigned long php_cairo_ft_read_func(FT_Stream stream, unsigned long offset, unsigned char* buffer, unsigned long count) {
	stream_closure *closure;
	closure = (stream_closure *)stream->descriptor.pointer;
	php_stream_seek(closure->stream, offset, SEEK_SET);
	return php_stream_read(closure->stream, (char *)buffer, count);
}

static void cairo_user_data_callback_ft_free(pecl_ft_container *ft_container) {
    if(ft_container->ft_face != NULL) {
        FT_Done_Face(ft_container->ft_face);
    }
    
    if(ft_container->ft_stream != NULL) {
        pefree(ft_container->ft_stream, 1);
    }
    
    if(ft_container->ft_lib != NULL) {
            FT_Done_FreeType(ft_container->ft_lib);
    }
    
    pefree(ft_container, 1);
}

static zend_bool php_cairo_create_ft_font_face(pecl_ft_container *ft_container, cairo_ft_font_face_object *font_face_object, php_stream *stream, zend_bool owned_stream, int load_flags, zend_bool throw_exceptions) 
{
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


	ft_stream = pecalloc(1, sizeof(*ft_stream), 1);
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
		pefree(ft_stream, 1);
        
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
                pefree(ft_stream, 1);
		return error;
	}

	return 0;
}

/* ----------------------------------------------------------------
    Cairo\FtFontFace Class API
------------------------------------------------------------------*/

ZEND_BEGIN_ARG_INFO_EX(CairoFtFontFace_construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_INFO(0, face)
	ZEND_ARG_INFO(0, load_flags)
ZEND_END_ARG_INFO()

/* {{{ proto CairoFtFontFace::__construct(string fontFilename, long load_flags)
	   Creates a new font face for the FreeType font backend from a pre-opened FreeType face. */
PHP_METHOD(CairoFtFontFace, __construct)
{
	zend_long load_flags = 0;
	int error = 0;
	zval *stream_zval = NULL;
	cairo_ft_font_face_object *font_face_object;
        pecl_ft_container *ft_container;

	php_stream *stream;
	zend_bool owned_stream = 0;
	php_stream_statbuf ssbuf;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "z|l", &stream_zval, &load_flags) == FAILURE)
	{
		return;
	}

	if(Z_TYPE_P(stream_zval) == IS_STRING) {
		stream = php_stream_open_wrapper(Z_STRVAL_P(stream_zval), "rb", REPORT_ERRORS, NULL);
		owned_stream = 1;
	} else if(Z_TYPE_P(stream_zval) == IS_RESOURCE)  {
		php_stream_from_zval(stream, stream_zval);	
	} else {	
		zend_throw_exception(ce_cairo_exception, "CairoFtFontFace::__construct() expects parameter 1 to be a string or a stream resource", 0);
		return;
	}

	if(!stream) {
		return;
	}
	
	if(php_stream_stat(stream, &ssbuf) != 0) {
		zend_throw_exception(ce_cairo_exception, "Cannot determine size of stream", 0);
		return;
	}

	//font_face_object = (cairo_ft_font_face_object *)zend_object_store_get_object(getThis());
        font_face_object = Z_CAIRO_FT_FONT_FACE_P(getThis());
        
        if(!font_face_object) {
            return;
        }

        ft_container = pecalloc(1, sizeof(pecl_ft_container), 1);
    
	error = FT_Init_FreeType(&ft_container->ft_lib);
	if(error) {
                pefree(ft_container, 1);
		zend_throw_exception(ce_cairo_exception, "Failed to initalise FreeType library", 0);
		RETURN_NULL();
	}
	
	error = php_cairo_create_ft_font_face(ft_container, font_face_object, stream, owned_stream, load_flags, 1);

	if (error) {
		const char *err_string = php_cairo_get_ft_error(error);
		zend_throw_exception_ex(ce_cairo_exception, error, "CairoFtFontFace::__construct(): An error occurred opening the file %s", err_string);
                pefree(ft_container, 1);
		RETURN_NULL();
	}
        
	php_cairo_throw_exception(cairo_font_face_status(font_face_object->font_face));
}

/* }}} */

/* {{{ proto long Cairo\FtFontFace->getStatus()
       Returns the current integer status of the CairoFontFace */
PHP_METHOD(CairoFtFontFace, getStatus)
{
	cairo_ft_font_face_object *font_face_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }

        font_face_object = Z_CAIRO_FT_FONT_FACE_P(getThis());
	if(!font_face_object) {
            return;
        }
        
        object_init_ex(return_value, ce_cairo_status);
        php_eos_datastructures_set_enum_value(return_value, cairo_font_face_status(font_face_object->font_face));
}
/* }}} */

/* {{{ proto long Cairo\FtFontFace->getType()
       Returns the current integer type of the CairoFontFace backend */
PHP_METHOD(CairoFtFontFace, getType)
{
	cairo_ft_font_face_object *font_face_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }

        font_face_object = Z_CAIRO_FT_FONT_FACE_P(getThis());
	if(!font_face_object) {
            return;
        }
        
        object_init_ex(return_value, ce_cairo_fonttype);
        php_eos_datastructures_set_enum_value(return_value, cairo_font_face_get_type(font_face_object->font_face));
}
/* }}} */

/* ----------------------------------------------------------------
    Cairo\FtFontFace Object management
------------------------------------------------------------------*/

/* {{{ */
static void cairo_ft_font_face_free_obj(zend_object *object)
{
    cairo_ft_font_face_object *intern = cairo_ft_font_face_fetch_object(object);

    if(!intern) {
            return;
    }

    if(intern->font_face && cairo_font_face_get_reference_count(intern->font_face) > 0){
            cairo_font_face_destroy(intern->font_face);
    }
    intern->font_face = NULL;
    
    if(intern->closure != NULL) {
        if(intern->closure->owned_stream) {
            php_stream_close(intern->closure->stream);
        }
        efree(intern->closure);
    }

    zend_object_std_dtor(&intern->std);
}

/* {{{ */
static zend_object* cairo_ft_font_face_obj_ctor(zend_class_entry *ce, cairo_ft_font_face_object **intern)
{
	cairo_ft_font_face_object *object = ecalloc(1, sizeof(cairo_ft_font_face_object) + zend_object_properties_size(ce));
        
        object->font_face = NULL;
        object->closure = NULL;
        
	zend_object_std_init(&object->std, ce);
	object->std.handlers = &cairo_ft_font_face_object_handlers;
	*intern = object;

	return &object->std;
}
/* }}} */

/* {{{ */
static zend_object* cairo_ft_font_face_create_object(zend_class_entry *ce)
{
	cairo_ft_font_face_object *ft_font_face_obj = NULL;
	zend_object *return_value = cairo_ft_font_face_obj_ctor(ce, &ft_font_face_obj);

	object_properties_init(&(ft_font_face_obj->std), ce);
	return return_value;
}
/* }}} */

/* {{{ cairo_ft_font_methods */
const zend_function_entry cairo_ft_font_methods[] = {
	PHP_ME(CairoFtFontFace, __construct, CairoFtFontFace_construct_args, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
        PHP_ME(CairoFtFontFace, getStatus, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoFtFontFace, getType, NULL, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};
/* }}} */

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(cairo_ft_font)
{
	zend_class_entry ft_font_face_ce;

        memcpy(&cairo_ft_font_face_object_handlers,
                    zend_get_std_object_handlers(),
                    sizeof(zend_object_handlers));
        
        /* FontOptions */
        cairo_ft_font_face_object_handlers.offset = XtOffsetOf(cairo_ft_font_face_object, std);
        cairo_ft_font_face_object_handlers.free_obj = cairo_ft_font_face_free_obj;
        
        INIT_NS_CLASS_ENTRY(ft_font_face_ce, CAIRO_NAMESPACE, ZEND_NS_NAME("FontFace", "Ft"), cairo_ft_font_methods);
        ft_font_face_ce.create_object = cairo_ft_font_face_create_object;
        ce_cairo_ftfont = zend_register_internal_class_ex(&ft_font_face_ce, ce_cairo_fontface);

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
