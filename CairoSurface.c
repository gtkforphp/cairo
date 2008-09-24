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
  | Author: Akshat Gupta <g.akshat@gmail.com>                            |
  |         Elizabeth Smith <auroraeosrose@php.net>                      |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#include "php_cairo_api.h"
#include "php_cairo_internal.h"

/* {{{ Class CairoSurface */

static zend_object_handlers CairoSurface_handlers;

cairo_status_t _write_func(void *closure, const unsigned char *data, unsigned int length)
{
	unsigned int written;
	php_stream *zs = (php_stream *)closure ;
	TSRMLS_FETCH();
	written = php_stream_write(zs, data, length);
	if(written == length)
		return CAIRO_STATUS_SUCCESS;
	else {
		printf("is it an error ?");
		return CAIRO_STATUS_WRITE_ERROR;
	}
}

cairo_status_t _read_func(void *closure, unsigned char *data, unsigned int length)
{
	unsigned int read;
	php_stream *zs = (php_stream *)closure;
	TSRMLS_FETCH();
	read = php_stream_read(zs, data, length);
	if(read == length)
		return CAIRO_STATUS_SUCCESS;
	else {
		printf("is it an error");
		return CAIRO_STATUS_READ_ERROR;
	}

}

ZEND_BEGIN_ARG_INFO_EX(CairoSurface__create_similar_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 3)
  ZEND_ARG_INFO(0, content)
  ZEND_ARG_INFO(0, width)
  ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(CairoSurface__mark_dirty_rectangle_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
  ZEND_ARG_INFO(0, x)
  ZEND_ARG_INFO(0, y)
  ZEND_ARG_INFO(0, width)
  ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(CairoSurface__set_device_offset_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, x_offset)
  ZEND_ARG_INFO(0, y_offset)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(CairoSurface__set_fallback_resolution_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, x_ppi)
  ZEND_ARG_INFO(0, y_ppi)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(CairoSurface__write_to_png_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, file)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(CairoSurface__write_to_png_stream_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, zstream)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(CairoImageSurface____construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, widthm)
  ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(CairoImageSurface__create_from_data_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 4)
  ZEND_ARG_INFO(0, obj)
  ZEND_ARG_INFO(0, format)
  ZEND_ARG_INFO(0, width)
  ZEND_ARG_INFO(0, height)
  ZEND_ARG_INFO(0, stride)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(CairoImageSurface__create_from_png_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, file)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(CairoImageSurface__create_from_png_stream_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
 ZEND_ARG_INFO(0, zstream)
ZEND_END_ARG_INFO()

/* {{{ Methods */


/* {{{ proto void construct()
   */
PHP_METHOD(CairoSurface, __construct)
{

	if (ZEND_NUM_ARGS()>0)	{
		WRONG_PARAM_COUNT;
		return;
	}

	php_error(E_WARNING,"No direct call for this constructor");


}
/* }}} __construct */



/* {{{ proto object createSimilar(int content, int width, int height)
   */
PHP_METHOD(CairoSurface, createSimilar)
{
	zend_class_entry *ce;
	zval * _this_zval = NULL;
	cairo_surface_t *sur;
	int content;
	long width = 0;
	long height = 0;
	cairo_surface_object *curr, *sobj;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Olll", &_this_zval, CairoSurface_ce_ptr, &content, &width, &height) == FAILURE) {
		return;
	}

	curr = (cairo_surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	sur = cairo_surface_create_similar(curr->surface, content, width, height);
	ce = get_CairoSurface_ce_ptr(sur);
	object_init_ex(return_value, ce);
	sobj = (cairo_surface_object *)zend_objects_get_address(return_value TSRMLS_CC);
	sobj->surface = cairo_surface_reference(sur);

}
/* }}} createSimilar */


/* {{{ proto void finish()
   */
PHP_METHOD(CairoSurface, finish)
{

	zval * _this_zval = NULL;
	cairo_surface_object *curr;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoSurface_ce_ptr) == FAILURE) {
		return;
	}

	curr = (cairo_surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_surface_finish(curr->surface);
}
/* }}} finish */



/* {{{ proto void flush()
   */
PHP_METHOD(CairoSurface, flush)
{

	zval * _this_zval = NULL;
	cairo_surface_object *curr;
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoSurface_ce_ptr) == FAILURE) {
		return;
	}

	curr = (cairo_surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	
	cairo_surface_flush(curr->surface);

}
/* }}} flush */



/* {{{ proto int getContent()
   */
PHP_METHOD(CairoSurface, getContent)
{

	zval * _this_zval = NULL;
	cairo_surface_object *curr;
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoSurface_ce_ptr) == FAILURE) {
		return;
	}

	curr = (cairo_surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	
	RETURN_LONG(cairo_surface_get_content(curr->surface));
}
/* }}} getContent */



/* {{{ proto array getDeviceOffset()
   */
PHP_METHOD(CairoSurface, getDeviceOffset)
{

	zval * _this_zval = NULL;
	double x_offset, y_offset;
	cairo_surface_object *curr;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoSurface_ce_ptr) == FAILURE) {
		return;
	}

	curr = (cairo_surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);

	cairo_surface_get_device_offset(curr->surface, &x_offset, &y_offset);

	array_init(return_value);
	add_assoc_double(return_value, "x", x_offset);
	add_assoc_double(return_value, "y", y_offset);

}
/* }}} getDeviceOffset */



/* {{{ proto object getFontOptions()
   */
PHP_METHOD(CairoSurface, getFontOptions)
{

	zval * _this_zval = NULL;
	
	cairo_font_options_t *options = cairo_font_options_create();
	cairo_surface_object *curr;	
	cairo_fontoptions_object *fobj;
	zend_class_entry *ce;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoSurface_ce_ptr) == FAILURE) {
		return;
	}

	curr = (cairo_surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
    ce = get_CairoFontFace_ce_ptr();
	cairo_surface_get_font_options(curr->surface, options);
	object_init_ex(return_value, ce);
	fobj = (cairo_fontoptions_object *)zend_objects_get_address(return_value TSRMLS_CC);
	fobj->fontoptions = options;

}
/* }}} getFontOptions */



/* {{{ proto void markDirtyRectangle([int x, int y, int width, int height])
   */
PHP_METHOD(CairoSurface, markDirtyRectangle)
{

	zval * _this_zval = NULL;
	long x = 0;
	long y = 0;
	long width = -1;
	long height = -1;
	cairo_surface_object *curr;


	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O|llll", &_this_zval, CairoSurface_ce_ptr, &x, &y, &width, &height) == FAILURE) {
		return;
	}
	curr = (cairo_surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_surface_mark_dirty_rectangle(curr->surface, x, y, width, height);

}
/* }}} markDirtyRectangle */



/* {{{ proto void setDeviceOffset(float x_offset, float y_offset)
   */
PHP_METHOD(CairoSurface, setDeviceOffset)
{

	zval * _this_zval = NULL;
	double x_offset = 0.0;
	double y_offset = 0.0;
	cairo_surface_object *curr;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odd", &_this_zval, CairoSurface_ce_ptr, &x_offset, &y_offset) == FAILURE) {
		return;
	}

	curr = (cairo_surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_surface_set_device_offset(curr->surface, x_offset, y_offset);

}
/* }}} setDeviceOffset */



/* {{{ proto void setFallbackResolution(float x_ppi, float y_ppi)
   */
PHP_METHOD(CairoSurface, setFallbackResolution)
{

	zval * _this_zval = NULL;
	double x_ppi = 0.0;
	double y_ppi = 0.0;
	cairo_surface_object *curr;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odd", &_this_zval, CairoSurface_ce_ptr, &x_ppi, &y_ppi) == FAILURE) {
		return;
	}

	curr = (cairo_surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_surface_set_fallback_resolution(curr->surface, x_ppi, y_ppi);	

}
/* }}} setFallbackResolution */



/* {{{ proto void writeToPng(string file)
   */
PHP_METHOD(CairoSurface, writeToPng)
{

	zval * _this_zval = NULL;
	const char * file = NULL;
	int file_len = 0;
	cairo_status_t status;
	cairo_surface_object *curr;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Os", &_this_zval, CairoSurface_ce_ptr, &file, &file_len) == FAILURE) {
		return;
	}

	curr = (cairo_surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	status = cairo_surface_write_to_png(curr->surface, file);

}
/* }}} writeToPng */


/* {{{ proto void writeToPngStream(stream file)
	*/
PHP_METHOD(CairoSurface, writeToPngStream)
{
	zval *_this_zval = NULL;
	cairo_status_t status;
	zval *zstream;
	php_stream *stream;
	cairo_surface_object *curr;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Or", &_this_zval, CairoSurface_ce_ptr, &zstream)) {
		return;
	}
	
	curr = (cairo_surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	php_stream_from_zval(stream, &zstream);
	status = cairo_surface_write_to_png_stream(curr->surface, _write_func, stream);

}

/* }}} writeToPngStream*/


static zend_function_entry CairoSurface_methods[] = {
	PHP_ME(CairoSurface, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(CairoSurface, createSimilar, CairoSurface__create_similar_args, ZEND_ACC_PUBLIC)
	PHP_ME(CairoSurface, finish, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CairoSurface, flush, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CairoSurface, getContent, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CairoSurface, getDeviceOffset, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CairoSurface, getFontOptions, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CairoSurface, markDirtyRectangle, CairoSurface__mark_dirty_rectangle_args, ZEND_ACC_PUBLIC)
	PHP_ME(CairoSurface, setDeviceOffset, CairoSurface__set_device_offset_args, ZEND_ACC_PUBLIC)
	PHP_ME(CairoSurface, setFallbackResolution, CairoSurface__set_fallback_resolution_args, ZEND_ACC_PUBLIC)
	PHP_ME(CairoSurface, writeToPng, CairoSurface__write_to_png_args, ZEND_ACC_PUBLIC)
	PHP_ME(CairoSurface, writeToPngStream, CairoSurface__write_to_png_stream_args, ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

/* }}} Methods */


static void CairoSurface_object_dtor(void *object)
{
	cairo_surface_object *surface = (cairo_surface_object *)object;
	zend_hash_destroy(surface->std.properties);
	FREE_HASHTABLE(surface->std.properties);
	if(surface->surface){
		cairo_surface_finish(surface->surface);
		cairo_surface_destroy(surface->surface);
		
	}
	efree(object);
}

zend_object_value CairoSurface_object_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	cairo_surface_object *surface;
	zval *temp;

	surface = emalloc(sizeof(cairo_surface_object));
	memset(surface,0,sizeof(cairo_surface_object));

	surface->std.ce = ce;

	ALLOC_HASHTABLE(surface->std.properties);
	zend_hash_init(surface->std.properties, 0, NULL, ZVAL_PTR_DTOR, 0);
	zend_hash_copy(surface->std.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref,(void *) &temp, sizeof(zval *));
	retval.handle = zend_objects_store_put(surface, NULL, (zend_objects_free_object_storage_t)CairoSurface_object_dtor, NULL TSRMLS_CC);
	retval.handlers = &CairoSurface_handlers;
	return retval;
}

void class_init_CairoSurface(TSRMLS_D)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "CairoSurface", CairoSurface_methods);
	CairoSurface_ce_ptr = zend_register_internal_class(&ce TSRMLS_CC);
	CairoSurface_ce_ptr->create_object = CairoSurface_object_new;
	memcpy(&CairoSurface_handlers, zend_get_std_object_handlers(),sizeof(zend_object_handlers));
	CairoSurface_handlers.clone_obj = NULL;
}

/* }}} Class CairoSurface */

/* {{{ Class CairoImageSurface	-- done  :)*/

static zend_class_entry * CairoImageSurface_ce_ptr = NULL;
static zend_object_handlers CairoImageSurface_handlers;


/* {{{ Methods */


/* {{{ proto void construct(int format, int widthm, int height)
   */
PHP_METHOD(CairoImageSurface, __construct)
{
	zval * _this_zval;

	cairo_format_t format = 0;
	long widthm = 0;
	long height = 0;
	cairo_surface_object *curr;


	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lll", &format, &widthm, &height) == FAILURE) {
		return;
	}

	_this_zval = getThis();
	curr = (cairo_surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	curr->surface = cairo_image_surface_create(format, widthm, height);

}
/* }}} __construct */



/* {{{ proto void createFromData(string obj, int format, int width, int height [, int stride])
   */
PHP_METHOD(CairoImageSurface, createFromData)
{

	zval * _this_zval = NULL;
	char * buffer = NULL;
	int buffer_len = 0;
	long format = 0;
	long width = 0;
	long height = 0;
	long stride = -1;
	cairo_surface_object *curr;


	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Oslll|l", &_this_zval, CairoImageSurface_ce_ptr, &buffer, &buffer_len, &format, &width, &height, &stride) == FAILURE) {
		return;
	}

	curr = (cairo_surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_surface_finish(curr->surface);
	cairo_surface_destroy(curr->surface);
	
	if(stride < 0 ){
		switch(format) {
			case CAIRO_FORMAT_ARGB32:
			case CAIRO_FORMAT_RGB24:
				stride = width * 4;
				break;
			case CAIRO_FORMAT_RGB16_565:
				stride = width * 2;
				break;
			case CAIRO_FORMAT_A8:
				stride = width;
				break;
			case CAIRO_FORMAT_A1:
				stride = (width + 1) / 8;
				break;
			default:
				php_error(E_WARNING, "Unknown format");
				return;
				
		}
	}
	/*
	if (height * stride > buffer_len) {
		php_error(E_WARNING,"buffer is not long enough");
		return;
	}
	*/
	curr->surface = cairo_image_surface_create_for_data(buffer, format, width, height, stride);

}
/* }}} createFromData */



/* {{{ proto void createFromPng(string file)
   */
PHP_METHOD(CairoImageSurface, createFromPng)
{

	zval * _this_zval = NULL;
	const char * file = NULL;
	int file_len = 0;
	cairo_surface_object *curr;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Os", &_this_zval, CairoImageSurface_ce_ptr, &file, &file_len) == FAILURE) {
		return;
	}

	curr = (cairo_surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);

	curr->surface = cairo_image_surface_create_from_png(file);

}
/* }}} createFromPng */



/* {{{ proto void createFromPngStream(stream zstream)
 */

PHP_METHOD(CairoImageSurface, createFromPngStream)
{	
	zval *_this_zval = NULL;
	zval *zstream;
	php_stream *stream;
	cairo_surface_object *curr;

   if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Or", &_this_zval, CairoImageSurface_ce_ptr, &zstream)) {
		return;
	}
										
	curr = (cairo_surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	
	php_stream_from_zval(stream, &zstream);
	curr->surface = cairo_image_surface_create_from_png_stream( _read_func, stream);


}

/* }}} createFromPngStream*/



/* {{{ proto string getData() -- not required
   */
PHP_METHOD(CairoImageSurface, getData)
{

	zval * _this_zval = NULL;
	char *str;
	cairo_surface_object *curr;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoImageSurface_ce_ptr) == FAILURE) {
		return;
	}

	curr = (cairo_surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);

	
	str = cairo_image_surface_get_data(curr->surface);
	RETURN_STRING(str, 0);
}
/* }}} getData */



/* {{{ proto int getFormat()
   */
PHP_METHOD(CairoImageSurface, getFormat)
{
	zval * _this_zval = NULL;
	cairo_surface_object *curr;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoImageSurface_ce_ptr) == FAILURE) {
		return;
	}
	curr = (cairo_surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	
	RETURN_LONG(cairo_image_surface_get_format(curr->surface));
}
/* }}} getFormat */



/* {{{ proto int getHeight()
   */
PHP_METHOD(CairoImageSurface, getHeight)
{
	zval * _this_zval = NULL;
	cairo_surface_object *curr;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoImageSurface_ce_ptr) == FAILURE) {
		return;
	}

	curr = (cairo_surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	RETURN_LONG(cairo_image_surface_get_height(curr->surface));

}
/* }}} getHeight */



/* {{{ proto int getStride()
   */
PHP_METHOD(CairoImageSurface, getStride)
{
	zval * _this_zval = NULL;
	cairo_surface_object *curr;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoImageSurface_ce_ptr) == FAILURE) {
		return;
	}

	curr = (cairo_surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	RETURN_LONG(cairo_image_surface_get_stride(curr->surface));

}
/* }}} getStride */



/* {{{ proto int getWidth()
   */
PHP_METHOD(CairoImageSurface, getWidth)
{
	zval * _this_zval = NULL;
	cairo_surface_object *curr;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoImageSurface_ce_ptr) == FAILURE) {
		return;
	}


	curr = (cairo_surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);

	RETURN_LONG(cairo_image_surface_get_width(curr->surface));
}
/* }}} getWidth */


static zend_function_entry CairoImageSurface_methods[] = {
	PHP_ME(CairoImageSurface, __construct, CairoImageSurface____construct_args, /**/ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(CairoImageSurface, createFromData, CairoImageSurface__create_from_data_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoImageSurface, createFromPng, CairoImageSurface__create_from_png_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoImageSurface, createFromPngStream, CairoImageSurface__create_from_png_stream_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoImageSurface, getData, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoImageSurface, getFormat, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoImageSurface, getHeight, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoImageSurface, getStride, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoImageSurface, getWidth, NULL, /**/ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

/* }}} Methods */

static zend_object_value CairoImageSurface_object_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	retval = CairoSurface_object_new(ce TSRMLS_CC);
	retval.handlers = &CairoImageSurface_handlers;
	return retval;
}


void class_init_CairoImageSurface(TSRMLS_D)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "CairoImageSurface", CairoImageSurface_methods);
	CairoImageSurface_ce_ptr = zend_register_internal_class_ex(&ce, CairoSurface_ce_ptr, "CairoSurface" TSRMLS_CC);
	CairoImageSurface_ce_ptr->create_object = CairoImageSurface_object_new;
	memcpy(&CairoImageSurface_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
}

/* }}} Class CairoImageSurface */

/* {{{ Helper Functions */
PHP_CAIRO_API zend_class_entry *  get_CairoSurface_ce_ptr(cairo_surface_t *surface)
{
	zend_class_entry *type;
	if(surface == NULL)
		return NULL;
	
	switch(cairo_surface_get_type(surface)) {
		case CAIRO_SURFACE_TYPE_IMAGE:
			type = CairoImageSurface_ce_ptr;
			break;
#ifdef CAIRO_HAS_PDF_SURFACE
		case CAIRO_SURFACE_TYPE_PDF:
			type = get_CairoPdfSurface_ce_ptr();
			break;
#endif
#ifdef CAIRO_HAS_PS_SURFACE
		case CAIRO_SURFACE_TYPE_PS:
			type = get_CairoPsSurface_ce_ptr();
			break;
#endif
#ifdef CAIRO_HAS_SVG_SURFACE
		case CAIRO_SURFACE_TYPE_SVG:
			type = get_CairoSvgSurface_ce_ptr();
			break;
#endif
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
#endif
		default:
			php_error(E_WARNING,"Unsupported Surface Type");
			return NULL;
	}
	return type;
}

/* }}} Helper Function*/


