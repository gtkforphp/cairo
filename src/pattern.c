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
zend_class_entry *ce_cairo_pattern_solid;
zend_class_entry *ce_cairo_pattern_gradient;
zend_class_entry *ce_cairo_pattern_gradient_linear;
zend_class_entry *ce_cairo_pattern_gradient_radial;
zend_class_entry *ce_cairo_pattern_surface;
zend_class_entry *ce_cairo_pattern_mesh;
zend_class_entry *ce_cairo_pattern_raster;

zend_class_entry *ce_cairo_pattern_type;
zend_class_entry *ce_cairo_extend;
zend_class_entry *ce_cairo_filter;

static zend_object_handlers cairo_pattern_object_handlers;

typedef struct _cairo_pattern_object {
	cairo_pattern_t *pattern;
	zend_object std;
} cairo_pattern_object;

static cairo_user_data_key_t matrix_key;

void cairo_pattern_destroy_func (void *data)
{
	Z_DELREF_P(data);
	efree(data);
}

static inline cairo_pattern_object *cairo_pattern_fetch_object(zend_object *object)
{
	return (cairo_pattern_object *) ((char*)(object) - XtOffsetOf(cairo_pattern_object, std));
}

#define Z_CAIRO_PATTERN_P(zv) cairo_pattern_fetch_object(Z_OBJ_P(zv))

static inline cairo_pattern_object *cairo_pattern_object_get(zval *zv)
{
	cairo_pattern_object *object = Z_CAIRO_PATTERN_P(zv);
	if(object->pattern == NULL) {
		zend_throw_exception_ex(ce_cairo_exception, 0,
			"Internal pattern object missing in %s, you must call parent::__construct in extended classes",
			ZSTR_VAL(Z_OBJCE_P(zv)->name));
		return NULL;
	}
	return object;
}

/* ----------------------------------------------------------------
    Cairo\Pattern C API
------------------------------------------------------------------*/

zend_class_entry* php_cairo_get_pattern_ce(cairo_pattern_t *pattern)
{
	zend_class_entry *type;
	if(pattern == NULL) {
		return ce_cairo_pattern;
	}

	switch(cairo_pattern_get_type(pattern)) {
		case CAIRO_PATTERN_TYPE_SOLID:
			type = ce_cairo_pattern_solid;
			break;
		case CAIRO_PATTERN_TYPE_SURFACE:
			type = ce_cairo_pattern_surface;
			break;
		case CAIRO_PATTERN_TYPE_LINEAR:
			type = ce_cairo_pattern_gradient_linear;
			break;
		case CAIRO_PATTERN_TYPE_RADIAL:
			type = ce_cairo_pattern_gradient_radial;
			break;
		case CAIRO_PATTERN_TYPE_MESH:
			type = ce_cairo_pattern_mesh;
			break;
		case CAIRO_PATTERN_TYPE_RASTER_SOURCE:
			type = ce_cairo_pattern_raster;
			break;
		default:
			php_error(E_WARNING, "Unsupported Cairo Surface Type");
			return NULL;
	}
	return type;
}

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

	pattern_object = cairo_pattern_object_get(getThis());
	if(!pattern_object) {
		return;
	}

	object_init_ex(return_value, ce_cairo_status);
	php_eos_datastructures_set_enum_value(return_value, cairo_pattern_status(pattern_object->pattern));
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

	pattern_object = cairo_pattern_object_get(getThis());
	if(!pattern_object) {
		return;
	}

	object_init_ex(return_value, ce_cairo_pattern_type);
	php_eos_datastructures_set_enum_value(return_value, cairo_pattern_get_type(pattern_object->pattern));
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

	pattern_object = cairo_pattern_object_get(getThis());
	if(!pattern_object) {
		return;
	}

	object_init_ex(return_value, ce_cairo_extend);
	php_eos_datastructures_set_enum_value(return_value, cairo_pattern_get_extend(pattern_object->pattern));
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
	zval *extend_enum;

	if (zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET|ZEND_PARSE_PARAMS_THROW,
		ZEND_NUM_ARGS(), "O", &extend_enum, ce_cairo_extend) == FAILURE) {
		if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "l", &extend) == FAILURE) {
			return;
		} else {
			if(!php_eos_datastructures_check_value(ce_cairo_extend, extend)) {
				return;
			}
		}
	} else {
		extend = php_eos_datastructures_get_enum_value(extend_enum);
	}

	pattern_object = cairo_pattern_object_get(getThis());
	if(!pattern_object) {
		return;
	}

	cairo_pattern_set_extend(pattern_object->pattern, extend);
}

/* }}} */

ZEND_BEGIN_ARG_INFO(CairoPattern_getFilter_args, ZEND_SEND_BY_VAL)
ZEND_END_ARG_INFO()

/* {{{ proto int CairoPattern->getFilter()
       Gets the current filter mode for a pattern */
PHP_METHOD(CairoPattern, getFilter)
{
	cairo_pattern_object *pattern_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}

	pattern_object = cairo_pattern_object_get(getThis());
	if(!pattern_object) {
		return;
	}

	object_init_ex(return_value, ce_cairo_filter);
	php_eos_datastructures_set_enum_value(return_value, cairo_pattern_get_filter(pattern_object->pattern));
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoPattern_setFilter_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, filter)
ZEND_END_ARG_INFO()

/* {{{ proto void CairoPattern::setFilter(int filter)
       Sets the filter to be used for resizing when using this pattern  */
PHP_METHOD(CairoPattern, setFilter)
{
	cairo_pattern_object *pattern_object;
	long filter = 0;
	zval *filter_enum;

	if (zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET|ZEND_PARSE_PARAMS_THROW,
		ZEND_NUM_ARGS(), "O", &filter_enum, ce_cairo_filter) == FAILURE) {
		if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "l", &filter) == FAILURE) {
			return;
		} else {
			if(!php_eos_datastructures_check_value(ce_cairo_filter, filter)) {
				return;
			}
		}
	} else {
		filter = php_eos_datastructures_get_enum_value(filter_enum);
	}

	pattern_object = cairo_pattern_object_get(getThis());
	if(!pattern_object) {
		return;
	}

	cairo_pattern_set_filter(pattern_object->pattern, filter);
}

/* }}} */

ZEND_BEGIN_ARG_INFO(CairoPattern_getMatrix_args, ZEND_SEND_BY_VAL)
ZEND_END_ARG_INFO()

/* {{{ proto object CairoPattern->getMatrix()
   Returns the pattern's transformation matrix */
PHP_METHOD(CairoPattern, getMatrix)
{
	cairo_pattern_object *pattern_object;
	zval *matrix = NULL;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}

	pattern_object = cairo_pattern_object_get(getThis());
	if(!pattern_object) {
		return;
	}

	matrix = cairo_pattern_get_user_data(pattern_object->pattern, &matrix_key);

	if(!matrix) {
		zval *matrix_store = emalloc(sizeof(zval));
		cairo_status_t status;

		object_init_ex(return_value, ce_cairo_matrix);
		cairo_pattern_get_matrix(pattern_object->pattern, cairo_matrix_object_get_matrix(return_value));
		ZVAL_COPY(matrix_store, return_value);
		status = cairo_pattern_set_user_data(pattern_object->pattern, &matrix_key,
			(void *)matrix_store, cairo_pattern_destroy_func);
	} else {
		ZVAL_COPY(return_value, matrix);
	}
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoPattern_setMatrix_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, matrix, Cairo\\Matrix, 0) 
ZEND_END_ARG_INFO()

/* {{{ proto void CairoPattern->setMatrix(CairoMatrix object)
   Sets the pattern's transformation matrix using the created matrix object.
   This matrix is a transformation from user space to pattern space. */
PHP_METHOD(CairoPattern, setMatrix)
{
	zval *matrix_zval;
	cairo_pattern_object *pattern_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "O", &matrix_zval, ce_cairo_matrix) == FAILURE) {
		return;
	}

	pattern_object = cairo_pattern_object_get(getThis());
	if(!pattern_object) {
		return;
	}

	cairo_pattern_set_matrix(pattern_object->pattern, cairo_matrix_object_get_matrix(matrix_zval));

	zval *matrix_store = emalloc(sizeof(zval));
	cairo_status_t status;

	ZVAL_COPY(matrix_store, matrix_zval);

	status = cairo_pattern_set_user_data(pattern_object->pattern, &matrix_key,
			(void *)matrix_store, cairo_pattern_destroy_func);
}
/* }}} */

/* ----------------------------------------------------------------
    Cairo\Pattern\Solid Class API
------------------------------------------------------------------ */

ZEND_BEGIN_ARG_INFO_EX(CairoPatternSolid___construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 3)
	ZEND_ARG_INFO(0, red)
	ZEND_ARG_INFO(0, green)
	ZEND_ARG_INFO(0, blue)
	ZEND_ARG_INFO(0, alpha)
ZEND_END_ARG_INFO()

/* {{{ proto void contruct(float red, float green, float blue[, float alpha])
	Returns new Cairo\Pattern\Solid using rgb and optionally alpha */
PHP_METHOD(CairoPatternSolid, __construct)
{
	double red = 0.0, green = 0.0, blue = 0.0, alpha = 0;
	cairo_pattern_object *pattern_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "ddd|d", &red, &green, &blue, &alpha) == FAILURE) {
		return;
	}

	pattern_object = Z_CAIRO_PATTERN_P(getThis());
	if(!pattern_object) {
		return;
	}

	if(!alpha) {
		pattern_object->pattern = cairo_pattern_create_rgb(red, green, blue);
	} else {
		pattern_object->pattern = cairo_pattern_create_rgba(red, green, blue, alpha);
	}
	php_cairo_throw_exception(cairo_pattern_status(pattern_object->pattern));
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoPatternSolid_getRgba_args, ZEND_SEND_BY_VAL)
ZEND_END_ARG_INFO()

/* {{{ proto array Cairo\Pattern\Solid->getRgba()
   This function returns an array with four elements,
   the float values of red, green, blue, and alpha from the solid pattern */
PHP_METHOD(CairoPatternSolid, getRgba)
{
	cairo_pattern_object *pattern_object;
	double red, green, blue, alpha;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}

	pattern_object = cairo_pattern_object_get(getThis());
	if(!pattern_object) {
		return;
	}

	cairo_pattern_get_rgba(pattern_object->pattern, &red, &green, &blue, &alpha);

	array_init(return_value);
	add_assoc_double(return_value, "red", red);
	add_assoc_double(return_value, "green", green);
	add_assoc_double(return_value, "blue", blue);
	add_assoc_double(return_value, "alpha", alpha);
}
/* }}} */

/* ----------------------------------------------------------------
    Cairo\Pattern\Gradient Class API
------------------------------------------------------------------ */

ZEND_BEGIN_ARG_INFO(CairoPatternGradient_addColorStopRgb_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, offset)
	ZEND_ARG_INFO(0, red)
	ZEND_ARG_INFO(0, green)
	ZEND_ARG_INFO(0, blue)
ZEND_END_ARG_INFO()

/* {{{ proto void CairoGradientPattern->addColorStopRgb(float offset, float red, float green, float blue)
   Adds an opaque color stop to a gradient pattern.
   The offset specifies the location along the gradient's control vector. */
PHP_METHOD(CairoPatternGradient, addColorStopRgb)
{
	double offset = 0.0, red = 0.0, green = 0.0, blue = 0.0;
	cairo_pattern_object *pattern_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "dddd", &offset, &red, &green, &blue) == FAILURE) {
		return;
	}

	pattern_object = cairo_pattern_object_get(getThis());
	if(!pattern_object) {
		return;
	}
	cairo_pattern_add_color_stop_rgb(pattern_object->pattern, offset, red, green, blue);
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoPatternGradient_addColorStopRgba_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, offset)
	ZEND_ARG_INFO(0, red)
	ZEND_ARG_INFO(0, green)
	ZEND_ARG_INFO(0, blue)
	ZEND_ARG_INFO(0, alpha)
ZEND_END_ARG_INFO()

/* {{{ proto void CairoGradientPattern->addColorStopRgba(float offset, float red, float green, float blue, float alpha)
   Adds a transparent color stop to a gradient pattern.
   The offset specifies the location along the gradient's control vector. */
PHP_METHOD(CairoPatternGradient, addColorStopRgba)
{
	double offset = 0.0, red = 0.0, green = 0.0, blue = 0.0, alpha = 1.0;
	cairo_pattern_object *pattern_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "ddddd", &offset, &red, &green, &blue, &alpha) == FAILURE) {
		return;
	}

	pattern_object = cairo_pattern_object_get(getThis());
	if(!pattern_object) {
		return;
	}
	cairo_pattern_add_color_stop_rgba(pattern_object->pattern, offset, red, green, blue, alpha);
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoPatternGradient_getColorStopRgba_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

/* {{{ proto array CairoGradientPattern->getColorStopRgba()
   Gets the color and offset information at the given index for a gradient pattern */
PHP_METHOD(CairoPatternGradient, getColorStopRgba)
{
	long index;
	double offset, red, green, blue, alpha;
	cairo_pattern_object *pattern_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "l", &index) == FAILURE) {
		return;
	}

	pattern_object = cairo_pattern_object_get(getThis());
	if(!pattern_object) {
		return;
	}
	cairo_pattern_get_color_stop_rgba(pattern_object->pattern, index, &offset, &red, &green, &blue, &alpha);

	array_init(return_value);
	add_assoc_double(return_value, "red", red);
	add_assoc_double(return_value, "green", green);
	add_assoc_double(return_value, "blue", blue);
	add_assoc_double(return_value, "alpha", alpha);
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoPatternGradient_getColorStopCount_args, ZEND_SEND_BY_VAL)
ZEND_END_ARG_INFO()

/* {{{ proto array CairoGradientPattern->getColorStopCount()
   Gets the number of color stops specified in the given gradient pattern */
PHP_METHOD(CairoPatternGradient, getColorStopCount)
{
	int count;
	cairo_pattern_object *pattern_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}

	pattern_object = cairo_pattern_object_get(getThis());
	if(!pattern_object) {
		return;
	}
	cairo_pattern_get_color_stop_count(pattern_object->pattern, &count);

	RETURN_LONG(count);
}
/* }}} */

/* ----------------------------------------------------------------
    Cairo\Pattern\Gradient\Radial Class API
------------------------------------------------------------------ */

ZEND_BEGIN_ARG_INFO(CairoPatternGradientRadial___construct_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, x0)
	ZEND_ARG_INFO(0, y0)
	ZEND_ARG_INFO(0, r0)
	ZEND_ARG_INFO(0, x1)
	ZEND_ARG_INFO(0, y1)
	ZEND_ARG_INFO(0, r1)
ZEND_END_ARG_INFO()

/* {{{ proto void construct(float x0, float y0, float r0, float x1, float y1, float r1)
  Create a new Gradient along the line defined by (x0, y0) and (x1, y1).
  Before using the gradient pattern, a number of color stops should be defined. */
PHP_METHOD(CairoPatternGradientRadial, __construct)
{
	cairo_pattern_object *pattern_object;
	double x0 = 0.0, y0 = 0.0, r0 = 0.0, x1 = 0.0, y1 = 0.0, r1 = 0.0;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "dddddd", &x0, &y0, &r0, &x1, &y1, &r1) == FAILURE) {
		return;
	}

	pattern_object = Z_CAIRO_PATTERN_P(getThis());
	if(!pattern_object) {
		return;
	}
	pattern_object->pattern = cairo_pattern_create_radial(x0, y0, r0, x1, y1, r1);
	php_cairo_throw_exception(cairo_pattern_status(pattern_object->pattern) );
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoPatternGradientRadial_getCircles_args, ZEND_SEND_BY_VAL)
ZEND_END_ARG_INFO()

/* {{{ proto void Cairo\Pattern\Gradient\Radial->getCircles()
   Gets the gradient endpoint circles for a radial gradient
   each specified as a center coordinate and a radius.*/
PHP_METHOD(CairoPatternGradientRadial, getCircles)
{
	cairo_pattern_object *pattern_object;
	double x0 = 0.0, y0 = 0.0, r0 = 0.0, x1 = 0.0, y1 = 0.0, r1 = 0.0;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}

	pattern_object = cairo_pattern_object_get(getThis());
	if(!pattern_object) {
		return;
	}
	cairo_pattern_get_radial_circles(pattern_object->pattern, &x0, &y0, &r0, &x1, &y1, &r1);

	array_init(return_value);
	add_assoc_double(return_value, "x0", x0);
	add_assoc_double(return_value, "y0", y0);
	add_assoc_double(return_value, "r0", r0);
	add_assoc_double(return_value, "x1", x1);
	add_assoc_double(return_value, "y1", y1);
	add_assoc_double(return_value, "r1", r1);
}
/* }}} */

/* ----------------------------------------------------------------
    Cairo\Pattern\Gradient\Linear Class API
------------------------------------------------------------------ */

ZEND_BEGIN_ARG_INFO(CairoPatternGradientLinear___construct_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, x0)
	ZEND_ARG_INFO(0, y0)
	ZEND_ARG_INFO(0, x1)
	ZEND_ARG_INFO(0, y1)
ZEND_END_ARG_INFO()

/* {{{ proto void construct(float x0, float y0, float x1, float y1)
  Create a new CairoLinearGradient along the line defined by (x0, y0) and (x1, y1).
  Before using the gradient pattern, a number of color stops should be defined. */
PHP_METHOD(CairoPatternGradientLinear, __construct)
{
	cairo_pattern_object *pattern_object;
	double x0 = 0.0, y0 = 0.0, x1 = 0.0, y1 = 0.0;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "dddd", &x0, &y0, &x1, &y1) == FAILURE) {
		return;
	}

	pattern_object = Z_CAIRO_PATTERN_P(getThis());
	if(!pattern_object) {
		return;
	}
	pattern_object->pattern = cairo_pattern_create_linear(x0, y0, x1, y1);
	php_cairo_throw_exception(cairo_pattern_status(pattern_object->pattern));
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoPatternGradientLinear_getPoints_args, ZEND_SEND_BY_VAL)
ZEND_END_ARG_INFO()

/* {{{ proto void cairo_pattern_get_linear_points(CairoLinearGradient object)
   proto void CairoLinearGradient->getPoints()
   Gets the gradient endpoints for a linear gradient. */
PHP_METHOD(CairoPatternGradientLinear, getPoints)
{
	cairo_pattern_object *pattern_object;
	double x0, y0, x1, y1;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}

	pattern_object = cairo_pattern_object_get(getThis());
	if(!pattern_object) {
		return;
	}
	cairo_pattern_get_linear_points(pattern_object->pattern, &x0, &y0, &x1, &y1);

	array_init(return_value);
	add_assoc_double(return_value, "x0", x0);
	add_assoc_double(return_value, "y0", y0);
	add_assoc_double(return_value, "x1", x1);
	add_assoc_double(return_value, "y1", y1);
}
/* }}} */

/* ----------------------------------------------------------------
    Cairo\Pattern\Surface Class API
------------------------------------------------------------------ */

ZEND_BEGIN_ARG_INFO(CairoPatternSurface___construct_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, surface, Cairo\\Surface, 0)
ZEND_END_ARG_INFO()

/* {{{ proto void contruct(float red, float green, float blue[, float alpha])
	Returns new CairoSurfacePattern using supplied surface */
PHP_METHOD(CairoPatternSurface, __construct)
{
	cairo_pattern_object *pattern_object;
	zval * surface_zval = NULL;

	//if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "O", &surface_zval, ce_cairo_surface) == FAILURE) {
	//	return;
	//}

	pattern_object = Z_CAIRO_PATTERN_P(getThis());
	if(!pattern_object) {
		return;
	}

	// TODO: make this work when surfaces exist
	// get our surface via a cairo surface api call
	// create our pattern
	// pattern_object->pattern = cairo_pattern_create_for_surface(surface_object->surface);
	php_cairo_throw_exception(cairo_pattern_status(pattern_object->pattern));
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoPatternSurface_getSurface_args, ZEND_SEND_BY_VAL)
ZEND_END_ARG_INFO()

/* {{{ proto CairoSurface object CairoSurfacePattern->getSurface()
   This function returns the surface object */
PHP_METHOD(CairoPatternSurface, getSurface)
{
	cairo_pattern_object *pattern_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}

	pattern_object = cairo_pattern_object_get(getThis());
	if(!pattern_object) {
		return;
	}

	// TODO: make this work when surfaces exist
	// get our surface out
	// cairo_pattern_get_surface(pattern_object->pattern, &surface)
	// pull the zval out of teh surface or create new - see the matrix stuff
}
/* }}} */

/* ----------------------------------------------------------------
    Cairo\Pattern\Mesh Class API
------------------------------------------------------------------ */
ZEND_BEGIN_ARG_INFO(CairoPatternMesh___construct_args, ZEND_SEND_BY_VAL)
ZEND_END_ARG_INFO()

/* {{{ proto void contruct()
	Returns new Cairo\Pattern\Mesh  */
PHP_METHOD(CairoPatternMesh, __construct)
{
	cairo_pattern_object *pattern_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}

	pattern_object = Z_CAIRO_PATTERN_P(getThis());
	if(!pattern_object) {
		return;
	}

	pattern_object->pattern = cairo_pattern_create_mesh();
	php_cairo_throw_exception(cairo_pattern_status(pattern_object->pattern));
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoPatternMesh_beginPatch_args, ZEND_SEND_BY_VAL)
ZEND_END_ARG_INFO()

/* {{{  proto void Mesh->beginPatch()
  begin a patch in a mesh pattern */
PHP_METHOD(CairoPatternMesh, beginPatch)
{
	cairo_pattern_object *pattern_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}

	pattern_object = cairo_pattern_object_get(getThis());
	if(!pattern_object) {
		return;
	}
	cairo_mesh_pattern_begin_patch(pattern_object->pattern);

	php_cairo_throw_exception(cairo_pattern_status(pattern_object->pattern));
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoPatternMesh_endPatch_args, ZEND_SEND_BY_VAL)
ZEND_END_ARG_INFO()

/* {{{  proto void Mesh->endPatch()
  end a patch in a mesh pattern*/
PHP_METHOD(CairoPatternMesh, endPatch)
{
	cairo_pattern_object *pattern_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}

	pattern_object = cairo_pattern_object_get(getThis());
	if(!pattern_object) {
		return;
	}
	cairo_mesh_pattern_end_patch(pattern_object->pattern);

	php_cairo_throw_exception(cairo_pattern_status(pattern_object->pattern));
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoPatternMesh_moveTo_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

/* {{{  proto void Mesh->moveTo(float x, float y)
  move to a new starting point position in the patch */
PHP_METHOD(CairoPatternMesh, moveTo)
{
	cairo_pattern_object *pattern_object;
	double x, y;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "dd",
									&x, &y) == FAILURE) {
		return;
	}

	pattern_object = cairo_pattern_object_get(getThis());
	if(!pattern_object) {
		return;
	}
	cairo_mesh_pattern_move_to(pattern_object->pattern, x, y);

	php_cairo_throw_exception(cairo_pattern_status(pattern_object->pattern));
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoPatternMesh_lineTo_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

/* {{{  proto void Mesh->lineTo(float x, float y)
   add a line from the current point to position in the patch */
PHP_METHOD(CairoPatternMesh, lineTo)
{
	cairo_pattern_object *pattern_object;
	double x, y;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "dd",
									&x, &y) == FAILURE) {
		return;
	}

	pattern_object = cairo_pattern_object_get(getThis());
	if(!pattern_object) {
		return;
	}
	cairo_mesh_pattern_line_to(pattern_object->pattern, x, y);

	php_cairo_throw_exception(cairo_pattern_status(pattern_object->pattern));
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoPatternMesh_curveTo_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, x1)
	ZEND_ARG_INFO(0, y1)
	ZEND_ARG_INFO(0, x2)
	ZEND_ARG_INFO(0, y2)
	ZEND_ARG_INFO(0, x3)
	ZEND_ARG_INFO(0, y3)
ZEND_END_ARG_INFO()

/* {{{  proto void Mesh->curveTo(float x1, float y1, float x2,
 *           float y2, float x3, float y3)
   cubic bezier spline added to current path  */
PHP_METHOD(CairoPatternMesh, curveTo)
{
	cairo_pattern_object *pattern_object;
	double x1, y1, x2, y2, x3, y3;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "dddddd",
									&x1, &y1, &x2, &y2, &x3, &y3) == FAILURE) {
		return;
	}

	pattern_object = cairo_pattern_object_get(getThis());
	if(!pattern_object) {
		return;
	}
	cairo_mesh_pattern_curve_to(pattern_object->pattern, x1, y1, x2, y2, x3, y3);

	php_cairo_throw_exception(cairo_pattern_status(pattern_object->pattern));
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoPatternMesh_setControlPoint_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, corner_num)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

/* {{{  proto void Mesh->setControlPoint(int corner_num,
 *            float x, float y)
   sets the internal control point of the current patch */
PHP_METHOD(CairoPatternMesh, setControlPoint)
{
	cairo_pattern_object *pattern_object;
	long corner_num;
	double x, y;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "ldd", &corner_num,
									&x, &y) == FAILURE) {
		return;
	}

	pattern_object = cairo_pattern_object_get(getThis());
	if(!pattern_object) {
		return;
	}
	cairo_mesh_pattern_set_control_point(pattern_object->pattern, corner_num,
											x, y);

	php_cairo_throw_exception(cairo_pattern_status(pattern_object->pattern));
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoPatternMesh_setCornerColorRgb_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, corner_num)
	ZEND_ARG_INFO(0, red)
	ZEND_ARG_INFO(0, green)
	ZEND_ARG_INFO(0, blue)
ZEND_END_ARG_INFO()

/* {{{  proto void Mesh->setCornerColorRgb(int corner_num,
 *            float red, float blue, float green)
   Gets the control point of patch number for a mesh pattern */
PHP_METHOD(CairoPatternMesh, setCornerColorRgb)
{
	cairo_pattern_object *pattern_object;
	long corner_num;
	double red, green, blue;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "ldddd", &corner_num,
									&red, &green, &blue) == FAILURE) {
		return;
	}

	pattern_object = cairo_pattern_object_get(getThis());
	if(!pattern_object) {
		return;
	}
	cairo_mesh_pattern_set_corner_color_rgb(pattern_object->pattern, corner_num,
											 red, green, blue);

	php_cairo_throw_exception(cairo_pattern_status(pattern_object->pattern));
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoPatternMesh_setCornerColorRgba_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, corner_num)
	ZEND_ARG_INFO(0, red)
	ZEND_ARG_INFO(0, green)
	ZEND_ARG_INFO(0, blue)
	ZEND_ARG_INFO(0, alpha)
ZEND_END_ARG_INFO()

/* {{{  proto void Mesh->setCornerColorRgba(int corner_num,
 *            float red, float blue, float green, float alpha)
   Gets the control point of patch number for a mesh pattern */
PHP_METHOD(CairoPatternMesh, setCornerColorRgba)
{
	cairo_pattern_object *pattern_object;
	long corner_num;
	double red, green, blue, alpha;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "ldddd", &corner_num,
									&red, &green, &blue, &alpha) == FAILURE) {
		return;
	}

	pattern_object = cairo_pattern_object_get(getThis());
	if(!pattern_object) {
		return;
	}
	cairo_mesh_pattern_set_corner_color_rgba(pattern_object->pattern, corner_num,
											 red, green, blue, alpha);

	php_cairo_throw_exception(cairo_pattern_status(pattern_object->pattern));
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoPatternMesh_getPatchCount_args, ZEND_SEND_BY_VAL)
ZEND_END_ARG_INFO()

/* {{{  proto void Mesh->getPatchCount()
   Gets the path for a mesh pattern */
PHP_METHOD(CairoPatternMesh, getPatchCount)
{
	cairo_pattern_object *pattern_object;
	cairo_status_t status;
	unsigned int count;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}

	pattern_object = cairo_pattern_object_get(getThis());
	if(!pattern_object) {
		return;
	}
	status = cairo_mesh_pattern_get_patch_count(pattern_object->pattern, &count);
	RETURN_LONG(count);
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoPatternMesh_getPath_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, patch_num)
ZEND_END_ARG_INFO()

/* {{{  proto void Mesh->getPath()
   Gets the path for a mesh pattern */
PHP_METHOD(CairoPatternMesh, getPath)
{
	cairo_pattern_object *pattern_object;
	long patch_num;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "l", &patch_num) == FAILURE) {
		return;
	}

	pattern_object = cairo_pattern_object_get(getThis());
	if(!pattern_object) {
		return;
	}
	cairo_mesh_pattern_get_path(pattern_object->pattern, patch_num);

	// TODO: create a path object once we have one
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoPatternMesh_getControlPoint_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, patch_num)
	ZEND_ARG_INFO(0, point_num)
ZEND_END_ARG_INFO()

/* {{{  proto void Mesh->getControlPoint()
   Gets the control point of patch number for a mesh pattern */
PHP_METHOD(CairoPatternMesh, getControlPoint)
{
	cairo_pattern_object *pattern_object;
	long patch_num, point_num;
	double x, y;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "ll", &patch_num, &point_num) == FAILURE) {
		return;
	}

	pattern_object = cairo_pattern_object_get(getThis());
	if(!pattern_object) {
		return;
	}
	cairo_mesh_pattern_get_control_point(pattern_object->pattern, patch_num, point_num,
											 &x, &y);

	array_init(return_value);
	add_assoc_double(return_value, "x", x);
	add_assoc_double(return_value, "y", y);
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoPatternMesh_getCornerColorRgba_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, patch_num)
	ZEND_ARG_INFO(0, corner_num)
ZEND_END_ARG_INFO()

/* {{{  proto void Mesh->getPoints()
   Gets the color information in corner of path for a mesh pattern */
PHP_METHOD(CairoPatternMesh, getCornerColorRgba)
{
	cairo_pattern_object *pattern_object;
	long patch_num, corner_num;
	double red, green, blue, alpha;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "ll", &patch_num, &corner_num) == FAILURE) {
		return;
	}

	pattern_object = cairo_pattern_object_get(getThis());
	if(!pattern_object) {
		return;
	}
	cairo_mesh_pattern_get_corner_color_rgba(pattern_object->pattern, patch_num, corner_num,
											 &red, &green, &blue, &alpha);

	array_init(return_value);
	add_assoc_double(return_value, "red", red);
	add_assoc_double(return_value, "green", green);
	add_assoc_double(return_value, "blue", blue);
	add_assoc_double(return_value, "alpha", alpha);
}
/* }}} */

/* ----------------------------------------------------------------
    Cairo\Pattern\RasterSource Class API
------------------------------------------------------------------ */

ZEND_BEGIN_ARG_INFO(CairoPatternRasterSource___construct_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, target)
	ZEND_ARG_INFO(0, width)
	ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()

/* {{{ proto void contruct(enum Cairo\Content, int width, int height)
	Returns new Cairo\Pattern\RasterSource using supplied surface */
PHP_METHOD(CairoPatternRasterSource, __construct)
{
	cairo_pattern_object *pattern_object;
	long width, height, content;

	// TODO: fix parsing for enum when it exists
	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "lll", &content, &width, &height) == FAILURE) {
		return;
	}

	pattern_object = Z_CAIRO_PATTERN_P(getThis());
	if(!pattern_object) {
		return;
	}

	// TODO: create callbacks in C that feed to php methods as callbacks
	// register them all, and do the create
	// also figure out callback data - varargs?
	php_cairo_throw_exception(cairo_pattern_status(pattern_object->pattern));
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoPatternRasterSource_acquire_args, ZEND_SEND_BY_VAL)
  ZEND_ARG_OBJ_INFO(0, target, Cairo\\Surface, 0)
  ZEND_ARG_INFO(0, extents)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoPatternRasterSource_release_args, ZEND_SEND_BY_VAL)
  ZEND_ARG_OBJ_INFO(0, surface, Cairo\\Surface, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoPatternRasterSource_snapshot_args, ZEND_SEND_BY_VAL)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoPatternRasterSource_copy_args, ZEND_SEND_BY_VAL)
  ZEND_ARG_OBJ_INFO(0, pattern, Cairo\\Pattern, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoPatternRasterSource_finish_args, ZEND_SEND_BY_VAL)
ZEND_END_ARG_INFO()

/* ----------------------------------------------------------------
    Cairo\Pattern Object management
------------------------------------------------------------------*/

/* {{{ */
static void cairo_pattern_free_obj(zend_object *object)
{
	cairo_pattern_object *intern = cairo_pattern_fetch_object(object);

	if(!intern) {
		return;
	}

	if(intern->pattern){
		cairo_pattern_destroy(intern->pattern);
	}
	intern->pattern = NULL;

	zend_object_std_dtor(&intern->std);
}
/* }}} */

/* {{{ */
static zend_object* cairo_pattern_obj_ctor(zend_class_entry *ce, cairo_pattern_object **intern)
{
	cairo_pattern_object *object = ecalloc(1, sizeof(cairo_pattern_object) + zend_object_properties_size(ce));
	object->pattern = NULL;

	zend_object_std_init(&object->std, ce);
	object->std.handlers = &cairo_pattern_object_handlers;
	*intern = object;

	return &object->std;
}
/* }}} */

/* {{{ */
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

/* {{{ cairo_pattern_methods[] */
const zend_function_entry cairo_pattern_methods[] = {
	PHP_ME(CairoPattern, __construct, CairoPattern___construct_args, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(CairoPattern, getType, CairoPattern_getType_args, ZEND_ACC_PUBLIC)
	PHP_ME(CairoPattern, getStatus, CairoPattern_getStatus_args, ZEND_ACC_PUBLIC)
	PHP_ME(CairoPattern, getMatrix, CairoPattern_getMatrix_args, ZEND_ACC_PUBLIC)
	PHP_ME(CairoPattern, setMatrix, CairoPattern_setMatrix_args, ZEND_ACC_PUBLIC)
	PHP_ME(CairoPattern, getExtend, CairoPattern_getExtend_args, ZEND_ACC_PUBLIC)
	PHP_ME(CairoPattern, setExtend, CairoPattern_setExtend_args, ZEND_ACC_PUBLIC)
	PHP_ME(CairoPattern, getFilter, CairoPattern_getFilter_args, ZEND_ACC_PUBLIC)
	PHP_ME(CairoPattern, setFilter, CairoPattern_setFilter_args, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};
/* }}} 

/* {{{ cairo_pattern_solid_methods[] */
const zend_function_entry cairo_pattern_solid_methods[] = {
	PHP_ME(CairoPatternSolid, __construct, CairoPatternSolid___construct_args, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(CairoPatternSolid, getRgba, CairoPatternSolid_getRgba_args, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};
/* }}} */

/* {{{ cairo_pattern_gradient_methods[] */
const zend_function_entry cairo_pattern_gradient_methods[] = {
	PHP_ME(CairoPatternGradient, addColorStopRgb, CairoPatternGradient_addColorStopRgb_args, ZEND_ACC_PUBLIC)
	PHP_ME(CairoPatternGradient, addColorStopRgba, CairoPatternGradient_addColorStopRgba_args, ZEND_ACC_PUBLIC)
	PHP_ME(CairoPatternGradient, getColorStopRgba, CairoPatternGradient_getColorStopRgba_args, ZEND_ACC_PUBLIC)
	PHP_ME(CairoPatternGradient, getColorStopCount, CairoPatternGradient_getColorStopCount_args, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};
/* }}} */

/* {{{ cairo_pattern_gradient_radial_methods[] */
const zend_function_entry cairo_pattern_gradient_radial_methods[] = {
	PHP_ME(CairoPatternGradientRadial, __construct, CairoPatternGradientRadial___construct_args, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(CairoPatternGradientRadial, getCircles, CairoPatternGradientRadial_getCircles_args, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};
/* }}} */

/* {{{ cairo_pattern_gradient_linear_methods[] */
const zend_function_entry cairo_pattern_gradient_linear_methods[] = {
	PHP_ME(CairoPatternGradientLinear, __construct, CairoPatternGradientLinear___construct_args, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(CairoPatternGradientLinear, getPoints, CairoPatternGradientLinear_getPoints_args, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};
/* }}} */

/* {{{ cairo_pattern_surface_methods[] */
const zend_function_entry cairo_pattern_surface_methods[] = {
	PHP_ME(CairoPatternSurface, __construct, CairoPatternSurface___construct_args, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(CairoPatternSurface, getSurface, CairoPatternSurface_getSurface_args, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};
/* }}} */

/* {{{ cairo_pattern_mesh_methods[] */
const zend_function_entry cairo_pattern_mesh_methods[] = {
	PHP_ME(CairoPatternMesh, __construct, CairoPatternMesh___construct_args, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(CairoPatternMesh, beginPatch, CairoPatternMesh_beginPatch_args, ZEND_ACC_PUBLIC)
	PHP_ME(CairoPatternMesh, endPatch, CairoPatternMesh_endPatch_args, ZEND_ACC_PUBLIC)
	PHP_ME(CairoPatternMesh, moveTo, CairoPatternMesh_moveTo_args, ZEND_ACC_PUBLIC)
	PHP_ME(CairoPatternMesh, lineTo, CairoPatternMesh_lineTo_args, ZEND_ACC_PUBLIC)
	PHP_ME(CairoPatternMesh, curveTo, CairoPatternMesh_curveTo_args, ZEND_ACC_PUBLIC)
	PHP_ME(CairoPatternMesh, setControlPoint, CairoPatternMesh_setControlPoint_args, ZEND_ACC_PUBLIC)
	PHP_ME(CairoPatternMesh, setCornerColorRgb, CairoPatternMesh_setCornerColorRgb_args, ZEND_ACC_PUBLIC)
	PHP_ME(CairoPatternMesh, setCornerColorRgba, CairoPatternMesh_setCornerColorRgba_args, ZEND_ACC_PUBLIC)
	PHP_ME(CairoPatternMesh, getPatchCount, CairoPatternMesh_getPatchCount_args, ZEND_ACC_PUBLIC)
	PHP_ME(CairoPatternMesh, getPath, CairoPatternMesh_getPath_args, ZEND_ACC_PUBLIC)
	PHP_ME(CairoPatternMesh, getControlPoint, CairoPatternMesh_getControlPoint_args, ZEND_ACC_PUBLIC)
	PHP_ME(CairoPatternMesh, getCornerColorRgba, CairoPatternMesh_getCornerColorRgba_args, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};
/* }}} */

/* {{{ cairo_pattern_raster_methods[] */
const zend_function_entry cairo_pattern_raster_methods[] = {
	PHP_ME(CairoPatternRasterSource, __construct, CairoPatternRasterSource___construct_args, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ABSTRACT_ME(CairoPatternRasterSource, acquire, CairoPatternRasterSource_acquire_args)
	PHP_ABSTRACT_ME(CairoPatternRasterSource, release, CairoPatternRasterSource_release_args)
	PHP_ABSTRACT_ME(CairoPatternRasterSource, snapshot, CairoPatternRasterSource_snapshot_args)
	PHP_ABSTRACT_ME(CairoPatternRasterSource, copy, CairoPatternRasterSource_copy_args)
	PHP_ABSTRACT_ME(CairoPatternRasterSource, finish, CairoPatternRasterSource_finish_args)
	ZEND_FE_END
};
/* }}} */

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(cairo_pattern)
{
	zend_class_entry 	pattern_ce,
						gradient_ce,
						solid_ce,
						linear_ce,
						radial_ce,
						surface_ce,
						mesh_ce,
						raster_ce,
						pattern_type_ce,
						extend_ce,
						filter_ce;

	memcpy(&cairo_pattern_object_handlers,
		   zend_get_std_object_handlers(),
		   sizeof(zend_object_handlers));

	cairo_pattern_object_handlers.offset = XtOffsetOf(cairo_pattern_object, std);
	cairo_pattern_object_handlers.free_obj = cairo_pattern_free_obj;

	INIT_NS_CLASS_ENTRY(pattern_ce, CAIRO_NAMESPACE, "Pattern", cairo_pattern_methods);
	ce_cairo_pattern = zend_register_internal_class(&pattern_ce);
	ce_cairo_pattern->create_object = cairo_pattern_create_object;
	ce_cairo_pattern->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS;

	INIT_NS_CLASS_ENTRY(solid_ce, CAIRO_NAMESPACE, ZEND_NS_NAME("Pattern", "Solid"), cairo_pattern_solid_methods);
	ce_cairo_pattern_solid = zend_register_internal_class_ex(&solid_ce, ce_cairo_pattern);

	INIT_NS_CLASS_ENTRY(gradient_ce, CAIRO_NAMESPACE, ZEND_NS_NAME("Pattern", "Gradient"), cairo_pattern_gradient_methods);
	ce_cairo_pattern_gradient = zend_register_internal_class_ex(&gradient_ce, ce_cairo_pattern);
	ce_cairo_pattern_gradient->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS;

	INIT_NS_CLASS_ENTRY(radial_ce, CAIRO_NAMESPACE,
		ZEND_NS_NAME("Pattern",  ZEND_NS_NAME("Gradient", "Radial")),
		cairo_pattern_gradient_radial_methods);
	ce_cairo_pattern_gradient_radial = zend_register_internal_class_ex(&radial_ce, ce_cairo_pattern_gradient);

	INIT_NS_CLASS_ENTRY(linear_ce, CAIRO_NAMESPACE,
		ZEND_NS_NAME("Pattern",  ZEND_NS_NAME("Gradient", "Linear")),
		cairo_pattern_gradient_linear_methods);
	ce_cairo_pattern_gradient_linear = zend_register_internal_class_ex(&linear_ce, ce_cairo_pattern_gradient);

	INIT_NS_CLASS_ENTRY(surface_ce, CAIRO_NAMESPACE, ZEND_NS_NAME("Pattern", "Surface"), cairo_pattern_surface_methods);
	ce_cairo_pattern_surface = zend_register_internal_class_ex(&surface_ce, ce_cairo_pattern);

	INIT_NS_CLASS_ENTRY(mesh_ce, CAIRO_NAMESPACE, ZEND_NS_NAME("Pattern", "Mesh"), cairo_pattern_mesh_methods);
	ce_cairo_pattern_mesh = zend_register_internal_class_ex(&mesh_ce, ce_cairo_pattern);

	INIT_NS_CLASS_ENTRY(raster_ce, CAIRO_NAMESPACE, ZEND_NS_NAME("Pattern", "RasterSource"), cairo_pattern_raster_methods);
	ce_cairo_pattern_raster = zend_register_internal_class_ex(&raster_ce, ce_cairo_pattern);

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
