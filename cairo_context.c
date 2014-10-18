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
  |         Akshat Gupta <g.akshat@gmail.com>                            |
  +----------------------------------------------------------------------+
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_cairo.h"

zend_class_entry *cairo_ce_cairocontext;
zend_class_entry *cairo_ce_cairoantialias;
zend_class_entry *cairo_ce_cairosubpixelorder;
zend_class_entry *cairo_ce_cairofillrule;
zend_class_entry *cairo_ce_cairolinecap;
zend_class_entry *cairo_ce_cairolinejoin;
zend_class_entry *cairo_ce_cairooperator;

/* Basic Context */
ZEND_BEGIN_ARG_INFO(CairoContext___construct_args, ZEND_SEND_BY_VAL)
	/* ZEND_ARG_OBJ_INFO(0, surface, CairoSurface, 0) */
	ZEND_ARG_INFO(0, surface)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoContext_pushGroupWithContent_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, content)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoContext_setSourceRGB_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, red)
	ZEND_ARG_INFO(0, green)
	ZEND_ARG_INFO(0, blue)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoContext_setSourceRGBA_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, red)
	ZEND_ARG_INFO(0, green)
	ZEND_ARG_INFO(0, blue)
	ZEND_ARG_INFO(0, alpha)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoContext_setSource_args, ZEND_SEND_BY_VAL)
	/* ZEND_ARG_OBJ_INFO(0, pattern, CairoPattern, 0) */
	ZEND_ARG_INFO(0, pattern)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(CairoContext_setSourceSurface_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
	/* ZEND_ARG_OBJ_INFO(0, surface, CairoSurface, 0) */
	ZEND_ARG_INFO(0, surface)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(CairoContext_setAntialias_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
	ZEND_ARG_INFO(0, antialias)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(CairoContext_setDash_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_INFO(0, dashes)
	ZEND_ARG_INFO(0, offset)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoContext_setFillRule_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, setting)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoContext_setLineWidth_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, width)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoContext_setMiterLimit_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, limit)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoContext_setTolerance_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, tolerance)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoContext_paintWithAlpha_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, alpha)
ZEND_END_ARG_INFO()

/* Transformations */
ZEND_BEGIN_ARG_INFO(CairoContext_translate_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoContext_transform_args, ZEND_SEND_BY_VAL)
	/* ZEND_ARG_OBJ_INFO(0, matrix, CairoMatrix, 0) - STUPID E_RECOVERABLE FROM THIS */
	ZEND_ARG_INFO(0, matrix)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoContext_rotate_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, angle)
ZEND_END_ARG_INFO()

/* Path support */
ZEND_BEGIN_ARG_INFO(CairoContext_curveTo_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, x1)
	ZEND_ARG_INFO(0, y1)
	ZEND_ARG_INFO(0, x2)
	ZEND_ARG_INFO(0, y2)
	ZEND_ARG_INFO(0, x3)
	ZEND_ARG_INFO(0, y3)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoContext_textPath_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, string)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoContext_appendPath_args, ZEND_SEND_BY_VAL)
	/* ZEND_ARG_OBJ_INFO(0, path, CairoPath, 0) */
	ZEND_ARG_INFO(0, path)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoContext_arc_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
	ZEND_ARG_INFO(0, radius)
	ZEND_ARG_INFO(0, angle1)
	ZEND_ARG_INFO(0, angle2)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoContext_rectangle_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
	ZEND_ARG_INFO(0, width)
	ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoContext_glyphPath_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_ARRAY_INFO(0, glyphs, 0)
ZEND_END_ARG_INFO()

/* Text related methods */
ZEND_BEGIN_ARG_INFO_EX(CairoContext_selectFontFace_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_INFO(0, family)
	ZEND_ARG_INFO(0, slant)
	ZEND_ARG_INFO(0, weight)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoContext_setFontSize_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, size)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoContext_setFontMatrix_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, matrix)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoContext_setFontOptions_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, fontoptions)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoContext_setFontFace_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, fontface)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoContext_setScaledFont_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, scaledfont)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoContext_text_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, text)
ZEND_END_ARG_INFO()

/* Basic Context Methods */

/* {{{ proto CairoContext cairo_create(CairoSurface surface)
   Returns new CairoContext object on the requested surface */
PHP_FUNCTION(cairo_create)
{
	zval *surface_zval = NULL;
	cairo_context_object *context_object;
	cairo_surface_object *surface_object;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &surface_zval, cairo_ce_cairosurface) == FAILURE) {
		return;
	}

	surface_object = (cairo_surface_object *)zend_object_store_get_object(surface_zval TSRMLS_CC);

	object_init_ex(return_value, cairo_ce_cairocontext);
	context_object = (cairo_context_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	context_object->context = cairo_create(surface_object->surface);
	php_cairo_trigger_error(cairo_status(context_object->context) TSRMLS_CC);

	/* we need to be able to get this zval out later, so ref and store */
	context_object->surface = surface_zval;
	Z_ADDREF_P(surface_zval);
}
/* }}} */

/* {{{ proto void __construct(object surface) 
   Returns new CairoContext object on the requested surface */
PHP_METHOD(CairoContext, __construct)
{
	zval *surface_zval = NULL;
	cairo_context_object *context_object;
	cairo_surface_object *surface_object;

	PHP_CAIRO_ERROR_HANDLING(TRUE)
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &surface_zval, cairo_ce_cairosurface) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(TRUE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(TRUE)

	surface_object = (cairo_surface_object *)zend_object_store_get_object(surface_zval TSRMLS_CC);
	context_object = (cairo_context_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
	context_object->context = cairo_create(surface_object->surface);
	php_cairo_throw_exception(cairo_status(context_object->context) TSRMLS_CC);

	/* we need to be able to get this zval out later, so ref and store */
	context_object->surface = surface_zval;
	Z_ADDREF_P(surface_zval);
}
/* }}} */

/* {{{ proto long cairo_status(CairoContext object)
   proto long CairoContext->status()
   Returns the current integer status of the CairoContext */
PHP_FUNCTION(cairo_status)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &context_zval, cairo_ce_cairocontext) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *) cairo_context_object_get(context_zval TSRMLS_CC);
	RETURN_LONG(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto void cairo_save(CairoContext object)
   proto void CairoContext->save()
   Makes a copy of the current state of the context and saves it on an internal stack of saved states */
PHP_FUNCTION(cairo_save)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &context_zval, cairo_ce_cairocontext) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *) cairo_context_object_get(context_zval TSRMLS_CC);
	cairo_save(context_object->context);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto void cairo_restore(CairoContext object)
   proto void CairoContext->restore()
   Restores the context to the state saved and removes that state from the stack of saved states */
PHP_FUNCTION(cairo_restore)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &context_zval, cairo_ce_cairocontext) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *) cairo_context_object_get(context_zval TSRMLS_CC);
	cairo_restore(context_object->context);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto CairoSurface object cairo_get_target(CairoContext object)
   proto CairoSurface object CairoContext->getTarget()
   Gets the target surface for the cairo context that was set on creation */
PHP_FUNCTION(cairo_get_target)
{
	zend_class_entry *ce;
	zval *context_zval = NULL;
	cairo_surface_t *surface;
	cairo_context_object *context_object;
	cairo_surface_object *surface_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &context_zval, cairo_ce_cairocontext) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *) cairo_context_object_get(context_zval TSRMLS_CC);

	/* Grab the surface properly */
	surface = cairo_get_target(context_object->context);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));

	/* If we have a surface object stored, grab that zval to use */
	if(context_object->surface) {
		zval_dtor(return_value);
		*return_value = *context_object->surface;
		zval_copy_ctor(return_value);
		Z_SET_REFCOUNT_P(return_value, 1);
	/* Otherwise we spawn a new object */
	} else {
		ce = php_cairo_get_surface_ce(surface TSRMLS_CC);
		object_init_ex(return_value, ce);
	}
	
	/* Get the surface_object and replace the internal surface pointer with what we fetched (should be the same) */
	surface_object = (cairo_surface_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	/* if there IS a value in surface, destroy it cause we're getting a new one */
	if (surface_object->surface != NULL) {
		cairo_surface_destroy(surface_object->surface);
	}
	/* Grab the surface properly */
	surface_object->surface = surface;
	cairo_surface_reference(surface_object->surface);
}
/* }}} */

/* {{{ proto void cairo_push_group(CairoContext object)
   proto void CairoContext->pushGroup()
   Temporarily redirects drawing to an intermediate surface known as a group. */
PHP_FUNCTION(cairo_push_group)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &context_zval, cairo_ce_cairocontext) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	cairo_push_group(context_object->context);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto void cairo_push_group_with_content(CairoContext object, int content)
   proto void CairoContext->pushGroupWithContent(int content)
   Temporarily redirects drawing to an intermediate surface known as a group. */
PHP_FUNCTION(cairo_push_group_with_content)
{
	zval *context_zval = NULL;
	/* should be cairo_content_t but we need a long */
        long content;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ol", &context_zval, cairo_ce_cairocontext, &content) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	cairo_push_group_with_content(context_object->context, content);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto CairoPattern object cairo_pop_group(CairoContext object)
   proto CairoPattern object CairoContext->popGroup()
   Terminates the redirection and returns a new pattern containing the results of all drawing operations performed to the group. */
PHP_FUNCTION(cairo_pop_group)
{
	zend_class_entry *ce;
	zval *context_zval = NULL;
	cairo_pattern_t *pattern;
	cairo_context_object *context_object;
	cairo_pattern_object *pattern_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &context_zval, cairo_ce_cairocontext) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	pattern = cairo_pop_group(context_object->context);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));

	ce = php_cairo_get_pattern_ce(pattern TSRMLS_CC);
	object_init_ex(return_value, ce);
	pattern_object = (cairo_pattern_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	pattern_object->pattern = pattern;
}
/* }}} */

/* {{{ proto void cairo_pop_group_to_source(CairoContext object)
   proto void CairoContext->popGroupToSource()
   Terminates the redirection and installs the resulting pattern as the source pattern in the given cairo context. */
PHP_FUNCTION(cairo_pop_group_to_source)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &context_zval, cairo_ce_cairocontext) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	cairo_pop_group_to_source(context_object->context);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto CairoSurface object cairo_get_group_target(CairoContext object)
   proto CairoSurface object CairoContext->getGroupTarget()
   Gets the current destination surface for the context */
PHP_FUNCTION(cairo_get_group_target)
{
	zend_class_entry *ce; 
	zval *context_zval = NULL;
	cairo_surface_t *surface;
	cairo_context_object *context_object;
	cairo_surface_object *surface_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &context_zval, cairo_ce_cairocontext) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	surface = cairo_get_group_target(context_object->context);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));

	ce = php_cairo_get_surface_ce(surface TSRMLS_CC);

	object_init_ex(return_value, ce);
	surface_object = (cairo_surface_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	surface_object->surface = cairo_get_group_target(context_object->context);
	cairo_surface_reference(surface_object->surface);
}
/* }}} */

/* {{{ proto void cairo_set_source_rgb(CairoContext object, float red, float green, float blue)
   proto void CairoContext->setSourceRGB(float red, float green, float blue)
   Sets the source pattern within context to an opaque color. This opaque color will then be used for any subsequent drawing operation until a new source pattern is set.  */
PHP_FUNCTION(cairo_set_source_rgb)
{
	zval * context_zval = NULL;
	double red = 0.0, green = 0.0, blue = 0.0;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Oddd", &context_zval, cairo_ce_cairocontext, &red, &green, &blue) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	cairo_set_source_rgb(context_object->context, red, green, blue);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto void cairo_set_source_rgba(CairoContext object, float red, float green, float blue, float alpha)
   proto void CairoContext->setSourceRGBA(float red, float green, float blue, float alpha)
   Sets the source pattern within context to an translucent  color. This opaque color will then be used for any subsequent drawing operation until a new source pattern is set.  */
PHP_FUNCTION(cairo_set_source_rgba)
{
	zval * context_zval = NULL;
	double red = 0.0, green = 0.0, blue = 0.0, alpha = 1.0;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odddd", &context_zval, cairo_ce_cairocontext, &red, &green, &blue, &alpha) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	cairo_set_source_rgba(context_object->context, red, green, blue, alpha);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto void cairo_set_source(CairoContext object, CairoPattern object)
   proto void CairoContext->setSource(CairoPattern object)
   Sets the source pattern within context to source. This pattern will then be used for any subsequent drawing operation until a new source pattern is set.  */
PHP_FUNCTION(cairo_set_source)
{
	zval *context_zval = NULL, *pattern_zval = NULL;
	cairo_context_object *context_object;
	cairo_pattern_object *pattern_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "OO", &context_zval, cairo_ce_cairocontext, &pattern_zval, cairo_ce_cairopattern) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	pattern_object = (cairo_pattern_object *)cairo_pattern_object_get(pattern_zval TSRMLS_CC);
	cairo_set_source(context_object->context, pattern_object->pattern);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));

	/* If there's already a pattern, then we deref and remove it */
	if(context_object->pattern) {
		Z_DELREF_P(context_object->pattern);
		context_object->pattern = NULL;
	}

	/* we need to be able to get this zval out later, so ref and store */
	context_object->pattern = pattern_zval;
	Z_ADDREF_P(pattern_zval);
}
/* }}} */

/* {{{ proto void cairo_set_source_surface(CairoContext object, CairoSurface object [,float x, float y])
       proto void CairoContext->setSourceSurface(object surface [,float x, float y])
       This is a convenience function for creating a pattern from surface and setting it as the source
   */
PHP_FUNCTION(cairo_set_source_surface)
{
	zval *context_zval = NULL, *surface_zval = NULL;
	cairo_context_object *context_object;
	cairo_surface_object *surface_object;
	double x = 0.0, y = 0.0;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "OO|dd", &context_zval, cairo_ce_cairocontext, &surface_zval, cairo_ce_cairosurface, &x, &y) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	surface_object = (cairo_surface_object *)cairo_surface_object_get(surface_zval TSRMLS_CC);
	cairo_set_source_surface(context_object->context, surface_object->surface, x, y);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));

	/* If there's already a pattern, then we deref and remove it because we just overwrote it */
	if(context_object->pattern) {
		Z_DELREF_P(context_object->pattern);
		context_object->pattern = NULL;
	}
}
/* }}} */

/* {{{ proto CairoPattern object cairo_get_source(CairoContext object)
   proto CairoPattern object CairoContext->getSource()
   Gets the current source pattern for the context. */
PHP_FUNCTION(cairo_get_source)
{
	zend_class_entry *ce;
	zval *context_zval = NULL;
	cairo_pattern_t *pattern;
	cairo_context_object *context_object;
	cairo_pattern_object *pattern_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &context_zval, cairo_ce_cairocontext) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	pattern = cairo_get_source(context_object->context);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));

	/* If we have a patter/source object stored, grab that zval to use */
	if(context_object->pattern) {
		zval_dtor(return_value);
		*return_value = *context_object->pattern;
		zval_copy_ctor(return_value);
		Z_SET_REFCOUNT_P(return_value, 1);
	/* Otherwise we spawn a new object */
	} else {
		ce = php_cairo_get_pattern_ce(pattern TSRMLS_CC);
		object_init_ex(return_value, ce);
	}
	
	/* Get the pattern object and replace the internal pattern pointer with what we fetched (should be the same) */
	pattern_object = (cairo_pattern_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	/* if there IS a value in pattern, destroy it cause we're getting a new one */
	if (pattern_object->pattern != NULL) {
		cairo_pattern_destroy(pattern_object->pattern);
	}
	pattern_object->pattern = pattern;
	cairo_pattern_reference(pattern_object->pattern);
}
/* }}} */

/* {{{ proto void cairo_set_antialias(CairoContext object[, int antialias])
   proto void CairoContext->setAntialias([int antialias])
   Set the antialiasing mode of the rasterizer used for drawing shapes. */
PHP_FUNCTION(cairo_set_antialias)
{
	zval *context_zval = NULL;
	long antialias = CAIRO_ANTIALIAS_DEFAULT;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O|l", &context_zval, cairo_ce_cairocontext, &antialias) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	cairo_set_antialias(context_object->context, antialias);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));	
}
/* }}} */

/* {{{ proto int cairo_get_antialias(CairoContext object)
   proto int CairoContext->getAntialias()
   Gets the current shape antialiasing mode */
PHP_FUNCTION(cairo_get_antialias)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &context_zval, cairo_ce_cairocontext) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	RETURN_LONG(cairo_get_antialias(context_object->context));
}
/* }}} */

/* {{{ proto void cairo_set_dash(CairoContext object, array dashes [, float offset])
   proto void CairoContext->setDash(array dashes [, float offset])
   Sets the dash pattern to be used by cairo_stroke() */
PHP_FUNCTION(cairo_set_dash)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;
	double offset = 0.0;
	long num_dashes = 0;
	double *dashes_array;
	zval * dashes = NULL, **ppzval;
	HashTable *dashes_hash = NULL;
	int i = 0;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Oa/|d", &context_zval, cairo_ce_cairocontext, &dashes, &offset) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	/* Grab the zend hash and see how big our array will be */
	dashes_hash = Z_ARRVAL_P(dashes);
	num_dashes = zend_hash_num_elements(dashes_hash);
	dashes_array = emalloc(num_dashes * sizeof(double));

	/* iterate the array, make sure we JUGGLE the value to a double */
	for(zend_hash_internal_pointer_reset(dashes_hash); zend_hash_has_more_elements(dashes_hash) == SUCCESS; zend_hash_move_forward(dashes_hash)) { 
		if (zend_hash_get_current_data(dashes_hash, (void **)&ppzval) == FAILURE) {
			continue; 
		}

		if (Z_TYPE_PP(ppzval) != IS_DOUBLE) {
			convert_to_double(*ppzval);
		}
		dashes_array[i++] = Z_DVAL_PP(ppzval);
	}

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	/* we use i in case we had a bad issue while iterating the array */
	cairo_set_dash(context_object->context, dashes_array, i, offset);
	efree(dashes_array);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));
}
/* }}} */

#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 4, 0)
/* {{{ proto int cairo_get_dash_count(CairoContext object)
   proto int CairoContext->getDashCount()
   This function returns the length of the dash array or 0 */
PHP_FUNCTION(cairo_get_dash_count)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &context_zval, cairo_ce_cairocontext) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	RETURN_LONG(cairo_get_dash_count(context_object->context));
}
/* }}} */

/* {{{ proto array cairo_get_dash(CairoContext object)
   proto array CairoContext->getDash()
   Gets the current dash array and offset */
PHP_FUNCTION(cairo_get_dash)
{
	zval *sub_array, *context_zval = NULL;
	cairo_context_object *context_object;
	double *dashes = NULL;
	double offset = 0;
	int num_dashes, i;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &context_zval, cairo_ce_cairocontext) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);

	/* Setup container for dashes */
	num_dashes = cairo_get_dash_count(context_object->context);
	dashes = emalloc(num_dashes * sizeof(double));

	/* Get dashes and push into PHP array */
	cairo_get_dash(context_object->context, dashes, &offset);

	MAKE_STD_ZVAL(sub_array);
	array_init(sub_array);
	for(i = 0; i < num_dashes; i++) {
		add_next_index_double(sub_array, dashes[i]);
	}
	efree(dashes);
	
	/* Put dashes and offset into return */
	array_init(return_value);
	add_assoc_zval(return_value, "dashes", sub_array);
	add_assoc_double(return_value, "offset", offset);
}
/* }}} */
#endif

/* {{{ proto void cairo_set_fill_rule(CairoContext object, int setting)
   proto void CairoContext->setFillRule(int setting)
   Set the current fill rule within the cairo context. The fill rule is used
   to determine which regions are inside or outside a complex path */
PHP_FUNCTION(cairo_set_fill_rule)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;
	long fill_rule = 0;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ol", &context_zval, cairo_ce_cairocontext, &fill_rule) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	cairo_set_fill_rule(context_object->context, fill_rule);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto int cairo_get_fill_rule(CairoContext object)
   proto int CairoContext->getFillRule()
   Gets the current fill rule */
PHP_FUNCTION(cairo_get_fill_rule)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &context_zval, cairo_ce_cairocontext) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	RETURN_LONG(cairo_get_fill_rule(context_object->context));
}
/* }}}  */

/* {{{ proto void cairo_set_line_cap(CairoContext object, int setting)
   proto void CairoContext->setLineCap(int setting)
   Sets the current line cap style within the cairo context. */
PHP_FUNCTION(cairo_set_line_cap)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;
	long line_cap = 0;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ol", &context_zval, cairo_ce_cairocontext, &line_cap) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	cairo_set_line_cap(context_object->context, line_cap);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto int cairo_get_line_cap(CairoContext object)
   proto int CairoContext->getLineCap()
   Gets the current line cap style */
PHP_FUNCTION(cairo_get_line_cap)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &context_zval, cairo_ce_cairocontext) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	RETURN_LONG(cairo_get_line_cap(context_object->context));
}
/* }}}  */

/* {{{ proto void cairo_set_line_join(CairoContext object, int setting)
   proto void CairoContext->setLineJoin(int setting)
   Sets the current line join style within the cairo context. */
PHP_FUNCTION(cairo_set_line_join)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;
	long line_join = 0;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ol", &context_zval, cairo_ce_cairocontext, &line_join) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	cairo_set_line_join(context_object->context, line_join);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto int cairo_get_line_join(CairoContext object)
   proto int CairoContext->getLineJoin()
   Gets the current line join style */
PHP_FUNCTION(cairo_get_line_join)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &context_zval, cairo_ce_cairocontext) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	RETURN_LONG(cairo_get_line_join(context_object->context));
}
/* }}}  */

/* {{{ proto void cairo_set_line_width(CairoContext object, float width)
   proto void CairoContext->setLineWidth(float width)
   Sets the current line width within the cairo context. The line width value
   specifies the diameter of a pen that is circular in user space */
PHP_FUNCTION(cairo_set_line_width)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;
	double width = 0.0;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Od", &context_zval, cairo_ce_cairocontext, &width) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	cairo_set_line_width(context_object->context, width);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto double cairo_get_line_width(CairoContext object)
   proto double CairoContext->getLineWidth()
   This function returns the current line width value exactly as set by cairo_set_line_width() */
PHP_FUNCTION(cairo_get_line_width)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &context_zval, cairo_ce_cairocontext) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	RETURN_DOUBLE(cairo_get_line_width(context_object->context));
}
/* }}} */

/* {{{ proto void cairo_set_miter_limit(CairoContext object, float limit)
   proto void CairoContext->setMiterLimit(float limit)
   Sets the current miter limit within the cairo context. */
PHP_FUNCTION(cairo_set_miter_limit)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;
	double limit = 0.0;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Od", &context_zval, cairo_ce_cairocontext, &limit) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	cairo_set_miter_limit(context_object->context, limit);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto double cairo_get_miter_limit(CairoContext object)
   proto double CairoContext->getMiterLimit()
   Gets the current miter limit */
PHP_FUNCTION(cairo_get_miter_limit)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &context_zval, cairo_ce_cairocontext) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	RETURN_DOUBLE(cairo_get_miter_limit(context_object->context));
}
/* }}} */

/* {{{ proto void cairo_set_operator(CairoContext object, int setting)
   proto void CairoContext->setOperator(int setting)
   Sets the compositing operator to be used for all drawing operations. */
PHP_FUNCTION(cairo_set_operator)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;
	long op = 0;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ol", &context_zval, cairo_ce_cairocontext, &op) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	cairo_set_operator(context_object->context, op);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto int cairo_get_operator(CairoContext object)
   proto int CairoContext->getOperator()
   Gets the current compositing operator for a cairo context. */
PHP_FUNCTION(cairo_get_operator)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &context_zval, cairo_ce_cairocontext) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	RETURN_LONG(cairo_get_operator(context_object->context));
}
/* }}}  */

/* {{{ proto void cairo_set_tolerance(CairoContext object, float tolerance)
   proto void CairoContext->setTolerance(float tolerance)
   Sets the tolerance used when converting paths into trapezoids. */
PHP_FUNCTION(cairo_set_tolerance)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;
	double tolerance = 0.1;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Od", &context_zval, cairo_ce_cairocontext, &tolerance) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	cairo_set_tolerance(context_object->context, tolerance);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto double cairo_get_tolerance(CairoContext object)
   proto double CairoContext->getTolerance()
   Gets the current tolerance value */
PHP_FUNCTION(cairo_get_tolerance)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &context_zval, cairo_ce_cairocontext) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	RETURN_DOUBLE(cairo_get_tolerance(context_object->context));
}
/* }}} */

/* {{{ proto void cairo_clip(CairoContext object)
   proto void CairoContext->clip()
   Establishes a new clip region by intersecting the current clip region with the current path as it
   would be filled by cairo_fill() and according to the current fill rule */
PHP_FUNCTION(cairo_clip)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &context_zval, cairo_ce_cairocontext) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	cairo_clip(context_object->context);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));
}
/* }}} */

#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 10, 0)
/* {{{ proto boolean cairo_in_clip(CairoContext object, double x, double y)
   proto boolean CairoContext->inClip(double x, double y)
   Tests whether the given point is inside the area that would be visible 
   through the current clip
*/
PHP_FUNCTION(cairo_in_clip)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;
	double x = 0.0, y = 0.0;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odd", &context_zval, cairo_ce_cairocontext, &x, &y) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	RETURN_BOOL(cairo_in_clip(context_object->context, x, y));
}
/* }}} */
#endif

/* {{{ proto void cairo_clip_preserve(CairoContext object)
   proto void CairoContext->clipPreserve()
   Establishes a new clip region by intersecting the current clip region with the current path as it
   would be filled by cairo_fill() and according to the current fill rule
   Unlike cairo_clip(), cairo_clip_preserve() preserves the path within the cairo context. */
PHP_FUNCTION(cairo_clip_preserve)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &context_zval, cairo_ce_cairocontext) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	cairo_clip_preserve(context_object->context);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto void cairo_reset_clip(CairoContext object)
   proto void CairoContext->resetclip()
   Reset the current clip region to its original, unrestricted state. */
PHP_FUNCTION(cairo_reset_clip)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &context_zval, cairo_ce_cairocontext) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	cairo_reset_clip(context_object->context);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));
}
/* }}} */

#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 4, 0)
/* {{{ proto array cairo_clip_extents(CairoContext object)
   proto array CairoContext->clipExtents()
   Computes a bounding box in user coordinates covering the area inside the current clip. */
PHP_FUNCTION(cairo_clip_extents)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;
	double x1, y1, x2, y2;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &context_zval, cairo_ce_cairocontext) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	cairo_clip_extents(context_object->context, &x1, &y1, &x2, &y2);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));

	array_init(return_value);
	add_next_index_double(return_value, x1);
	add_next_index_double(return_value, y1);
	add_next_index_double(return_value, x2);
	add_next_index_double(return_value, y2);
}
/* }}} */

/* {{{ proto array cairo_clip_rectangle_list(CairoContext object)
   proto array CairoContext->strokeRectangleList()
   Gets the current stroke region as a list of rectangles in user coordinates. */
PHP_FUNCTION(cairo_clip_rectangle_list)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;
	cairo_rectangle_list_t *rectangles;
	int i;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &context_zval, cairo_ce_cairocontext) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	rectangles = cairo_copy_clip_rectangle_list(context_object->context);
	PHP_CAIRO_ERROR(rectangles->status);

	/* walk our rectangles, create array, push it onto return */
	array_init(return_value);

	for (i = 0; i < rectangles->num_rectangles; i++) {
		zval *new_array;
		cairo_rectangle_t rectangle = rectangles->rectangles[i];

		MAKE_STD_ZVAL(new_array);
		array_init(new_array);
		add_assoc_double(new_array, "x", rectangle.x);
		add_assoc_double(new_array, "y", rectangle.y);
		add_assoc_double(new_array, "width", rectangle.width);
		add_assoc_double(new_array, "height", rectangle.height);
		add_next_index_zval(return_value, new_array);
	}

	/* don't forget to clean up */
	cairo_rectangle_list_destroy(rectangles);
}
/* }}} */
#endif

/* {{{ proto void cairo_fill(CairoContext object)
   proto void CairoContext->fill()
   A drawing operator that fills the current path according to the current fill rule,
   (each sub-path is implicitly closed before being filled). */
PHP_FUNCTION(cairo_fill)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &context_zval, cairo_ce_cairocontext) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	cairo_fill(context_object->context);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto void cairo_fill_preserve(CairoContext object)
   proto void CairoContext->fillPreserve()
   A drawing operator that fills the current path according to the current fill rule,
   (each sub-path is implicitly closed before being filled). Unlike cairo_fill(),
   cairo_fill_preserve() preserves the path within the cairo context.  */
PHP_FUNCTION(cairo_fill_preserve)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &context_zval, cairo_ce_cairocontext) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	cairo_fill_preserve(context_object->context);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto array cairo_fill_extents(CairoContext object)
   proto array CairoContext->fillExtents()
   Computes a bounding box in user coordinates covering the area that would be affected,
   (the "inked" area), by a cairo_fill() operation given the current path and fill parameters. */
PHP_FUNCTION(cairo_fill_extents)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;
	double x1, y1, x2, y2;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &context_zval, cairo_ce_cairocontext) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	cairo_fill_extents(context_object->context, &x1, &y1, &x2, &y2);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));

	array_init(return_value);
	add_next_index_double(return_value, x1);
	add_next_index_double(return_value, y1);
	add_next_index_double(return_value, x2);
	add_next_index_double(return_value, y2);
}
/* }}} */

/* {{{ proto bool cairo_in_fill(CairoContext object, int x, int y)
   proto bool CairoContext->inFill(int x, int y)
   Tests whether the given point is inside the area that would be affected by a cairo_fill()
   operation given the current path and filling parameters. */
PHP_FUNCTION(cairo_in_fill)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;
	double x = 0.0, y = 0.0;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odd", &context_zval, cairo_ce_cairocontext, &x, &y) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	RETURN_BOOL(cairo_in_fill(context_object->context, x, y));
}
/* }}} */

/* {{{ proto void cairo_mask(CairoContext object, CairoPattern object)
   proto void CairoContext->mask(CairoPattern object)
   A drawing operator that paints the current source using the alpha channel of pattern as a mask.  */
PHP_FUNCTION(cairo_mask)
{
	zval *context_zval = NULL, *pattern_zval = NULL;
	cairo_context_object *context_object;
	cairo_pattern_object *pattern_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "OO", &context_zval, cairo_ce_cairocontext, &pattern_zval, cairo_ce_cairopattern) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	pattern_object = (cairo_pattern_object *)cairo_pattern_object_get(pattern_zval TSRMLS_CC);
	cairo_mask(context_object->context, pattern_object->pattern);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto void cairo_mask_surface(CairoContext object, CairoSurface object [,float x, float y])
       proto void CairoContext->maskSurface(object surface [,float x, float y])
       A drawing operator that paints the current source using the alpha channel of surface as a mask.
   */
PHP_FUNCTION(cairo_mask_surface)
{
	zval *context_zval = NULL, *surface_zval = NULL;
	cairo_context_object *context_object;
	cairo_surface_object *surface_object;
	double x = 0.0, y = 0.0;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "OO|dd", &context_zval, cairo_ce_cairocontext, &surface_zval, cairo_ce_cairosurface, &x, &y) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	surface_object = (cairo_surface_object *)cairo_surface_object_get(surface_zval TSRMLS_CC);
	cairo_mask_surface(context_object->context, surface_object->surface, x, y);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto void cairo_paint(CairoContext object)
   proto void CairoContext->paint()
   A drawing operator that paints the current source everywhere within the current clip region. */
PHP_FUNCTION(cairo_paint)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &context_zval, cairo_ce_cairocontext) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	cairo_paint(context_object->context);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto void cairo_paint_with_alpha(CairoContext object, float alpha)
   proto void CairoContext->paintWithAlpha(float alpha)
   A drawing operator that paints the current source everywhere within the current clip region using a mask of constant alpha value alpha. */
PHP_FUNCTION(cairo_paint_with_alpha)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;
	double alpha = 0.0;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Od", &context_zval, cairo_ce_cairocontext, &alpha) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	cairo_paint_with_alpha(context_object->context, alpha);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto void cairo_stroke(CairoContext object)
   proto void CairoContext->stroke()
   A drawing operator that strokes the current path according to the current line width, line join, line cap, and dash settings. */
PHP_FUNCTION(cairo_stroke)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &context_zval, cairo_ce_cairocontext) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	cairo_stroke(context_object->context);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto void cairo_stroke_preserve(CairoContext object)
   proto void CairoContext->strokePreserve()
   A drawing operator that strokes the current path according to the current line width, line join, line cap, and dash settings.
   Unlike cairo_stroke(), cairo_stroke_preserve() preserves the path within the cairo context.  */
PHP_FUNCTION(cairo_stroke_preserve)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &context_zval, cairo_ce_cairocontext) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	cairo_stroke_preserve(context_object->context);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto array cairo_stroke_extents(CairoContext object)
   proto array CairoContext->strokeExtents()
   Computes a bounding box in user coordinates covering the area that would be affected, (the "inked" area), by a cairo_stroke()
   operation operation given the current path and stroke parameters. */
PHP_FUNCTION(cairo_stroke_extents)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;
	double x1, y1, x2, y2;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &context_zval, cairo_ce_cairocontext) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	cairo_stroke_extents(context_object->context, &x1, &y1, &x2, &y2);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));

	array_init(return_value);
	add_next_index_double(return_value, x1);
	add_next_index_double(return_value, y1);
	add_next_index_double(return_value, x2);
	add_next_index_double(return_value, y2);
}
/* }}} */

/* {{{ proto bool cairo_in_stroke(CairoContext object, int x, int y)
   proto bool CairoContext->inStroke(int x, int y)
   Tests whether the given point is inside the area that would be affected by a cairo_stroke()
   operation given the current path and stroking parameters.  */
PHP_FUNCTION(cairo_in_stroke)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;
	double x = 0.0, y = 0.0;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odd", &context_zval, cairo_ce_cairocontext, &x, &y) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	RETURN_BOOL(cairo_in_stroke(context_object->context, x, y));
}
/* }}} */

/* {{{ proto void cairo_copy_page(CairoContext object)
   proto void CairoContext->copyPage()
   Emits the current page for backends that support multiple pages, but doesn't clear it,
   so, the contents of the current page will be retained for the next page too.*/
PHP_FUNCTION(cairo_copy_page)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &context_zval, cairo_ce_cairocontext) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	cairo_copy_page(context_object->context);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto void cairo_show_page(CairoContext object)
   proto void CairoContext->showPage()
   Emits and clears the current page for backends that support multiple pages.
   Use cairo_copy_page() if you don't want to clear the page. */
PHP_FUNCTION(cairo_show_page)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &context_zval, cairo_ce_cairocontext) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	cairo_show_page(context_object->context);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));
}
/* }}} */

/* Transformations Methods */

/* {{{ proto void cairo_translate(CairoContext object, float x, float y)
   proto void CairoContext->translate(float x, float y)
   Modifies the current transformation matrix by translating the user-space origin by (x, y) */
PHP_FUNCTION(cairo_translate)
{
	zval *context_zval = NULL;
	double x = 0.0, y = 0.0;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odd", &context_zval, cairo_ce_cairocontext, &x, &y) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	cairo_translate(context_object->context, x, y);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto void cairo_scale(CairoContext object, float x, float y)
   proto void CairoContext->scale(float x, float y)
   Modifies the current transformation matrix by scaling the X and Y user-space axes by x and y respectively */
PHP_FUNCTION(cairo_scale)
{
	zval *context_zval = NULL;
	double x = 0.0, y = 0.0;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odd", &context_zval, cairo_ce_cairocontext, &x, &y) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	cairo_scale(context_object->context, x, y);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto void cairo_rotate(CairoContext object, float angle)
   proto void CairoContext->rotate(float angle)
   Modifies the current transformation matrix by rotating the user-space axes by angle radians */
PHP_FUNCTION(cairo_rotate)
{
	zval *context_zval = NULL;
	double angle = 0.0;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Od", &context_zval, cairo_ce_cairocontext, &angle) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	cairo_rotate(context_object->context, angle);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto void cairo_transform(CairoContext object, CairoMatrix matrix)
   proto void CairoContext->transform(CairoMatrix matrix)
   Modifies the current transformation matrix by applying a matrix as an additional transformation */
PHP_FUNCTION(cairo_transform)
{
	zval *context_zval = NULL, *matrix_zval = NULL;
	cairo_context_object *context_object;
	cairo_matrix_object *matrix_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "OO", &context_zval, cairo_ce_cairocontext, &matrix_zval, cairo_ce_cairomatrix) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	matrix_object = (cairo_matrix_object *)cairo_matrix_object_get(matrix_zval TSRMLS_CC);
	cairo_transform(context_object->context, matrix_object->matrix);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto void cairo_set_matrix(CairoContext object, CairoMatrix matrix)
   proto void CairoContext->setMatrix(CairoMatrix matrix)
   Sets the current transformation matrix */
PHP_FUNCTION(cairo_set_matrix)
{
	zval *context_zval = NULL, *matrix_zval = NULL;
	cairo_context_object *context_object;
	cairo_matrix_object *matrix_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "OO", &context_zval, cairo_ce_cairocontext, &matrix_zval, cairo_ce_cairomatrix) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	matrix_object = (cairo_matrix_object *)cairo_matrix_object_get(matrix_zval TSRMLS_CC);
	cairo_set_matrix(context_object->context, matrix_object->matrix);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));

	/* If there's already a matrix, then we deref and remove it */
	if(context_object->matrix) {
		Z_DELREF_P(context_object->matrix);
		context_object->matrix = NULL;
	}

	/* we need to be able to get this zval out later, so ref and store */
	context_object->matrix = matrix_zval;
	Z_ADDREF_P(matrix_zval);
}
/* }}} */

/* {{{ proto CairoMatrix matrix cairo_get_matrix(CairoContext object)
   proto CairoMatrix matrix CairoContext->getMatrix()
   Returns the current transformation matrix */
PHP_FUNCTION(cairo_get_matrix)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;
	cairo_matrix_object *matrix_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &context_zval, cairo_ce_cairocontext) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);

	/* If we have a matrix object stored, grab that zval to use */
	if(context_object->matrix) {
		zval_dtor(return_value);
		*return_value = *context_object->matrix;
		zval_copy_ctor(return_value);
		Z_SET_REFCOUNT_P(return_value, 1);
	/* Otherwise we spawn a new object */
	} else {
		object_init_ex(return_value, cairo_ce_cairomatrix);	
	}

	matrix_object = (cairo_matrix_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	matrix_object->matrix = ecalloc(sizeof(cairo_matrix_t), 1); 
	cairo_get_matrix(context_object->context, matrix_object->matrix);
}
/* }}} */

/* {{{ proto void cairo_identity_matrix(CairoContext object)
   proto void CairoContext->identityMatrix()
   Resets the current transformation matrix by setting it equal to the identity matrix */
PHP_FUNCTION(cairo_identity_matrix)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &context_zval, cairo_ce_cairocontext) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	cairo_identity_matrix(context_object->context);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto array cairo_user_to_device(CairoContext object, int x, int y)
   proto array CairoContext->userToDevice(int x, int y)
   Transform a coordinate from user space to device space by multiplying the given point by the current transformation matrix */
PHP_FUNCTION(cairo_user_to_device)
{
	zval *context_zval = NULL;
	double x = 0.0, y = 0.0;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odd", &context_zval, cairo_ce_cairocontext, &x, &y) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);

	cairo_user_to_device(context_object->context, &x, &y);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));

	array_init(return_value);
	add_next_index_double(return_value, x);
	add_next_index_double(return_value, y);
}
/* }}} */

/* {{{ proto array cairo_user_to_device_distance(CairoContext object, int x, int y)
   proto array CairoContext->userToDeviceDistance(int x, int y)
   Transform a coordinate from user space to device space by multiplying the
   given point by the current transformation matrix except that the translation components
   are ignored */
PHP_FUNCTION(cairo_user_to_device_distance)
{
	zval *context_zval = NULL;
	double x = 0.0, y = 0.0;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odd", &context_zval, cairo_ce_cairocontext, &x, &y) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);

	cairo_user_to_device_distance(context_object->context, &x, &y);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));

	array_init(return_value);
	add_next_index_double(return_value, x);
	add_next_index_double(return_value, y);
}
/* }}} */

/* {{{ proto array cairo_device_to_user(CairoContext object, int x, int y)
   proto array CairoContext->deviceToUser(int x, int y)
   Transform a coordinate from device space to user space by multiplying the given
   point by the inverse of the current transformation matrix */
PHP_FUNCTION(cairo_device_to_user)
{
	zval *context_zval = NULL;
	double x = 0.0, y = 0.0;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odd", &context_zval, cairo_ce_cairocontext, &x, &y) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);

	cairo_device_to_user(context_object->context, &x, &y);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));

	array_init(return_value);
	add_next_index_double(return_value, x);
	add_next_index_double(return_value, y);
}
/* }}} */

/* {{{ proto void cairo_device_to_user_distance(CairoContext object, int x, int y)
   proto void CairoContext->deviceToUserDistance(int x, int y)
   Transform a distance vector from device space to user space. */
PHP_FUNCTION(cairo_device_to_user_distance)
{
	zval *context_zval = NULL;
	double x = 0.0, y = 0.0;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odd", &context_zval, cairo_ce_cairocontext, &x, &y) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);

	cairo_device_to_user_distance(context_object->context, &x, &y);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));

	array_init(return_value);
	add_next_index_double(return_value, x);
	add_next_index_double(return_value, y);
}
/* }}} */

/* Path Methods */

/* {{{ proto CairoPath object cairo_copy_path(CairoContext object)
   proto CairoPath object CairoContext->copyPath()
   Creates a copy of the current path and returns it to the user as a CairoPath object */
PHP_FUNCTION(cairo_copy_path)
{
	zval *context_zval = NULL;
	cairo_path_object *path_object;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &context_zval, cairo_ce_cairocontext) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	object_init_ex(return_value, php_cairo_get_path_ce());
	path_object = (cairo_path_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	path_object->path = cairo_copy_path(context_object->context);
	PHP_CAIRO_ERROR(path_object->path->status);
}
/* }}} */

/* {{{ proto CairoPath object cairo_copy_path_flat(CairoContext object)
   proto CairoPath object CairoContext->copyPathFlat()
   Creates a copy of the current path and returns it to the user as a CairoPath object
   any curves in the path will be approximated with piecewise-linear approximations*/
PHP_FUNCTION(cairo_copy_path_flat)
{
	zval *context_zval = NULL;
	cairo_path_object *path_object;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &context_zval, cairo_ce_cairocontext) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	object_init_ex(return_value, php_cairo_get_path_ce());
	path_object = (cairo_path_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	path_object->path = cairo_copy_path_flat(context_object->context);
	PHP_CAIRO_ERROR(path_object->path->status);
}
/* }}} */

/* {{{ proto void cairo_append_path(CairoContext object, CairoPath object)
   proto void CairoContext->appendPath(CairoPath object)
   Append the path onto the current path.  */
PHP_FUNCTION(cairo_append_path)
{
	zval *context_zval = NULL;
	zval *path_zval = NULL;
	const cairo_path_t *path;
	cairo_path_object *path_object;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "OO", &context_zval, cairo_ce_cairocontext, &path_zval, php_cairo_get_path_ce()) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	path_object = (cairo_path_object *)cairo_path_object_get(path_zval TSRMLS_CC);
	path = path_object->path;
	cairo_append_path(context_object->context, path); 
	PHP_CAIRO_ERROR(cairo_status(context_object->context));
}
/* }}} */

#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 6, 0)
/* {{{ proto bool cairo_has_current_point(CairoContext object)
   proto bool CairoContext->hasCurrentPoint()
   Returns whether a current point is defined on the current path.  */
PHP_FUNCTION(cairo_has_current_point)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &context_zval, cairo_ce_cairocontext) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	RETURN_BOOL(cairo_has_current_point(context_object->context)); 
}
/* }}} */
#endif

/* {{{ proto array cairo_get_current_point(CairoContext object)
   proto array CairoContext->getCurrentPoint()
   Gets the current point of the current path, which is conceptually the final point reached by the path so far.  */
PHP_FUNCTION(cairo_get_current_point)
{
	zval *context_zval = NULL;
	double x, y;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &context_zval, cairo_ce_cairocontext) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));

	cairo_get_current_point(context_object->context, &x, &y);
	array_init(return_value);
	add_next_index_double(return_value, x);
	add_next_index_double(return_value, y);
}
/* }}} */

/* {{{ proto void cairo_new_path(CairoContext object)
   proto void CairoContext->newPath()
   Clears the current path. After this call there will be no path and no current point. */
PHP_FUNCTION(cairo_new_path)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &context_zval, cairo_ce_cairocontext) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	cairo_new_path(context_object->context); 
	PHP_CAIRO_ERROR(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto void cairo_new_sub_path(CairoContext object)
   proto void CairoContext->newSubPath()
   Begin a new sub-path. Note that the existing path is not affected. After this call there will be no current point.  */
PHP_FUNCTION(cairo_new_sub_path)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &context_zval, cairo_ce_cairocontext) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	cairo_new_sub_path(context_object->context); 
	PHP_CAIRO_ERROR(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto void cairo_close_path(CairoContext object)
   proto void CairoContext->closePath()
   Adds a line segment to the path from the current point to the beginning of the current sub-path,
   and closes this sub-path. After this call the current point will be at the joined endpoint of the sub-path.   */
PHP_FUNCTION(cairo_close_path)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &context_zval, cairo_ce_cairocontext) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	cairo_close_path(context_object->context); 
	PHP_CAIRO_ERROR(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto void cairo_arc(CairoContext object, float x, float y, float radius, float angle1, float angle2)
   proto void CairoContext->arc(float x, float y, float radius, float angle1, float angle2)
   Adds a circular arc of the given radius to the current path.
   The arc is centered at (x, y), begins at angle1 and proceeds in the direction of increasing angles to end at angle2*/
PHP_FUNCTION(cairo_arc)
{
	zval *context_zval = NULL;
	double x = 0.0, y = 0.0, radius = 0.0, angle1 = 0.0, angle2 = 0.0;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Oddddd", &context_zval, cairo_ce_cairocontext, &x, &y, &radius, &angle1, &angle2) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	cairo_arc(context_object->context, x, y, radius, angle1, angle2); 
	PHP_CAIRO_ERROR(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto void cairo_arc_negative(CairoContext object, float x, float y, float radius, float angle1, float angle2)
   proto void CairoContext->arcNegative(float x, float y, float radius, float angle1, float angle2)
   Adds a circular arc of the given radius to the current path.
   The arc is centered at (x, y), begins at angle1 and proceeds in the direction of decreasing angles to end at angle2.*/
PHP_FUNCTION(cairo_arc_negative)
{
	zval *context_zval = NULL;
	double x = 0.0, y = 0.0, radius = 0.0, angle1 = 0.0, angle2 = 0.0;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Oddddd", &context_zval, cairo_ce_cairocontext, &x, &y, &radius, &angle1, &angle2) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	cairo_arc_negative(context_object->context, x, y, radius, angle1, angle2); 
	PHP_CAIRO_ERROR(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto void cairo_curve_to(CairoContext object, float x1, float y1, float x2, float y2, float x3, float y3)
   proto void CairoContext->curveTo(float x1, float y1, float x2, float y2, float x3, float y3)
   Adds a cubic Bézier spline to the path from the current point to position (x3, y3) in user-space coordinates, using (x1, y1) and (x2, y2) as the control points.
   After this call the current point will be (x3, y3).  */
PHP_FUNCTION(cairo_curve_to)
{
	zval *context_zval = NULL;
	double x1 = 0.0, y1 = 0.0, x2 = 0.0, y2 = 0.0, x3 = 0.0, y3 = 0.0;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odddddd", &context_zval, cairo_ce_cairocontext, &x1, &y1, &x2, &y2, &x3, &y3) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	cairo_curve_to(context_object->context, x1, y1, x2, y2, x3, y3); 
	PHP_CAIRO_ERROR(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto void cairo_line_to(CairoContext object, float x, float y)
   proto void CairoContext->lineTo(float x, float y)
   Adds a line to the path from the current point to position (x, y) in user-space coordinates. After this call the current point will be (x, y). */
PHP_FUNCTION(cairo_line_to)
{
	zval *context_zval = NULL;
	double x = 0.0, y = 0.0;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odd", &context_zval, cairo_ce_cairocontext, &x, &y) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	cairo_line_to(context_object->context, x, y); 
	PHP_CAIRO_ERROR(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto void cairo_move_to(CairoContext object, float x, float y)
   proto void CairoContext->moveTo(float x, float y)
   Begin a new sub-path. After this call the current point will be (x, y) */
PHP_FUNCTION(cairo_move_to)
{
	zval *context_zval = NULL;
	double x = 0.0, y = 0.0;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odd", &context_zval, cairo_ce_cairocontext, &x, &y) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	cairo_move_to(context_object->context, x, y); 
	PHP_CAIRO_ERROR(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto void cairo_rectangle(CairoContext object, float x, float y, float width, float height)
   proto void CairoContext->rectangle(float x, float y, float width, float height)
   Adds a closed sub-path rectangle of the given size to the current path at position (x, y) in user-space coordinates.  */
PHP_FUNCTION(cairo_rectangle)
{
	zval *context_zval = NULL;
	double x = 0.0, y = 0.0, width = 0.0, height = 0.0;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odddd", &context_zval, cairo_ce_cairocontext, &x, &y, &width, &height) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	cairo_rectangle(context_object->context, x, y, width, height); 
	PHP_CAIRO_ERROR(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto void cairo_text_path(CairoContext object, array glyphs)
   proto void CairoContext->glyphPath(array glyphs)
   Adds closed paths for the glyphs to the current path. */
PHP_FUNCTION(cairo_glyph_path)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;
	const cairo_glyph_t *glyphs = NULL;
	long num_glyphs = 0;

	zval * php_glyphs = NULL, **ppzval;
	HashTable *glyphs_hash = NULL;
	int i = 0;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Oa", &context_zval, cairo_ce_cairocontext, &php_glyphs) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	/* Grab the zend hash */
	glyphs_hash = Z_ARRVAL_P(php_glyphs);

	/* iterate the array, each value inside MUST be an instance of CairoGlyph */
	for(zend_hash_internal_pointer_reset(glyphs_hash); zend_hash_has_more_elements(glyphs_hash) == SUCCESS; zend_hash_move_forward(glyphs_hash)) { 
		if (zend_hash_get_current_data(glyphs_hash, (void **)&ppzval) == FAILURE) {
			continue; 
		}

		/* TODO: check here for is object and instanceof CairoGlyph, then rip the internal glyph out and stick it in the array
		then increment the glyph count
		if (Z_TYPE_PP(ppzval) != IS_DOUBLE) {
			convert_to_double(*ppzval);
		}
		dashes_array[i++] = Z_DVAL_PP(ppzval);*/
	}

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	cairo_glyph_path(context_object->context, glyphs, num_glyphs);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));
}
/* }}} */


/* {{{ proto void cairo_text_path(CairoContext object, string text)
   proto void CairoContext->textPath(string text)
   Adds closed paths for text to the current path
   NOTE: text must be UTF-8 charset or results will be unexpected */
PHP_FUNCTION(cairo_text_path)
{
	zval *context_zval = NULL;
	const char *string;
	int str_len;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Os", &context_zval, cairo_ce_cairocontext, &string, &str_len) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	cairo_text_path(context_object->context, string); 
	PHP_CAIRO_ERROR(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto void cairo_rel_curve_to(CairoContext object, float x1, float y1, float x2, float y2, float x3, float y3)
   proto void CairoContext->relCurveTo(float x1, float y1, float x2, float y2, float x3, float y3)
   Adds a cubic Bézier spline to the path from the current point to a point offset from the current point by (x3, y3),
   using points offset by (x1, y1) and (x2, y2) as the control points. */
PHP_FUNCTION(cairo_rel_curve_to)
{
	zval *context_zval = NULL;
	double x1 = 0.0, y1 = 0.0, x2 = 0.0, y2 = 0.0, x3 = 0.0, y3 = 0.0;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odddddd", &context_zval, cairo_ce_cairocontext, &x1, &y1, &x2, &y2, &x3, &y3) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	cairo_rel_curve_to(context_object->context, x1, y1, x2, y2, x3, y3); 
	PHP_CAIRO_ERROR(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto void cairo_rel_line_to(CairoContext object, float x, float y)
   proto void CairoContext->relLineTo(float x, float y)
   Adds a line to the path from the current point to a point that is offset from the current point by (x, y) in user space */
PHP_FUNCTION(cairo_rel_line_to)
{
	zval *context_zval = NULL;
	double x = 0.0, y = 0.0;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odd", &context_zval, cairo_ce_cairocontext, &x, &y) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	cairo_rel_line_to(context_object->context, x, y); 
	PHP_CAIRO_ERROR(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto void cairo_rel_move_to(CairoContext object, float x, float y)
   proto void CairoContext->relMoveTo(float x, float y)
   Begin a new sub-path. After this call the current point will offset by (x, y). */
PHP_FUNCTION(cairo_rel_move_to)
{
	zval *context_zval = NULL;
	double x = 0.0, y = 0.0;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odd", &context_zval, cairo_ce_cairocontext, &x, &y) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	cairo_rel_move_to(context_object->context, x, y); 
	PHP_CAIRO_ERROR(cairo_status(context_object->context));
}
/* }}} */

#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 6, 0)
/* {{{ proto array cairo_path_extents(CairoContext object)
   proto array CairoContext->pathExtents()
   Computes a bounding box in user-space coordinates covering the points on the current path */
PHP_FUNCTION(cairo_path_extents)
{
	zval *context_zval = NULL;
	double x1, y1, x2, y2;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &context_zval, cairo_ce_cairocontext) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));

	cairo_path_extents(context_object->context, &x1, &y1, &x2, &y2);
	array_init(return_value);
	add_next_index_double(return_value, x1);
	add_next_index_double(return_value, y1);
	add_next_index_double(return_value, x2);
	add_next_index_double(return_value, y2);
}
/* }}} */
#endif

/* Text items */

/* {{{ proto void cairo_select_font_face(CairoContext object, string family, CairoFontSlant slant, CairoFontWeight weight) 
  	   proto void CairoContext->selectFontFace(string family, CairoFontSlant slant, CairoFontWeight weight)
	   Selects a family and style of font from a simplified description as a family name, slant and weight.
	   */
PHP_FUNCTION(cairo_select_font_face)
{
	zval *context_zval = NULL;
	long slant = CAIRO_FONT_SLANT_NORMAL, weight = CAIRO_FONT_WEIGHT_NORMAL, family_len;
	char *family, *cairo_family;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Os|ll", 
				&context_zval, cairo_ce_cairocontext,
				&family, &family_len,
				&slant, &weight) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	cairo_family = estrdup(family);		
	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	cairo_select_font_face(context_object->context, family, slant, weight);
	efree(cairo_family);
}
/* }}} */

/* {{{ proto void cairo_set_font_size(CairoContext context, double size)
  	   proto void CairoContext->selectFontFace(double size)
	   Sets the current font matrix to a scale by a factor of size, replacing any font matrix previously 
	   set with cairo_set_font_size() or cairo_set_font_matrix()
	   */
PHP_FUNCTION(cairo_set_font_size)
{
	zval *context_zval = NULL;
	double size;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Od", 
				&context_zval, cairo_ce_cairocontext, &size	) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	cairo_set_font_size(context_object->context, size);

	/* If there's a font matrix stored, we've just reset it */
	if(context_object->font_matrix) {
		Z_DELREF_P(context_object->font_matrix);
		context_object->font_matrix = NULL;
	}
}
/* }}} */

/* {{{ proto void cairo_set_font_matrix(CairoContext object, CairoMatrix matrix)
   proto void CairoContext->setFontMatrix(CairoMatrix matrix)
   Sets the current transformation matrix for fonts */
PHP_FUNCTION(cairo_set_font_matrix)
{
	zval *context_zval = NULL, *matrix_zval = NULL;
	cairo_context_object *context_object;
	cairo_matrix_object *matrix_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "OO", &context_zval, cairo_ce_cairocontext, &matrix_zval, cairo_ce_cairomatrix) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	matrix_object = (cairo_matrix_object *)cairo_matrix_object_get(matrix_zval TSRMLS_CC);
	cairo_set_font_matrix(context_object->context, matrix_object->matrix);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));

	/* If there's already a matrix, then we deref and remove it */
	if(context_object->font_matrix) {
		Z_DELREF_P(context_object->font_matrix);
		context_object->font_matrix = NULL;
	}

	/* we need to be able to get this zval out later, so ref and store */
	context_object->font_matrix = matrix_zval;
	Z_ADDREF_P(matrix_zval);
}
/* }}} */

/* {{{ proto CairoMatrix matrix cairo_get_font_matrix(CairoContext object)
   proto CairoMatrix matrix CairoContext->getFontMatrix()
   Returns the current transformation matrix fot the font*/
PHP_FUNCTION(cairo_get_font_matrix)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;
	cairo_matrix_object *matrix_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &context_zval, cairo_ce_cairocontext) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);

	/* If we have a matrix object stored, grab that zval to use */
	if(context_object->font_matrix) {
		zval_dtor(return_value);
		*return_value = *context_object->font_matrix;
		zval_copy_ctor(return_value);
		Z_SET_REFCOUNT_P(return_value, 1);
	/* Otherwise we spawn a new object */
	} else {
		object_init_ex(return_value, cairo_ce_cairomatrix);	
	}

	matrix_object = (cairo_matrix_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	matrix_object->matrix = ecalloc(sizeof(cairo_matrix_t), 1); 
	cairo_get_font_matrix(context_object->context, matrix_object->matrix);
}
/* }}} */

/* {{{ proto void cairo_set_font_options(CairoContext object, CairoFontOptions object)
       proto void CairoContext->setFontOptions(CairoFontOptions object)
       Sets the font options to be used with the context  */
PHP_FUNCTION(cairo_set_font_options)
{
	zval *context_zval = NULL, *font_options_zval = NULL;
	cairo_context_object *context_object;
	cairo_font_options_object *font_options_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "OO", &context_zval, cairo_ce_cairocontext, &font_options_zval, cairo_ce_cairofontoptions) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	font_options_object = (cairo_font_options_object *)cairo_font_options_object_get(font_options_zval TSRMLS_CC);
	cairo_set_font_options(context_object->context, font_options_object->font_options);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));

	/* If there's already a font_options stored, then we deref and remove it */
	if(context_object->font_options) {
		Z_DELREF_P(context_object->font_options);
		context_object->font_options = NULL;
	}

	/* we need to be able to get this zval out later, so ref and store */
	context_object->font_options = font_options_zval;
	Z_ADDREF_P(font_options_zval);
}
/* }}} */

/* {{{ proto CairoFontOptions object cairo_get_font_options(CairoContext object)
       proto CairoFontOptions object CairoContext->getFontOptions()
       Retrieves the font options selected by the context.  If no font options have been selected or set then the default options
	   will be returned.  */
PHP_FUNCTION(cairo_get_font_options)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;
	cairo_font_options_object *font_options_object;
	cairo_font_options_t *font_options = NULL;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &context_zval, cairo_ce_cairocontext) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);

	/* Grab the font options properly */
	cairo_get_font_options(context_object->context, font_options);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));

	/* If we have a font face object stored, grab that zval to use */
	if(context_object->font_options) {
		zval_dtor(return_value);
		*return_value = *context_object->font_options;
		zval_copy_ctor(return_value);
		Z_SET_REFCOUNT_P(return_value, 1);
	/* Otherwise we spawn a new object */
	} else {
		object_init_ex(return_value, cairo_ce_cairofontoptions);	
	}

	font_options_object = (cairo_font_options_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	font_options_object->font_options = font_options;
}
/* }}} */

/* {{{ proto void cairo_set_font_face(CairoContext object, CairoFontFace object)
       proto void CairoContext->setFontFace(CairoFontFace object)
       Sets the font face to be used with the context  */
PHP_FUNCTION(cairo_set_font_face)
{
	zval *context_zval = NULL, *font_face_zval = NULL;
	cairo_context_object *context_object;
	cairo_font_face_object *font_face_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "OO", &context_zval, cairo_ce_cairocontext, &font_face_zval, cairo_ce_cairofontface) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	font_face_object = (cairo_font_face_object *)cairo_font_face_object_get(font_face_zval TSRMLS_CC);
	cairo_set_font_face(context_object->context, font_face_object->font_face);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));

	/* If there's already a font face stored, then we deref and remove it */
	if(context_object->font_face) {
		Z_DELREF_P(context_object->font_face);
		context_object->font_face = NULL;
	}

	/* we need to be able to get this zval out later, so ref and store */
	context_object->font_face = font_face_zval;
	Z_ADDREF_P(font_face_zval);
}
/* }}} */

/* {{{ proto CairoFontFace object cairo_get_font_face(CairoContext object)
       proto CairoFontFace object CairoContext->getFontFace()
       Retrieves the font face selected by the context.  If no font face has been selected or set then the default face
	   will be returned.  */
PHP_FUNCTION(cairo_get_font_face)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;
	cairo_font_face_object *font_face_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &context_zval, cairo_ce_cairocontext) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);

	/* If we have a font face object stored, grab that zval to use */
	if(context_object->font_face) {
		zval_dtor(return_value);
		*return_value = *context_object->font_face;
		zval_copy_ctor(return_value);
		Z_SET_REFCOUNT_P(return_value, 1);
	/* Otherwise we spawn a new object */
	} else {
		object_init_ex(return_value, cairo_ce_cairotoyfontface);
	}

	font_face_object = (cairo_font_face_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	/* if there IS a value in font_face_object, destroy it cause we're getting a new one */
	if (font_face_object->font_face != NULL) {
		cairo_font_face_destroy(font_face_object->font_face);
	}
	font_face_object->font_face = cairo_get_font_face(context_object->context);
	cairo_font_face_reference(font_face_object->font_face);
}
/* }}} */

/* {{{ proto void cairo_set_scaled_font(CairoContext object, CairoScaledFont object)
       proto void CairoContext->setScaledFont(CairoScaledFont object)
       Replaces the current font face, font matrix, and font options in the context with those of the scaled font.  */
PHP_FUNCTION(cairo_set_scaled_font)
{
	zval *context_zval = NULL, *scaled_font_zval = NULL;
	cairo_context_object *context_object;
	cairo_scaled_font_object *scaled_font_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "OO", &context_zval, cairo_ce_cairocontext, &scaled_font_zval, cairo_ce_cairoscaledfont) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	scaled_font_object = (cairo_scaled_font_object *)cairo_scaled_font_object_get(scaled_font_zval TSRMLS_CC);
	cairo_set_scaled_font(context_object->context, scaled_font_object->scaled_font);
	PHP_CAIRO_ERROR(cairo_status(context_object->context));

	/* If there's already a font face, font matrix, scaled font, and or font options stored, then we deref and remove them */
	if(context_object->font_face) {
		Z_DELREF_P(context_object->font_face);
		context_object->font_face = NULL;
	}
	if(context_object->font_matrix) {
		Z_DELREF_P(context_object->font_matrix);
		context_object->font_matrix = NULL;
	}
	if(context_object->font_options) {
		Z_DELREF_P(context_object->font_options);
		context_object->font_options = NULL;
	}
	if(context_object->scaled_font) {
		Z_DELREF_P(context_object->scaled_font);
		context_object->scaled_font = NULL;
	}

	/* if the scaled font has a font_face, matrix, or option zvals stored, move them to context as well and ref again */
	if(scaled_font_object->font_face) {
		context_object->font_face = scaled_font_object->font_face;
		Z_ADDREF_P(context_object->font_face);
	}
	if(scaled_font_object->matrix) {
		context_object->font_matrix = scaled_font_object->matrix;
		Z_ADDREF_P(context_object->font_matrix);
	}
	if(scaled_font_object->font_options) {
		context_object->font_options = scaled_font_object->font_options;
		Z_ADDREF_P(context_object->font_options);
	}

	/* we need to be able to get this zval out later, so ref and store */
	context_object->scaled_font = scaled_font_zval;
	Z_ADDREF_P(scaled_font_zval);
}
/* }}} */

#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 4, 0)
/* {{{ proto CairoScaledFont object cairo_get_scaled_font(CairoContext object)
       proto CairoScaledFont object CairoContext->getScaledFont()
       Retrieves the scaled font face selected by the context.  If no scaled font has been selected or set then the default face
	   will be returned.  */
PHP_FUNCTION(cairo_get_scaled_font)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;
	cairo_scaled_font_object *scaled_font_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &context_zval, cairo_ce_cairocontext) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);

	/* If we have a scaled font object stored, grab that zval to use */
	if(context_object->scaled_font) {
		zval_dtor(return_value);
		*return_value = *context_object->scaled_font;
		zval_copy_ctor(return_value);
		Z_SET_REFCOUNT_P(return_value, 1);
	/* Otherwise we spawn a new object */
	} else {
		object_init_ex(return_value, cairo_ce_cairoscaledfont);
	}

	scaled_font_object = (cairo_scaled_font_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	/* if there IS a value in scaled_font_object, destroy it cause we're getting a new one */
	if (scaled_font_object->scaled_font != NULL) {
		cairo_scaled_font_destroy(scaled_font_object->scaled_font);
	}
	scaled_font_object->scaled_font = cairo_get_scaled_font(context_object->context);
	cairo_scaled_font_reference(scaled_font_object->scaled_font);
}
/* }}} */
#endif

/* {{{ proto array cairo_show_text(CairoContext object, string text)
   proto array CairoContext->showText(string text)
   A drawing operator that generates the shape from a string of UTF-8 characters,
   rendered according to the current font_face, font_size (font_matrix), and font_options. 
   */
PHP_FUNCTION(cairo_show_text)
{
	zval *context_zval = NULL;
	char *text, *cairo_text;
	int text_len;
	cairo_context_object *context_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Os", 
				&context_zval, cairo_ce_cairocontext,
				&text, &text_len ) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);

	cairo_text = estrdup(text);
	cairo_show_text(context_object->context, text);
	efree(cairo_text);
}
/* }}} */

/* {{{ proto array cairo_font_extents(CairoContext object)
       proto array CairoContext->fontExtents()
       Gets the metrics for a font in an assoc array
*/
PHP_FUNCTION(cairo_font_extents)
{
	zval *context_zval = NULL;
	cairo_context_object *context_object;
	cairo_font_extents_t extents;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &context_zval, cairo_ce_cairocontext) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	cairo_font_extents(context_object->context, &extents);

	array_init(return_value);
	add_assoc_double(return_value, "ascent", extents.ascent);
	add_assoc_double(return_value, "descent", extents.descent);
	add_assoc_double(return_value, "height", extents.height);
	add_assoc_double(return_value, "max_x_advance", extents.max_x_advance);
	add_assoc_double(return_value, "max_y_advance", extents.max_y_advance);
}
/* }}} */

/* {{{ proto array cairo_text_extents(CairoContext object, string text)
   proto array CairoContext->textExtents(string text)
   Gets the extents for a string of text.
   */
PHP_FUNCTION(cairo_text_extents)
{
	zval *context_zval = NULL;
	char *text, *cairo_text;
	int text_len;
	cairo_context_object *context_object;
	cairo_text_extents_t extents;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Os", 
				&context_zval, cairo_ce_cairocontext,
				&text, &text_len ) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	cairo_text = estrdup(text);

	context_object = (cairo_context_object *)cairo_context_object_get(context_zval TSRMLS_CC);
	cairo_text_extents(context_object->context, cairo_text, &extents);
	efree(cairo_text);

	array_init(return_value);
	add_assoc_double(return_value, "x_bearing", extents.x_bearing);
	add_assoc_double(return_value, "y_bearing", extents.y_bearing);
	add_assoc_double(return_value, "width", extents.width);
	add_assoc_double(return_value, "height", extents.height);
	add_assoc_double(return_value, "x_advance", extents.x_advance);
	add_assoc_double(return_value, "y_advance", extents.y_advance);
}
/* }}} */

/* {{{ cairo_context_methods[] */
const zend_function_entry cairo_context_methods[] = {
	PHP_ME(CairoContext, __construct, CairoContext___construct_args, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME_MAPPING(status, cairo_status, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(save, cairo_save, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(restore, cairo_restore, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(getTarget, cairo_get_target, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(pushGroup, cairo_push_group, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(pushGroupWithContent, cairo_push_group_with_content, CairoContext_pushGroupWithContent_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(popGroup, cairo_pop_group, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(popGroupToSource, cairo_pop_group_to_source, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(getGroupTarget, cairo_get_group_target, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(setSourceRGB, cairo_set_source_rgb, CairoContext_setSourceRGB_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(setSourceRGBA, cairo_set_source_rgba, CairoContext_setSourceRGBA_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(setSource, cairo_set_source, CairoContext_setSource_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(setSourceSurface, cairo_set_source_surface, CairoContext_setSourceSurface_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(getSource, cairo_get_source, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(setAntialias, cairo_set_antialias, CairoContext_setAntialias_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(getAntialias, cairo_get_antialias, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(setDash, cairo_set_dash, CairoContext_setDash_args, ZEND_ACC_PUBLIC)
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 4, 0)
	PHP_ME_MAPPING(getDashCount, cairo_get_dash_count, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(getDash, cairo_get_dash, NULL, ZEND_ACC_PUBLIC)
#endif
	PHP_ME_MAPPING(setFillRule, cairo_set_fill_rule, CairoContext_setFillRule_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(getFillRule, cairo_get_fill_rule, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(setLineCap, cairo_set_line_cap, CairoContext_setFillRule_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(getLineCap, cairo_get_line_cap, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(setLineJoin, cairo_set_line_join, CairoContext_setFillRule_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(getLineJoin, cairo_get_line_join, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(setLineWidth, cairo_set_line_width, CairoContext_setLineWidth_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(getLineWidth, cairo_get_line_width, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(setMiterLimit, cairo_set_miter_limit, CairoContext_setMiterLimit_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(getMiterLimit, cairo_get_miter_limit, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(setOperator, cairo_set_operator, CairoContext_setFillRule_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(getOperator, cairo_get_operator, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(setTolerance, cairo_set_tolerance, CairoContext_setTolerance_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(getTolerance, cairo_get_tolerance, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(clip, cairo_clip, NULL, ZEND_ACC_PUBLIC)
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 10, 0)
	PHP_ME_MAPPING(inClip, cairo_in_clip, NULL, ZEND_ACC_PUBLIC)
#endif
	PHP_ME_MAPPING(clipPreserve, cairo_clip_preserve, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(resetClip, cairo_reset_clip, NULL, ZEND_ACC_PUBLIC)

#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 4, 0)
	PHP_ME_MAPPING(clipExtents, cairo_clip_extents, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(clipRectangleList, cairo_clip_rectangle_list, NULL, ZEND_ACC_PUBLIC)
#endif

	PHP_ME_MAPPING(fill, cairo_fill, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(fillPreserve, cairo_fill_preserve, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(fillExtents, cairo_fill_extents, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(inFill, cairo_in_fill, CairoContext_translate_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(mask, cairo_mask, CairoContext_setSource_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(maskSurface, cairo_mask_surface, CairoContext_setSourceSurface_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(paint, cairo_paint, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(paintWithAlpha, cairo_paint_with_alpha, CairoContext_paintWithAlpha_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(stroke, cairo_stroke, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(strokePreserve, cairo_stroke_preserve, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(strokeExtents, cairo_stroke_extents, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(inStroke, cairo_in_stroke, CairoContext_translate_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(copyPage, cairo_copy_page, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(showPage, cairo_show_page, NULL, ZEND_ACC_PUBLIC)
	/* Transformations */
	PHP_ME_MAPPING(translate, cairo_translate, CairoContext_translate_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(scale, cairo_scale, CairoContext_translate_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(rotate, cairo_rotate, CairoContext_rotate_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(transform, cairo_transform, CairoContext_transform_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(setMatrix, cairo_set_matrix, CairoContext_transform_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(getMatrix, cairo_get_matrix, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(identityMatrix, cairo_identity_matrix, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(userToDevice, cairo_user_to_device, CairoContext_translate_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(userToDeviceDistance, cairo_user_to_device_distance, CairoContext_translate_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(deviceToUser, cairo_device_to_user, CairoContext_translate_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(deviceToUserDistance, cairo_device_to_user_distance, CairoContext_translate_args, ZEND_ACC_PUBLIC)
	/* Paths */
	PHP_ME_MAPPING(copyPath, cairo_copy_path, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(copyPathFlat, cairo_copy_path_flat, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(appendPath, cairo_append_path, CairoContext_appendPath_args, ZEND_ACC_PUBLIC)
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 6, 0)
	PHP_ME_MAPPING(hasCurrentPoint, cairo_has_current_point, NULL, ZEND_ACC_PUBLIC)
#endif
	PHP_ME_MAPPING(getCurrentPoint, cairo_get_current_point, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(newPath, cairo_new_path, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(newSubPath, cairo_new_sub_path, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(closePath, cairo_close_path, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(arc, cairo_arc, CairoContext_arc_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(arcNegative, cairo_arc_negative, CairoContext_arc_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(curveTo, cairo_curve_to, CairoContext_curveTo_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(lineTo, cairo_line_to, CairoContext_translate_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(moveTo, cairo_move_to, CairoContext_translate_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(rectangle, cairo_rectangle, CairoContext_rectangle_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(glyphPath, cairo_glyph_path, CairoContext_glyphPath_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(textPath, cairo_text_path, CairoContext_textPath_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(relCurveTo, cairo_rel_curve_to, CairoContext_curveTo_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(relLineTo, cairo_rel_line_to, CairoContext_translate_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(relMoveTo, cairo_rel_move_to, CairoContext_translate_args, ZEND_ACC_PUBLIC)
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 6, 0)
	PHP_ME_MAPPING(pathExtents, cairo_path_extents, NULL, ZEND_ACC_PUBLIC)
#endif
	/* Text */
	PHP_ME_MAPPING(selectFontFace, cairo_select_font_face, CairoContext_selectFontFace_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(setFontSize, cairo_set_font_size, CairoContext_setFontSize_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(setFontMatrix, cairo_set_font_matrix, CairoContext_setFontMatrix_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(getFontMatrix, cairo_get_font_matrix, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(setFontOptions, cairo_set_font_options, CairoContext_setFontOptions_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(getFontOptions, cairo_get_font_options, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(setFontFace, cairo_set_font_face, CairoContext_setFontFace_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(getFontFace, cairo_get_font_face, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(setScaledFont, cairo_set_scaled_font, CairoContext_setScaledFont_args, ZEND_ACC_PUBLIC)
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 4, 0)
	PHP_ME_MAPPING(getScaledFont, cairo_get_scaled_font, NULL, ZEND_ACC_PUBLIC)
#endif
	PHP_ME_MAPPING(showText, cairo_show_text, CairoContext_text_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(fontExtents, cairo_font_extents, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(textExtents, cairo_text_extents, CairoContext_text_args, ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};
/* }}} */

static void cairo_context_object_destroy(void *object TSRMLS_DC)
{
	cairo_context_object *context = (cairo_context_object *)object;
	zend_hash_destroy(context->std.properties);
	FREE_HASHTABLE(context->std.properties);

	if(context->surface) {
		Z_DELREF_P(context->surface);
		context->surface = NULL;
	}
	if(context->matrix) {
		Z_DELREF_P(context->matrix);
		context->matrix = NULL;
	}
	if(context->pattern) {
		Z_DELREF_P(context->pattern);
		context->pattern = NULL;
	}
	if(context->font_face) {
		Z_DELREF_P(context->font_face);
		context->font_face = NULL;
	}
	if(context->font_matrix) {
		Z_DELREF_P(context->font_matrix);
		context->font_matrix = NULL;
	}
	if(context->font_options) {
		Z_DELREF_P(context->font_options);
		context->font_options = NULL;
	}
	if(context->scaled_font) {
		Z_DELREF_P(context->scaled_font);
		context->scaled_font = NULL;
	}

	if(context->context){
		cairo_destroy(context->context);
	}
	efree(object);
}

static zend_object_value cairo_context_object_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	cairo_context_object *context;
#if PHP_VERSION_ID < 50399
	zval *temp;
#endif

	context = ecalloc(1, sizeof(cairo_context_object));

	context->std.ce = ce;
	context->surface = NULL;
	context->matrix = NULL;
	context->pattern = NULL;
	context->font_face = NULL;
	context->font_matrix = NULL;
	context->scaled_font = NULL;

	ALLOC_HASHTABLE(context->std.properties);
	zend_hash_init(context->std.properties, 0, NULL, ZVAL_PTR_DTOR, 0);
#if PHP_VERSION_ID < 50399
	zend_hash_copy(context->std.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref,(void *) &temp, sizeof(zval *));
#else
	object_properties_init(&context->std, ce);
#endif
	retval.handle = zend_objects_store_put(context, NULL, (zend_objects_free_object_storage_t)cairo_context_object_destroy, NULL TSRMLS_CC);
	retval.handlers = &cairo_std_object_handlers;
	return retval;
}

PHP_CAIRO_API zend_class_entry* php_cairo_get_context_ce()
{
	return cairo_ce_cairocontext;
}

PHP_CAIRO_API extern cairo_t * php_cairo_context_reference(cairo_t *context)
{
	return cairo_reference(context);
}

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(cairo_context)
{
	zend_class_entry ce, antialias_ce, subpixelorder_ce, fillrule_ce, linecap_ce, linejoin_ce, operator_ce;

	INIT_CLASS_ENTRY(ce, "CairoContext", cairo_context_methods);
	cairo_ce_cairocontext = zend_register_internal_class(&ce TSRMLS_CC);
	cairo_ce_cairocontext->create_object = cairo_context_object_new;

	INIT_CLASS_ENTRY(antialias_ce, "CairoAntialias", NULL);
	cairo_ce_cairoantialias = zend_register_internal_class(&antialias_ce TSRMLS_CC);
	cairo_ce_cairoantialias->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS | ZEND_ACC_FINAL_CLASS;

	#define REGISTER_CAIRO_ANTIALIAS_LONG_CONST(const_name, value) \
		zend_declare_class_constant_long(cairo_ce_cairoantialias, const_name, sizeof(const_name)-1, (long)value TSRMLS_CC); \
		REGISTER_LONG_CONSTANT(#value,  value,  CONST_CS | CONST_PERSISTENT);

	REGISTER_CAIRO_ANTIALIAS_LONG_CONST("MODE_DEFAULT", CAIRO_ANTIALIAS_DEFAULT);
	REGISTER_CAIRO_ANTIALIAS_LONG_CONST("MODE_NONE", CAIRO_ANTIALIAS_NONE);
	REGISTER_CAIRO_ANTIALIAS_LONG_CONST("MODE_GRAY", CAIRO_ANTIALIAS_GRAY);
	REGISTER_CAIRO_ANTIALIAS_LONG_CONST("MODE_SUBPIXEL", CAIRO_ANTIALIAS_SUBPIXEL);

	INIT_CLASS_ENTRY(subpixelorder_ce, "CairoSubpixelOrder", NULL);
	cairo_ce_cairosubpixelorder = zend_register_internal_class(&subpixelorder_ce TSRMLS_CC);
	cairo_ce_cairosubpixelorder->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS | ZEND_ACC_FINAL_CLASS;

	#define REGISTER_CAIRO_SUBPIXELORDER_LONG_CONST(const_name, value) \
		zend_declare_class_constant_long(cairo_ce_cairosubpixelorder, const_name, sizeof(const_name)-1, (long)value TSRMLS_CC); \
		REGISTER_LONG_CONSTANT(#value,  value,  CONST_CS | CONST_PERSISTENT);

	REGISTER_CAIRO_SUBPIXELORDER_LONG_CONST("ORDER_DEFAULT", CAIRO_SUBPIXEL_ORDER_DEFAULT);
	REGISTER_CAIRO_SUBPIXELORDER_LONG_CONST("ORDER_RGB", CAIRO_SUBPIXEL_ORDER_RGB);
	REGISTER_CAIRO_SUBPIXELORDER_LONG_CONST("ORDER_BGR", CAIRO_SUBPIXEL_ORDER_BGR);
	REGISTER_CAIRO_SUBPIXELORDER_LONG_CONST("ORDER_VRGB", CAIRO_SUBPIXEL_ORDER_VRGB);
	REGISTER_CAIRO_SUBPIXELORDER_LONG_CONST("ORDER_VBGR", CAIRO_SUBPIXEL_ORDER_VBGR);

	INIT_CLASS_ENTRY(fillrule_ce, "CairoFillRule", NULL);
	cairo_ce_cairofillrule = zend_register_internal_class(&fillrule_ce TSRMLS_CC);
	cairo_ce_cairofillrule->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS | ZEND_ACC_FINAL_CLASS;

	#define REGISTER_CAIRO_FILLRULE_LONG_CONST(const_name, value) \
		zend_declare_class_constant_long(cairo_ce_cairofillrule, const_name, sizeof(const_name)-1, (long)value TSRMLS_CC); \
		REGISTER_LONG_CONSTANT(#value,  value,  CONST_CS | CONST_PERSISTENT);

	REGISTER_CAIRO_FILLRULE_LONG_CONST("WINDING", CAIRO_FILL_RULE_WINDING);
	REGISTER_CAIRO_FILLRULE_LONG_CONST("EVEN_ODD", CAIRO_FILL_RULE_EVEN_ODD);

	INIT_CLASS_ENTRY(linecap_ce, "CairoLineCap", NULL);
	cairo_ce_cairolinecap = zend_register_internal_class(&linecap_ce TSRMLS_CC);
	cairo_ce_cairolinecap->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS | ZEND_ACC_FINAL_CLASS;

	#define REGISTER_CAIRO_LINECAP_LONG_CONST(const_name, value) \
		zend_declare_class_constant_long(cairo_ce_cairolinecap, const_name, sizeof(const_name)-1, (long)value TSRMLS_CC); \
		REGISTER_LONG_CONSTANT(#value,  value,  CONST_CS | CONST_PERSISTENT);

	REGISTER_CAIRO_LINECAP_LONG_CONST("BUTT", CAIRO_LINE_CAP_BUTT);
	REGISTER_CAIRO_LINECAP_LONG_CONST("ROUND", CAIRO_LINE_CAP_ROUND);
	REGISTER_CAIRO_LINECAP_LONG_CONST("SQUARE", CAIRO_LINE_CAP_SQUARE);

	INIT_CLASS_ENTRY(linejoin_ce, "CairoLineJoin", NULL);
	cairo_ce_cairolinejoin = zend_register_internal_class(&linejoin_ce TSRMLS_CC);
	cairo_ce_cairolinejoin->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS | ZEND_ACC_FINAL_CLASS;

	#define REGISTER_CAIRO_LINEJOIN_LONG_CONST(const_name, value) \
		zend_declare_class_constant_long(cairo_ce_cairolinejoin, const_name, sizeof(const_name)-1, (long)value TSRMLS_CC); \
		REGISTER_LONG_CONSTANT(#value,  value,  CONST_CS | CONST_PERSISTENT);

	REGISTER_CAIRO_LINEJOIN_LONG_CONST("MITER", CAIRO_LINE_JOIN_MITER);
	REGISTER_CAIRO_LINEJOIN_LONG_CONST("ROUND", CAIRO_LINE_JOIN_ROUND);
	REGISTER_CAIRO_LINEJOIN_LONG_CONST("BEVEL", CAIRO_LINE_JOIN_BEVEL);

	INIT_CLASS_ENTRY(operator_ce, "CairoOperator", NULL);
	cairo_ce_cairooperator = zend_register_internal_class(&operator_ce TSRMLS_CC);
	cairo_ce_cairooperator->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS | ZEND_ACC_FINAL_CLASS;

	#define REGISTER_CAIRO_OPERATOR_LONG_CONST(const_name, value) \
		zend_declare_class_constant_long(cairo_ce_cairooperator, const_name, sizeof(const_name)-1, (long)value TSRMLS_CC); \
		REGISTER_LONG_CONSTANT(#value,  value,  CONST_CS | CONST_PERSISTENT);

	REGISTER_CAIRO_OPERATOR_LONG_CONST("CLEAR", CAIRO_OPERATOR_CLEAR);
	REGISTER_CAIRO_OPERATOR_LONG_CONST("SOURCE", CAIRO_OPERATOR_SOURCE);
	REGISTER_CAIRO_OPERATOR_LONG_CONST("OVER", CAIRO_OPERATOR_OVER);
	REGISTER_CAIRO_OPERATOR_LONG_CONST("IN", CAIRO_OPERATOR_IN);
	REGISTER_CAIRO_OPERATOR_LONG_CONST("OUT", CAIRO_OPERATOR_OUT);
	REGISTER_CAIRO_OPERATOR_LONG_CONST("ATOP", CAIRO_OPERATOR_ATOP);
	REGISTER_CAIRO_OPERATOR_LONG_CONST("DEST", CAIRO_OPERATOR_DEST);
	REGISTER_CAIRO_OPERATOR_LONG_CONST("DEST_OVER", CAIRO_OPERATOR_DEST_OVER);
	REGISTER_CAIRO_OPERATOR_LONG_CONST("DEST_IN", CAIRO_OPERATOR_DEST_IN);
	REGISTER_CAIRO_OPERATOR_LONG_CONST("DEST_OUT", CAIRO_OPERATOR_DEST_OUT);
	REGISTER_CAIRO_OPERATOR_LONG_CONST("DEST_ATOP", CAIRO_OPERATOR_DEST_ATOP);
	REGISTER_CAIRO_OPERATOR_LONG_CONST("XOR", CAIRO_OPERATOR_XOR);
	REGISTER_CAIRO_OPERATOR_LONG_CONST("ADD", CAIRO_OPERATOR_ADD);
	REGISTER_CAIRO_OPERATOR_LONG_CONST("SATURATE", CAIRO_OPERATOR_SATURATE);

#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 10, 0)
	REGISTER_CAIRO_OPERATOR_LONG_CONST("MULTIPLY", CAIRO_OPERATOR_MULTIPLY);
	REGISTER_CAIRO_OPERATOR_LONG_CONST("SCREEN", CAIRO_OPERATOR_SCREEN);
	REGISTER_CAIRO_OPERATOR_LONG_CONST("OVERLAY", CAIRO_OPERATOR_OVERLAY);
	REGISTER_CAIRO_OPERATOR_LONG_CONST("DARKEN", CAIRO_OPERATOR_DARKEN);
	REGISTER_CAIRO_OPERATOR_LONG_CONST("LIGHTEN", CAIRO_OPERATOR_LIGHTEN);
	REGISTER_CAIRO_OPERATOR_LONG_CONST("COLOR_DODGE", CAIRO_OPERATOR_COLOR_DODGE);
	REGISTER_CAIRO_OPERATOR_LONG_CONST("COLOR_BURN", CAIRO_OPERATOR_COLOR_BURN);
	REGISTER_CAIRO_OPERATOR_LONG_CONST("HARD_LIGHT", CAIRO_OPERATOR_HARD_LIGHT);
	REGISTER_CAIRO_OPERATOR_LONG_CONST("SOFT_LIGHT", CAIRO_OPERATOR_SOFT_LIGHT);
	REGISTER_CAIRO_OPERATOR_LONG_CONST("DIFFERENCE", CAIRO_OPERATOR_DIFFERENCE);
	REGISTER_CAIRO_OPERATOR_LONG_CONST("EXCLUSION", CAIRO_OPERATOR_EXCLUSION);
	REGISTER_CAIRO_OPERATOR_LONG_CONST("HSL_HUE", CAIRO_OPERATOR_HSL_HUE);
	REGISTER_CAIRO_OPERATOR_LONG_CONST("HSL_SATURATION", CAIRO_OPERATOR_HSL_SATURATION);
	REGISTER_CAIRO_OPERATOR_LONG_CONST("HSL_COLOR", CAIRO_OPERATOR_HSL_COLOR);
	REGISTER_CAIRO_OPERATOR_LONG_CONST("HSL_LUMINOSITY", CAIRO_OPERATOR_HSL_LUMINOSITY);
#endif

	return SUCCESS;
}
/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
