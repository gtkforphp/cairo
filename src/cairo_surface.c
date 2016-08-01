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

#include "php_cairo.h"
#include "php_cairo_internal.h"

zend_class_entry *ce_cairo_surface;
zend_class_entry *ce_cairo_content;
zend_class_entry *ce_cairo_surfacetype;

static zend_object_handlers cairo_surface_object_handlers; 

typedef struct _cairo_surface_object {
	cairo_surface_t *surface;
	zend_object std;
} cairo_surface_object;

static inline cairo_surface_object *cairo_surface_fetch_object(zend_object *object)
{
    return (cairo_surface_object *) ((char*)(object) - XtOffsetOf(cairo_surface_object, std));
}

ZEND_BEGIN_ARG_INFO(CairoSurface_createSimilar_args, ZEND_SEND_BY_VAL)
    ZEND_ARG_INFO(0, content)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoSurface_createForRectangle_args, ZEND_SEND_BY_VAL)
    ZEND_ARG_INFO(0, x)
    ZEND_ARG_INFO(0, y)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoSurface_markDirtyRectangle_args, ZEND_SEND_BY_VAL)
    ZEND_ARG_INFO(0, x)
    ZEND_ARG_INFO(0, y)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoSurface_setDeviceOffset_args, ZEND_SEND_BY_VAL)
    ZEND_ARG_INFO(0, x)
    ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoSurface_setFallbackResolution_args, ZEND_SEND_BY_VAL)
    ZEND_ARG_INFO(0, x)
    ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoSurface_writeToPng_args, ZEND_SEND_BY_VAL)
    ZEND_ARG_INFO(0, file)
ZEND_END_ARG_INFO()

/* {{{ proto void contruct()
   CairoSurface CANNOT be extended in userspace, this will throw an exception on use */
PHP_METHOD(CairoSurface, __construct) {
    zend_throw_exception(cairo_ce_cairoexception, "CairoSurface cannot be constructed", 0 TSRMLS_CC);
}
/* }}} */



/* {{{ cairo_surface_methods[] */
const zend_function_entry cairo_surface_methods[] = {
    PHP_ME(CairoSurface, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    /*
    PHP_ME_MAPPING(createSimilar, cairo_surface_create_similar, CairoSurface_createSimilar_args, ZEND_ACC_PUBLIC)
    PHP_ME_MAPPING(createForRectangle, cairo_surface_create_for_rectangle, CairoSurface_createForRectangle_args, ZEND_ACC_PUBLIC)
    PHP_ME_MAPPING(status, cairo_surface_status, NULL, ZEND_ACC_PUBLIC)
    PHP_ME_MAPPING(finish, cairo_surface_finish, NULL, ZEND_ACC_PUBLIC)
    PHP_ME_MAPPING(flush, cairo_surface_flush, NULL, ZEND_ACC_PUBLIC)
    PHP_ME_MAPPING(getFontOptions, cairo_surface_get_font_options, NULL, ZEND_ACC_PUBLIC)
    PHP_ME_MAPPING(getContent, cairo_surface_get_content, NULL, ZEND_ACC_PUBLIC)
    PHP_ME_MAPPING(markDirty, cairo_surface_mark_dirty, NULL, ZEND_ACC_PUBLIC)
    PHP_ME_MAPPING(markDirtyRectangle, cairo_surface_mark_dirty_rectangle, CairoSurface_markDirtyRectangle_args, ZEND_ACC_PUBLIC)
    PHP_ME_MAPPING(setDeviceOffset, cairo_surface_set_device_offset, CairoSurface_setDeviceOffset_args, ZEND_ACC_PUBLIC)
    PHP_ME_MAPPING(getDeviceOffset, cairo_surface_get_device_offset, NULL, ZEND_ACC_PUBLIC)
    PHP_ME_MAPPING(setFallbackResolution, cairo_surface_set_fallback_resolution, CairoSurface_setFallbackResolution_args, ZEND_ACC_PUBLIC)
    PHP_ME_MAPPING(getFallbackResolution, cairo_surface_get_fallback_resolution, NULL, ZEND_ACC_PUBLIC)
    PHP_ME_MAPPING(getType, cairo_surface_get_type, NULL, ZEND_ACC_PUBLIC)
    PHP_ME_MAPPING(copyPage, cairo_surface_copy_page, NULL, ZEND_ACC_PUBLIC)
    PHP_ME_MAPPING(showPage, cairo_surface_show_page, NULL, ZEND_ACC_PUBLIC)
    PHP_ME_MAPPING(hasShowTextGlyphs, cairo_surface_has_show_text_glyphs, NULL, ZEND_ACC_PUBLIC)
#ifdef CAIRO_HAS_PNG_FUNCTIONS
    PHP_ME_MAPPING(writeToPng, cairo_surface_write_to_png, CairoSurface_writeToPng_args, ZEND_ACC_PUBLIC)
#endif
    */
    {
        NULL, NULL, NULL}
};
/* }}} */

/* ----------------------------------------------------------------
    Cairo\Rectangle Object management
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
    }
    intern->buffer = NULL;

    if (intern->surface) {
        cairo_surface_finish(intern->surface);
        cairo_surface_destroy(intern->surface);
    }
    intern->surface = NULL;

    /* closure free up time */
    if (intern->closure) {
        if (intern->closure->owned_stream == 1) {
            php_stream_close(intern->closure->stream);
        }
        efree(intern->closure);
    }
    intern->closure = NULL;

    if (intern->parent_zval) {
        Z_DELREF_P(intern->parent_zval);
    }
    intern->parent_zval = NULL;

    zend_object_std_dtor(&intern->std);
}

/* {{{ */
static zend_object* cairo_surface_create_object(zend_class_entry *ce)
{
	cairo_surface_object *intern = NULL;
	zend_object *return_value = cairo_surface_obj_ctor(ce, &intern);

	object_properties_init(&(intern->std), ce);
	return return_value;
}
/* }}} */

/* Helper methods for stream surface read/writes */
cairo_status_t php_cairo_write_func(void *closure, const unsigned char *data, unsigned int length) {
    unsigned int written;
    stream_closure *cast_closure;
#ifdef ZTS
    TSRMLS_D;
#endif

    cast_closure = (stream_closure *) closure;
#ifdef ZTS
    TSRMLS_C = cast_closure->TSRMLS_C;
#endif

    written = php_stream_write(cast_closure->stream, data, length);
    if (written == length) {
        return CAIRO_STATUS_SUCCESS;
    } else {
        return CAIRO_STATUS_WRITE_ERROR;
    }
}

cairo_status_t php_cairo_read_func(void *closure, const unsigned char *data, unsigned int length) {
    unsigned int read;
    stream_closure *cast_closure;
#ifdef ZTS
    TSRMLS_D;
#endif

    cast_closure = (stream_closure *) closure;
#ifdef ZTS
    TSRMLS_C = cast_closure->TSRMLS_C;
#endif

    read = php_stream_read(cast_closure->stream, (char *) data, length);
    if (read == length) {
        return CAIRO_STATUS_SUCCESS;
    } else {
        return CAIRO_STATUS_READ_ERROR;
    }
}

/* Helper function to return the right ce given a class */
zend_class_entry* php_cairo_get_surface_ce(cairo_surface_t *surface TSRMLS_DC) {
    zend_class_entry *type;
    if (surface == NULL)
        return ce_cairo_surface;

    switch (cairo_surface_get_type(surface)) {
        case CAIRO_SURFACE_TYPE_IMAGE:
            type = cairo_ce_cairoimagesurface;
            break;
#ifdef CAIRO_HAS_PDF_SURFACE
        case CAIRO_SURFACE_TYPE_PDF:
            type = cairo_ce_cairopdfsurface;
            break;
#endif
#ifdef CAIRO_HAS_SVG_SURFACE
        case CAIRO_SURFACE_TYPE_SVG:
            type = cairo_ce_cairosvgsurface;
            break;
#endif

#ifdef CAIRO_HAS_PS_SURFACE
        case CAIRO_SURFACE_TYPE_PS:
            type = cairo_ce_cairopssurface;
            break;
#endif

#ifdef CAIRO_HAS_RECORDING_SURFACE
        case CAIRO_SURFACE_TYPE_RECORDING:
            type = cairo_ce_cairorecordingsurface;
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
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 10, 0)
        case CAIRO_SURFACE_TYPE_SUBSURFACE:
            type = cairo_ce_cairosubsurface;
            break;
#endif

        default:
            php_error(E_WARNING, "Unsupported Cairo Surface Type");
            return NULL;
    }
    return type;
}

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(cairo_surface) {
    zend_class_entry ce, content_ce, type_ce;

    INIT_CLASS_ENTRY(ce, "CairoSurface", cairo_surface_methods);
    ce_cairo_surface = zend_register_internal_class(&ce TSRMLS_CC);
    ce_cairo_surface->create_object = cairo_surface_object_new;
    ce_cairo_surface->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS;

    INIT_CLASS_ENTRY(content_ce, "CairoContent", NULL);
    ce_cairo_content = zend_register_internal_class(&content_ce TSRMLS_CC);
    ce_cairo_content->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS | ZEND_ACC_FINAL_CLASS;

#define REGISTER_CAIRO_CONTENT_LONG_CONST(const_name, value) \
	zend_declare_class_constant_long(ce_cairo_content, const_name, sizeof(const_name)-1, (long)value TSRMLS_CC); \
	REGISTER_LONG_CONSTANT(#value,  value,  CONST_CS | CONST_PERSISTENT);

    REGISTER_CAIRO_CONTENT_LONG_CONST("COLOR", CAIRO_CONTENT_COLOR);
    REGISTER_CAIRO_CONTENT_LONG_CONST("ALPHA", CAIRO_CONTENT_ALPHA);
    REGISTER_CAIRO_CONTENT_LONG_CONST("COLOR_ALPHA", CAIRO_CONTENT_COLOR_ALPHA);

    INIT_CLASS_ENTRY(type_ce, "CairoSurfaceType", NULL);
    ce_cairo_surfacetype = zend_register_internal_class(&type_ce TSRMLS_CC);
    ce_cairo_surfacetype->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS | ZEND_ACC_FINAL_CLASS;

#define REGISTER_CAIRO_SURFACETYPE_LONG_CONST(const_name, value) \
	zend_declare_class_constant_long(ce_cairo_surfacetype, const_name, sizeof(const_name)-1, (long)value TSRMLS_CC); \
	REGISTER_LONG_CONSTANT(#value,  value,  CONST_CS | CONST_PERSISTENT);

    REGISTER_CAIRO_SURFACETYPE_LONG_CONST("IMAGE", CAIRO_SURFACE_TYPE_IMAGE);
    REGISTER_CAIRO_SURFACETYPE_LONG_CONST("PDF", CAIRO_SURFACE_TYPE_PDF);
    REGISTER_CAIRO_SURFACETYPE_LONG_CONST("PS", CAIRO_SURFACE_TYPE_PS);
    REGISTER_CAIRO_SURFACETYPE_LONG_CONST("XLIB", CAIRO_SURFACE_TYPE_XLIB);
    REGISTER_CAIRO_SURFACETYPE_LONG_CONST("XCB", CAIRO_SURFACE_TYPE_XCB);
    REGISTER_CAIRO_SURFACETYPE_LONG_CONST("GLITZ", CAIRO_SURFACE_TYPE_GLITZ);
    REGISTER_CAIRO_SURFACETYPE_LONG_CONST("QUARTZ", CAIRO_SURFACE_TYPE_QUARTZ);
    REGISTER_CAIRO_SURFACETYPE_LONG_CONST("WIN32", CAIRO_SURFACE_TYPE_WIN32);
    REGISTER_CAIRO_SURFACETYPE_LONG_CONST("BEOS", CAIRO_SURFACE_TYPE_BEOS);
    REGISTER_CAIRO_SURFACETYPE_LONG_CONST("DIRECTFB", CAIRO_SURFACE_TYPE_DIRECTFB);
    REGISTER_CAIRO_SURFACETYPE_LONG_CONST("SVG", CAIRO_SURFACE_TYPE_SVG);
    REGISTER_CAIRO_SURFACETYPE_LONG_CONST("OS2", CAIRO_SURFACE_TYPE_OS2);
    REGISTER_CAIRO_SURFACETYPE_LONG_CONST("WIN32_PRINTING", CAIRO_SURFACE_TYPE_WIN32_PRINTING);
    REGISTER_CAIRO_SURFACETYPE_LONG_CONST("QUARTZ_IMAGE", CAIRO_SURFACE_TYPE_QUARTZ_IMAGE);

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
