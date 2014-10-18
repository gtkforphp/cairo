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

#include "php.h"
#include "php_cairo.h"
#include "zend_exceptions.h"

zend_class_entry *cairo_ce_cairoimagesurface;
zend_class_entry *cairo_ce_cairoformat;

ZEND_BEGIN_ARG_INFO(CairoImageSurface___construct_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, format)
	ZEND_ARG_INFO(0, width)
	ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(CairoImageSurface_createForData_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 4)
	ZEND_ARG_INFO(0, data)
	ZEND_ARG_INFO(0, format)
	ZEND_ARG_INFO(0, width)
	ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoFormat_strideForWidth_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, format)
	ZEND_ARG_INFO(0, width)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoImageSurface_createFromPng_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, file)
ZEND_END_ARG_INFO()

#if CAIRO_VERSION < CAIRO_VERSION_ENCODE(1, 6, 0)
static int php_cairo_format_stride_for_width(cairo_format_t format, int width) {
	int bpp = 0, stride = 0;

	switch (format) {
		case CAIRO_FORMAT_ARGB32:
			bpp = 32;
		case CAIRO_FORMAT_RGB24:
			bpp = 32;
		case CAIRO_FORMAT_A8:
			bpp = 8;
		case CAIRO_FORMAT_A1:
			bpp = 1;
		default:
			bpp = 0;
	}

	if (bpp > 0) {
		stride = (((bpp * width) + 31) >> 5) << 2;
		return stride;
	}

	return 0;
}
#endif

/* {{{ proto void __construct(int format, int width, int height)
       Returns new CairoSurfaceImage object created on an image surface */
PHP_METHOD(CairoImageSurface, __construct)
{
	long format, width, height;
	cairo_surface_object *surface_object;

	PHP_CAIRO_ERROR_HANDLING(TRUE)
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lll", &format, &width, &height) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(TRUE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(TRUE)

	surface_object = (cairo_surface_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
	surface_object->surface = cairo_image_surface_create(format, width, height);
	php_cairo_throw_exception(cairo_surface_status(surface_object->surface) TSRMLS_CC);
}
/* }}} */

/* {{{ proto CairoSurfaceImage cairo_image_surface_create(int format, int width, int height)
       Returns new CairoSurfaceImage object created on an image surface */
PHP_FUNCTION(cairo_image_surface_create)
{
	long format, width, height;
	cairo_surface_object *surface_object;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lll", &format, &width, &height) == FAILURE) {
		return;
	}

	object_init_ex(return_value, cairo_ce_cairoimagesurface);
	surface_object = (cairo_surface_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	surface_object->surface = cairo_image_surface_create(format, width, height);
	php_cairo_trigger_error(cairo_surface_status(surface_object->surface) TSRMLS_CC);
}
/* }}} */

/* {{{ proto CairoImageSurface object cairo_image_surface_create_for_data(string data, int format, int width, int height)
       Creates an image surface for the provided pixel data. */
PHP_FUNCTION(cairo_image_surface_create_for_data)
{
	/* NOTE: we have to keep the data buffer around, so we put it in the cairo_surface_object */
	char *data;
	int data_len;
	long format, width, height, stride = -1;
	cairo_surface_object *surface_object;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "slll", &data, &data_len, &format, &width, &height) == FAILURE) {
		return;
	}

	if (format < 0) {
		zend_error(E_WARNING, "Invalid format for cairo_image_surface_create_for_data()");
		return;
	}

	if (width < 1 || height < 1) {
		zend_error(E_WARNING, "Invalid surface dimensions for cairo_image_surface_create_for_data()");
		return;
	}

	/* Figure out our stride */
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 6, 0)
	/* This is the way the stride SHOULD be done */
	stride = cairo_format_stride_for_width (format, width);
#else
	stride = php_cairo_format_stride_for_width(format, width);
#endif
	if (stride <= 0) {
		zend_error(E_WARNING, "Could not calculate stride for surface in cairo_image_surface_create_for_data()");
		return;
	}

	/* Create the object, stick in the buffer and surface, check our status */
	object_init_ex(return_value, cairo_ce_cairoimagesurface);
	surface_object = (cairo_surface_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	/* allocate our internal surface object buffer - has to be left lying around until we destroy the image */
	surface_object->buffer = safe_emalloc(stride * height, sizeof(char), 0);
	
	if(surface_object->buffer == NULL) {
		zend_error(E_WARNING, "cairo_image_surface_create_for_data(): Could not allocate memory for buffer");
		return;
	}

	/* copy our data into the buffer */
	surface_object->buffer = memcpy(surface_object->buffer, data, data_len);
	/* create our surface and check for errors */
	surface_object->surface = cairo_image_surface_create_for_data((unsigned char*)surface_object->buffer, format, width, height, stride);
	php_cairo_trigger_error(cairo_surface_status(surface_object->surface) TSRMLS_CC);
}
/* }}} */

/* {{{ proto CairoImageSurface Object CairoImageSurface::createForData(string data, int format, int width, int height, int stride)
       Creates an image surface for the provided pixel data. */
PHP_METHOD(CairoImageSurface, createForData)
{
	/* NOTE: we have to keep the data buffer around, so we put it in the cairo_surface_object */
	char *data;
	int data_len;
	long format, width, height, stride = -1;
	cairo_surface_object *surface_object;

	PHP_CAIRO_ERROR_HANDLING(TRUE)
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "slll", &data, &data_len, &format, &width, &height) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(TRUE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(TRUE)
	
	if (format < 0) {
		zend_throw_exception(cairo_ce_cairoexception, "CairoImageSurface::createForData(): invalid format", 0 TSRMLS_CC);
		return;
	}

	if (width < 1 || height < 1) {
		zend_throw_exception(cairo_ce_cairoexception, "CairoImageSurface::createForData(): invalid surface dimensions", 0 TSRMLS_CC);
		return;
	}
	
	if (stride >= INT_MAX || stride < -1) {
		zend_error(E_WARNING, "Invalid stride for cairo_image_surface_create_for_data()");
		return;
	}

	/* Figure out our stride */
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 6, 0)
	/* This is the way the stride SHOULD be done */
	stride = cairo_format_stride_for_width (format, width);
#else
	stride = php_cairo_format_stride_for_width(format, width);
#endif
	if (stride <= 0) {
		zend_error(E_WARNING, "Could not calculate stride for surface in cairo_image_surface_create_for_data()");
		return;
	}

	/* Create the object, stick in the buffer and surface, check our status */
	object_init_ex(return_value, cairo_ce_cairoimagesurface);
	surface_object = (cairo_surface_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	/* allocate our internal surface object buffer - has to be left lying around until we destroy the image */
	surface_object->buffer = safe_emalloc(stride * height, sizeof(char), 0);

	if(surface_object->buffer == NULL) {
		zend_throw_exception(cairo_ce_cairoexception, "CairoImageSurface::createForData(): Could not allocate memory for buffer", 0 TSRMLS_CC);
		return;
	}

	/* copy our data into the buffer */
	surface_object->buffer = memcpy(surface_object->buffer, data, data_len);
	/* create our surface and check for errors */
	surface_object->surface = cairo_image_surface_create_for_data((unsigned char*)surface_object->buffer, format, width, height, stride);
	php_cairo_throw_exception(cairo_surface_status(surface_object->surface) TSRMLS_CC);
}
/* }}} */

/* {{{ proto string cairo_image_surface_get_data(CairoImageSurface object)
       proto string CairoImageSurface->getData()
       Get the string data of the image surface, for direct inspection or modification */
PHP_FUNCTION(cairo_image_surface_get_data)
{
	zval *surface_zval;
	cairo_surface_object *surface_object;
	unsigned char *data;	
	long height, stride;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &surface_zval, cairo_ce_cairoimagesurface) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	surface_object = (cairo_surface_object *)cairo_surface_object_get(surface_zval TSRMLS_CC);
	PHP_CAIRO_ERROR(cairo_surface_status(surface_object->surface));

	data = cairo_image_surface_get_data(surface_object->surface);
	height = cairo_image_surface_get_height(surface_object->surface);
	stride = cairo_image_surface_get_stride(surface_object->surface);
	RETURN_STRINGL(data, height * stride, 1);
}
/* }}} */

/* {{{ proto int cairo_image_surface_get_format(CairoImageSurface object)
       proto int CairoImageSurface->getFormat()
       Get the format of the surface */
PHP_FUNCTION(cairo_image_surface_get_format)
{
	zval *surface_zval;
	cairo_surface_object *surface_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &surface_zval, cairo_ce_cairoimagesurface) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	surface_object = (cairo_surface_object *)cairo_surface_object_get(surface_zval TSRMLS_CC);
	PHP_CAIRO_ERROR(cairo_surface_status(surface_object->surface));

	RETURN_LONG(cairo_image_surface_get_format(surface_object->surface));
}
/* }}} */

/* {{{ proto int cairo_image_surface_get_width(CairoImageSurface object)
       proto int CairoImageSurface->getWidth()
       Get the width of the image surface in pixels. */
PHP_FUNCTION(cairo_image_surface_get_width)
{
	zval *surface_zval;
	cairo_surface_object *surface_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &surface_zval, cairo_ce_cairoimagesurface) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	surface_object = (cairo_surface_object *)cairo_surface_object_get(surface_zval TSRMLS_CC);
	PHP_CAIRO_ERROR(cairo_surface_status(surface_object->surface));

	RETURN_LONG(cairo_image_surface_get_width(surface_object->surface));
}
/* }}} */

/* {{{ proto int cairo_image_surface_get_height(CairoImageSurface object)
       proto int CairoImageSurface->getHeight()
       Get the height of the image surface in pixels. */
PHP_FUNCTION(cairo_image_surface_get_height)
{
	zval *surface_zval;
	cairo_surface_object *surface_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &surface_zval, cairo_ce_cairoimagesurface) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	surface_object = (cairo_surface_object *)cairo_surface_object_get(surface_zval TSRMLS_CC);
	PHP_CAIRO_ERROR(cairo_surface_status(surface_object->surface));

	RETURN_LONG(cairo_image_surface_get_height(surface_object->surface));
}
/* }}} */

/* {{{ proto int cairo_image_surface_get_stride(CairoImageSurface object)
       proto int CairoImageSurface->getStride()
       Get the stride of the image surface in bytes */
PHP_FUNCTION(cairo_image_surface_get_stride)
{
	zval *surface_zval;
	cairo_surface_object *surface_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &surface_zval, cairo_ce_cairoimagesurface) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	surface_object = (cairo_surface_object *)cairo_surface_object_get(surface_zval TSRMLS_CC);
	PHP_CAIRO_ERROR(cairo_surface_status(surface_object->surface));

	RETURN_LONG(cairo_image_surface_get_stride(surface_object->surface));
}
/* }}} */

#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 6, 0)
/* {{{ proto int cairo_format_stride_for_width(long format, long width)
	   This function provides a stride value that will respect all alignment 
	   requirements of the accelerated image-rendering code within cairo. */
PHP_FUNCTION(cairo_format_stride_for_width)
{
	long format, width;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &format, &width) == FAILURE) {
		return;
	}

	RETURN_LONG(cairo_format_stride_for_width(format, width));
}
/* }}} */

/* {{{ proto int CairoFormat::strideForWidth(long format, long width)
	   This function provides a stride value that will respect all alignment 
	   requirements of the accelerated image-rendering code within cairo. */
PHP_METHOD(CairoFormat, strideForWidth)
{
	long format, width;

	PHP_CAIRO_ERROR_HANDLING(TRUE)
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &format, &width) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(TRUE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(TRUE)

	RETURN_LONG(cairo_format_stride_for_width(format, width));
}
/* }}} */
#endif

#ifdef CAIRO_HAS_PNG_FUNCTIONS
/* {{{ proto CairoImageSurface object cairo_image_surface_create_from_png(file|resource file)
       Creates a new image surface and initializes the contents to the given PNG file. */
PHP_FUNCTION(cairo_image_surface_create_from_png)
{
	cairo_surface_object *surface_object;
	zval *stream_zval = NULL;
	stream_closure *closure;
	zend_bool owned_stream = 0;
	php_stream *stream = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &stream_zval) == FAILURE) {
		return;
	}

	object_init_ex(return_value, cairo_ce_cairoimagesurface);
	surface_object = (cairo_surface_object *)zend_object_store_get_object(return_value TSRMLS_CC);

	if(Z_TYPE_P(stream_zval) == IS_STRING) {
		stream = php_stream_open_wrapper(Z_STRVAL_P(stream_zval), "rw+b", REPORT_ERRORS|ENFORCE_SAFE_MODE, NULL);
		owned_stream = 1;
	} else if(Z_TYPE_P(stream_zval) == IS_RESOURCE)  {
		php_stream_from_zval(stream, &stream_zval);	
	} else {
		zend_error(E_WARNING, "cairo_image_surface_create_from_png() expects parameter 1 to be a string or a stream resource");
		RETURN_NULL();
	}

	if(!stream) {
		RETURN_NULL();
	}

	/* Pack TSRMLS info and stream into struct */
	closure = ecalloc(1, sizeof(stream_closure));
	closure->stream = stream;
	closure->owned_stream = owned_stream;
#ifdef ZTS
	closure->TSRMLS_C = TSRMLS_C;
#endif

	surface_object->closure = closure;
	surface_object->surface = cairo_image_surface_create_from_png_stream((cairo_read_func_t) php_cairo_read_func, (void *)closure);
	php_cairo_trigger_error(cairo_surface_status(surface_object->surface) TSRMLS_CC);
}
/* }}} */

/* {{{ proto CairoImageSurface object CairoImageSurface::createFromPng(file|resource file)
       Creates a new image surface and initializes the contents to the given PNG file. */
PHP_METHOD(CairoImageSurface, createFromPng)
{
	cairo_surface_object *surface_object;
	zval *stream_zval = NULL;
	stream_closure *closure;
	zend_bool owned_stream = 0;
	php_stream *stream = NULL;

	PHP_CAIRO_ERROR_HANDLING(TRUE)
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &stream_zval) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(TRUE)
		return;
	}

	object_init_ex(return_value, cairo_ce_cairoimagesurface);
	surface_object = (cairo_surface_object *)zend_object_store_get_object(return_value TSRMLS_CC);

	if(Z_TYPE_P(stream_zval) == IS_STRING) {
		stream = php_stream_open_wrapper(Z_STRVAL_P(stream_zval), "rb", REPORT_ERRORS|ENFORCE_SAFE_MODE, NULL);
		owned_stream = 1;
	} else if(Z_TYPE_P(stream_zval) == IS_RESOURCE)  {
		php_stream_from_zval(stream, &stream_zval);	
	} else {
		zend_throw_exception(cairo_ce_cairoexception, "CairoImageSurface::createFromPng() expects parameter 1 to be a string or a stream resource", 0 TSRMLS_CC);
		return;
	}

	if(!stream) {
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(TRUE)

	/* Pack TSRMLS info and stream into struct */
	closure = ecalloc(1, sizeof(stream_closure));
	closure->stream = stream;
	closure->owned_stream = owned_stream;
#ifdef ZTS
	closure->TSRMLS_C = TSRMLS_C;
#endif

	surface_object->closure = closure;
	surface_object->surface = cairo_image_surface_create_from_png_stream((cairo_read_func_t) php_cairo_read_func, (void *)closure);
	PHP_CAIRO_ERROR(cairo_surface_status(surface_object->surface));
}
/* }}} */
#endif

/* {{{ cairo_context_methods[] */
const zend_function_entry cairo_image_surface_methods[] = {
	PHP_ME(CairoImageSurface, __construct, CairoImageSurface___construct_args, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(CairoImageSurface, createForData, CairoImageSurface_createForData_args, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME_MAPPING(getData, cairo_image_surface_get_data, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(getFormat, cairo_image_surface_get_format, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(getWidth, cairo_image_surface_get_width, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(getHeight, cairo_image_surface_get_height, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(getStride, cairo_image_surface_get_stride, NULL, ZEND_ACC_PUBLIC)
#ifdef CAIRO_HAS_PNG_FUNCTIONS
	PHP_ME(CairoImageSurface, createFromPng, CairoImageSurface_createFromPng_args, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)  
#endif
	{NULL, NULL, NULL}
};
/* }}} */

#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 6, 0)
/* {{{ cairo_context_methods[] */
const zend_function_entry cairo_format_methods[] = {
	PHP_ME(CairoFormat, strideForWidth, CairoFormat_strideForWidth_args, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	{NULL, NULL, NULL}
};
#endif

/* }}} */

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(cairo_image_surface)
{
	zend_class_entry ce, format_ce;

	INIT_CLASS_ENTRY(ce, "CairoImageSurface", cairo_image_surface_methods);
	cairo_ce_cairoimagesurface = zend_register_internal_class_ex(&ce, cairo_ce_cairosurface, "CairoSurface" TSRMLS_CC);
	cairo_ce_cairoimagesurface->create_object = cairo_surface_object_new;

#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 6, 0)
	INIT_CLASS_ENTRY(format_ce, "CairoFormat", cairo_format_methods);
#else
	INIT_CLASS_ENTRY(format_ce, "CairoFormat", NULL);
#endif
	cairo_ce_cairoformat = zend_register_internal_class(&format_ce TSRMLS_CC);
	cairo_ce_cairoformat->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS | ZEND_ACC_FINAL_CLASS;

	#define REGISTER_CAIRO_FORMAT_LONG_CONST(const_name, value) \
	zend_declare_class_constant_long(cairo_ce_cairoformat, const_name, sizeof(const_name)-1, (long)value TSRMLS_CC); \
	REGISTER_LONG_CONSTANT(#value,  value,  CONST_CS | CONST_PERSISTENT);

	REGISTER_CAIRO_FORMAT_LONG_CONST("ARGB32", CAIRO_FORMAT_ARGB32);
	REGISTER_CAIRO_FORMAT_LONG_CONST("RGB24", CAIRO_FORMAT_RGB24);
	REGISTER_CAIRO_FORMAT_LONG_CONST("A8", CAIRO_FORMAT_A8);
	REGISTER_CAIRO_FORMAT_LONG_CONST("A1", CAIRO_FORMAT_A1);

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
