#include "php_cairo_api.h"
#include "CairoMatrix.h"
#include "CairoExceptionMacro.h"
#include "php_cairo_ce_ptr.h"

/* {{{ Class CairoMatrix */

//static zend_class_entry * CairoMatrix_ce_ptr = NULL;

/* {{{ Methods */


/* {{{ proto void construct([float xx, float yx, float xy, float yy, float x0, float y0])
   */
PHP_METHOD(CairoMatrix, __construct)
{
	zval * _this_zval;

	double xx = 1.0;
	double yx = 0.0;
	double xy = 0.0;
	double yy = 1.0;
	double x0 = 0.0;
	double y0 = 0.0;
	matrix_object *curr;


	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|dddddd", &xx, &yx, &xy, &yy, &x0, &y0) == FAILURE) {
		return;
	}

	_this_zval = getThis();
	curr = (matrix_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_matrix_init(&curr->matrix, xx, yx, xy, yy, x0, y0);
	
}
/* }}} __construct */



/* {{{ proto object initRotate(float radians)
   */
PHP_METHOD(CairoMatrix, initRotate)
{

	zval * _this_zval = NULL;
	cairo_matrix_t matrix;
	double radians = 0.0;
	matrix_object *curr, *mobj;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Od", &_this_zval, CairoMatrix_ce_ptr, &radians) == FAILURE) {
		return;
	}

	curr = (matrix_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_matrix_init_rotate(&matrix, radians);
	object_init_ex(return_value, CairoMatrix_ce_ptr);
	mobj = (matrix_object *)zend_objects_get_address(return_value TSRMLS_CC);
	mobj->matrix = matrix;
}
/* }}} initRotate */



/* {{{ proto void invert()
   */
PHP_METHOD(CairoMatrix, invert)
{

	zval * _this_zval = NULL;
	cairo_status_t status;
	matrix_object *curr;


	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoMatrix_ce_ptr) == FAILURE) {
		return;
	}

	curr = (matrix_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	status = cairo_matrix_invert(&curr->matrix);
	PHP_CAIRO_ERROR(status);	
}
/* }}} invert */



/* {{{ proto object multiply(object o2)
   */
PHP_METHOD(CairoMatrix, multiply)
{

	zval * _this_zval = NULL;
	zval * o2 = NULL;
	cairo_matrix_t result;
	matrix_object *curr, *mobj, *mret;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Oo", &_this_zval, CairoMatrix_ce_ptr, &o2) == FAILURE) {
		return;
	}

	curr = (matrix_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	mobj = (matrix_object *)zend_objects_get_address(o2 TSRMLS_CC);
	cairo_matrix_multiply(&result, &curr->matrix, &mobj->matrix);
	object_init_ex(return_value, CairoMatrix_ce_ptr);
	mret = (matrix_object *)zend_objects_get_address(return_value TSRMLS_CC);
	mret->matrix = result;
}
/* }}} multiply */



/* {{{ proto void rotate(float radians)
   */
PHP_METHOD(CairoMatrix, rotate)
{

	zval * _this_zval = NULL;
	double radians = 0.0;
	matrix_object *curr;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Od", &_this_zval, CairoMatrix_ce_ptr, &radians) == FAILURE) {
		return;
	}

	curr = (matrix_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_matrix_rotate(&curr->matrix, radians);

}
/* }}} rotate */



/* {{{ proto void scale(float sx, float xy)
   */
PHP_METHOD(CairoMatrix, scale)
{

	zval * _this_zval = NULL;
	double sx = 1.0;
	double xy = 1.0;
	matrix_object *curr;


	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odd", &_this_zval, CairoMatrix_ce_ptr, &sx, &xy) == FAILURE) {
		return;
	}

	curr = (matrix_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_matrix_scale(&curr->matrix, sx, xy);

}
/* }}} scale */



/* {{{ proto array transformDistance(float dx, float dy)
   */
PHP_METHOD(CairoMatrix, transformDistance)
{

	zval * _this_zval = NULL;
	double dx = 0.0;
	double dy = 0.0;
	matrix_object *curr;
	
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odd", &_this_zval, CairoMatrix_ce_ptr, &dx, &dy) == FAILURE) {
		return;
	}

	curr = (matrix_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_matrix_transform_distance(&curr->matrix, &dx, &dy);

	array_init(return_value);
	add_assoc_double(return_value, "x", dx);
	add_assoc_double(return_value, "y", dy);

}
/* }}} transformDistance */



/* {{{ proto array transformPoint(float x, float y)
   */
PHP_METHOD(CairoMatrix, transformPoint)
{

	zval * _this_zval = NULL;
	double x = 0.0;
	double y = 0.0;
	matrix_object *curr;
	

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odd", &_this_zval, CairoMatrix_ce_ptr, &x, &y) == FAILURE) {
		return;
	}


	curr = (matrix_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_matrix_transform_point(&curr->matrix, &x, &y);
	array_init(return_value);
	add_assoc_double(return_value, "x", x);
	add_assoc_double(return_value, "y", y);

}
/* }}} transformPoint */



/* {{{ proto void translate(float tx, float ty)
   */
PHP_METHOD(CairoMatrix, translate)
{

	zval * _this_zval = NULL;
	double tx = 0.0;
	double ty = 0.0;
	matrix_object *curr;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odd", &_this_zval, CairoMatrix_ce_ptr, &tx, &ty) == FAILURE) {
		return;
	}

	curr = (matrix_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_matrix_translate(&curr->matrix, tx, ty);

}
/* }}} translate */


static zend_function_entry CairoMatrix_methods[] = {
	PHP_ME(CairoMatrix, __construct, CairoMatrix____construct_args, /**/ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(CairoMatrix, initRotate, CairoMatrix__init_rotate_args, /**/ZEND_ACC_PRIVATE)
	PHP_ME(CairoMatrix, invert, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoMatrix, multiply, CairoMatrix__multiply_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoMatrix, rotate, CairoMatrix__rotate_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoMatrix, scale, CairoMatrix__scale_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoMatrix, transformDistance, CairoMatrix__transform_distance_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoMatrix, transformPoint, CairoMatrix__transform_point_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoMatrix, translate, CairoMatrix__translate_args, /**/ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

/* }}} Methods */

static zend_object_handlers CairoMatrix_handlers;

static void CairoMatrix_object_dtor(void *object)
{
	matrix_object *matrix = (matrix_object *)object;
	zend_hash_destroy(matrix->std.properties);
	FREE_HASHTABLE(matrix->std.properties);
	efree(object);
}


static zend_object_value CairoMatrix_object_new(zend_class_entry *ce)
{
	zend_object_value retval;
	matrix_object *matrix;
	zval *temp;
	matrix = emalloc(sizeof(matrix_object));
	memset(matrix,0,sizeof(matrix_object));
	matrix->std.ce = ce;
	ALLOC_HASHTABLE(matrix->std.properties);
	zend_hash_init(matrix->std.properties, 0, NULL, ZVAL_PTR_DTOR,0);
	zend_hash_copy(matrix->std.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref, (void *) &temp, sizeof(zval *));
	retval.handle = zend_objects_store_put(matrix, NULL, (zend_objects_free_object_storage_t)CairoMatrix_object_dtor, NULL TSRMLS_CC);
	retval.handlers = &CairoMatrix_handlers;
	return retval;
}


void class_init_CairoMatrix(void)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "CairoMatrix", CairoMatrix_methods);
	CairoMatrix_ce_ptr = zend_register_internal_class(&ce);
	CairoMatrix_ce_ptr->create_object = CairoMatrix_object_new;
	memcpy(&CairoMatrix_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	CairoMatrix_handlers.clone_obj = NULL;

}

/* }}} Class CairoMatrix */
