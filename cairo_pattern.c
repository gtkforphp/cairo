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
#include "zend_exceptions.h"
#include "php_cairo.h"

zend_class_entry *cairo_ce_cairopattern;
zend_class_entry *cairo_ce_cairogradientpattern;
zend_class_entry *cairo_ce_cairosolidpattern;
zend_class_entry *cairo_ce_cairosurfacepattern;
zend_class_entry *cairo_ce_cairomeshpattern;
zend_class_entry *cairo_ce_cairolineargradient;
zend_class_entry *cairo_ce_cairoradialgradient;
zend_class_entry *cairo_ce_cairopatterntype;
zend_class_entry *cairo_ce_cairoextend;
zend_class_entry *cairo_ce_cairofilter;

ZEND_BEGIN_ARG_INFO_EX(CairoSolidPattern___construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 3)
	ZEND_ARG_INFO(0, red)
	ZEND_ARG_INFO(0, green)
	ZEND_ARG_INFO(0, blue)
	ZEND_ARG_INFO(0, alpha)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoSurfacePattern___construct_args, ZEND_SEND_BY_VAL)
	/* ZEND_ARG_OBJ_INFO(0, surface, CairoSurface, 0) - argh, catchable fatal error syndrome */
	ZEND_ARG_INFO(0, surface)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoSurfacePattern_setExtend_args, ZEND_SEND_BY_VAL)
  ZEND_ARG_INFO(0, extend)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoSurfacePattern_setFilter_args, ZEND_SEND_BY_VAL)
  ZEND_ARG_INFO(0, filter)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoGradient_addColorStopRgb_args, ZEND_SEND_BY_VAL)
  ZEND_ARG_INFO(0, offset)
  ZEND_ARG_INFO(0, red)
  ZEND_ARG_INFO(0, green)
  ZEND_ARG_INFO(0, blue)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoGradient_addColorStopRgba_args, ZEND_SEND_BY_VAL)
  ZEND_ARG_INFO(0, offset)
  ZEND_ARG_INFO(0, red)
  ZEND_ARG_INFO(0, green)
  ZEND_ARG_INFO(0, blue)
  ZEND_ARG_INFO(0, alpha)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoGradient_getColorStopRgba_args, ZEND_SEND_BY_VAL)
  ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoLinearGradient___construct_args, ZEND_SEND_BY_VAL)
  ZEND_ARG_INFO(0, x0)
  ZEND_ARG_INFO(0, y0)
  ZEND_ARG_INFO(0, x1)
  ZEND_ARG_INFO(0, y1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoRadialGradient___construct_args, ZEND_SEND_BY_VAL)
  ZEND_ARG_INFO(0, x0)
  ZEND_ARG_INFO(0, y0)
  ZEND_ARG_INFO(0, r0)
  ZEND_ARG_INFO(0, x1)
  ZEND_ARG_INFO(0, y1)
  ZEND_ARG_INFO(0, r1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoPattern_setMatrix_args, ZEND_SEND_BY_VAL)
	/* more stupidity of not being able to override E_RECOVERABLE_ERROR to Exception fixing
	ZEND_ARG_OBJ_INFO(0, matrix, CairoMatrix, 0) */
	ZEND_ARG_INFO(0, matrix)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoMeshPattern_translate_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoMeshPattern_curveTo_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, x1)
	ZEND_ARG_INFO(0, y1)
	ZEND_ARG_INFO(0, x2)
	ZEND_ARG_INFO(0, y2)
	ZEND_ARG_INFO(0, x3)
	ZEND_ARG_INFO(0, y3)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoMeshPattern_setControlPoint_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, point)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoMeshPattern_setCornerColorRGB_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, point)
	ZEND_ARG_INFO(0, r)
	ZEND_ARG_INFO(0, g)
	ZEND_ARG_INFO(0, b)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoMeshPattern_setCornerColorRGBA_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, point)
	ZEND_ARG_INFO(0, r)
	ZEND_ARG_INFO(0, g)
	ZEND_ARG_INFO(0, b)
	ZEND_ARG_INFO(0, a)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoMeshPattern_getPath_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, patch)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoMeshPattern_getControlPoint_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, patch)
	ZEND_ARG_INFO(0, point)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoMeshPattern_getCornerColorRgba_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, patch)
	ZEND_ARG_INFO(0, corner)
ZEND_END_ARG_INFO()

/* {{{ proto void contruct()
   CairoPattern CANNOT be extended in userspace, this will throw an exception on use */
PHP_METHOD(CairoPattern, __construct)
{
	zend_throw_exception(cairo_ce_cairoexception, "CairoPattern cannot be constructed", 0 TSRMLS_CC);
}
/* }}} */

/* {{{ proto void cairo_pattern_get_type(CairoPattern object)
   proto void CairoPattern->getType()
   This function returns the type a pattern */
PHP_FUNCTION(cairo_pattern_get_type)
{
	zval *pattern_zval = NULL;
	cairo_pattern_object *pattern_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &pattern_zval, cairo_ce_cairopattern) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	pattern_object = (cairo_pattern_object *)cairo_pattern_object_get(pattern_zval TSRMLS_CC);
	PHP_CAIRO_ERROR(cairo_pattern_status(pattern_object->pattern));
	RETURN_LONG(cairo_pattern_get_type(pattern_object->pattern));
}

/* }}} */

/* {{{ proto long cairo_pattern_status(CairoPattern object)
   proto long CairoPattern->status()
   Returns the current integer status of the CairoPattern */
PHP_FUNCTION(cairo_pattern_status)
{
	zval *pattern_zval = NULL;
	cairo_pattern_object *pattern_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &pattern_zval, cairo_ce_cairopattern) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	pattern_object = (cairo_pattern_object *) cairo_pattern_object_get(pattern_zval TSRMLS_CC);
	RETURN_LONG(cairo_pattern_status(pattern_object->pattern));
}
/* }}} */

/* {{{ proto long cairo_pattern_get_matrix(CairoPattern object)
   proto long CairoPattern->getMatrix()
   Returns the pattern's transformation matrix */
PHP_FUNCTION(cairo_pattern_get_matrix)
{
	zval *pattern_zval = NULL;
	cairo_pattern_object *pattern_object;
	cairo_matrix_object *matrix_object;
	cairo_matrix_t matrix;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &pattern_zval, cairo_ce_cairopattern) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	pattern_object = (cairo_pattern_object *) cairo_pattern_object_get(pattern_zval TSRMLS_CC);

	/* If we have a matrix object stored, grab that zval to use */
	if(pattern_object->matrix) {
		zval_dtor(return_value);
		*return_value = *pattern_object->matrix;
		zval_copy_ctor(return_value);
		Z_SET_REFCOUNT_P(return_value, 1);
	/* Otherwise we spawn a new object */
	} else {
		object_init_ex(return_value, cairo_ce_cairomatrix);
	}

	cairo_pattern_get_matrix(pattern_object->pattern, &matrix);
	matrix_object = (cairo_matrix_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	matrix_object->matrix = &matrix;
	matrix_object->matrix = emalloc(sizeof(cairo_matrix_t));
	PHP_CAIRO_ERROR(cairo_pattern_status(pattern_object->pattern));
}
/* }}} */

/* {{{ proto void cairo_pattern_set_matrix(CairoPattern object, CairoMatrix object)
   proto void CairoPattern->setMatrix(CairoMatrix object)
   Sets the pattern's transformation matrix using the created matrix object.
   This matrix is a transformation from user space to pattern space. */
PHP_FUNCTION(cairo_pattern_set_matrix)
{
	zval *pattern_zval = NULL, *matrix_zval = NULL;
	cairo_pattern_object *pattern_object;
	cairo_matrix_object *matrix_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "OO", &pattern_zval, cairo_ce_cairopattern, &matrix_zval, cairo_ce_cairomatrix) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	pattern_object = (cairo_pattern_object *)cairo_pattern_object_get(pattern_zval TSRMLS_CC);
	matrix_object = (cairo_matrix_object *)zend_object_store_get_object(matrix_zval TSRMLS_CC);
	cairo_pattern_set_matrix(pattern_object->pattern, matrix_object->matrix);
	PHP_CAIRO_ERROR(cairo_pattern_status(pattern_object->pattern));

	/* If there's already a matrix, then we deref and remove it */
	if(pattern_object->matrix) {
		Z_DELREF_P(pattern_object->matrix);
		pattern_object->matrix = NULL;
	}

	/* we need to be able to get this zval out later, so ref and store */
	pattern_object->matrix = matrix_zval;
	Z_ADDREF_P(matrix_zval);
}
/* }}} */

/* {{{ cairo_pattern_methods[] */
const zend_function_entry cairo_pattern_methods[] = {
	PHP_ME(CairoPattern, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME_MAPPING(getType, cairo_pattern_get_type, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(status, cairo_pattern_status, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(getMatrix, cairo_pattern_get_matrix, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(setMatrix, cairo_pattern_set_matrix, CairoPattern_setMatrix_args, ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};
/* }}} */

/* {{{ proto void cairo_pattern_add_color_stop_rgb(CairoPattern object, float offset, float red, float green, float blue)
   proto void CairoGradientPattern->addColorStopRgb(float offset, float red, float green, float blue)
   Adds an opaque color stop to a gradient pattern. The offset specifies the location along the gradient's control vector. */
PHP_FUNCTION(cairo_pattern_add_color_stop_rgb)
{
	double offset = 0.0, red = 0.0, green = 0.0, blue = 0.0;
	zval *pattern_zval = NULL;
	cairo_pattern_object *pattern_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odddd", &pattern_zval, cairo_ce_cairogradientpattern, &offset, &red, &green, &blue) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	pattern_object = (cairo_pattern_object *) cairo_pattern_object_get(pattern_zval TSRMLS_CC);
	cairo_pattern_add_color_stop_rgb(pattern_object->pattern, offset, red, green, blue);
	PHP_CAIRO_ERROR(cairo_pattern_status(pattern_object->pattern));
}
/* }}} */

/* {{{ proto void cairo_pattern_add_color_stop_rgba(CairoPattern object, float offset, float red, float green, float blue, float alpha)
   proto void CairoGradientPattern->addColorStopRgba(float offset, float red, float green, float blue, float alpha)
   Adds a transparent color stop to a gradient pattern. The offset specifies the location along the gradient's control vector. */
PHP_FUNCTION(cairo_pattern_add_color_stop_rgba)
{
	double offset = 0.0, red = 0.0, green = 0.0, blue = 0.0, alpha = 1.0;
	zval *pattern_zval = NULL;
	cairo_pattern_object *pattern_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Oddddd", &pattern_zval, cairo_ce_cairogradientpattern, &offset, &red, &green, &blue, &alpha) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	pattern_object = (cairo_pattern_object *) cairo_pattern_object_get(pattern_zval TSRMLS_CC);
	cairo_pattern_add_color_stop_rgba(pattern_object->pattern, offset, red, green, blue, alpha);
	PHP_CAIRO_ERROR(cairo_pattern_status(pattern_object->pattern));
}
/* }}} */

#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 4, 0)
/* {{{ proto array cairo_pattern_get_color_stop_rgba(CairoPattern object)
   proto array CairoGradientPattern->getColorStopRgba()
   Gets the color and offset information at the given index for a gradient pattern */
PHP_FUNCTION(cairo_pattern_get_color_stop_rgba)
{
	long index;
	double offset, red, green, blue, alpha;
	zval *pattern_zval = NULL;
	cairo_pattern_object *pattern_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ol", &pattern_zval, cairo_ce_cairogradientpattern, &index) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	pattern_object = (cairo_pattern_object *) cairo_pattern_object_get(pattern_zval TSRMLS_CC);
	cairo_pattern_get_color_stop_rgba(pattern_object->pattern, index, &offset, &red, &green, &blue, &alpha);
	PHP_CAIRO_ERROR(cairo_pattern_status(pattern_object->pattern));

	array_init(return_value);
	add_assoc_double(return_value, "red", red);
	add_assoc_double(return_value, "green", green);
	add_assoc_double(return_value, "blue", blue);
	add_assoc_double(return_value, "alpha", alpha);
}
/* }}} */

/* {{{ proto array cairo_pattern_get_color_stop_count(CairoPattern object)
   proto array CairoGradientPattern->getColorStopCount()
   Gets the number of color stops specified in the given gradient pattern */
PHP_FUNCTION(cairo_pattern_get_color_stop_count)
{
	int count;
	zval *pattern_zval = NULL;
	cairo_pattern_object *pattern_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &pattern_zval, cairo_ce_cairogradientpattern) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	pattern_object = (cairo_pattern_object *) cairo_pattern_object_get(pattern_zval TSRMLS_CC);
	PHP_CAIRO_ERROR(cairo_pattern_status(pattern_object->pattern));
	cairo_pattern_get_color_stop_count(pattern_object->pattern, &count);

	RETURN_LONG(count);
}
/* }}} */
#endif

/* {{{ proto int CairoGradientPattern->getExtend()
       Gets the current extend mode for a pattern */
PHP_METHOD(CairoGradientPattern, getExtend)
{
	zval *pattern_zval = NULL;
	cairo_pattern_object *pattern_object;

	PHP_CAIRO_ERROR_HANDLING(TRUE)
	if (zend_parse_parameters_none() == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(TRUE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(TRUE)

	pattern_object = (cairo_pattern_object *)cairo_pattern_object_get(getThis() TSRMLS_CC);
	PHP_CAIRO_ERROR(cairo_pattern_status(pattern_object->pattern));
	RETURN_LONG(cairo_pattern_get_extend(pattern_object->pattern));
}
/* }}} */

/* {{{ proto void CairoGradientPattern::setExtend(int extend)
       Sets the mode to be used for drawing outside the area of a pattern */
PHP_METHOD(CairoGradientPattern, setExtend)
{
	cairo_pattern_object *pattern_object;
	long extend = 0;

	PHP_CAIRO_ERROR_HANDLING(TRUE)
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &extend) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(TRUE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(TRUE)

	pattern_object = (cairo_pattern_object *)cairo_pattern_object_get(getThis() TSRMLS_CC);
	cairo_pattern_set_extend(pattern_object->pattern, extend);
	PHP_CAIRO_ERROR(cairo_pattern_status(pattern_object->pattern));
}

/* }}} */

/* {{{ cairo_gradientpattern_methods[] */
const zend_function_entry cairo_gradientpattern_methods[] = {
	PHP_ME_MAPPING(addColorStopRgb, cairo_pattern_add_color_stop_rgb, CairoGradient_addColorStopRgb_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(addColorStopRgba, cairo_pattern_add_color_stop_rgba, CairoGradient_addColorStopRgba_args, ZEND_ACC_PUBLIC)
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 4, 0)
	PHP_ME_MAPPING(getColorStopRgba, cairo_pattern_get_color_stop_rgba, CairoGradient_getColorStopRgba_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(getColorStopCount, cairo_pattern_get_color_stop_count, NULL, ZEND_ACC_PUBLIC)
#endif
	PHP_ME(CairoGradientPattern, getExtend, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CairoGradientPattern, setExtend, CairoSurfacePattern_setExtend_args, ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};
/* }}} */

/* {{{ proto CairoSolidPattern cairo_pattern_create_rgb(float red, float green, float blue)
   Returns new CairoSolidPattern object with the color designated */
PHP_FUNCTION(cairo_pattern_create_rgb)
{
	double red = 0.0, green = 0.0, blue = 0.0;
	cairo_pattern_object *pattern_object;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ddd", &red, &green, &blue) == FAILURE) {
		return;
	}

	object_init_ex(return_value, cairo_ce_cairosolidpattern);
	pattern_object = (cairo_pattern_object *)zend_object_store_get_object(return_value TSRMLS_CC);

	pattern_object->pattern = cairo_pattern_create_rgb(red, green, blue);
	php_cairo_trigger_error(cairo_pattern_status(pattern_object->pattern) TSRMLS_CC);
}
/* }}} */

/* {{{ proto CairoSolidPattern cairo_pattern_create_rgba(float red, float green, float blue, float alpha)
   Returns new CairoSolidPattern object with the color designated */
PHP_FUNCTION(cairo_pattern_create_rgba)
{
	double red = 0.0, green = 0.0, blue = 0.0, alpha = 1.0;
	cairo_pattern_object *pattern_object;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dddd", &red, &green, &blue, &alpha) == FAILURE) {
		return;
	}

	object_init_ex(return_value, cairo_ce_cairosolidpattern);
	pattern_object = (cairo_pattern_object *)zend_object_store_get_object(return_value TSRMLS_CC);

	pattern_object->pattern = cairo_pattern_create_rgba(red, green, blue, alpha);
	php_cairo_trigger_error(cairo_pattern_status(pattern_object->pattern) TSRMLS_CC);
}
/* }}} */

/* {{{ proto void contruct(float red, float green, float blue[, float alpha])
	Returns new CairoSolidPattern using rgb and optionally alpha
	This is the same as cairo_pattern_create_rgba and cairo_pattern_create_rgb */
PHP_METHOD(CairoSolidPattern, __construct)
{
	double red = 0.0, green = 0.0, blue = 0.0, alpha = 0;
	cairo_pattern_object *pattern_object;

	PHP_CAIRO_ERROR_HANDLING(TRUE)
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ddd|d", &red, &green, &blue, &alpha) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(TRUE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(TRUE)

	pattern_object = (cairo_pattern_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
	if(!alpha) {
		pattern_object->pattern = cairo_pattern_create_rgb(red, green, blue);
	} else {
		pattern_object->pattern = cairo_pattern_create_rgba(red, green, blue, alpha);
	}
	php_cairo_throw_exception(cairo_pattern_status(pattern_object->pattern) TSRMLS_CC);
}
/* }}} */

#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 4, 0)
/* {{{ proto array cairo_pattern_get_rgba(CairoSolidPattern object)
   proto array CairoSolidPattern->getRgba()
   This function returns an array with four elements, the float values of red, green, blue, and alpha from the solid pattern */
PHP_FUNCTION(cairo_pattern_get_rgba)
{
	zval *pattern_zval = NULL;
	cairo_pattern_object *pattern_object;
	double red, green, blue, alpha;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &pattern_zval, cairo_ce_cairosolidpattern) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	pattern_object = (cairo_pattern_object *)cairo_pattern_object_get(pattern_zval TSRMLS_CC);
	cairo_pattern_get_rgba(pattern_object->pattern, &red, &green, &blue, &alpha);
	PHP_CAIRO_ERROR(cairo_pattern_status(pattern_object->pattern));

	array_init(return_value);
	add_assoc_double(return_value, "red", red);
	add_assoc_double(return_value, "green", green);
	add_assoc_double(return_value, "blue", blue);
	add_assoc_double(return_value, "alpha", alpha);
}
/* }}} */
#endif

/* {{{ cairo_solidpattern_methods[] */
const zend_function_entry cairo_solidpattern_methods[] = {
	PHP_ME(CairoSolidPattern, __construct, CairoSolidPattern___construct_args, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 4, 0)
	PHP_ME_MAPPING(getRgba, cairo_pattern_get_rgba, NULL, ZEND_ACC_PUBLIC)
#endif
	{NULL, NULL, NULL}
};
/* }}} */

/* {{{ proto CairoSurfacePattern cairo_pattern_create_for_surface(CairoSurface object)
   Returns new CairoSurfacePattern object with the surface designated */
PHP_FUNCTION(cairo_pattern_create_for_surface)
{
	zval * surface_zval = NULL;
	cairo_pattern_object *pattern_object;
	cairo_surface_object *surface_object;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &surface_zval, cairo_ce_cairosurface) == FAILURE) {
		return;
	}

	object_init_ex(return_value, cairo_ce_cairosurfacepattern);
	pattern_object = (cairo_pattern_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	surface_object = (cairo_surface_object *)cairo_surface_object_get(surface_zval TSRMLS_CC);

	pattern_object->pattern = cairo_pattern_create_for_surface(surface_object->surface);
	php_cairo_trigger_error(cairo_pattern_status(pattern_object->pattern) TSRMLS_CC);

	/* we need to be able to get this zval out later, so ref and store */
	pattern_object->surface = surface_zval;
	Z_ADDREF_P(surface_zval);
}
/* }}} */

/* {{{ proto void contruct(float red, float green, float blue[, float alpha])
	Returns new CairoSurfacePattern using supplied surface
	this is the same as cairo_pattern_create_for_surface */
PHP_METHOD(CairoSurfacePattern, __construct)
{
	zval * surface_zval = NULL;
	cairo_pattern_object *pattern_object;
	cairo_surface_object *surface_object;

	PHP_CAIRO_ERROR_HANDLING(TRUE)
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O",  &surface_zval, cairo_ce_cairosurface) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(TRUE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(TRUE)

	pattern_object = (cairo_pattern_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
	surface_object = (cairo_surface_object *)cairo_surface_object_get(surface_zval TSRMLS_CC);
	pattern_object->pattern = cairo_pattern_create_for_surface(surface_object->surface);
	php_cairo_throw_exception(cairo_pattern_status(pattern_object->pattern) TSRMLS_CC);

	/* we need to be able to get this zval out later, so ref and store */
	pattern_object->surface = surface_zval;
	Z_ADDREF_P(surface_zval);
}
/* }}} */

#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 4, 0)
/* {{{ proto CairoSurface object cairo_pattern_get_surface(CairoSurfacePattern object)
   proto CairoSurface object CairoSurfacePattern->getSurface()
   This function returns the surface object */
PHP_FUNCTION(cairo_pattern_get_surface)
{
	zend_class_entry *surface_ce;
	cairo_surface_t *surface;
	zval *pattern_zval = NULL;
	cairo_pattern_object *pattern_object;
	cairo_surface_object *surface_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &pattern_zval, cairo_ce_cairosurfacepattern) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	pattern_object = (cairo_pattern_object *)cairo_pattern_object_get(pattern_zval TSRMLS_CC);
	PHP_CAIRO_ERROR(cairo_pattern_get_surface(pattern_object->pattern, &surface));

	/* If we have a surface object stored, grab that zval to use */
	if(pattern_object->surface) {
		zval_dtor(return_value);
		*return_value = *pattern_object->surface;
		zval_copy_ctor(return_value);
		Z_SET_REFCOUNT_P(return_value, 1);
	/* Otherwise we spawn a new object */
	} else {
		surface_ce = php_cairo_get_surface_ce(surface TSRMLS_CC);
		object_init_ex(return_value, surface_ce);
		surface = cairo_surface_reference(surface);
	}

	surface_object = (cairo_surface_object *)zend_object_store_get_object(return_value TSRMLS_CC);
}
/* }}} */
#endif

/* {{{ proto int cairo_pattern_get_filter(CairoSurfacePattern object)
   proto int CairoPattern->getFilter()
   Gets the current filter for a pattern */
PHP_FUNCTION(cairo_pattern_get_filter)
{
	zval *pattern_zval = NULL;
	cairo_pattern_object *pattern_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &pattern_zval, cairo_ce_cairosurfacepattern) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	pattern_object = (cairo_pattern_object *)cairo_pattern_object_get(pattern_zval TSRMLS_CC);
	PHP_CAIRO_ERROR(cairo_pattern_status(pattern_object->pattern));
	RETURN_LONG(cairo_pattern_get_filter(pattern_object->pattern));
}
/* }}} */

/* {{{ proto void cairo_pattern_set_filter(CairoSurfacePattern object, int filter)
   proto void CairoPattern->setFilter(int filter)
   Sets the filter to be used for resizing when using this pattern */
PHP_FUNCTION(cairo_pattern_set_filter)
{
	zval *pattern_zval = NULL;
	cairo_pattern_object *pattern_object;
	long filter = 0;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ol", &pattern_zval, cairo_ce_cairosurfacepattern, &filter) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	pattern_object = (cairo_pattern_object *)cairo_pattern_object_get(pattern_zval TSRMLS_CC);
	cairo_pattern_set_filter(pattern_object->pattern, filter);
	PHP_CAIRO_ERROR(cairo_pattern_status(pattern_object->pattern));
}
/* }}} */

/* {{{ proto int CairoSurfacePattern->getExtend()
   Gets the current extend mode for a pattern */
PHP_METHOD(CairoSurfacePattern, getExtend)
{
	cairo_pattern_object *pattern_object;

	PHP_CAIRO_ERROR_HANDLING(TRUE)
	if (zend_parse_parameters_none() == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(TRUE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(TRUE)

	pattern_object = (cairo_pattern_object *)cairo_pattern_object_get(getThis() TSRMLS_CC);
	PHP_CAIRO_ERROR(cairo_pattern_status(pattern_object->pattern));
	RETURN_LONG(cairo_pattern_get_extend(pattern_object->pattern));
}
/* }}} */

/* {{{ proto int cairo_pattern_get_extend(CairoSurfacePattern|CairoGradientPattern object)
   Gets the current extend mode for a pattern */
PHP_FUNCTION(cairo_pattern_get_extend)
{
	zval *pattern_zval = NULL;
	cairo_pattern_object *pattern_object;

	/* we want a gradient pattern OR a surface pattern */
	if (zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, ZEND_NUM_ARGS() TSRMLS_CC, "O", &pattern_zval, cairo_ce_cairogradientpattern) == FAILURE) {
		if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &pattern_zval, cairo_ce_cairosurfacepattern) == FAILURE) {
			return;
		}
	}

	pattern_object = (cairo_pattern_object *)cairo_pattern_object_get(pattern_zval TSRMLS_CC);
	PHP_CAIRO_ERROR(cairo_pattern_status(pattern_object->pattern));
	RETURN_LONG(cairo_pattern_get_extend(pattern_object->pattern));
}
/* }}} */

/* {{{ proto void CairoSurfacePattern->setExtend(int extend)
       Sets the mode to be used for drawing outside the area of a pattern */
PHP_METHOD(CairoSurfacePattern, setExtend)
{
	cairo_pattern_object *pattern_object;
	long extend = 0;

	PHP_CAIRO_ERROR_HANDLING(TRUE)
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &extend) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(TRUE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(TRUE)

	pattern_object = (cairo_pattern_object *)cairo_pattern_object_get(getThis() TSRMLS_CC);
	cairo_pattern_set_extend(pattern_object->pattern, extend);
	PHP_CAIRO_ERROR(cairo_pattern_status(pattern_object->pattern));
}

/* }}} */

/* {{{ proto void cairo_pattern_set_extend(CairoSurfacePattern|CairoGradientPattern object, int extend)
       Sets the mode to be used for drawing outside the area of a pattern */
PHP_FUNCTION(cairo_pattern_set_extend)
{
	zval *pattern_zval = NULL;
	cairo_pattern_object *pattern_object;
	long extend = 0;

	/* we want a gradient pattern OR a surface pattern */
	if (zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, ZEND_NUM_ARGS() TSRMLS_CC, "Ol", &pattern_zval, cairo_ce_cairogradientpattern, &extend) == FAILURE) {
		if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "Ol", &pattern_zval, cairo_ce_cairosurfacepattern, &extend) == FAILURE) {
			return;
		}
	}

	pattern_object = (cairo_pattern_object *)cairo_pattern_object_get(pattern_zval TSRMLS_CC);
	cairo_pattern_set_extend(pattern_object->pattern, extend);
	PHP_CAIRO_ERROR(cairo_pattern_status(pattern_object->pattern));
}

/* }}} */

/* {{{ cairo_surfacepattern_methods[] */
const zend_function_entry cairo_surfacepattern_methods[] = {
	PHP_ME(CairoSurfacePattern, __construct, CairoSurfacePattern___construct_args, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
#
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 4, 0)
	PHP_ME_MAPPING(getSurface, cairo_pattern_get_surface, NULL, ZEND_ACC_PUBLIC)
#endif
	PHP_ME_MAPPING(setFilter, cairo_pattern_set_filter, CairoSurfacePattern_setFilter_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(getFilter, cairo_pattern_get_filter, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CairoSurfacePattern, setExtend, CairoSurfacePattern_setExtend_args, ZEND_ACC_PUBLIC)
	PHP_ME(CairoSurfacePattern, getExtend, NULL, ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};
/* }}} */

/* {{{ proto CairoLinearGradient cairo_pattern_create_linear(float x0, float y0, float x1, float y1)
   Create a new CairoLinearGradient along the line defined by (x0, y0) and (x1, y1).
   Before using the gradient pattern, a number of color stops should be defined.  */
PHP_FUNCTION(cairo_pattern_create_linear)
{
	cairo_pattern_object *pattern_object;
	double x0 = 0.0, y0 = 0.0, x1 = 0.0, y1 = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dddd", &x0, &y0, &x1, &y1) == FAILURE) {
		return;
	}

	object_init_ex(return_value, cairo_ce_cairolineargradient);
	pattern_object = (cairo_pattern_object *)zend_object_store_get_object(return_value TSRMLS_CC);

	pattern_object->pattern = cairo_pattern_create_linear(x0, y0, x1, y1);
	php_cairo_trigger_error(cairo_pattern_status(pattern_object->pattern) TSRMLS_CC);
}

/* {{{ proto void construct(float x0, float y0, float x1, float y1)
  Create a new CairoLinearGradient along the line defined by (x0, y0) and (x1, y1).
  Before using the gradient pattern, a number of color stops should be defined. */
PHP_METHOD(CairoLinearGradient, __construct)
{
	cairo_pattern_object *pattern_object;
	double x0 = 0.0, y0 = 0.0, x1 = 0.0, y1 = 0.0;

	PHP_CAIRO_ERROR_HANDLING(TRUE)
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dddd", &x0, &y0, &x1, &y1) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(TRUE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(TRUE)

	pattern_object = (cairo_pattern_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
	pattern_object->pattern = cairo_pattern_create_linear(x0, y0, x1, y1);
	php_cairo_throw_exception(cairo_pattern_status(pattern_object->pattern) TSRMLS_CC);
}
/* }}} */

#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 4, 0)
/* {{{ proto void cairo_pattern_get_linear_points(CairoLinearGradient object)
   proto void CairoLinearGradient->getPoints()
   Gets the gradient endpoints for a linear gradient. */
PHP_FUNCTION(cairo_pattern_get_linear_points)
{
	zval *pattern_zval = NULL;
	cairo_pattern_object *pattern_object;
	double x0, y0, x1, y1;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &pattern_zval, cairo_ce_cairolineargradient) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	pattern_object = (cairo_pattern_object *)cairo_pattern_object_get(pattern_zval TSRMLS_CC);
	cairo_pattern_get_linear_points(pattern_object->pattern, &x0, &y0, &x1, &y1);
	PHP_CAIRO_ERROR(cairo_pattern_status(pattern_object->pattern));

	array_init(return_value);
	add_assoc_double(return_value, "x0", x0);
	add_assoc_double(return_value, "y0", y0);
	add_assoc_double(return_value, "x1", x1);
	add_assoc_double(return_value, "y1", y1);
}
#endif

/* }}} */

/* {{{ cairo_lineargradient_methods[] */
const zend_function_entry cairo_lineargradient_methods[] = {
	PHP_ME(CairoLinearGradient, __construct, CairoLinearGradient___construct_args, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 4, 0)
	PHP_ME_MAPPING(getPoints, cairo_pattern_get_linear_points, NULL, ZEND_ACC_PUBLIC)
#endif
	{NULL, NULL, NULL}
};
/* }}} */

/* {{{ proto CairoRadialGradient cairo_pattern_create_radial(float x0, float y0, float r0, float x1, float y1, float r1)
   Create a new CairoRadialGradient between the two circles defined.
   Before using the gradient pattern, a number of color stops should be defined.  */
PHP_FUNCTION(cairo_pattern_create_radial)
{
	cairo_pattern_object *pattern_object;
	double x0 = 0.0, y0 = 0.0, r0 = 0.0, x1 = 0.0, y1 = 0.0, r1 = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dddddd", &x0, &y0, &r0, &x1, &y1, &r1) == FAILURE) {
		return;
	}

	object_init_ex(return_value, cairo_ce_cairoradialgradient);
	pattern_object = (cairo_pattern_object *)zend_object_store_get_object(return_value TSRMLS_CC);

	pattern_object->pattern = cairo_pattern_create_radial(x0, y0, r0, x1, y1, r1);
	php_cairo_trigger_error(cairo_pattern_status(pattern_object->pattern) TSRMLS_CC);
}

/* {{{ proto void construct(float x0, float y0, float r0, float x1, float y1, float r1)
  Create a new CairoLinearGradient along the line defined by (x0, y0) and (x1, y1).
  Before using the gradient pattern, a number of color stops should be defined. */
PHP_METHOD(CairoRadialGradient, __construct)
{
	cairo_pattern_object *pattern_object;
	double x0 = 0.0, y0 = 0.0, r0 = 0.0, x1 = 0.0, y1 = 0.0, r1 = 0.0;

	PHP_CAIRO_ERROR_HANDLING(TRUE)
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dddddd", &x0, &y0, &r0, &x1, &y1, &r1) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(TRUE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(TRUE)

	pattern_object = (cairo_pattern_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
	pattern_object->pattern = cairo_pattern_create_radial(x0, y0, r0, x1, y1, r1);
	php_cairo_throw_exception(cairo_pattern_status(pattern_object->pattern) TSRMLS_CC);
}
/* }}} */

#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 4, 0)
/* {{{ proto void cairo_pattern_get_radial_circles(CairoRadialGradient object)
   proto void CairoRadialGradient->getCircles()
   Gets the gradient endpoint circles for a radial gradient, each specified as a center coordinate and a radius. */
PHP_FUNCTION(cairo_pattern_get_radial_circles)
{
	zval *pattern_zval = NULL;
	cairo_pattern_object *pattern_object;
	double x0, y0, r0, x1, y1, r1;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &pattern_zval, cairo_ce_cairoradialgradient) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	pattern_object = (cairo_pattern_object *)cairo_pattern_object_get(pattern_zval TSRMLS_CC);
	cairo_pattern_get_radial_circles(pattern_object->pattern, &x0, &y0, &r0, &x1, &y1, &r1);
	PHP_CAIRO_ERROR(cairo_pattern_status(pattern_object->pattern));

	array_init(return_value);
	add_assoc_double(return_value, "x0", x0);
	add_assoc_double(return_value, "y0", y0);
	add_assoc_double(return_value, "r0", r0);
	add_assoc_double(return_value, "x1", x1);
	add_assoc_double(return_value, "y1", y1);
	add_assoc_double(return_value, "r1", r1);
}
#endif

#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 12, 0)
/* {{{ proto CairoMeshPattern cairo_pattern_create_mesh(void)
   Create a new CairoMeshPattern */
PHP_FUNCTION(cairo_pattern_create_mesh)
{
	cairo_pattern_object *pattern_object;

	PHP_CAIRO_ERROR_HANDLING(TRUE)
	if (zend_parse_parameters_none() == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(TRUE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(TRUE)

	object_init_ex(return_value, cairo_ce_cairomeshpattern);
	pattern_object = (cairo_pattern_object *)zend_object_store_get_object(return_value TSRMLS_CC);

	pattern_object->pattern = cairo_pattern_create_mesh();
	php_cairo_trigger_error(cairo_pattern_status(pattern_object->pattern) TSRMLS_CC);
}

/* {{{ proto void construct()
   Create a new CairoMeshPattern */
PHP_METHOD(CairoMeshPattern, __construct)
{
	cairo_pattern_object *pattern_object;

	PHP_CAIRO_ERROR_HANDLING(TRUE)
	if (zend_parse_parameters_none() == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(TRUE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(TRUE)

	pattern_object = (cairo_pattern_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
	pattern_object->pattern = cairo_pattern_create_mesh();
	php_cairo_throw_exception(cairo_pattern_status(pattern_object->pattern) TSRMLS_CC);
}
/* }}} */

/* {{{ proto void cairo_mesh_pattern_begin_patch(CairoMeshPattern object)
   proto void CairoMeshPattern->beginPatch()
   Begin a patch in a mesh pattern. */
PHP_FUNCTION(cairo_mesh_pattern_begin_patch)
{
	zval *pattern_zval;
	cairo_pattern_object *pattern_object;

	PHP_CAIRO_ERROR_HANDLING(TRUE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &pattern_zval, cairo_ce_cairopattern) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(TRUE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(TRUE)

	pattern_object = (cairo_pattern_object *)zend_object_store_get_object(pattern_zval TSRMLS_CC);
	cairo_mesh_pattern_begin_patch(pattern_object->pattern);
	php_cairo_throw_exception(cairo_pattern_status(pattern_object->pattern) TSRMLS_CC);
}
/* }}} */

/* {{{ proto void cairo_mesh_pattern_end_patch(CairoMeshPattern object)
   proto void CairoMeshPattern->endPatch()
   End a patch in a mesh pattern. */
PHP_FUNCTION(cairo_mesh_pattern_end_patch)
{
	zval *pattern_zval;
	cairo_pattern_object *pattern_object;

	PHP_CAIRO_ERROR_HANDLING(TRUE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &pattern_zval, cairo_ce_cairopattern) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(TRUE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(TRUE)

	pattern_object = (cairo_pattern_object *)zend_object_store_get_object(pattern_zval TSRMLS_CC);
	cairo_mesh_pattern_end_patch(pattern_object->pattern);
	php_cairo_throw_exception(cairo_pattern_status(pattern_object->pattern) TSRMLS_CC);
}
/* }}} */

/* {{{ proto void cairo_mesh_pattern_move_to(CairoMeshPattern object, float x, float y)
   proto void CairoMeshPattern->moveTo(float x, float y)
   Begin a new sub-path. After this call the current point will be (x, y) */
PHP_FUNCTION(cairo_mesh_pattern_move_to)
{
	zval *pattern_zval = NULL;
	double x = 0.0, y = 0.0;
	cairo_pattern_object *pattern_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odd", &pattern_zval, cairo_ce_cairopattern, &x, &y) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	pattern_object = (cairo_pattern_object *)cairo_pattern_object_get(pattern_zval TSRMLS_CC);
	cairo_mesh_pattern_move_to(pattern_object->pattern, x, y);
	PHP_CAIRO_ERROR(cairo_pattern_status(pattern_object->pattern));
}
/* }}} */

/* {{{ proto void cairo_mesh_pattern_line_to(CairoMeshPattern object, float x, float y)
   proto void CairoMeshPattern->lineTo(float x, float y)
   Begin a new sub-path. After this call the current point will be (x, y) */
PHP_FUNCTION(cairo_mesh_pattern_line_to)
{
	zval *pattern_zval = NULL;
	double x = 0.0, y = 0.0;
	cairo_pattern_object *pattern_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odd", &pattern_zval, cairo_ce_cairopattern, &x, &y) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	pattern_object = (cairo_pattern_object *)cairo_pattern_object_get(pattern_zval TSRMLS_CC);
	cairo_mesh_pattern_line_to(pattern_object->pattern, x, y);
	PHP_CAIRO_ERROR(cairo_pattern_status(pattern_object->pattern));
}
/* }}} */

/* {{{ proto void cairo_mesh_pattern_curve_to(CairoMeshPattern object, float x1, float y1, float x2, float y2, float x3, float y3)
   proto void CairoMeshPattern->curveTo(float x1, float y1, float x2, float y2, float x3, float y3)
   Adds a cubic Bézier spline to the current patch */
PHP_FUNCTION(cairo_mesh_pattern_curve_to)
{
	zval *pattern_zval = NULL;
	double x1 = 0.0, y1 = 0.0, x2 = 0.0, y2 = 0.0, x3 = 0.0, y3 = 0.0;
	cairo_pattern_object *pattern_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odddddd",
				&pattern_zval, cairo_ce_cairopattern, &x1, &y1, &x2, &y2, &x3, &y3) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	pattern_object = (cairo_pattern_object *)cairo_pattern_object_get(pattern_zval TSRMLS_CC);
	cairo_mesh_pattern_curve_to(pattern_object->pattern, x1, y1, x2, y2, x3, y3);
	PHP_CAIRO_ERROR(cairo_pattern_status(pattern_object->pattern));
}
/* }}} */

/* {{{ proto void cairo_mesh_pattern_set_control_point(CairoMeshPattern object, int point, float x, float y)
   proto void CairoMeshPattern->setControlPoint(int point, float x, float y)
   Set an internal control point of the current patch. */
PHP_FUNCTION(cairo_mesh_pattern_set_control_point)
{
	zval *pattern_zval = NULL;
	double x = 0.0, y = 0.0;
	long point = 0;
	cairo_pattern_object *pattern_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Oldd",
				&pattern_zval, cairo_ce_cairopattern, &point, &x, &y) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	pattern_object = (cairo_pattern_object *)cairo_pattern_object_get(pattern_zval TSRMLS_CC);
	cairo_mesh_pattern_set_control_point(pattern_object->pattern, point, x, y);
	PHP_CAIRO_ERROR(cairo_pattern_status(pattern_object->pattern));
}
/* }}} */

/* {{{ proto void cairo_mesh_pattern_set_corner_color_rgb(CairoMeshPattern object, int point, float r, float g, float b)
   proto void CairoMeshPattern->setControlPoint(int point, float r, float g, float b)
   Sets the color of a corner of the current patch in a mesh pattern. */
PHP_FUNCTION(cairo_mesh_pattern_set_corner_color_rgb)
{
	zval *pattern_zval = NULL;
	double r = 0.0, g = 0.0, b = 0.0;
	long point = 0;
	cairo_pattern_object *pattern_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Olddd",
				&pattern_zval, cairo_ce_cairopattern, &point, &r, &g, &b) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	pattern_object = (cairo_pattern_object *)cairo_pattern_object_get(pattern_zval TSRMLS_CC);
	cairo_mesh_pattern_set_corner_color_rgb(pattern_object->pattern, point, r, g, b);
	PHP_CAIRO_ERROR(cairo_pattern_status(pattern_object->pattern));
}
/* }}} */

/* {{{ proto void cairo_mesh_pattern_set_corner_color_rgba(CairoMeshPattern object, int point, float r, float g, float b, float a)
   proto void CairoMeshPattern->setControlPoint(int point, float r, float g, float b, float a)
   Sets the color of a corner of the current patch in a mesh pattern. */
PHP_FUNCTION(cairo_mesh_pattern_set_corner_color_rgba)
{
	zval *pattern_zval = NULL;
	double r = 0.0, g = 0.0, b = 0.0, a = 0.0;
	long point = 0;
	cairo_pattern_object *pattern_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Oldddd",
				&pattern_zval, cairo_ce_cairopattern, &point, &r, &g, &b, &a) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	pattern_object = (cairo_pattern_object *)cairo_pattern_object_get(pattern_zval TSRMLS_CC);
	cairo_mesh_pattern_set_corner_color_rgba(pattern_object->pattern, point, r, g, b, a);
	PHP_CAIRO_ERROR(cairo_pattern_status(pattern_object->pattern));
}
/* }}} */

/* {{{ proto void cairo_mesh_pattern_get_patch_count(CairoMeshPattern object)
   proto void CairoMeshPattern->getPatchCount()
   Gets the number of patches specified in the given mesh pattern. */
PHP_FUNCTION(cairo_mesh_pattern_get_patch_count)
{
	zval *pattern_zval = NULL;
	cairo_pattern_object *pattern_object;
	cairo_status_t status;
	unsigned int count;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &pattern_zval, cairo_ce_cairopattern) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	pattern_object = (cairo_pattern_object *)cairo_pattern_object_get(pattern_zval TSRMLS_CC);
	status = cairo_mesh_pattern_get_patch_count(pattern_object->pattern, &count);
	PHP_CAIRO_ERROR(status);

	RETURN_LONG(count);
}
/* }}} */

/* {{{ proto void cairo_mesh_pattern_get_path(CairoMeshPattern object, int patch_num)
   proto void CairoMeshPattern->getPath(int patchNum)
   Gets path defining the patch patch_num for a mesh pattern. */
PHP_FUNCTION(cairo_mesh_pattern_get_path)
{
	zval *pattern_zval = NULL;
	cairo_pattern_object *pattern_object;
	cairo_path_object *path_object;
	long patch_num;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ol", &pattern_zval, cairo_ce_cairopattern, &patch_num) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	pattern_object = (cairo_pattern_object *)cairo_pattern_object_get(pattern_zval TSRMLS_CC);
	object_init_ex(return_value, php_cairo_get_path_ce());
	path_object = (cairo_path_object *) zend_object_store_get_object(return_value TSRMLS_CC);
	path_object->path = cairo_mesh_pattern_get_path(pattern_object->pattern, patch_num);
	PHP_CAIRO_ERROR(path_object->path->status);
}
/* }}} */

/* {{{ proto array cairo_mesh_pattern_get_control_point(CairoPattern object, long patch, long point)
   proto array CairoMeshPattern->getCornerColorRgba(long patch, long point)
   Gets the control point point_num of patch patch_num for a mesh pattern. */
PHP_FUNCTION(cairo_mesh_pattern_get_control_point)
{
	long patch_num, corner_num;
	double x, y;
	zval *pattern_zval = NULL;
	cairo_pattern_object *pattern_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Oll", &pattern_zval, cairo_ce_cairomeshpattern, &patch_num, &corner_num) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	pattern_object = (cairo_pattern_object *) cairo_pattern_object_get(pattern_zval TSRMLS_CC);
	cairo_mesh_pattern_get_control_point(pattern_object->pattern, patch_num, corner_num, &x, &y);
	PHP_CAIRO_ERROR(cairo_pattern_status(pattern_object->pattern));

	array_init(return_value);
	add_assoc_double(return_value, "x", x);
	add_assoc_double(return_value, "y", y);
}
/* }}} */

/* {{{ proto array cairo_mesh_pattern_get_corner_color_rgba(CairoPattern object)
   proto array CairoMeshPattern->getCornerColorRgba()
   Gets the color information in corner corner_num of patch patch_num for a mesh pattern. */

PHP_FUNCTION(cairo_mesh_pattern_get_corner_color_rgba)
{
	long patch_num, corner_num;
	double red, green, blue, alpha;
	zval *pattern_zval = NULL;
	cairo_pattern_object *pattern_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Oll", &pattern_zval, cairo_ce_cairomeshpattern, &patch_num, &corner_num) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	pattern_object = (cairo_pattern_object *) cairo_pattern_object_get(pattern_zval TSRMLS_CC);
	cairo_mesh_pattern_get_corner_color_rgba(pattern_object->pattern, patch_num, corner_num, &red, &green, &blue, &alpha);
	PHP_CAIRO_ERROR(cairo_pattern_status(pattern_object->pattern));

	array_init(return_value);
	add_assoc_double(return_value, "red", red);
	add_assoc_double(return_value, "green", green);
	add_assoc_double(return_value, "blue", blue);
	add_assoc_double(return_value, "alpha", alpha);
}
/* }}} */
#endif

/* }}} */

/* {{{ cairo_radialgradient_methods[] */
const zend_function_entry cairo_radialgradient_methods[] = {
	PHP_ME(CairoRadialGradient, __construct, CairoRadialGradient___construct_args, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 4, 0)
	PHP_ME_MAPPING(getCircles, cairo_pattern_get_radial_circles, NULL, ZEND_ACC_PUBLIC)
#endif
	{NULL, NULL, NULL}
};
/* }}} */

#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 12, 0)
/* {{{ cairo_meshpattern_methods[] */
const zend_function_entry cairo_meshpattern_methods[] = {
	PHP_ME(CairoMeshPattern, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME_MAPPING(beginPatch, cairo_mesh_pattern_begin_patch, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(endPatch, cairo_mesh_pattern_end_patch, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(moveTo, cairo_mesh_pattern_move_to, CairoMeshPattern_translate_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(lineTo, cairo_mesh_pattern_line_to, CairoMeshPattern_translate_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(curveTo, cairo_mesh_pattern_curve_to, CairoMeshPattern_curveTo_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(setControlPoint, cairo_mesh_pattern_set_control_point, CairoMeshPattern_setControlPoint_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(setCornerColorRGB, cairo_mesh_pattern_set_corner_color_rgb, CairoMeshPattern_setCornerColorRGB_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(setCornerColorRGBA, cairo_mesh_pattern_set_corner_color_rgba, CairoMeshPattern_setCornerColorRGBA_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(getPatchCount, cairo_mesh_pattern_get_patch_count, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(getPath, cairo_mesh_pattern_get_path, CairoMeshPattern_getPath_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(getControlPoint, cairo_mesh_pattern_get_control_point, CairoMeshPattern_getControlPoint_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(getCornerColorRgba, cairo_mesh_pattern_get_corner_color_rgba, CairoMeshPattern_getCornerColorRgba_args, ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};
/* }}} */
#endif

PHP_CAIRO_API zend_class_entry* php_cairo_get_pattern_ce(cairo_pattern_t *pattern TSRMLS_DC)
{
	zend_class_entry *type;
	if(pattern == NULL)
		return cairo_ce_cairopattern;
	switch(cairo_pattern_get_type(pattern)) {
		case CAIRO_PATTERN_TYPE_SOLID:
			type = cairo_ce_cairosolidpattern;
			break;
		case CAIRO_PATTERN_TYPE_SURFACE:
			type = cairo_ce_cairosurfacepattern;
			break;
		case CAIRO_PATTERN_TYPE_LINEAR:
			type = cairo_ce_cairolineargradient;
			break;
		case CAIRO_PATTERN_TYPE_RADIAL:
			type = cairo_ce_cairoradialgradient;
			break;
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 12, 0)
		case CAIRO_PATTERN_TYPE_MESH:
			type = cairo_ce_cairomeshpattern;
			break;
#endif
		default:
			php_error(E_WARNING, "Unsupported Cairo Surface Type");
			return NULL;
	}
	return type;
}

static void cairo_pattern_object_destroy(void *object TSRMLS_DC)
{
	cairo_pattern_object *pattern = (cairo_pattern_object *)object;
	zend_hash_destroy(pattern->std.properties);
	FREE_HASHTABLE(pattern->std.properties);

	if(pattern->matrix) {
		Z_DELREF_P(pattern->matrix);
		pattern->matrix = NULL;
	}
	if(pattern->surface) {
		Z_DELREF_P(pattern->surface);
		pattern->surface = NULL;
	}
	if(pattern->pattern){
		cairo_pattern_destroy(pattern->pattern);
	}
	efree(object);
}

static zend_object_value cairo_pattern_object_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	cairo_pattern_object *pattern;
#if PHP_VERSION_ID < 50399
	zval *temp;
#endif

	pattern = ecalloc(1, sizeof(cairo_pattern_object));

	pattern->std.ce = ce;

	ALLOC_HASHTABLE(pattern->std.properties);
	zend_hash_init(pattern->std.properties, 0, NULL, ZVAL_PTR_DTOR, 0);
#if PHP_VERSION_ID < 50399
	zend_hash_copy(pattern->std.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref,(void *) &temp, sizeof(zval *));
#else
	object_properties_init(&pattern->std, ce);
#endif
	retval.handle = zend_objects_store_put(pattern, NULL, (zend_objects_free_object_storage_t)cairo_pattern_object_destroy, NULL TSRMLS_CC);
	retval.handlers = &cairo_std_object_handlers;
	return retval;
}

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(cairo_pattern)
{
	zend_class_entry ce, gradient_ce, solid_ce, surface_ce, linear_ce, radial_ce, pattern_ce, extend_ce, filter_ce, mesh_ce;

	INIT_CLASS_ENTRY(ce, "CairoPattern", cairo_pattern_methods);
	cairo_ce_cairopattern = zend_register_internal_class(&ce TSRMLS_CC);
	cairo_ce_cairopattern->create_object = cairo_pattern_object_new;
	cairo_ce_cairopattern->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS;

	INIT_CLASS_ENTRY(gradient_ce, "CairoGradientPattern", cairo_gradientpattern_methods);
	cairo_ce_cairogradientpattern = zend_register_internal_class_ex(&gradient_ce, cairo_ce_cairopattern, "CairoPattern" TSRMLS_CC);
	cairo_ce_cairogradientpattern->create_object = cairo_pattern_object_new;
	cairo_ce_cairogradientpattern->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS;

	INIT_CLASS_ENTRY(solid_ce, "CairoSolidPattern", cairo_solidpattern_methods);
	cairo_ce_cairosolidpattern = zend_register_internal_class_ex(&solid_ce, cairo_ce_cairopattern, "CairoPattern" TSRMLS_CC);
	cairo_ce_cairosolidpattern->create_object = cairo_pattern_object_new;

	INIT_CLASS_ENTRY(surface_ce, "CairoSurfacePattern", cairo_surfacepattern_methods);
	cairo_ce_cairosurfacepattern = zend_register_internal_class_ex(&surface_ce, cairo_ce_cairopattern, "CairoPattern" TSRMLS_CC);
	cairo_ce_cairosurfacepattern->create_object = cairo_pattern_object_new;

	INIT_CLASS_ENTRY(linear_ce, "CairoLinearGradient", cairo_lineargradient_methods);
	cairo_ce_cairolineargradient = zend_register_internal_class_ex(&linear_ce, cairo_ce_cairogradientpattern, "CairoGradientPattern" TSRMLS_CC);
	cairo_ce_cairolineargradient->create_object = cairo_pattern_object_new;

	INIT_CLASS_ENTRY(radial_ce, "CairoRadialGradient", cairo_radialgradient_methods);
	cairo_ce_cairoradialgradient = zend_register_internal_class_ex(&radial_ce, cairo_ce_cairogradientpattern, "CairoGradientPattern" TSRMLS_CC);
	cairo_ce_cairoradialgradient->create_object = cairo_pattern_object_new;

#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 12, 0)
	INIT_CLASS_ENTRY(mesh_ce, "CairoMeshPattern", cairo_meshpattern_methods);
	cairo_ce_cairomeshpattern = zend_register_internal_class_ex(&mesh_ce, cairo_ce_cairopattern, "CairoPattern" TSRMLS_CC);
	cairo_ce_cairomeshpattern->create_object = cairo_pattern_object_new;
#endif

	INIT_CLASS_ENTRY(pattern_ce, "CairoPatternType", NULL);
	cairo_ce_cairopatterntype = zend_register_internal_class(&pattern_ce TSRMLS_CC);
	cairo_ce_cairopatterntype->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS | ZEND_ACC_FINAL_CLASS;

	#define REGISTER_CAIRO_TYPE_LONG_CONST(const_name, value) \
		zend_declare_class_constant_long(cairo_ce_cairopatterntype, const_name, sizeof(const_name)-1, (long)value TSRMLS_CC); \
		REGISTER_LONG_CONSTANT(#value,  value,  CONST_CS | CONST_PERSISTENT);

	REGISTER_CAIRO_TYPE_LONG_CONST("SOLID", CAIRO_PATTERN_TYPE_SOLID);
	REGISTER_CAIRO_TYPE_LONG_CONST("SURFACE", CAIRO_PATTERN_TYPE_SURFACE);
	REGISTER_CAIRO_TYPE_LONG_CONST("LINEAR", CAIRO_PATTERN_TYPE_LINEAR);
	REGISTER_CAIRO_TYPE_LONG_CONST("RADIAL", CAIRO_PATTERN_TYPE_RADIAL);

	INIT_CLASS_ENTRY(extend_ce, "CairoExtend", NULL);
	cairo_ce_cairoextend = zend_register_internal_class(&extend_ce TSRMLS_CC);
	cairo_ce_cairoextend->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS | ZEND_ACC_FINAL_CLASS;

	#define REGISTER_CAIRO_EXTEND_LONG_CONST(const_name, value) \
		zend_declare_class_constant_long(cairo_ce_cairoextend, const_name, sizeof(const_name)-1, (long)value TSRMLS_CC); \
		REGISTER_LONG_CONSTANT(#value,  value,  CONST_CS | CONST_PERSISTENT);

	REGISTER_CAIRO_EXTEND_LONG_CONST("NONE", CAIRO_EXTEND_NONE);
	REGISTER_CAIRO_EXTEND_LONG_CONST("REPEAT", CAIRO_EXTEND_REPEAT);
	REGISTER_CAIRO_EXTEND_LONG_CONST("REFLECT", CAIRO_EXTEND_REFLECT);
	REGISTER_CAIRO_EXTEND_LONG_CONST("PAD", CAIRO_EXTEND_PAD);

	INIT_CLASS_ENTRY(filter_ce, "CairoFilter", NULL);
	cairo_ce_cairofilter = zend_register_internal_class(&filter_ce TSRMLS_CC);
	cairo_ce_cairofilter->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS | ZEND_ACC_FINAL_CLASS;

	#define REGISTER_CAIRO_FILTER_LONG_CONST(const_name, value) \
		zend_declare_class_constant_long(cairo_ce_cairofilter, const_name, sizeof(const_name)-1, (long)value TSRMLS_CC); \
		REGISTER_LONG_CONSTANT(#value,  value,  CONST_CS | CONST_PERSISTENT);

	REGISTER_CAIRO_FILTER_LONG_CONST("FAST", CAIRO_FILTER_FAST);
	REGISTER_CAIRO_FILTER_LONG_CONST("GOOD", CAIRO_FILTER_GOOD);
	REGISTER_CAIRO_FILTER_LONG_CONST("BEST", CAIRO_FILTER_BEST);
	REGISTER_CAIRO_FILTER_LONG_CONST("NEAREST", CAIRO_FILTER_NEAREST);
	REGISTER_CAIRO_FILTER_LONG_CONST("BILINEAR", CAIRO_FILTER_BILINEAR);
	REGISTER_CAIRO_FILTER_LONG_CONST("GAUSSIAN", CAIRO_FILTER_GAUSSIAN);

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
