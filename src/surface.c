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

zend_class_entry *ce_cairo_surface;
zend_class_entry *ce_cairo_content;
zend_class_entry *ce_cairo_surfacetype;


static zend_object_handlers cairo_surface_object_handlers; 

//typedef struct _stream_closure {
//    php_stream *stream;
//    zend_bool owned_stream;
//} stream_closure;

//typedef struct _cairo_surface_object {
//	cairo_surface_t *surface;
//        char * buffer;
//	stream_closure *closure;
//	zval *parent_zval;
//	zend_object std;
//} cairo_surface_object;

cairo_surface_object *cairo_surface_fetch_object(zend_object *object)
{
    return (cairo_surface_object *) ((char*)(object) - XtOffsetOf(cairo_surface_object, std));
}

//#define Z_CAIRO_SURFACE_P(zv) cairo_surface_fetch_object(Z_OBJ_P(zv))

cairo_surface_object *cairo_surface_object_get(zval *zv)
{
	cairo_surface_object *object = Z_CAIRO_SURFACE_P(zv);
	if(object->surface == NULL) {
		zend_throw_exception_ex(ce_cairo_exception, 0,
			"Internal surface object missing in %s, you must call parent::__construct in extended classes",
			ZSTR_VAL(Z_OBJCE_P(zv)->name));
		return NULL;
	}
	return object;
}

/* ----------------------------------------------------------------
    Cairo\Pattern Class API
------------------------------------------------------------------ */

ZEND_BEGIN_ARG_INFO(CairoSurface___construct_args, ZEND_SEND_BY_VAL)
ZEND_END_ARG_INFO()

/* {{{ proto void contruct()
   CairoSurface CANNOT be extended in userspace, this will throw an exception on use */
PHP_METHOD(CairoSurface, __construct) {
    zend_throw_exception(ce_cairo_exception, "CairoSurface cannot be constructed", 0);
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoSurface_createSimilar_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, content)
	ZEND_ARG_INFO(0, width)
	ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()

/* {{{ proto CairoSurface object CairoSurface->createSimilar(int content, double width, double height)
       Create a new surface that is as compatible as possible with an existing surface. */
PHP_METHOD(CairoSurface, createSimilar)
{
	cairo_surface_object *surface_object, *new_surface_object;
	cairo_surface_t *new_surface;
	zend_long content;
	double width, height;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "ldd", &content, &width, &height) == FAILURE) {
		return;
	}
        
	surface_object = cairo_surface_object_get(getThis());
	if(!surface_object) {
            return;
        }
	new_surface = cairo_surface_create_similar(surface_object->surface, content, width, height);

	/* we can't always rely on the same type of surface being returned, so we use php_cairo_get_surface_ce */
        object_init_ex(return_value, php_cairo_get_surface_ce(new_surface));
	new_surface_object = Z_CAIRO_SURFACE_P(return_value);
        
	if(!new_surface_object) {
		return;
        }
        
	new_surface_object->surface = new_surface;
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoSurface_createForRectangle_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
	ZEND_ARG_INFO(0, width)
	ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()

/* {{{ proto CairoSurface object CairoSurface->createForRectangle(double x, double y, double width, double height)
       create a new surface that is a rectangle within the target surface. */
PHP_METHOD(CairoSurface, createForRectangle)
{
	zval *surface_zval = NULL;
	cairo_surface_object *surface_object, *new_surface_object;
	cairo_surface_t *new_surface;
	double x, y, width, height;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "dddd", &x, &y, &width, &height) == FAILURE) {
            return;
	}

	surface_object = cairo_surface_object_get(getThis());
	if(!surface_object) {
            return;
        }
	new_surface = cairo_surface_create_for_rectangle(surface_object->surface, x, y, width, height);

        surface_zval = getThis();
	Z_ADDREF_P(surface_zval);

	object_init_ex(return_value, ce_cairo_subsurface);
        new_surface_object = Z_CAIRO_SURFACE_P(return_value);
	new_surface_object->parent_zval = surface_zval;
	new_surface_object->surface = new_surface;
}
/* }}} */


/* {{{ proto int CairoSurface->getStatus()
       Checks whether an error has previously occurred for this surface. */
PHP_METHOD(CairoSurface, getStatus)
{
	cairo_surface_object *surface_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}

	surface_object = cairo_surface_object_get(getThis());
	if(!surface_object) {
            return;
        }
        
        object_init_ex(return_value, ce_cairo_status);
        php_eos_datastructures_set_enum_value(return_value, cairo_surface_status(surface_object->surface));
}
/* }}} */

/* {{{ proto void CairoSurface->finish()
       This function finishes the surface and drops all references to external resources. For example,
       for the Xlib backend it means that cairo will no longer access the drawable, which can be freed. */
PHP_METHOD(CairoSurface, finish)
{
	cairo_surface_object *surface_object;

        if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}

	surface_object = cairo_surface_object_get(getThis());
	if(!surface_object) {
            return;
        }
        
	cairo_surface_finish(surface_object->surface);
}
/* }}} */

/* {{{ proto void CairoSurface->flush()
       Do any pending drawing for the surface and also restore any temporary modification's cairo has made
       to the surface's state. This function must be called before switching from drawing on the surface
       with cairo to drawing on it directly with native APIs. */
PHP_METHOD(CairoSurface, flush)
{
	cairo_surface_object *surface_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}

	surface_object = cairo_surface_object_get(getThis());
	if(!surface_object) {
            return;
        }
	cairo_surface_flush(surface_object->surface);
}
/* }}} */

/* {{{ proto CairoFontOptions object CairoSurface->getFontOptions()
       Retrieves the default font rendering options for the surface.  */
PHP_METHOD(CairoSurface, getFontOptions)
{
	cairo_surface_object *surface_object;
	cairo_font_options_object *font_object;
	cairo_font_options_t *options = cairo_font_options_create();
        
	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}

	surface_object = cairo_surface_object_get(getThis());
	if(!surface_object) {
            return;
        }

	object_init_ex(return_value, ce_cairo_fontoptions);
        font_object = cairo_font_options_fetch_object(Z_OBJ_P(return_value));

	cairo_surface_get_font_options(surface_object->surface, options);
	font_object->font_options = options;
}
/* }}} */

/* {{{ proto int CairoSurface->getContent()
       This function returns the content type of surface which indicates whether the surface contains color and/or alpha information.  */
PHP_METHOD(CairoSurface, getContent)
{
	cairo_surface_object *surface_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}

	surface_object = cairo_surface_object_get(getThis());
	if(!surface_object) {
            return;
        }
        
        object_init_ex(return_value, ce_cairo_content);
        php_eos_datastructures_set_enum_value(return_value, cairo_surface_get_content(surface_object->surface));
}
/* }}} */

/* {{{ proto void CairoSurface->markDirty()
       Tells cairo that drawing has been done to surface using means other than cairo, and that cairo should reread any cached areas. */
PHP_METHOD(CairoSurface, markDirty)
{
	cairo_surface_object *surface_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}

	surface_object = cairo_surface_object_get(getThis());
	if(!surface_object) {
            return;
        }
        
	cairo_surface_mark_dirty(surface_object->surface);
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoSurface_markDirtyRectangle_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
	ZEND_ARG_INFO(0, width)
	ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()

/* {{{ proto void CairoSurface->markDirtyRectangle(float x, float y, float width, float height)
       Drawing has been done only to the specified rectangle, so that cairo can retain cached contents for other parts of the surface.
       Any cached clip set on the surface will be reset by this function, to make sure that future cairo calls have the clip set that they expect.*/
PHP_METHOD(CairoSurface, markDirtyRectangle)
{
	cairo_surface_object *surface_object;
	double x = 0.0, y = 0.0, width = 0.0, height = 0.0;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "dddd", &x, &y, &width, &height) == FAILURE) {
		return;
	}

	surface_object = cairo_surface_object_get(getThis());
	if(!surface_object) {
            return;
        }
        
	cairo_surface_mark_dirty_rectangle(surface_object->surface, x, y, width, height);
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoSurface_setDeviceOffset_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

/* {{{ proto void CairoSurface->setDeviceOffset(float x, float y)
       Sets an offset that is added to the device coordinates determined by the CTM when drawing to surface. */
PHP_METHOD(CairoSurface, setDeviceOffset)
{
	cairo_surface_object *surface_object;
	double x = 0.0, y = 0.0;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "dd", &x, &y) == FAILURE) {
		return;
	}
        
        surface_object = cairo_surface_object_get(getThis());
	if(!surface_object) {
            return;
        }
        
	cairo_surface_set_device_offset(surface_object->surface, x, y);
}
/* }}} */

/* {{{ proto array CairoSurface->getDeviceOffset()
       This function returns the previous device offset */
PHP_METHOD(CairoSurface, getDeviceOffset)
{
	cairo_surface_object *surface_object;
	double x, y;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}

	surface_object = cairo_surface_object_get(getThis());
	if(!surface_object) {
            return;
        }
        
	cairo_surface_get_device_offset(surface_object->surface, &x, &y);

	array_init(return_value);
	add_next_index_double(return_value, x);
	add_next_index_double(return_value, y);
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoSurface_setFallbackResolution_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

/* {{{ proto void CairoSurface->setFallbackResolution(float x, float y)
      Set the horizontal and vertical resolution for image fallbacks.
      When certain operations aren't supported natively by a backend, cairo will fallback by
      rendering operations to an image and then overlaying that image onto the output. */
PHP_METHOD(CairoSurface, setFallbackResolution)
{
	cairo_surface_object *surface_object;
	double x = 0.0, y = 0.0;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "dd", &x, &y) == FAILURE) {
		return;
	}
        
        surface_object = cairo_surface_object_get(getThis());
	if(!surface_object) {
            return;
        }
        
	cairo_surface_set_fallback_resolution(surface_object->surface, x, y);
}
/* }}} */

/* {{{ proto array CairoSurface->getFallbackResolution()
       This function returns the previous fallback resolution */
PHP_METHOD(CairoSurface, getFallbackResolution)
{
	cairo_surface_object *surface_object;
	double x, y;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}

	surface_object = cairo_surface_object_get(getThis());
	if(!surface_object) {
            return;
        }
        
	cairo_surface_get_fallback_resolution(surface_object->surface, &x, &y);

	array_init(return_value);
	add_next_index_double(return_value, x);
	add_next_index_double(return_value, y);
}
/* }}} */

/* {{{ proto int CairoSurface->getType()
       This function returns the type of the backend used to create a surface. */
PHP_METHOD(CairoSurface, getType)
{
	cairo_surface_object *surface_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}

	surface_object = cairo_surface_object_get(getThis());
	if(!surface_object) {
            return;
        }
        
        object_init_ex(return_value, ce_cairo_surfacetype);
        php_eos_datastructures_set_enum_value(return_value, cairo_surface_get_type(surface_object->surface));
}
/* }}} */

/* {{{ proto void CairoSurface->showPage()
       Emits and clears the current page for backends that support multiple pages.
       Same as CairoContext->showPage(); */
PHP_METHOD(CairoSurface, showPage)
{
	cairo_surface_object *surface_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}

	surface_object = cairo_surface_object_get(getThis());
	if(!surface_object) {
            return;
        }
        
	cairo_surface_show_page(surface_object->surface);
}
/* }}} */

/* {{{ proto void CairoSurface->copyPage()
       Emits the current page for backends that support multiple pages,
       but doesn't clear it, so that the contents of the current page will be retained for the next page.
       Same as CairoContext->copyPage(); */
PHP_METHOD(CairoSurface, copyPage)
{
	cairo_surface_object *surface_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}

	surface_object = cairo_surface_object_get(getThis());
	if(!surface_object) {
            return;
        }
        
	cairo_surface_copy_page(surface_object->surface);
}
/* }}} */

/* {{{ proto bool CairoSurface->hasShowTextGlyphs()
       Returns whether the surface supports sophisticated cairo_show_text_glyphs() operations
       Users can use this function to avoid computing UTF-8 text and cluster mapping if the target surface does not use it.  */
PHP_METHOD(CairoSurface, hasShowTextGlyphs)
{
	cairo_surface_object *surface_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}

	surface_object = cairo_surface_object_get(getThis());
	if(!surface_object) {
            return;
        }
        
	RETURN_BOOL(cairo_surface_has_show_text_glyphs(surface_object->surface));
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoSurface_writeToPng_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, file)
ZEND_END_ARG_INFO()

#ifdef CAIRO_HAS_PNG_FUNCTIONS
/* {{{ proto int CairoSurface->writeToPng(file|resource file)
       Writes the contents of surface to a new file filename or PHP stream as a PNG image.
       Unlike some other stream supporting functions, you may NOT pass a null filename */
PHP_METHOD(CairoSurface, writeToPng)
{
	cairo_surface_object *surface_object;
	zval *stream_zval = NULL;
	stream_closure *closure;
	php_stream *stream = NULL;
	zend_bool owned_stream = 0;
	cairo_status_t status;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "z", &stream_zval) == FAILURE) {
		return;
	}

	surface_object = cairo_surface_object_get(getThis());
	if(!surface_object) {
            return;
        }

	if(Z_TYPE_P(stream_zval) == IS_STRING) {
		stream = php_stream_open_wrapper(Z_STRVAL_P(stream_zval), "w+b", REPORT_ERRORS, NULL);
		owned_stream = 1;
	} else if(Z_TYPE_P(stream_zval) == IS_RESOURCE)  {
		php_stream_from_zval(stream, stream_zval);	
	} else {
                zend_throw_exception(ce_cairo_exception, "Cairo\\Surface::writeToPng() expects parameter 1 to be a string or a stream resource", 0);
		return;
	}

	/* Pack TSRMLS info and stream into struct */
	closure = ecalloc(1, sizeof(stream_closure));
	closure->stream = stream;
	closure->owned_stream = owned_stream;

	status = cairo_surface_write_to_png_stream(surface_object->surface, php_cairo_write_func, (void *)closure);
	if (owned_stream) {
            php_stream_close(stream);
	}
	efree(closure);
        
        php_cairo_throw_exception(status);
}
/* }}} */
#endif

/* ----------------------------------------------------------------
    Cairo\Surface Object management
------------------------------------------------------------------*/

/* {{{ */
static void cairo_surface_free_obj(zend_object *object)
{
    cairo_surface_object *intern = cairo_surface_fetch_object(object);

    if(!intern) {
            return;
    }

    /* buffer for the create_from_data image stuff */
    if (intern->buffer) {
            efree(intern->buffer);
            intern->buffer = NULL;
    }

    if (intern->surface) {
            cairo_surface_finish(intern->surface);
            cairo_surface_destroy(intern->surface);
            intern->surface = NULL;
    }

    /* closure free up time */
    if (intern->closure) {
            if (intern->closure->owned_stream == 1) {
                php_stream_close(intern->closure->stream);
            }
            efree(intern->closure);
            intern->closure = NULL;
    }

    if (intern->parent_zval) {
            Z_DELREF_P(intern->parent_zval);
            intern->parent_zval = NULL;
    }

    zend_object_std_dtor(&intern->std);
}
/* }}} */

/* {{{ */
static zend_object* cairo_surface_obj_ctor(zend_class_entry *ce, cairo_surface_object **intern)
{
	cairo_surface_object *object = ecalloc(1, sizeof(cairo_surface_object) + zend_object_properties_size(ce));
        
        object->surface = NULL;
        object->buffer = NULL;
        object->closure = NULL;
        
	zend_object_std_init(&object->std, ce);
	object->std.handlers = &cairo_surface_object_handlers;
	*intern = object;

	return &object->std;
}
/* }}} */

/* {{{ */
zend_object* cairo_surface_create_object(zend_class_entry *ce)
{
	cairo_surface_object *surface = NULL;
	zend_object *return_value = cairo_surface_obj_ctor(ce, &surface);

	object_properties_init(&(surface->std), ce);
	return return_value;
}
/* }}} */


/* ----------------------------------------------------------------
    Cairo\Surface C API
------------------------------------------------------------------*/

/* Helper methods for stream surface read/writes */
cairo_status_t php_cairo_write_func(void *closure, const unsigned char *data, unsigned int length)
{
	size_t written;
	stream_closure *cast_closure;

	cast_closure = (stream_closure *)closure;

	written = php_stream_write(cast_closure->stream, data, length);
	if (written == length) {
            return CAIRO_STATUS_SUCCESS;
	} else {
            return CAIRO_STATUS_WRITE_ERROR;
	}
}

cairo_status_t php_cairo_read_func(void *closure, const unsigned char *data, unsigned int length)
{
	unsigned int read;
	stream_closure *cast_closure;

	cast_closure = (stream_closure *)closure;

	read = php_stream_read(cast_closure->stream, (char *)data, length);
	if (read == length) {
		return CAIRO_STATUS_SUCCESS;
	} else {
		return CAIRO_STATUS_READ_ERROR;
	}
}

zend_class_entry* php_cairo_get_surface_ce(cairo_surface_t *surface)
{
        zend_class_entry *type;
        
        if(surface == NULL) {
            return ce_cairo_surface;
        }

        switch (cairo_surface_get_type(surface)) {
            case CAIRO_SURFACE_TYPE_IMAGE:
                type = ce_cairo_imagesurface;
                break;

#ifdef CAIRO_HAS_PDF_SURFACE
            case CAIRO_SURFACE_TYPE_PDF:
                type = ce_cairo_pdfsurface;
                break;
#endif
#ifdef CAIRO_HAS_SVG_SURFACE
            case CAIRO_SURFACE_TYPE_SVG:
                type = ce_cairo_svgsurface;
                break;
#endif

#ifdef CAIRO_HAS_PS_SURFACE
            case CAIRO_SURFACE_TYPE_PS:
                type = ce_cairo_pssurface;
                break;
#endif

#ifdef CAIRO_HAS_RECORDING_SURFACE
            case CAIRO_SURFACE_TYPE_RECORDING:
                type = ce_cairo_recordingsurface;
                break;
#endif
                /*
                #ifdef CAIRO_HAS_WIN32_SURFACE
        case CAIRO_SURFACE_TYPE_WIN32:
                type = get_CairoWin32Surface_ce_ptr();
                break;
                #endif
                #ifdef CAIRO_HAS_XLIB_SURFACE
        case CAIRO_SURFACE_TYPE_XLIB:
                type = get_CairoXlibSurface_ce_ptr();
                break;
                #endif
                #ifdef CAIRO_HAS_QUARTZ_SURFACE
        case CAIRO_SURFACE_TYPE_QUARTZ:
                type = get_CairoQuartzSurface_ce_ptr();
                break;
                #endif */

            case CAIRO_SURFACE_TYPE_SUBSURFACE:
                type = ce_cairo_subsurface;
                break;

            default:
                php_error(E_WARNING, "Unsupported Cairo Surface Type");
                return NULL;
        }
        return type;
}

/* ----------------------------------------------------------------
    Cairo\Surface Definition and registration
------------------------------------------------------------------*/

/* {{{ cairo_pattern_methods[] */
const zend_function_entry cairo_surface_methods[] = {
	PHP_ME(CairoSurface, __construct, CairoSurface___construct_args, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
        PHP_ME(CairoSurface, createSimilar, CairoSurface_createSimilar_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoSurface, createForRectangle, CairoSurface_createForRectangle_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoSurface, getStatus, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoSurface, finish, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoSurface, flush, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoSurface, getFontOptions, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoSurface, getContent, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoSurface, markDirty, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoSurface, markDirtyRectangle, CairoSurface_markDirtyRectangle_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoSurface, setDeviceOffset, CairoSurface_setDeviceOffset_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoSurface, getDeviceOffset, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoSurface, setFallbackResolution, CairoSurface_setFallbackResolution_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoSurface, getFallbackResolution, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoSurface, getType, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoSurface, showPage, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoSurface, copyPage, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoSurface, hasShowTextGlyphs, NULL, ZEND_ACC_PUBLIC)
#ifdef CAIRO_HAS_PNG_FUNCTIONS
        PHP_ME(CairoSurface, writeToPng, CairoSurface_writeToPng_args, ZEND_ACC_PUBLIC)
#endif
	ZEND_FE_END
};
/* }}} */


/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(cairo_surface) 
{
        zend_class_entry surface_ce, content_ce, type_ce;

        //memcpy(&cairo_surface_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
        memcpy(&cairo_surface_object_handlers, zend_get_std_object_handlers(), sizeof(cairo_surface_object_handlers));
        
        /* Surface */
        cairo_surface_object_handlers.offset = XtOffsetOf(cairo_surface_object, std);
        cairo_surface_object_handlers.free_obj = cairo_surface_free_obj;

        INIT_NS_CLASS_ENTRY(surface_ce, CAIRO_NAMESPACE, "Surface", cairo_surface_methods);
        ce_cairo_surface = zend_register_internal_class(&surface_ce);
        ce_cairo_surface->create_object = cairo_surface_create_object;
        ce_cairo_surface->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS;
        
        /* CairoContent */
        INIT_NS_CLASS_ENTRY(content_ce, CAIRO_NAMESPACE, ZEND_NS_NAME("Surface", "Content"), NULL);
	ce_cairo_content = zend_register_internal_class_ex(&content_ce, php_eos_datastructures_get_enum_ce());
	ce_cairo_content->ce_flags |= ZEND_ACC_FINAL;
        
        #define CAIRO_CONTENT_DECLARE_ENUM(name) \
            zend_declare_class_constant_long(ce_cairo_content, #name, \
            sizeof(#name)-1, CAIRO_CONTENT_## name);
            
        CAIRO_CONTENT_DECLARE_ENUM(COLOR);
        CAIRO_CONTENT_DECLARE_ENUM(ALPHA);
        CAIRO_CONTENT_DECLARE_ENUM(COLOR_ALPHA);
        
        /* SurfaceType */
        INIT_NS_CLASS_ENTRY(type_ce, CAIRO_NAMESPACE, ZEND_NS_NAME("Surface", "Type"), NULL);
        ce_cairo_surfacetype = zend_register_internal_class_ex(&type_ce, php_eos_datastructures_get_enum_ce());
        ce_cairo_surfacetype->ce_flags |= ZEND_ACC_FINAL;
        
        #define CAIRO_SURFACETYPE_DECLARE_ENUM(name) \
            zend_declare_class_constant_long(ce_cairo_surfacetype, #name, \
            sizeof(#name)-1, CAIRO_SURFACE_TYPE_## name);
            
        CAIRO_SURFACETYPE_DECLARE_ENUM(IMAGE);
        CAIRO_SURFACETYPE_DECLARE_ENUM(PDF);
        CAIRO_SURFACETYPE_DECLARE_ENUM(PS);
        CAIRO_SURFACETYPE_DECLARE_ENUM(XLIB);
        CAIRO_SURFACETYPE_DECLARE_ENUM(XCB);
        CAIRO_SURFACETYPE_DECLARE_ENUM(GLITZ);
        CAIRO_SURFACETYPE_DECLARE_ENUM(QUARTZ);
        CAIRO_SURFACETYPE_DECLARE_ENUM(WIN32);
        CAIRO_SURFACETYPE_DECLARE_ENUM(BEOS);
        CAIRO_SURFACETYPE_DECLARE_ENUM(DIRECTFB);
        CAIRO_SURFACETYPE_DECLARE_ENUM(SVG);
        CAIRO_SURFACETYPE_DECLARE_ENUM(OS2);
        CAIRO_SURFACETYPE_DECLARE_ENUM(WIN32_PRINTING);
        CAIRO_SURFACETYPE_DECLARE_ENUM(QUARTZ_IMAGE);
        CAIRO_SURFACETYPE_DECLARE_ENUM(SCRIPT);
        CAIRO_SURFACETYPE_DECLARE_ENUM(QT);
        CAIRO_SURFACETYPE_DECLARE_ENUM(RECORDING);
        CAIRO_SURFACETYPE_DECLARE_ENUM(VG);
        CAIRO_SURFACETYPE_DECLARE_ENUM(GL);
        CAIRO_SURFACETYPE_DECLARE_ENUM(DRM);
        CAIRO_SURFACETYPE_DECLARE_ENUM(TEE);
        CAIRO_SURFACETYPE_DECLARE_ENUM(XML);
        CAIRO_SURFACETYPE_DECLARE_ENUM(SKIA);
        CAIRO_SURFACETYPE_DECLARE_ENUM(SUBSURFACE);
        CAIRO_SURFACETYPE_DECLARE_ENUM(COGL);
        
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
