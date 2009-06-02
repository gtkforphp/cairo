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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <cairo.h>

#include "php.h"
#include "php_cairo.h"

#define ALLOCATE_MATRIX(matrix_value) if (!matrix_value) { matrix_value = ecalloc(sizeof(cairo_matrix_t), 1); }

zend_class_entry *cairo_ce_cairomatrix;

ZEND_BEGIN_ARG_INFO_EX(CairoMatrix____construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
  ZEND_ARG_INFO(0, yx)
  ZEND_ARG_INFO(0, xy)
  ZEND_ARG_INFO(0, yy)
  ZEND_ARG_INFO(0, x0)
  ZEND_ARG_INFO(0, y0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(CairoMatrix_translate_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, tx)
  ZEND_ARG_INFO(0, ty)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(CairoMatrix_scale_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, sx)
  ZEND_ARG_INFO(0, sy)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(CairoMatrix_rotate_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, radians)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(CairoMatrix_multiply_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_OBJ_INFO(0, matrix1, CairoMatrix, 1)
  ZEND_ARG_OBJ_INFO(0, matrix2, CairoMatrix, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(CairoMatrix_transform_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, dx)
  ZEND_ARG_INFO(0, dy)
ZEND_END_ARG_INFO()

/* {{{ proto CairoMatrix cairo_matrix_init([float xx, float yx, float xy, float yy, float x0, float y0])
   Returns new CairoMatrix object which is used throughout cairo to convert between different coordinate spaces */
PHP_FUNCTION(cairo_matrix_init)
{
	double xx = 1.0, yx = 0.0, xy = 0.0, yy = 1.0, x0 = 0.0, y0 = 0.0;
	cairo_matrix_object *matrix_object;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|dddddd", &xx, &yx, &xy, &yy, &x0, &y0) == FAILURE) {
		return;
	}

	object_init_ex(return_value, cairo_ce_cairomatrix);
	matrix_object = (cairo_matrix_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	ALLOCATE_MATRIX(matrix_object->matrix);

	cairo_matrix_init(matrix_object->matrix, xx, yx, xy, yy, x0, y0);
}
/* }}} */

/* {{{ proto void construct([float xx, float yx, float xy, float yy, float x0, float y0])
   CairoMatrix is used throughout cairo to convert between different coordinate spaces. 
   A CairoMatrix holds an affinetransformation, such as a scale, rotation, shear, or a combination of these */
PHP_METHOD(CairoMatrix, __construct)
{
	double xx = 1.0, yx = 0.0, xy = 0.0, yy = 1.0, x0 = 0.0, y0 = 0.0;
	cairo_matrix_object *matrix_object;

	PHP_CAIRO_ERROR_TO_EXCEPTION
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|dddddd", &xx, &yx, &xy, &yy, &x0, &y0) == FAILURE) {
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS

	matrix_object = (cairo_matrix_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
	ALLOCATE_MATRIX(matrix_object->matrix);

	cairo_matrix_init(matrix_object->matrix, xx, yx, xy, yy, x0, y0);
}
/* }}} */

/* {{{ proto object cairo_matrix_init_identity()
       proto object CairoMatrix::initIdentity()
	   Create initialized matrix to be an identity transformation.
   */
PHP_FUNCTION(cairo_matrix_init_identity)
{
	cairo_matrix_object *matrix_object;

	PHP_CAIRO_ERROR_HANDLING
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS

	object_init_ex(return_value, cairo_ce_cairomatrix);
	matrix_object = (cairo_matrix_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	ALLOCATE_MATRIX(matrix_object->matrix);

	cairo_matrix_init_identity(matrix_object->matrix);
}
/* }}} */

/* {{{ proto object cairo_matrix_init_translate(float tx, float ty)
       proto object CairoMatrix::initTranslate(float tx, float ty)
	   Create initialized matrix to a transformation that translates by tx and ty in the X and Y dimensions, respectively.
   */
PHP_FUNCTION(cairo_matrix_init_translate)
{
	double tx = 0.0, ty = 0.0;
	cairo_matrix_object *matrix_object;

	PHP_CAIRO_ERROR_HANDLING
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dd", &tx, &ty) == FAILURE) {
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS

	object_init_ex(return_value, cairo_ce_cairomatrix);
	matrix_object = (cairo_matrix_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	ALLOCATE_MATRIX(matrix_object->matrix);

	cairo_matrix_init_translate(matrix_object->matrix, tx, ty);
}
/* }}} */

/* {{{ proto object cairo_matrix_init_scale(float sx, float sy)
       proto object CairoMatrix::initScale(float sx, float sy)
	   Create initialized matrix to a transformation that scales by sx and sy in the X and Y dimensions, respectively.
   */
PHP_FUNCTION(cairo_matrix_init_scale)
{
	double sx = 0.0, sy = 0.0;
	cairo_matrix_object *matrix_object;

	PHP_CAIRO_ERROR_HANDLING
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dd", &sx, &sy) == FAILURE) {
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS

	object_init_ex(return_value, cairo_ce_cairomatrix);
	matrix_object = (cairo_matrix_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	ALLOCATE_MATRIX(matrix_object->matrix);

	cairo_matrix_init_scale(matrix_object->matrix, sx, sy);
}
/* }}} */

/* {{{ proto object cairo_matrix_init_rotate(float radians)
       proto object CairoMatrix::initRotate(float radians)
	   Create initialized matrix to a transformation that rotates by radians.
   */
PHP_FUNCTION(cairo_matrix_init_rotate)
{
	double radians = 0.0;
	cairo_matrix_object *matrix_object;

	PHP_CAIRO_ERROR_HANDLING
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "d", &radians) == FAILURE) {
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS

	object_init_ex(return_value, cairo_ce_cairomatrix);
	matrix_object = (cairo_matrix_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	ALLOCATE_MATRIX(matrix_object->matrix);

	cairo_matrix_init_rotate(matrix_object->matrix, radians);
}
/* }}} */

/* {{{ proto void cairo_matrix_translate(CairoMatrix object, float tx, float ty)
       proto void CairoMatrix::translate(float tx, float ty)
	   Applies a translation to the transformation. The effect of the new transformation
	   is to first translate the coordinates by tx and ty, then apply the original
	   transformation to the coordinates. */
PHP_FUNCTION(cairo_matrix_translate)
{
	zval * matrix_zval = NULL;
	double tx = 0.0, ty = 0.0;
	cairo_matrix_object *matrix_object;

	PHP_CAIRO_ERROR_HANDLING
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odd", &matrix_zval, cairo_ce_cairomatrix, &tx, &ty) == FAILURE) {
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS

	matrix_object = (cairo_matrix_object *)cairo_matrix_object_get(matrix_zval TSRMLS_CC);
	cairo_matrix_translate(matrix_object->matrix, tx, ty);
}
/* }}} */

/* {{{ proto void cairo_matrix_scale(CairoMatrix object, float sx, float sy)
       proto void CairoMatrix::scale(float sx, float sy)
	   Applies scaling by sx, sy to the transformation in matrix. The effect of
	   the new transformation is to first scale the coordinates by sx and sy, then apply
	   the original transformation to the coordinates.
   */
PHP_FUNCTION(cairo_matrix_scale)
{
	zval * matrix_zval = NULL;
	double sx = 0.0, sy = 0.0;
	cairo_matrix_object *matrix_object;

    PHP_CAIRO_ERROR_HANDLING
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odd", &matrix_zval, cairo_ce_cairomatrix, &sx, &sy) == FAILURE) {
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS

	matrix_object = (cairo_matrix_object *)cairo_matrix_object_get(matrix_zval TSRMLS_CC);
	cairo_matrix_scale(matrix_object->matrix, sx, sy);
}
/* }}} */

/* {{{ proto void cairo_matrix_rotate(CairoMatrix object, float radians)
       proto void CairoMatrix::rotate(float radians)
	   Applies rotation by radians to the transformation in matrix. The effect of the new
	   transformation is to first rotate the coordinates by radians, then apply the original transformation to the coordinates.
   */
PHP_FUNCTION(cairo_matrix_rotate)
{
	zval * matrix_zval = NULL;
	double radians = 0.0;
	cairo_matrix_object *matrix_object;

    PHP_CAIRO_ERROR_HANDLING
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Od", &matrix_zval, cairo_ce_cairomatrix, &radians) == FAILURE) {
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS

	matrix_object = (cairo_matrix_object *)cairo_matrix_object_get(matrix_zval TSRMLS_CC);
	cairo_matrix_rotate(matrix_object->matrix, radians);
}
/* }}} */

/* {{{ proto void cairo_matrix_invert(CairoMatrix object)
       proto void CairoMatrix::invert()
	   Changes matrix to be the inverse of it's original value. Not all transformation
	   matrices have inverses; if the matrix collapses points together (it is degenerate),
	   then it has no inverse and this function will fail.
   */
PHP_FUNCTION(cairo_matrix_invert)
{
	zval * matrix_zval = NULL;
	cairo_status_t status;
	cairo_matrix_object *matrix_object;

    PHP_CAIRO_ERROR_HANDLING
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &matrix_zval, cairo_ce_cairomatrix) == FAILURE) {
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS

	matrix_object = (cairo_matrix_object *)cairo_matrix_object_get(matrix_zval TSRMLS_CC);
	status = cairo_matrix_invert(matrix_object->matrix);
	PHP_CAIRO_ERROR(status);
}
/* }}} */

/* {{{ proto void cairo_matrix_multiply(CairoMatrix matrix1, CairoMatrix matrix2)
       proto CairoMatrix CairoMatrix::multiply(CairoMatrix matrix1, CairoMatrix matrix2)
	   Multiplies the affine transformations in two matrices together and returns the result */
PHP_FUNCTION(cairo_matrix_multiply)
{
	zval *matrix1 = NULL, *matrix2 = NULL;
	cairo_matrix_object *matrix_object, *matrix_object1, *matrix_object2;

	PHP_CAIRO_ERROR_HANDLING
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "OO", &matrix1, cairo_ce_cairomatrix, &matrix2, cairo_ce_cairomatrix) == FAILURE) {
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS
	
	object_init_ex(return_value, cairo_ce_cairomatrix);
	matrix_object = (cairo_matrix_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	ALLOCATE_MATRIX(matrix_object->matrix);

	matrix_object1 = (cairo_matrix_object *)cairo_matrix_object_get(matrix1 TSRMLS_CC);
	matrix_object2 = (cairo_matrix_object *)cairo_matrix_object_get(matrix2 TSRMLS_CC);

	cairo_matrix_multiply(matrix_object->matrix, matrix_object1->matrix, matrix_object2->matrix);
}
/* }}} */

/* {{{ proto array cairo_matrix_transform_distance(CairoMatrix object, float dx, float dy)
       proto array CairoMatrix::transformDistance(float dx, float dy)
	   Transforms the distance vector (dx,dy) by matrix. This is similar to transform point
	   except that the translation components of the transformation are ignored
   */
PHP_FUNCTION(cairo_matrix_transform_distance)
{
	zval * matrix_zval = NULL;
	double dx = 0.0, dy = 0.0;
	cairo_matrix_object *matrix_object;
	
	PHP_CAIRO_ERROR_HANDLING
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odd", &matrix_zval, cairo_ce_cairomatrix, &dx, &dy) == FAILURE) {
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS

	matrix_object = (cairo_matrix_object *)cairo_matrix_object_get(matrix_zval TSRMLS_CC);
	cairo_matrix_transform_distance(matrix_object->matrix, &dx, &dy);

	array_init(return_value);
	add_assoc_double(return_value, "x", dx);
	add_assoc_double(return_value, "y", dy);
}
/* }}} */

/* {{{ proto array cairo_matrix_transform_point(CairoMatrix object, float x, float y)
       proto array CairoMatrix::transformPoint(float x, float y)
	   Transforms the point (x, y) by matrix. */
PHP_FUNCTION(cairo_matrix_transform_point)
{
	zval * matrix_zval = NULL;
	double x = 0.0, y = 0.0;
	cairo_matrix_object *matrix_object;
	
	PHP_CAIRO_ERROR_HANDLING
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odd", &matrix_zval, cairo_ce_cairomatrix, &x, &y) == FAILURE) {
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS

	matrix_object = (cairo_matrix_object *)cairo_matrix_object_get(matrix_zval TSRMLS_CC);
	cairo_matrix_transform_point(matrix_object->matrix, &x, &y);

	array_init(return_value);
	add_assoc_double(return_value, "x", x);
	add_assoc_double(return_value, "y", y);
}
/* }}} */

/* {{{ cairo_matrix_methods[] */
const zend_function_entry cairo_matrix_methods[] = {
	PHP_ME(CairoMatrix, __construct, CairoMatrix____construct_args, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME_MAPPING(initIdentity, cairo_matrix_init_identity, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME_MAPPING(initTranslate, cairo_matrix_init_translate, CairoMatrix_translate_args, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME_MAPPING(initScale, cairo_matrix_init_scale, CairoMatrix_scale_args, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME_MAPPING(initRotate, cairo_matrix_init_rotate, CairoMatrix_rotate_args, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME_MAPPING(translate, cairo_matrix_translate, CairoMatrix_translate_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(scale, cairo_matrix_scale, CairoMatrix_scale_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(rotate, cairo_matrix_rotate, CairoMatrix_scale_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(invert, cairo_matrix_invert, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(multiply, cairo_matrix_multiply, CairoMatrix_multiply_args, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME_MAPPING(transformDistance, cairo_matrix_transform_distance, CairoMatrix_transform_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(transformPoint, cairo_matrix_transform_point, CairoMatrix_transform_args, ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};
/* }}} */

static void cairo_matrix_object_destroy(void *object TSRMLS_DC)
{
	cairo_matrix_object *matrix = (cairo_matrix_object *)object;
	if (matrix->matrix != NULL) {
		efree(matrix->matrix);
	}
	zend_hash_destroy(matrix->std.properties);
	FREE_HASHTABLE(matrix->std.properties);
	efree(object);
}

static zend_object_value cairo_matrix_object_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	cairo_matrix_object *matrix;
	zval *temp;

	matrix = emalloc(sizeof(cairo_matrix_object));
	memset(matrix,0,sizeof(cairo_matrix_object));

	matrix->matrix = NULL;
	matrix->std.ce = ce;

	ALLOC_HASHTABLE(matrix->std.properties);
	zend_hash_init(matrix->std.properties, 0, NULL, ZVAL_PTR_DTOR, 0);
	zend_hash_copy(matrix->std.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref,(void *) &temp, sizeof(zval *));
	retval.handle = zend_objects_store_put(matrix, NULL, (zend_objects_free_object_storage_t)cairo_matrix_object_destroy, NULL TSRMLS_CC);
	retval.handlers = &cairo_std_object_handlers;
	return retval;
}

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(cairo_matrix)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "CairoMatrix", cairo_matrix_methods);
	cairo_ce_cairomatrix = zend_register_internal_class(&ce TSRMLS_CC);
	cairo_ce_cairomatrix->create_object = cairo_matrix_object_new;

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
