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

#include "php_cairo.h"
#include "php_cairo_internal.h"

zend_class_entry *ce_cairo_matrix;
static zend_object_handlers cairo_matrix_object_handlers; 

typedef struct _cairo_matrix_object {
	cairo_matrix_t *matrix;
	zend_object std;
} cairo_matrix_object;

#define CAIRO_MATRIX_FETCH_OBJ(zv) ((cairo_matrix_object*) \
	(((char*)Z_OBJ_P(zv)) - XtOffsetOf(cairo_matrix_object, std)))

#define CAIRO_ALLOC_MATRIX(matrix_value) if (!matrix_value) \
	{ matrix_value = ecalloc(sizeof(cairo_matrix_t), 1); }

#define CAIRO_VALUE_FROM_STRUCT(n,m)         \
	if(strcmp(Z_STRVAL_P(member), m) == 0) { \
		value = matrix->matrix->n;           \
		break;                               \
	}

#define CAIRO_VALUE_TO_STRUCT(n,m)                  \
	if(strcmp(Z_STRVAL_P(member), m) == 0) {        \
		matrix->matrix->n = zval_get_double(value); \
		break;                                      \
	}

#define CAIRO_ADD_STRUCT_VALUE(n,m)                  \
	ZVAL_DOUBLE(&tmp, matrix->matrix->n);            \
	zend_hash_str_update(props, m, sizeof(m)-1, &tmp);

/* ----------------------------------------------------------------
    Cairo\Matrix Class API
------------------------------------------------------------------*/

ZEND_BEGIN_ARG_INFO_EX(CairoMatrix____construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
	ZEND_ARG_INFO(0, yx)
	ZEND_ARG_INFO(0, xy)
	ZEND_ARG_INFO(0, yy)
	ZEND_ARG_INFO(0, x0)
	ZEND_ARG_INFO(0, y0)
ZEND_END_ARG_INFO()

/* {{{ proto void __construct([float xx, float yx, float xy, float yy, float x0, float y0])
	CairoMatrix is used throughout cairo to convert between different coordinate
	spaces. A CairoMatrix holds an affine transformation, such as a scale, rotation,
	shear, or a combination of these */
PHP_METHOD(CairoMatrix, __construct)
{
	double xx = 1.0, yx = 0.0, xy = 0.0, yy = 1.0, x0 = 0.0, y0 = 0.0;
	cairo_matrix_object *matrix_object;

	PHP_CAIRO_EXCEPTIONS();
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "|dddddd", &xx, &yx, &xy, &yy, &x0, &y0) == FAILURE) {
		PHP_CAIRO_RESTORE();
		return;
	}
	PHP_CAIRO_RESTORE();

	matrix_object = CAIRO_MATRIX_FETCH_OBJ(getThis());
	CAIRO_ALLOC_MATRIX(matrix_object->matrix);

	cairo_matrix_init(matrix_object->matrix, xx, yx, xy, yy, x0, y0);
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoMatrix_initIdentity_args, ZEND_SEND_BY_VAL)
ZEND_END_ARG_INFO()

/* {{{ proto object CairoMatrix::initIdentity()
       Create initialized matrix to be an identity transformation. */
PHP_METHOD(CairoMatrix, initIdentity)
{
	cairo_matrix_object *matrix_object;

	PHP_CAIRO_EXCEPTIONS();
	if (zend_parse_parameters_none() == FAILURE) {
		PHP_CAIRO_RESTORE();
		return;
	}
	PHP_CAIRO_RESTORE();

	object_init_ex(return_value, ce_cairo_matrix);
	matrix_object = CAIRO_MATRIX_FETCH_OBJ(return_value);
	CAIRO_ALLOC_MATRIX(matrix_object->matrix);

	cairo_matrix_init_identity(matrix_object->matrix);
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoMatrix_initTranslate_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, tx)
	ZEND_ARG_INFO(0, ty)
ZEND_END_ARG_INFO()

/* {{{ proto object CairoMatrix::initTranslate(float tx, float ty)
       Create initialized matrix to a transformation that translates by
       tx and ty in the X and Y dimensions, respectively. */
PHP_METHOD(CairoMatrix, initTranslate)
{
	double tx = 0.0, ty = 0.0;
	cairo_matrix_object *matrix_object;

	PHP_CAIRO_EXCEPTIONS();
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "dd", &tx, &ty) == FAILURE) {
		PHP_CAIRO_RESTORE();
		return;
	}
	PHP_CAIRO_RESTORE();

	object_init_ex(return_value, ce_cairo_matrix);
	matrix_object = CAIRO_MATRIX_FETCH_OBJ(return_value);
	CAIRO_ALLOC_MATRIX(matrix_object->matrix);

	cairo_matrix_init_translate(matrix_object->matrix, tx, ty);
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoMatrix_initScale_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, sx)
	ZEND_ARG_INFO(0, sy)
ZEND_END_ARG_INFO()

/* {{{ proto object CairoMatrix::initScale(float sx, float sy)
       Create initialized matrix to a transformation that scales
       by sx and sy in the X and Y dimensions, respectively. */
PHP_METHOD(CairoMatrix, initScale)
{
	double sx = 0.0, sy = 0.0;
	cairo_matrix_object *matrix_object;

	PHP_CAIRO_EXCEPTIONS();
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "dd", &sx, &sy) == FAILURE) {
		PHP_CAIRO_RESTORE();
		return;
	}
	PHP_CAIRO_RESTORE();

	object_init_ex(return_value, ce_cairo_matrix);
	matrix_object = CAIRO_MATRIX_FETCH_OBJ(return_value);
	CAIRO_ALLOC_MATRIX(matrix_object->matrix);

	cairo_matrix_init_scale(matrix_object->matrix, sx, sy);
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoMatrix_initRotate_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, radians)
ZEND_END_ARG_INFO()

/* {{{ proto object CairoMatrix::initRotate(float radians)
       Create initialized matrix to a transformation that rotates by radians. */
PHP_METHOD(CairoMatrix, initRotate)
{
	double radians = 0.0;
	cairo_matrix_object *matrix_object;

	PHP_CAIRO_EXCEPTIONS();
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "d", &radians) == FAILURE) {
		PHP_CAIRO_RESTORE();
		return;
	}
	PHP_CAIRO_RESTORE();

	object_init_ex(return_value, ce_cairo_matrix);
	matrix_object = CAIRO_MATRIX_FETCH_OBJ(return_value);
	CAIRO_ALLOC_MATRIX(matrix_object->matrix);

	cairo_matrix_init_rotate(matrix_object->matrix, radians);
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoMatrix_translate_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, tx)
	ZEND_ARG_INFO(0, ty)
ZEND_END_ARG_INFO()

/* {{{ proto void CairoMatrix->translate(float tx, float ty)
    Applies a translation to the transformation. The effect of the new transformation
    is to first translate the coordinates by tx and ty, then apply the original
    transformation to the coordinates. */
PHP_METHOD(CairoMatrix, translate)
{
	double tx = 0.0, ty = 0.0;
	cairo_matrix_object *matrix_object;

	PHP_CAIRO_EXCEPTIONS();
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "dd", &tx, &ty) == FAILURE) {
		PHP_CAIRO_RESTORE();
		return;
	}
	PHP_CAIRO_RESTORE();

	matrix_object = CAIRO_MATRIX_FETCH_OBJ(getThis());
	cairo_matrix_translate(matrix_object->matrix, tx, ty);
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoMatrix_scale_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, sx)
	ZEND_ARG_INFO(0, sy)
ZEND_END_ARG_INFO()

/* {{{ proto void CairoMatrix->scale(float sx, float sy)
       Applies scaling by sx, sy to the transformation in matrix. The effect of
       the new transformation is to first scale the coordinates by sx and sy, then apply
       the original transformation to the coordinates. */
PHP_METHOD(CairoMatrix, scale)
{
	double sx = 0.0, sy = 0.0;
	cairo_matrix_object *matrix_object;

	PHP_CAIRO_EXCEPTIONS();
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "dd", &sx, &sy) == FAILURE) {
		PHP_CAIRO_RESTORE();
		return;
	}
	PHP_CAIRO_RESTORE();

	matrix_object = CAIRO_MATRIX_FETCH_OBJ(getThis());
	cairo_matrix_scale(matrix_object->matrix, sx, sy);
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoMatrix_rotate_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, radians)
ZEND_END_ARG_INFO()

/* {{{ proto void CairoMatrix->rotate(float radians)
       Applies rotation by radians to the transformation in matrix. The effect of the new
       transformation is to first rotate the coordinates by radians, then
       apply the original transformation to the coordinates. */
PHP_METHOD(CairoMatrix, rotate)
{
	double radians = 0.0;
	cairo_matrix_object *matrix_object;

	PHP_CAIRO_EXCEPTIONS();
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "d", &radians) == FAILURE) {
		PHP_CAIRO_RESTORE();
		return;
	}
	PHP_CAIRO_RESTORE();

	matrix_object = CAIRO_MATRIX_FETCH_OBJ(getThis());
	cairo_matrix_rotate(matrix_object->matrix, radians);
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoMatrix_invert_args, ZEND_SEND_BY_VAL)
ZEND_END_ARG_INFO()

/* {{{ proto void CairoMatrix->invert()
       Changes matrix to be the inverse of it's original value. Not all transformation
       matrices have inverses; if the matrix collapses points together (it is degenerate),
       then it has no inverse and this function will fail. */
PHP_METHOD(CairoMatrix, invert)
{
	cairo_status_t status;
	cairo_matrix_object *matrix_object;

    PHP_CAIRO_EXCEPTIONS();
	if (zend_parse_parameters_none() == FAILURE) {
		PHP_CAIRO_RESTORE();
		return;
	}
	PHP_CAIRO_RESTORE();

	matrix_object = CAIRO_MATRIX_FETCH_OBJ(getThis());
	status = cairo_matrix_invert(matrix_object->matrix);
	php_cairo_throw_exception(status);
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoMatrix_multiply_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, matrix1)
	ZEND_ARG_INFO(0, matrix2)
ZEND_END_ARG_INFO()

/* {{{ proto CairoMatrix CairoMatrix::multiply(CairoMatrix matrix1, CairoMatrix matrix2)
       Multiplies the affine transformations in two matrices together and returns the result */
PHP_METHOD(CairoMatrix, multiply)
{
	zval *matrix1 = NULL, *matrix2 = NULL;
	cairo_matrix_object *matrix_object, *matrix_object1, *matrix_object2;

	PHP_CAIRO_EXCEPTIONS();
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "OO", &matrix1, ce_cairo_matrix, &matrix2, ce_cairo_matrix) == FAILURE) {
		PHP_CAIRO_RESTORE();
		return;
	}
	PHP_CAIRO_RESTORE();

	object_init_ex(return_value, ce_cairo_matrix);
	matrix_object = CAIRO_MATRIX_FETCH_OBJ(return_value);
	CAIRO_ALLOC_MATRIX(matrix_object->matrix);

	matrix_object1 = CAIRO_MATRIX_FETCH_OBJ(matrix1);
	matrix_object2 = CAIRO_MATRIX_FETCH_OBJ(matrix2);

	cairo_matrix_multiply(matrix_object->matrix, matrix_object1->matrix, matrix_object2->matrix);
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoMatrix_transform_args, ZEND_SEND_BY_VAL)
  ZEND_ARG_INFO(0, dx)
  ZEND_ARG_INFO(0, dy)
ZEND_END_ARG_INFO()

/* {{{ proto array CairoMatrix->transformDistance(float dx, float dy)
       Transforms the distance vector (dx,dy) by matrix. This is similar to transform point
       except that the translation components of the transformation are ignored */
PHP_METHOD(CairoMatrix, transformDistance)
{
	double dx = 0.0, dy = 0.0;
	cairo_matrix_object *matrix_object;

	PHP_CAIRO_EXCEPTIONS();
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "dd", &dx, &dy) == FAILURE) {
		PHP_CAIRO_RESTORE();
		return;
	}
	PHP_CAIRO_RESTORE();

	matrix_object = CAIRO_MATRIX_FETCH_OBJ(getThis());
	cairo_matrix_transform_distance(matrix_object->matrix, &dx, &dy);

	array_init(return_value);
	add_assoc_double(return_value, "x", dx);
	add_assoc_double(return_value, "y", dy);
}
/* }}} */

/* {{{ proto array CairoMatrix->transformPoint(float x, float y)
       Transforms the point (x, y) by matrix. */
PHP_METHOD(CairoMatrix, transformPoint)
{
	double x = 0.0, y = 0.0;
	cairo_matrix_object *matrix_object;

	PHP_CAIRO_EXCEPTIONS();
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "dd", &x, &y) == FAILURE) {
		PHP_CAIRO_RESTORE();
		return;
	}
	PHP_CAIRO_RESTORE();

	matrix_object = CAIRO_MATRIX_FETCH_OBJ(getThis());
	cairo_matrix_transform_point(matrix_object->matrix, &x, &y);

	array_init(return_value);
	add_assoc_double(return_value, "x", x);
	add_assoc_double(return_value, "y", y);
}
/* }}} */

/* ----------------------------------------------------------------
    Cairo\Matrix Object management
------------------------------------------------------------------*/

/* {{{ */
static void cairo_matrix_free_storage(zend_object *object)
{
	cairo_matrix_object *intern = (cairo_matrix_object*) ((char*)object - XtOffsetOf(cairo_matrix_object, std));

	if(!intern) {
		return;
	}

	if(intern->matrix) {
		efree(intern->matrix);
	}
	intern->matrix = NULL;

	zend_object_std_dtor(&intern->std);
}
/* }}} */

/* {{{ */
static zend_object* cairo_matrix_obj_ctor(zend_class_entry *ce, cairo_matrix_object **pmatrix)
{
	cairo_matrix_object *object = ecalloc(1, sizeof(cairo_matrix_object) + zend_object_properties_size(ce));
	object->matrix = NULL;

	zend_object_std_init(&object->std, ce);
	object->std.handlers = &cairo_matrix_object_handlers;
	*pmatrix = object;

	return &object->std;
}
/* }}} */

/* {{{ */
static zend_object* cairo_matrix_object_new(zend_class_entry *ce)
{
	cairo_matrix_object *matrix = NULL;
	zend_object *return_value = cairo_matrix_obj_ctor(ce, &matrix);

	object_properties_init(&(matrix->std), ce);
	return return_value;
}
/* }}} */

/* {{{ */
static zend_object* cairo_matrix_object_clone(zval *this_zval) 
{
	cairo_matrix_object *new_matrix;
	cairo_matrix_object *old_matrix = CAIRO_MATRIX_FETCH_OBJ(this_zval);
	zend_object *return_value = cairo_matrix_obj_ctor(Z_OBJCE_P(this_zval), &new_matrix);
	CAIRO_ALLOC_MATRIX(new_matrix->matrix);

	cairo_matrix_init(new_matrix->matrix, old_matrix->matrix->xx, old_matrix->matrix->yx, old_matrix->matrix->xy,
		old_matrix->matrix->yy, old_matrix->matrix->x0, old_matrix->matrix->y0);

	zend_objects_clone_members(&new_matrix->std, &old_matrix->std);

	return return_value;
}
/* }}} */

/* {{{ */
static zval *cairo_matrix_object_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv)
{
	zval *retval;
	zval tmp_member;
	double value;
	cairo_matrix_object *matrix = CAIRO_MATRIX_FETCH_OBJ(object);

	if(Z_TYPE_P(member) != IS_STRING) { \
		tmp_member = *member; \
		zval_copy_ctor(&tmp_member); \
		convert_to_string(&tmp_member); \
		member = &tmp_member; \
		cache_slot = NULL; \
	}

	do {
		CAIRO_VALUE_FROM_STRUCT(xx,"xx");
		CAIRO_VALUE_FROM_STRUCT(xy,"xy");
		CAIRO_VALUE_FROM_STRUCT(x0,"x0");
		CAIRO_VALUE_FROM_STRUCT(yx,"yx");
		CAIRO_VALUE_FROM_STRUCT(yy,"yy");
		CAIRO_VALUE_FROM_STRUCT(y0,"y0");

		/* not a struct member */
		retval = (zend_get_std_object_handlers())->read_property(object, member, type, cache_slot, rv);

		if(member == &tmp_member) {
			zval_dtor(member);
		}

		return retval;
	} while(0);

	retval = rv;
	ZVAL_DOUBLE(retval, value);

	if(member == &tmp_member) {
		zval_dtor(member);
	}

	return retval;
}
/* }}} */

/* {{{ */
static void cairo_matrix_object_write_property(zval *object, zval *member, zval *value, void **cache_slot)
{
	zval tmp_member;
	cairo_matrix_object *matrix = CAIRO_MATRIX_FETCH_OBJ(object);

	if(Z_TYPE_P(member) != IS_STRING) { \
		tmp_member = *member; \
		zval_copy_ctor(&tmp_member); \
		convert_to_string(&tmp_member); \
		member = &tmp_member; \
		cache_slot = NULL; \
	}

	do {
		CAIRO_VALUE_TO_STRUCT(xx,"xx");
		CAIRO_VALUE_TO_STRUCT(xy,"xy");
		CAIRO_VALUE_TO_STRUCT(x0,"x0");
		CAIRO_VALUE_TO_STRUCT(yx,"yx");
		CAIRO_VALUE_TO_STRUCT(yy,"yy");
		CAIRO_VALUE_TO_STRUCT(y0,"y0");

		/* not a struct member */
		(zend_get_std_object_handlers())->write_property(object, member, value, cache_slot);
	} while(0);

	if(member == &tmp_member) {
		zval_dtor(member);
	}
}
/* }}} */

/* {{{ */
static HashTable *cairo_matrix_object_get_properties(zval *object) 
{
	HashTable *props;
	zval tmp;
	cairo_matrix_object *matrix = CAIRO_MATRIX_FETCH_OBJ(object);

	props = zend_std_get_properties(object);

	if(!matrix->matrix) {
		return props;
	}

	CAIRO_ADD_STRUCT_VALUE(xx, "xx");
	CAIRO_ADD_STRUCT_VALUE(xy, "xy");
	CAIRO_ADD_STRUCT_VALUE(x0, "x0");
	CAIRO_ADD_STRUCT_VALUE(yx, "yx");
	CAIRO_ADD_STRUCT_VALUE(yy, "yy");
	CAIRO_ADD_STRUCT_VALUE(y0, "y0");

	return props;
}
/* }}} */

/* ----------------------------------------------------------------
    Cairo\Matrix Definition and registration
------------------------------------------------------------------*/

/* {{{ cairo_matrix_methods[] */
const zend_function_entry cairo_matrix_methods[] = {
	PHP_ME(CairoMatrix, __construct, CairoMatrix____construct_args, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(CairoMatrix, initIdentity, CairoMatrix_initIdentity_args, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(CairoMatrix, initTranslate, CairoMatrix_initTranslate_args, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(CairoMatrix, initScale, CairoMatrix_initScale_args, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(CairoMatrix, initRotate, CairoMatrix_initRotate_args, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(CairoMatrix, translate, CairoMatrix_translate_args, ZEND_ACC_PUBLIC)
	PHP_ME(CairoMatrix, scale, CairoMatrix_scale_args, ZEND_ACC_PUBLIC)
	PHP_ME(CairoMatrix, rotate, CairoMatrix_rotate_args, ZEND_ACC_PUBLIC)
	PHP_ME(CairoMatrix, invert, CairoMatrix_invert_args, ZEND_ACC_PUBLIC)
	PHP_ME(CairoMatrix, multiply, CairoMatrix_multiply_args, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(CairoMatrix, transformDistance, CairoMatrix_transform_args, ZEND_ACC_PUBLIC)
	PHP_ME(CairoMatrix, transformPoint, CairoMatrix_transform_args, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};
/* }}} */

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(cairo_matrix)
{
	zend_class_entry ce;

	memcpy(&cairo_matrix_object_handlers,
		   zend_get_std_object_handlers(),
		   sizeof(zend_object_handlers));

	cairo_matrix_object_handlers.offset = XtOffsetOf(cairo_matrix_object, std);
	cairo_matrix_object_handlers.free_obj = cairo_matrix_free_storage;
	cairo_matrix_object_handlers.clone_obj = cairo_matrix_object_clone;
	cairo_matrix_object_handlers.read_property = cairo_matrix_object_read_property;
	cairo_matrix_object_handlers.write_property = cairo_matrix_object_write_property;
	cairo_matrix_object_handlers.get_property_ptr_ptr = NULL;
	cairo_matrix_object_handlers.get_properties = cairo_matrix_object_get_properties;

	INIT_NS_CLASS_ENTRY(ce,  CAIRO_NAMESPACE, "Matrix", cairo_matrix_methods);
	ce.create_object = cairo_matrix_object_new;
	ce_cairo_matrix = zend_register_internal_class(&ce);

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
