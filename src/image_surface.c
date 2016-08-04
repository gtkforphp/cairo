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

zend_class_entry *ce_cairo_imagesurface;
zend_class_entry *ce_cairo_format;

/* ----------------------------------------------------------------
    Cairo\ImageSurface Class API
------------------------------------------------------------------*/

ZEND_BEGIN_ARG_INFO(CairoImageSurface___construct_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, format)
	ZEND_ARG_INFO(0, width)
	ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()

/* {{{ proto void __construct(int format, int width, int height)
       Returns new CairoSurfaceImage object created on an image surface */
PHP_METHOD(CairoImageSurface, __construct)
{
	long format, width, height;
	cairo_surface_object *surface_object;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "lll", &format, &width, &height) == FAILURE) {
		return;
	}

	surface_object = Z_CAIRO_SURFACE_P(getThis());
	if(!surface_object) {
            return;
        }
	surface_object->surface = cairo_image_surface_create(format, width, height);
	php_cairo_throw_exception(cairo_surface_status(surface_object->surface));
}
/* }}} */

ZEND_BEGIN_ARG_INFO_EX(CairoImageSurface_createForData_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 4)
	ZEND_ARG_INFO(0, data)
	ZEND_ARG_INFO(0, format)
	ZEND_ARG_INFO(0, width)
	ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()

/* {{{ proto CairoImageSurface Object CairoImageSurface::createForData(string data, int format, int width, int height, int stride)
       Creates an image surface for the provided pixel data. */
PHP_METHOD(CairoImageSurface, createForData)
{
	/* NOTE: we have to keep the data buffer around, so we put it in the cairo_surface_object */
	char *data;
	int data_len;
	long format, width, height, stride = -1;
	cairo_surface_object *surface_object;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "slll", &data, &data_len, &format, &width, &height) == FAILURE) {
		return;
	}
	
	if (format < 0) {
		zend_throw_exception(ce_cairo_exception, "CairoImageSurface::createForData(): invalid format", 0);
		return;
	}

	if (width < 1 || height < 1) {
		zend_throw_exception(ce_cairo_exception, "CairoImageSurface::createForData(): invalid surface dimensions", 0);
		return;
	}
	
	if (stride >= INT_MAX || stride < -1) {
		zend_error(E_WARNING, "Invalid stride for cairo_image_surface_create_for_data()");
		return;
	}

	/* Figure out our stride */
	/* This is the way the stride SHOULD be done */
	stride = cairo_format_stride_for_width (format, width);

	if (stride <= 0) {
		zend_error(E_WARNING, "Could not calculate stride for surface in cairo_image_surface_create_for_data()");
		return;
	}

	/* Create the object, stick in the buffer and surface, check our status */
	object_init_ex(return_value, ce_cairo_imagesurface);
	surface_object = Z_CAIRO_SURFACE_P(return_value);
        
	if(!surface_object) {
		return;
        }
        
	/* allocate our internal surface object buffer - has to be left lying around until we destroy the image */
	surface_object->buffer = safe_emalloc(stride * height, sizeof(char), 0);
        
	if(surface_object->buffer == NULL) {
		zend_throw_exception(ce_cairo_exception, "CairoImageSurface::createForData(): Could not allocate memory for buffer", 0);
		return;
	}

	/* copy our data into the buffer */
	surface_object->buffer = memcpy(surface_object->buffer, data, data_len);
	
        /* create our surface and check for errors */
	surface_object->surface = cairo_image_surface_create_for_data((unsigned char*)surface_object->buffer, format, width, height, stride);
	php_cairo_throw_exception(cairo_surface_status(surface_object->surface));
}
/* }}} */

/* {{{ proto string CairoImageSurface->getData()
       Get the string data of the image surface, for direct inspection or modification */
PHP_METHOD(CairoImageSurface, getData)
{
	cairo_surface_object *surface_object;
	unsigned char *data;	
	long height, stride;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }

        surface_object = Z_CAIRO_SURFACE_P(getThis());
	if(!surface_object) {
            return;
        }
        
	php_cairo_throw_exception(cairo_surface_status(surface_object->surface));

	data = cairo_image_surface_get_data(surface_object->surface);
	height = cairo_image_surface_get_height(surface_object->surface);
	stride = cairo_image_surface_get_stride(surface_object->surface);
        
	RETURN_STRINGL(data, height * stride);
}
/* }}} */

/* {{{ proto int CairoImageSurface->getFormat()
       Get the format of the surface */
PHP_METHOD(CairoImageSurface, getFormat)
{
	cairo_surface_object *surface_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }

        surface_object = Z_CAIRO_SURFACE_P(getThis());
	if(!surface_object) {
            return;
        }
        
	php_cairo_throw_exception(cairo_surface_status(surface_object->surface));

	RETURN_LONG(cairo_image_surface_get_format(surface_object->surface));
}
/* }}} */

/* {{{ proto int CairoImageSurface->getWidth()
       Get the width of the image surface in pixels. */
PHP_METHOD(CairoImageSurface, getWidth)
{
	cairo_surface_object *surface_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }

        surface_object = Z_CAIRO_SURFACE_P(getThis());
	if(!surface_object) {
            return;
        }
        
	php_cairo_throw_exception(cairo_surface_status(surface_object->surface));

	RETURN_LONG(cairo_image_surface_get_width(surface_object->surface));
}
/* }}} */

/* {{{ proto int CairoImageSurface->getHeight()
       Get the height of the image surface in pixels. */
PHP_METHOD(CairoImageSurface, getHeight)
{
	cairo_surface_object *surface_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }

        surface_object = Z_CAIRO_SURFACE_P(getThis());
	if(!surface_object) {
            return;
        }
        
	php_cairo_throw_exception(cairo_surface_status(surface_object->surface));

	RETURN_LONG(cairo_image_surface_get_height(surface_object->surface));
}
/* }}} */

/* {{{ proto int CairoImageSurface->getStride()
       Get the stride of the image surface in bytes */
PHP_METHOD(CairoImageSurface, getStride)
{
	cairo_surface_object *surface_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }

        surface_object = Z_CAIRO_SURFACE_P(getThis());
	if(!surface_object) {
            return;
        }
        
	php_cairo_throw_exception(cairo_surface_status(surface_object->surface));

	RETURN_LONG(cairo_image_surface_get_stride(surface_object->surface));
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoFormat_strideForWidth_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, format)
	ZEND_ARG_INFO(0, width)
ZEND_END_ARG_INFO()

/* {{{ proto int CairoFormat::strideForWidth(long format, long width)
        This function provides a stride value that will respect all alignment 
        requirements of the accelerated image-rendering code within cairo. */
PHP_METHOD(CairoFormat, strideForWidth)
{
	long format, width;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "ll", &format, &width) == FAILURE) {
		return;
	}
        
	RETURN_LONG(cairo_format_stride_for_width(format, width));
}
/* }}} */

#ifdef CAIRO_HAS_PNG_FUNCTIONS

ZEND_BEGIN_ARG_INFO(CairoImageSurface_createFromPng_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, file)
ZEND_END_ARG_INFO()

/* {{{ proto CairoImageSurface object CairoImageSurface::createFromPng(file|resource file)
       Creates a new image surface and initializes the contents to the given PNG file. */
PHP_METHOD(CairoImageSurface, createFromPng)
{
	cairo_surface_object *surface_object;
	zval *stream_zval = NULL;
	stream_closure *closure;
	zend_bool owned_stream = 0;
	php_stream *stream = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "z", &stream_zval) == FAILURE) {
		return;
	}

	object_init_ex(return_value, ce_cairo_imagesurface);
	surface_object = Z_CAIRO_SURFACE_P(return_value);

	if(Z_TYPE_P(stream_zval) == IS_STRING) {
                // "rb" or "rw+b" ?
		stream = php_stream_open_wrapper(Z_STRVAL_P(stream_zval), "rb", REPORT_ERRORS, NULL);
		owned_stream = 1;
	} else if(Z_TYPE_P(stream_zval) == IS_RESOURCE)  {
		php_stream_from_zval(stream, stream_zval);	
	} else {
		zend_throw_exception(ce_cairo_exception, "CairoImageSurface::createFromPng() expects parameter 1 to be a string or a stream resource", 0);
		return;
	}

	if(!stream) {
		return;
	}

	// Pack TSRMLS info and stream into struct
	closure = ecalloc(1, sizeof(stream_closure));
	closure->stream = stream;
	closure->owned_stream = owned_stream;

	surface_object->closure = closure;
	surface_object->surface = cairo_image_surface_create_from_png_stream((cairo_read_func_t) php_cairo_read_func, (void *)closure);
	php_cairo_throw_exception(cairo_surface_status(surface_object->surface));
}
/* }}} */
#endif

/* ----------------------------------------------------------------
    Cairo\FontOptions Definition and registration
------------------------------------------------------------------*/

/* {{{ cairo_imagesurface_methods[] */
const zend_function_entry cairo_imagesurface_methods[] = {
        PHP_ME(CairoImageSurface, __construct, CairoImageSurface___construct_args, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(CairoImageSurface, createForData, CairoImageSurface_createForData_args, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(CairoImageSurface, getData, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CairoImageSurface, getFormat, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CairoImageSurface, getWidth, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CairoImageSurface, getHeight, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CairoImageSurface, getStride, NULL, ZEND_ACC_PUBLIC)
#ifdef CAIRO_HAS_PNG_FUNCTIONS
	PHP_ME(CairoImageSurface, createFromPng, CairoImageSurface_createFromPng_args, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)  
#endif
	ZEND_FE_END
};
/* }}} */

/* {{{ cairo_format_methods[] */
const zend_function_entry cairo_format_methods[] = {
	PHP_ME(CairoFormat, strideForWidth, CairoFormat_strideForWidth_args, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_FE_END
};
/* }}} */

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(cairo_image_surface)
{
        zend_class_entry ce, format_ce;

	INIT_NS_CLASS_ENTRY(ce, CAIRO_NAMESPACE, ZEND_NS_NAME("Surface", "Image"), cairo_imagesurface_methods);
	ce_cairo_imagesurface = zend_register_internal_class_ex(&ce, ce_cairo_surface);
	ce_cairo_imagesurface->create_object = cairo_surface_create_object;

        INIT_NS_CLASS_ENTRY(format_ce, CAIRO_NAMESPACE, ZEND_NS_NAME("Surface", "ImageFormat"), cairo_format_methods);
	ce_cairo_format = zend_register_internal_class_ex(&format_ce, php_eos_datastructures_get_enum_ce());
	ce_cairo_format->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS | ZEND_ACC_FINAL;
        
        #define CAIRO_FORMAT_DECLARE_ENUM(name) \
            zend_declare_class_constant_long(ce_cairo_format, #name, \
            sizeof(#name)-1, CAIRO_FORMAT_## name);

        CAIRO_FORMAT_DECLARE_ENUM(ARGB32);
        CAIRO_FORMAT_DECLARE_ENUM(RGB30);
        CAIRO_FORMAT_DECLARE_ENUM(RGB24);
        CAIRO_FORMAT_DECLARE_ENUM(RGB16_565);
        CAIRO_FORMAT_DECLARE_ENUM(A8);
        CAIRO_FORMAT_DECLARE_ENUM(A1);
        
	return SUCCESS;
}
/* }}} */
