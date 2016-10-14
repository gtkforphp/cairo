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
  |         Mark Skilbeck <markskilbeck@php.net>                         |
  +----------------------------------------------------------------------+
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_cairo.h"
#include "zend_exceptions.h"

zend_class_entry *cairo_ce_cairosurface;
zend_class_entry *cairo_ce_cairocontent;
zend_class_entry *cairo_ce_cairosurfacetype;

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
PHP_METHOD(CairoSurface, __construct)
{
	zend_throw_exception(cairo_ce_cairoexception, "CairoSurface cannot be constructed", 0 TSRMLS_CC);
}
/* }}} */

/* {{{ proto CairoSurface object cairo_surface_create_similar(CairoSurface object, int content, double width, double height)
       proto CairoSurface object CairoSurface->createSimilar(int content, int width, int height)
       Create a new surface that is as compatible as possible with an existing surface. */
PHP_FUNCTION(cairo_surface_create_similar)
{
	zval *surface_zval = NULL;
	cairo_surface_object *surface_object, *new_surface_object;
	cairo_surface_t *new_surface;
	long content, width, height;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Olll", &surface_zval, cairo_ce_cairosurface, &content, &width, &height) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	surface_object = (cairo_surface_object *)cairo_surface_object_get(surface_zval TSRMLS_CC);
	new_surface = cairo_surface_create_similar(surface_object->surface, content, width, height);

	/* we can't always rely on the same type of surface being returned, so we use php_cairo_get_surface_ce */
	object_init_ex(return_value, php_cairo_get_surface_ce(new_surface TSRMLS_CC));
	new_surface_object = (cairo_surface_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	new_surface_object->surface = new_surface;
}
/* }}} */

/* {{{ proto CairoSurface object cairo_surface_create_for_rectangle(CairoSurface target, double x, double y, double width, double height)
	   proto CairoSurface object CairoSurface->createForRectangle(double x, double y, double width, double height)
	   Create a new surface that is a rectangle within the target surface. */

#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 10, 0)
PHP_FUNCTION(cairo_surface_create_for_rectangle)
{
	zval *surface_zval = NULL;
	cairo_surface_object *surface_object, *new_surface_object;
	cairo_surface_t *new_surface;
	double x, y, width, height;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odddd", &surface_zval, cairo_ce_cairosurface, &x, &y, &width, &height) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	surface_object = (cairo_surface_object *)cairo_surface_object_get(surface_zval TSRMLS_CC);
	new_surface = cairo_surface_create_for_rectangle(surface_object->surface, x, y, width, height);

	Z_ADDREF_P(surface_zval);

	object_init_ex(return_value, cairo_ce_cairosubsurface);
	new_surface_object = (cairo_surface_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	new_surface_object->parent_zval = surface_zval;
	new_surface_object->surface = new_surface;
}
#endif

/* }}} */

/* {{{ proto int cairo_surface_status(CairoSurface object)
       proto int CairoSurface->status()
       Checks whether an error has previously occurred for this surface. */
PHP_FUNCTION(cairo_surface_status)
{
	zval *surface_zval = NULL;
	cairo_surface_object *surface_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &surface_zval, cairo_ce_cairosurface) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	surface_object = (cairo_surface_object *)cairo_surface_object_get(surface_zval TSRMLS_CC);
	RETURN_LONG(cairo_surface_status(surface_object->surface));
}
/* }}} */

/* {{{ proto void cairo_surface_finish(CairoSurface object)
       proto void CairoSurface->finish()
       This function finishes the surface and drops all references to external resources. For example,
       for the Xlib backend it means that cairo will no longer access the drawable, which can be freed. */
PHP_FUNCTION(cairo_surface_finish)
{
	zval *surface_zval = NULL;
	cairo_surface_object *surface_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &surface_zval, cairo_ce_cairosurface) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	surface_object = (cairo_surface_object *)cairo_surface_object_get(surface_zval TSRMLS_CC);
	cairo_surface_finish(surface_object->surface);
}
/* }}} */

/* {{{ proto void cairo_surface_flush(CairoSurface object)
       proto void CairoSurface->flush()
       Do any pending drawing for the surface and also restore any temporary modification's cairo has made
       to the surface's state. This function must be called before switching from drawing on the surface
       with cairo to drawing on it directly with native APIs. */
PHP_FUNCTION(cairo_surface_flush)
{
	zval *surface_zval = NULL;
	cairo_surface_object *surface_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &surface_zval, cairo_ce_cairosurface) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	surface_object = (cairo_surface_object *)cairo_surface_object_get(surface_zval TSRMLS_CC);
	cairo_surface_flush(surface_object->surface);
}
/* }}} */

/* {{{ proto CairoFontOptions object cairo_surface_get_font_options(CairoSurface object)
       proto CairoFontOptions object CairoSurface->getFontOptions()
       Retrieves the default font rendering options for the surface.  */
PHP_FUNCTION(cairo_surface_get_font_options)
{
	zval *surface_zval = NULL;
	cairo_surface_object *surface_object;
	cairo_font_options_object *font_object;
	cairo_font_options_t *options = cairo_font_options_create();

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &surface_zval, cairo_ce_cairosurface) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	object_init_ex(return_value, cairo_ce_cairofontoptions);
	font_object = (cairo_font_options_object *)zend_object_store_get_object(return_value TSRMLS_CC);

	surface_object = (cairo_surface_object *)cairo_surface_object_get(surface_zval TSRMLS_CC);
	cairo_surface_get_font_options(surface_object->surface, options);
	font_object->font_options = options;
}
/* }}} */

/* {{{ proto int cairo_surface_get_content(CairoSurface object)
       proto int CairoSurface->getContent()
       This function returns the content type of surface which indicates whether the surface contains color and/or alpha information.  */
PHP_FUNCTION(cairo_surface_get_content)
{
	zval *surface_zval = NULL;
	cairo_surface_object *surface_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &surface_zval, cairo_ce_cairosurface) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	surface_object = (cairo_surface_object *)cairo_surface_object_get(surface_zval TSRMLS_CC);
	RETURN_LONG(cairo_surface_get_content(surface_object->surface));
}
/* }}} */

/* {{{ proto void cairo_surface_mark_dirty(CairoSurface object)
       proto void CairoSurface->markDirty()
       Tells cairo that drawing has been done to surface using means other than cairo, and that cairo should reread any cached areas. */
PHP_FUNCTION(cairo_surface_mark_dirty)
{
	zval *surface_zval = NULL;
	cairo_surface_object *surface_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &surface_zval, cairo_ce_cairosurface) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	surface_object = (cairo_surface_object *)cairo_surface_object_get(surface_zval TSRMLS_CC);
	cairo_surface_mark_dirty(surface_object->surface);
}
/* }}} */

/* {{{ proto void cairo_surface_mark_dirty_rectangle(CairoSurface object, float x, float y, float width, float height)
       proto void CairoSurface->markDirtyRectangle(float x, float y, float width, float height)
       Drawing has been done only to the specified rectangle, so that cairo can retain cached contents for other parts of the surface.
       Any cached clip set on the surface will be reset by this function, to make sure that future cairo calls have the clip set that they expect.*/
PHP_FUNCTION(cairo_surface_mark_dirty_rectangle)
{
	zval *surface_zval = NULL;
	cairo_surface_object *surface_object;
	double x = 0.0, y = 0.0, width = 0.0, height = 0.0;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odddd", &surface_zval, cairo_ce_cairosurface, &x, &y, &width, &height) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	surface_object = (cairo_surface_object *)cairo_surface_object_get(surface_zval TSRMLS_CC);
	cairo_surface_mark_dirty_rectangle(surface_object->surface, x, y, width, height);
}
/* }}} */

/* {{{ proto void cairo_surface_set_device_offset(CairoSurface object, float x, float y)
       proto void CairoSurface->setDeviceOffset(float x, float y)
       Sets an offset that is added to the device coordinates determined by the CTM when drawing to surface. */
PHP_FUNCTION(cairo_surface_set_device_offset)
{
	zval *surface_zval = NULL;
	cairo_surface_object *surface_object;
	double x = 0.0, y = 0.0;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odd", &surface_zval, cairo_ce_cairosurface, &x, &y) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	surface_object = (cairo_surface_object *)cairo_surface_object_get(surface_zval TSRMLS_CC);
	cairo_surface_set_device_offset(surface_object->surface, x, y);
}
/* }}} */

/* {{{ proto array cairo_surface_get_device_offset(CairoSurface object)
       proto array CairoSurface->getDeviceOffset()
       This function returns the previous device offset */
PHP_FUNCTION(cairo_surface_get_device_offset)
{
	zval *surface_zval = NULL;
	cairo_surface_object *surface_object;
	double x, y;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &surface_zval, cairo_ce_cairosurface) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	surface_object = (cairo_surface_object *)cairo_surface_object_get(surface_zval TSRMLS_CC);
	cairo_surface_get_device_offset(surface_object->surface, &x, &y);

	array_init(return_value);
	add_next_index_double(return_value, x);
	add_next_index_double(return_value, y);
}
/* }}} */

/* {{{ proto void cairo_surface_set_fallback_resolution(CairoSurface object, float x, float y)
       proto void CairoSurface->setFallbackResolution(float x, float y)
      Set the horizontal and vertical resolution for image fallbacks.
      When certain operations aren't supported natively by a backend, cairo will fallback by
      rendering operations to an image and then overlaying that image onto the output. */
PHP_FUNCTION(cairo_surface_set_fallback_resolution)
{
	zval *surface_zval = NULL;
	cairo_surface_object *surface_object;
	double x = 0.0, y = 0.0;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odd", &surface_zval, cairo_ce_cairosurface, &x, &y) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	surface_object = (cairo_surface_object *)cairo_surface_object_get(surface_zval TSRMLS_CC);
	cairo_surface_set_fallback_resolution(surface_object->surface, x, y);
}
/* }}} */

#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 8, 0)
/* {{{ proto array cairo_surface_get_fallback_resolution(CairoSurface object)
       proto array CairoSurface->getFallbackResolution()
       This function returns the previous fallback resolution */
PHP_FUNCTION(cairo_surface_get_fallback_resolution)
{
	zval *surface_zval = NULL;
	cairo_surface_object *surface_object;
	double x, y;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &surface_zval, cairo_ce_cairosurface) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	surface_object = (cairo_surface_object *)cairo_surface_object_get(surface_zval TSRMLS_CC);
	cairo_surface_get_fallback_resolution(surface_object->surface, &x, &y);

	array_init(return_value);
	add_next_index_double(return_value, x);
	add_next_index_double(return_value, y);
}
/* }}} */
#endif

/* {{{ proto int cairo_surface_get_type(CairoSurface object)
       proto int CairoSurface->getType()
       This function returns the type of the backend used to create a surface. */
PHP_FUNCTION(cairo_surface_get_type)
{
	zval *surface_zval = NULL;
	cairo_surface_object *surface_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &surface_zval, cairo_ce_cairosurface) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	surface_object = (cairo_surface_object *)cairo_surface_object_get(surface_zval TSRMLS_CC);
	RETURN_LONG(cairo_surface_get_type(surface_object->surface));
}
/* }}} */

#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 6, 0)
/* {{{ proto void cairo_surface_show_page(CairoSurface object)
       proto void CairoSurface->showPage()
       Emits and clears the current page for backends that support multiple pages.
       Same as CairoContext->showPage(); */
PHP_FUNCTION(cairo_surface_show_page)
{
	zval *surface_zval = NULL;
	cairo_surface_object *surface_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &surface_zval, cairo_ce_cairosurface) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	surface_object = (cairo_surface_object *)cairo_surface_object_get(surface_zval TSRMLS_CC);
	cairo_surface_show_page(surface_object->surface);
}
/* }}} */

/* {{{ proto void cairo_surface_copy_page(CairoSurface object)
       proto void CairoSurface->copyPage()
       Emits the current page for backends that support multiple pages,
       but doesn't clear it, so that the contents of the current page will be retained for the next page.
       Same as CairoContext->copyPage(); */
PHP_FUNCTION(cairo_surface_copy_page)
{
	zval *surface_zval = NULL;
	cairo_surface_object *surface_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &surface_zval, cairo_ce_cairosurface) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	surface_object = (cairo_surface_object *)cairo_surface_object_get(surface_zval TSRMLS_CC);
	cairo_surface_copy_page(surface_object->surface);
}
/* }}} */
#endif

#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 8, 0)
/* {{{ proto bool cairo_surface_has_show_text_glyphs(CairoSurface object)
       proto bool CairoSurface->hasShowTextGlyphs()
       Returns whether the surface supports sophisticated cairo_show_text_glyphs() operations
       Users can use this function to avoid computing UTF-8 text and cluster mapping if the target surface does not use it.  */
PHP_FUNCTION(cairo_surface_has_show_text_glyphs)
{
	zval *surface_zval = NULL;
	cairo_surface_object *surface_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &surface_zval, cairo_ce_cairosurface) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	surface_object = (cairo_surface_object *)cairo_surface_object_get(surface_zval TSRMLS_CC);
	RETURN_BOOL(cairo_surface_has_show_text_glyphs(surface_object->surface));
}
/* }}} */
#endif

#ifdef CAIRO_HAS_PNG_FUNCTIONS
/* {{{ proto int cairo_surface_write_to_png(CairoSurface object, file|resource file)
       proto int CairoSurface->writeToPng(file|resource file)
       Writes the contents of surface to a new file filename or PHP stream as a PNG image.
       Unlike some other stream supporting functions, you may NOT pass a null filename */
PHP_FUNCTION(cairo_surface_write_to_png)
{
	zval *surface_zval = NULL;
	cairo_surface_object *surface_object;
	zval *stream_zval = NULL;
	stream_closure *closure;
	php_stream *stream = NULL;
	zend_bool owned_stream = 0;
	cairo_status_t status;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Oz", &surface_zval, cairo_ce_cairosurface, &stream_zval) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	surface_object = (cairo_surface_object *)cairo_surface_object_get(surface_zval TSRMLS_CC);

	if(Z_TYPE_P(stream_zval) == IS_STRING) {
		stream = php_stream_open_wrapper(Z_STRVAL_P(stream_zval), "w+b", REPORT_ERRORS|ENFORCE_SAFE_MODE, NULL);
		owned_stream = 1;
	} else if(Z_TYPE_P(stream_zval) == IS_RESOURCE)  {
		php_stream_from_zval(stream, &stream_zval);	
	} else {
		if(getThis()) {
			zend_throw_exception(cairo_ce_cairoexception, "CairoSurface::writeToPng() expects parameter 1 to be a string or a stream resource", 0 TSRMLS_CC);
			return;
		} else {
			zend_error(E_WARNING, "cairo_surface_write_to_png() expects parameter 1 to be a string or a stream resource");
			return;
		}
		return;
	}

	/* Pack TSRMLS info and stream into struct */
	closure = ecalloc(1, sizeof(stream_closure));
	closure->stream = stream;
	closure->owned_stream = owned_stream;
#ifdef ZTS
	closure->TSRMLS_C = TSRMLS_C;
#endif

	status = cairo_surface_write_to_png_stream(surface_object->surface, php_cairo_write_func, (void *)closure);
	PHP_CAIRO_ERROR(status);
	if (owned_stream) {
		php_stream_close(stream);
	}
	efree(closure);
}
/* }}} */
#endif

/* {{{ cairo_surface_methods[] */
const zend_function_entry cairo_surface_methods[] = {
	PHP_ME(CairoSurface, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME_MAPPING(createSimilar, cairo_surface_create_similar, CairoSurface_createSimilar_args, ZEND_ACC_PUBLIC)
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 10, 0)
	PHP_ME_MAPPING(createForRectangle, cairo_surface_create_for_rectangle, CairoSurface_createForRectangle_args, ZEND_ACC_PUBLIC)
#endif
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
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 8, 0)
	PHP_ME_MAPPING(getFallbackResolution, cairo_surface_get_fallback_resolution, NULL, ZEND_ACC_PUBLIC)
#endif
	PHP_ME_MAPPING(getType, cairo_surface_get_type, NULL, ZEND_ACC_PUBLIC)
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 6, 0)
	PHP_ME_MAPPING(copyPage, cairo_surface_copy_page, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(showPage, cairo_surface_show_page, NULL, ZEND_ACC_PUBLIC)
#endif
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 8, 0)
	PHP_ME_MAPPING(hasShowTextGlyphs, cairo_surface_has_show_text_glyphs, NULL, ZEND_ACC_PUBLIC)
#endif
#ifdef CAIRO_HAS_PNG_FUNCTIONS
	PHP_ME_MAPPING(writeToPng, cairo_surface_write_to_png, CairoSurface_writeToPng_args, ZEND_ACC_PUBLIC)  
#endif
	{NULL, NULL, NULL}
};
/* }}} */

/* NOTE: cannot be static - used by cairo_*_surface.c files */
void cairo_surface_object_destroy(void *object TSRMLS_DC)
{
	cairo_surface_object *surface = (cairo_surface_object *)object;

	zend_hash_destroy(surface->std.properties);
	FREE_HASHTABLE(surface->std.properties);

	/* buffer for the create_from_data image stuff */ 
	if(surface->buffer != NULL) {
		efree(surface->buffer);
	}

	if(surface->surface != NULL){
		cairo_surface_finish(surface->surface);
		cairo_surface_destroy(surface->surface);
	}

	/* closure free up time */
	if(surface->closure != NULL) {
 		if(surface->closure->owned_stream == 1) {
			php_stream_close(surface->closure->stream);
		}
		efree(surface->closure);
	}

	if (surface->parent_zval != NULL) {
		Z_DELREF_P(surface->parent_zval);
	}

	efree(object);
}

/* NOTE: cannot be static - used by cairo_*_surface.c files */
zend_object_value cairo_surface_object_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	cairo_surface_object *surface;
#if PHP_VERSION_ID < 50399
	zval *temp;
#endif

	surface = ecalloc(1, sizeof(cairo_surface_object));

	surface->std.ce = ce;
	surface->buffer = NULL;

	ALLOC_HASHTABLE(surface->std.properties);
	zend_hash_init(surface->std.properties, 0, NULL, ZVAL_PTR_DTOR, 0);
#if PHP_VERSION_ID < 50399
	zend_hash_copy(surface->std.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref,(void *) &temp, sizeof(zval *));
#else
	object_properties_init(&surface->std, ce);
#endif
	retval.handle = zend_objects_store_put(surface, NULL, (zend_objects_free_object_storage_t)cairo_surface_object_destroy, NULL TSRMLS_CC);
	retval.handlers = zend_get_std_object_handlers();
	return retval;
}

/* Helper methods for stream surface read/writes */
cairo_status_t php_cairo_write_func(void *closure, const unsigned char *data, unsigned int length)
{
	unsigned int written;
	stream_closure *cast_closure;
#ifdef ZTS
	TSRMLS_D;
#endif

	cast_closure = (stream_closure *)closure;
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

cairo_status_t php_cairo_read_func(void *closure, const unsigned char *data, unsigned int length)
{
	unsigned int read;
	stream_closure *cast_closure;
#ifdef ZTS
	TSRMLS_D;
#endif

	cast_closure = (stream_closure *)closure;
#ifdef ZTS
	TSRMLS_C = cast_closure->TSRMLS_C;
#endif

	read = php_stream_read(cast_closure->stream, (char *)data, length);
	if (read == length) {
		return CAIRO_STATUS_SUCCESS;
	} else {
		return CAIRO_STATUS_READ_ERROR;
	}
}

/* Helper function to return the right ce given a class */
zend_class_entry* php_cairo_get_surface_ce(cairo_surface_t *surface TSRMLS_DC)
{
	zend_class_entry *type;
	if(surface == NULL)
		return cairo_ce_cairosurface;
	
	switch(cairo_surface_get_type(surface)) {
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
PHP_MINIT_FUNCTION(cairo_surface)
{
	zend_class_entry ce, content_ce, type_ce;

	INIT_CLASS_ENTRY(ce, "CairoSurface", cairo_surface_methods);
	cairo_ce_cairosurface = zend_register_internal_class(&ce TSRMLS_CC);
	cairo_ce_cairosurface->create_object = cairo_surface_object_new;
	cairo_ce_cairosurface->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS;

	INIT_CLASS_ENTRY(content_ce, "CairoContent", NULL);
	cairo_ce_cairocontent = zend_register_internal_class(&content_ce TSRMLS_CC);
	cairo_ce_cairocontent->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS | ZEND_ACC_FINAL_CLASS;

	#define REGISTER_CAIRO_CONTENT_LONG_CONST(const_name, value) \
	zend_declare_class_constant_long(cairo_ce_cairocontent, const_name, sizeof(const_name)-1, (long)value TSRMLS_CC); \
	REGISTER_LONG_CONSTANT(#value,  value,  CONST_CS | CONST_PERSISTENT);

	REGISTER_CAIRO_CONTENT_LONG_CONST("COLOR", CAIRO_CONTENT_COLOR);
	REGISTER_CAIRO_CONTENT_LONG_CONST("ALPHA", CAIRO_CONTENT_ALPHA);
	REGISTER_CAIRO_CONTENT_LONG_CONST("COLOR_ALPHA", CAIRO_CONTENT_COLOR_ALPHA);

	INIT_CLASS_ENTRY(type_ce, "CairoSurfaceType", NULL);
	cairo_ce_cairosurfacetype = zend_register_internal_class(&type_ce TSRMLS_CC);
	cairo_ce_cairosurfacetype->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS | ZEND_ACC_FINAL_CLASS;

	#define REGISTER_CAIRO_SURFACETYPE_LONG_CONST(const_name, value) \
	zend_declare_class_constant_long(cairo_ce_cairosurfacetype, const_name, sizeof(const_name)-1, (long)value TSRMLS_CC); \
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

#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 4, 0)
    REGISTER_CAIRO_SURFACETYPE_LONG_CONST("OS2", CAIRO_SURFACE_TYPE_OS2);
	REGISTER_CAIRO_SURFACETYPE_LONG_CONST("WIN32_PRINTING", CAIRO_SURFACE_TYPE_WIN32_PRINTING);
    REGISTER_CAIRO_SURFACETYPE_LONG_CONST("QUARTZ_IMAGE", CAIRO_SURFACE_TYPE_QUARTZ_IMAGE);
#endif

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
