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

#include <ext/eos_datastructures/php_eos_datastructures_api.h>

#include "php_cairo.h"
#include "php_cairo_internal.h"

zend_class_entry *ce_cairo_pattern;
zend_class_entry *ce_cairo_solidpattern;
zend_class_entry *ce_cairo_gradient;
zend_class_entry *ce_cairo_lineargradient;
zend_class_entry *ce_cairo_radialgradient;
zend_class_entry *ce_cairo_surfacepattern;
zend_class_entry *ce_cairo_meshpattern;

zend_class_entry *ce_cairo_pattern_type;
zend_class_entry *ce_cairo_extend;
zend_class_entry *ce_cairo_filter;

static zend_object_handlers cairo_pattern_object_handlers;

typedef struct _cairo_pattern_object {
	zval *matrix;
	zval *surface;
	cairo_pattern_t *pattern;
	zend_object std;
} cairo_pattern_object;

#define CAIRO_PATTERN_FETCH_OBJ(zv) ((cairo_pattern_object*) \
	(((char*)Z_OBJ_P(zv)) - XtOffsetOf(cairo_pattern_object, std)))

/* ----------------------------------------------------------------
    Cairo\Pattern Class API
------------------------------------------------------------------ */

ZEND_BEGIN_ARG_INFO(CairoPattern___construct_args, ZEND_SEND_BY_VAL)
ZEND_END_ARG_INFO()

/* {{{ proto void contruct() 
   CairoPattern CANNOT be extended in userspace, this will throw an exception on use */
PHP_METHOD(CairoPattern, __construct)
{
	zend_throw_exception(ce_cairo_exception, "Cairo\\Pattern cannot be constructed", 0);
}
/* }}} */

// TODO: status enum with toString helper
// TODO: make getStatus return enum not long
ZEND_BEGIN_ARG_INFO(CairoPattern_getStatus_args, ZEND_SEND_BY_VAL)
ZEND_END_ARG_INFO()

/* {{{ proto long CairoPattern->getStatus()
   Returns the current integer status of the CairoPattern */
PHP_METHOD(CairoPattern, getStatus)
{
	cairo_pattern_object *pattern_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}

	pattern_object = CAIRO_PATTERN_FETCH_OBJ(getThis());
	RETURN_LONG(cairo_pattern_status(pattern_object->pattern));
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoPattern_getType_args, ZEND_SEND_BY_VAL)
ZEND_END_ARG_INFO()

/* {{{ proto void CairoPattern->getType()
   This function returns the Cairo\Pattern\Type of a pattern */
PHP_METHOD(CairoPattern, getType)
{
	cairo_pattern_object *pattern_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}

	pattern_object = CAIRO_PATTERN_FETCH_OBJ(getThis());
	CAIRO_EXCEPTION_STATUS(cairo_pattern_status(pattern_object->pattern));

	object_init_ex(return_value, ce_cairo_pattern_type);
	php_cairo_set_enum_value(return_value, cairo_pattern_get_type(pattern_object->pattern));
}

/* }}} */

ZEND_BEGIN_ARG_INFO(CairoPattern_getExtend_args, ZEND_SEND_BY_VAL)
ZEND_END_ARG_INFO()

/* {{{ proto int CairoPattern->getExtend()
       Gets the current extend mode for a pattern */
PHP_METHOD(CairoPattern, getExtend)
{
	cairo_pattern_object *pattern_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}

	pattern_object = CAIRO_PATTERN_FETCH_OBJ(getThis());
	CAIRO_EXCEPTION_STATUS(cairo_pattern_status(pattern_object->pattern));

	object_init_ex(return_value, ce_cairo_extend);
	php_cairo_set_enum_value(return_value, cairo_pattern_get_extend(pattern_object->pattern));
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoPattern_setExtend_args, ZEND_SEND_BY_VAL)
  ZEND_ARG_INFO(0, extend)
ZEND_END_ARG_INFO()

/* {{{ proto void CairoPattern::setExtend(int extend)
       Sets the mode to be used for drawing outside the area of a pattern */
PHP_METHOD(CairoPattern, setExtend)
{
	cairo_pattern_object *pattern_object;
	long extend = 0;

	// parse for enum object - get value
	// parse for long - check value

	pattern_object = CAIRO_PATTERN_FETCH_OBJ(getThis());
	cairo_pattern_set_extend(pattern_object->pattern, extend);
	CAIRO_EXCEPTION_STATUS(cairo_pattern_status(pattern_object->pattern));
}

/* }}} */

/* {{{ proto long cairo_pattern_get_matrix(CairoPattern object)
   proto long CairoPattern->getMatrix()
   Returns the pattern's transformation matrix 
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

	/* If we have a matrix object stored, grab that zval to use 
	if(pattern_object->matrix) {
		zval_dtor(return_value);
		*return_value = *pattern_object->matrix;
		zval_copy_ctor(return_value);
		Z_SET_REFCOUNT_P(return_value, 1);
	/* Otherwise we spawn a new object 
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

ZEND_BEGIN_ARG_INFO(CairoPattern_setMatrix_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, matrix, Cairo\\Matrix, 0) 
ZEND_END_ARG_INFO()

/* {{{ proto void CairoPattern->setMatrix(CairoMatrix object)
   Sets the pattern's transformation matrix using the created matrix object.
   This matrix is a transformation from user space to pattern space. 
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

	/* If there's already a matrix, then we deref and remove it 
	if(pattern_object->matrix) {
		Z_DELREF_P(pattern_object->matrix);
		pattern_object->matrix = NULL;
	}

	/* we need to be able to get this zval out later, so ref and store 
	pattern_object->matrix = matrix_zval;
	Z_ADDREF_P(matrix_zval);
}
/* }}} */

/*

ZEND_BEGIN_ARG_INFO_EX(CairoSolidPattern___construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 3)
	ZEND_ARG_INFO(0, red)
	ZEND_ARG_INFO(0, green)
	ZEND_ARG_INFO(0, blue)
	ZEND_ARG_INFO(0, alpha)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoSurfacePattern___construct_args, ZEND_SEND_BY_VAL)
	/* ZEND_ARG_OBJ_INFO(0, surface, CairoSurface, 0) - argh, catchable fatal error syndrome 
	ZEND_ARG_INFO(0, surface)
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











/* {{{ proto void cairo_pattern_add_color_stop_rgb(CairoPattern object, float offset, float red, float green, float blue)
   proto void CairoGradientPattern->addColorStopRgb(float offset, float red, float green, float blue)
   Adds an opaque color stop to a gradient pattern. The offset specifies the location along the gradient's control vector. 
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
   Adds a transparent color stop to a gradient pattern. The offset specifies the location along the gradient's control vector. 
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

/* {{{ proto array cairo_pattern_get_color_stop_rgba(CairoPattern object)
   proto array CairoGradientPattern->getColorStopRgba()
   Gets the color and offset information at the given index for a gradient pattern 
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
   Gets the number of color stops specified in the given gradient pattern 
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





/* {{{ proto CairoSolidPattern cairo_pattern_create_rgb(float red, float green, float blue)
   Returns new CairoSolidPattern object with the color designated 
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
   Returns new CairoSolidPattern object with the color designated 
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
	This is the same as cairo_pattern_create_rgba and cairo_pattern_create_rgb 
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

/* {{{ proto array cairo_pattern_get_rgba(CairoSolidPattern object)
   proto array CairoSolidPattern->getRgba()
   This function returns an array with four elements, the float values of red, green, blue, and alpha from the solid pattern 
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

/* {{{ cairo_solidpattern_methods[] 
const zend_function_entry cairo_solidpattern_methods[] = {
	PHP_ME(CairoSolidPattern, __construct, CairoSolidPattern___construct_args, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 4, 0)
	PHP_ME_MAPPING(getRgba, cairo_pattern_get_rgba, NULL, ZEND_ACC_PUBLIC)
#endif
	{NULL, NULL, NULL}
};
/* }}} */

/* {{{ proto CairoSurfacePattern cairo_pattern_create_for_surface(CairoSurface object)
   Returns new CairoSurfacePattern object with the surface designated 
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

	/* we need to be able to get this zval out later, so ref and store 
	pattern_object->surface = surface_zval;
	Z_ADDREF_P(surface_zval);
}
/* }}} */

/* {{{ proto void contruct(float red, float green, float blue[, float alpha])
	Returns new CairoSurfacePattern using supplied surface
	this is the same as cairo_pattern_create_for_surface 
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

	/* we need to be able to get this zval out later, so ref and store 
	pattern_object->surface = surface_zval;
	Z_ADDREF_P(surface_zval);
}
/* }}} */

/* {{{ proto CairoSurface object cairo_pattern_get_surface(CairoSurfacePattern object)
   proto CairoSurface object CairoSurfacePattern->getSurface()
   This function returns the surface object 
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
	
	/* If we have a surface object stored, grab that zval to use 
	if(pattern_object->surface) {
		zval_dtor(return_value);
		*return_value = *pattern_object->surface;
		zval_copy_ctor(return_value);
		Z_SET_REFCOUNT_P(return_value, 1);
	/* Otherwise we spawn a new object 
	} else {
		surface_ce = php_cairo_get_surface_ce(surface TSRMLS_CC);
		object_init_ex(return_value, surface_ce);
		surface = cairo_surface_reference(surface);
	}

	surface_object = (cairo_surface_object *)zend_object_store_get_object(return_value TSRMLS_CC);
}
/* }}} */

/* {{{ proto int cairo_pattern_get_filter(CairoSurfacePattern object)
   proto int CairoPattern->getFilter()
   Gets the current filter for a pattern 
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
   Sets the filter to be used for resizing when using this pattern 
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
   Gets the current extend mode for a pattern 
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
   Gets the current extend mode for a pattern 
PHP_FUNCTION(cairo_pattern_get_extend)
{
	zval *pattern_zval = NULL;
	cairo_pattern_object *pattern_object;

	/* we want a gradient pattern OR a surface pattern 
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
       Sets the mode to be used for drawing outside the area of a pattern 
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
       Sets the mode to be used for drawing outside the area of a pattern 
PHP_FUNCTION(cairo_pattern_set_extend)
{
	zval *pattern_zval = NULL;
	cairo_pattern_object *pattern_object;
	long extend = 0;

	/* we want a gradient pattern OR a surface pattern 
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

/* {{{ cairo_surfacepattern_methods[] 
const zend_function_entry cairo_surfacepattern_methods[] = {
	PHP_ME(CairoSurfacePattern, __construct, CairoSurfacePattern___construct_args, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
#
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 4, 0)
	PHP_ME_MAPPING(getSurface, cairo_pattern_get_surface, NULL, ZEND_ACC_PUBLIC)
#endif
	
	PHP_ME(CairoSurfacePattern, setExtend, CairoSurfacePattern_setExtend_args, ZEND_ACC_PUBLIC)
	PHP_ME(CairoSurfacePattern, getExtend, NULL, ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};
/* }}} */

/* {{{ proto CairoLinearGradient cairo_pattern_create_linear(float x0, float y0, float x1, float y1)
   Create a new CairoLinearGradient along the line defined by (x0, y0) and (x1, y1).
   Before using the gradient pattern, a number of color stops should be defined.  
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
  Before using the gradient pattern, a number of color stops should be defined. 
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

/* {{{ proto void cairo_pattern_get_linear_points(CairoLinearGradient object)
   proto void CairoLinearGradient->getPoints()
   Gets the gradient endpoints for a linear gradient. 
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

/* }}} */

/* {{{ cairo_lineargradient_methods[] 
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
   Before using the gradient pattern, a number of color stops should be defined.  
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
  Before using the gradient pattern, a number of color stops should be defined. 
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

/* {{{ proto void cairo_pattern_get_radial_circles(CairoRadialGradient object)
   proto void CairoRadialGradient->getCircles()
   Gets the gradient endpoint circles for a radial gradient, each specified as a center coordinate and a radius.
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

/* }}} */

/* {{{ cairo_radialgradient_methods[] 
const zend_function_entry cairo_radialgradient_methods[] = {
	PHP_ME(CairoRadialGradient, __construct, CairoRadialGradient___construct_args, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 4, 0)
	PHP_ME_MAPPING(getCircles, cairo_pattern_get_radial_circles, NULL, ZEND_ACC_PUBLIC)
#endif
	{NULL, NULL, NULL}
};
/* }}} 

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
		default:
			php_error(E_WARNING, "Unsupported Cairo Surface Type");
			return NULL;
	}
	return type;
}

/* ----------------------------------------------------------------
    Cairo\Pattern Object management
------------------------------------------------------------------*/

/* {{{ 
static void cairo_pattern_object_free_obj(zend_object *object)
{
	cairo_pattern_object *intern = (cairo_pattern_object*) ((char*)object - XtOffsetOf(cairo_pattern_object, std));

	if(!intern) {
		return;
	}

	if(intern->matrix) {
		Z_DELREF_P(intern->matrix);
	}
	intern->matrix = NULL;

	if(intern->surface) {
		Z_DELREF_P(intern->surface);
	}
	intern->surface = NULL;

	if(intern->pattern){
		cairo_pattern_destroy(intern->pattern);
	}
	intern->pattern = NULL;

	zend_object_std_dtor(&intern->std);
}
/* }}} */

/* {{{ 
static zend_object* cairo_pattern_obj_ctor(zend_class_entry *ce, cairo_pattern_object **intern)
{
	cairo_pattern_object *object = ecalloc(1, sizeof(cairo_pattern_object) + zend_object_properties_size(ce));
	object->matrix = NULL;
	object->surface = NULL;
	object->pattern = NULL;

	zend_object_std_init(&object->std, ce);
	object->std.handlers = &cairo_matrix_object_handlers;
	*intern = object;

	return &object->std;
}
/* }}} */

/* {{{ 
static zend_object* cairo_pattern_create_object(zend_class_entry *ce)
{
	cairo_pattern_object *pattern = NULL;
	zend_object *return_value = cairo_pattern_obj_ctor(ce, &pattern);

	object_properties_init(&(pattern->std), ce);
	return return_value;
}
/* }}} */

/* ----------------------------------------------------------------
    Cairo\Pattern Definition and registration
------------------------------------------------------------------*/

/* {{{ cairo_pattern_methods[] 
const zend_function_entry cairo_pattern_methods[] = {
	PHP_ME(CairoPattern, __construct, CairoPattern___construct_args, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(CairoPattern, getType, CairoPattern_getType_args, ZEND_ACC_PUBLIC)
	PHP_ME(CairoPattern, status, CairoPattern_status_args, ZEND_ACC_PUBLIC)
	PHP_ME(CairoPattern, getMatrix, CairoPattern_getMatrix_args, ZEND_ACC_PUBLIC)
	PHP_ME(CairoPattern, setMatrix, CairoPattern_setMatrix_args, ZEND_ACC_PUBLIC)
	PHP_ME(CairoPattern, getExtend, CairoPattern_setExtend_args, ZEND_ACC_PUBLIC)
	PHP_ME(CairoPattern, setExtend, CairoPattern_setExtend_args, ZEND_ACC_PUBLIC)
	PHP_ME(CairoPattern, getFilter, CairoPattern_getFilter_args, ZEND_ACC_PUBLIC)
	PHP_ME(CairoPattern, setFilter, CairoPattern_setFilter_args, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};
/* }}} 

Pattern(abstract base class - how to make it not extendable in userspace?)
solidpattern
gradientPattern??
radialpattern??

pattern
pattern->mesh
pattern->solid
pattern->surface
pattern->gradient
pattern->gradient->radial
pattern->gradient->linear

/* {{{ cairo_gradient_methods[] 
const zend_function_entry cairo_gradient_methods[] = {
	PHP_ME(CairoGradient, addColorStopRgba, CairoGradient_addColorStopRgba_args, ZEND_ACC_PUBLIC)
	PHP_ME(CairoGradient, getColorStopRgba, CairoGradient_getColorStopRgba_args, ZEND_ACC_PUBLIC)
	PHP_ME(CairoGradient, getColorStopCount, CairoGradient_getColorStopCount_args, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};
/* }}} */

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(cairo_pattern)
{
	zend_class_entry 	pattern_ce,
						gradient_ce,
						solid_ce,
						surface_ce,
						linear_ce,
						radial_ce,
						mesh_ce,
						raster_source_ce,
						pattern_type_ce,
						extend_ce,
						filter_ce;
/*
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
	cairo_ce_cairoradialgradient->create_object = cairo_pattern_object_new; */

	INIT_NS_CLASS_ENTRY(pattern_type_ce,  CAIRO_NAMESPACE, ZEND_NS_NAME("Pattern", "Type"), NULL);
	ce_cairo_pattern_type = zend_register_internal_class_ex(&pattern_type_ce, php_eos_datastructures_get_enum_ce());
	ce_cairo_pattern_type->ce_flags |= ZEND_ACC_FINAL;

	#define CAIRO_PATTERN_TYPE_DECLARE_ENUM(name) \
		zend_declare_class_constant_long(ce_cairo_pattern_type, #name, \
		sizeof(#name)-1, CAIRO_PATTERN_TYPE_## name);

	CAIRO_PATTERN_TYPE_DECLARE_ENUM(SOLID);
	CAIRO_PATTERN_TYPE_DECLARE_ENUM(SURFACE);
	CAIRO_PATTERN_TYPE_DECLARE_ENUM(LINEAR);
	CAIRO_PATTERN_TYPE_DECLARE_ENUM(RADIAL);
	CAIRO_PATTERN_TYPE_DECLARE_ENUM(MESH);
	CAIRO_PATTERN_TYPE_DECLARE_ENUM(RASTER_SOURCE);

	INIT_NS_CLASS_ENTRY(extend_ce,  CAIRO_NAMESPACE, "Extend", NULL);
	ce_cairo_extend = zend_register_internal_class_ex(&extend_ce, php_eos_datastructures_get_enum_ce());
	ce_cairo_extend->ce_flags |= ZEND_ACC_FINAL;

	#define CAIRO_EXEND_DECLARE_ENUM(name) \
		zend_declare_class_constant_long(ce_cairo_extend, #name, \
		sizeof(#name)-1, CAIRO_EXTEND_## name);

	CAIRO_EXEND_DECLARE_ENUM(NONE);
	CAIRO_EXEND_DECLARE_ENUM(REPEAT);
	CAIRO_EXEND_DECLARE_ENUM(REFLECT);
	CAIRO_EXEND_DECLARE_ENUM(PAD);

	INIT_NS_CLASS_ENTRY(filter_ce,  CAIRO_NAMESPACE, "Filter", NULL);
	ce_cairo_filter = zend_register_internal_class_ex(&filter_ce, php_eos_datastructures_get_enum_ce());
	ce_cairo_filter->ce_flags |= ZEND_ACC_FINAL;

	#define CAIRO_FILTER_DECLARE_ENUM(name) \
		zend_declare_class_constant_long(ce_cairo_filter, #name, \
		sizeof(#name)-1, CAIRO_FILTER_## name);

	CAIRO_FILTER_DECLARE_ENUM(FAST);
	CAIRO_FILTER_DECLARE_ENUM(GOOD);
	CAIRO_FILTER_DECLARE_ENUM(BEST);
	CAIRO_FILTER_DECLARE_ENUM(NEAREST);
	CAIRO_FILTER_DECLARE_ENUM(BILINEAR);
	CAIRO_FILTER_DECLARE_ENUM(GAUSSIAN);

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
