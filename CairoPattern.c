#include "php_cairo_api.h"
#include "CairoPattern.h"
#include "CairoExceptionMacro.h"
#include "php_cairo_ce_ptr.h"

/* {{{ Class CairoPattern */


/* {{{ Methods */


/* {{{ proto void contruct()
   */
PHP_METHOD(CairoPattern, __construct)
{
	php_error(E_WARNING, "Pattern Cannot be initialized"); RETURN_FALSE;

}
/* }}} __construct */



/* {{{ proto object getMatrix()
   */
PHP_METHOD(CairoPattern, getMatrix)
{

	zval * _this_zval = NULL;
	cairo_matrix_t matrix;
	pattern_object *curr;
	matrix_object *mobj;
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoPattern_ce_ptr) == FAILURE) {
		return;
	}

	curr = (pattern_object *)zend_objects_get_address(_this_zval TSRMLS_CC);

	cairo_pattern_get_matrix(curr->pattern, &matrix);
	object_init_ex(return_value, CairoMatrix_ce_ptr);
	mobj = (matrix_object *)zend_objects_get_address(return_value TSRMLS_CC);
	mobj->matrix = matrix;
}
/* }}} getMatrix */



/* {{{ proto void setMatrix(object m)
   */
PHP_METHOD(CairoPattern, setMatrix)
{

	zval * _this_zval = NULL;
	zval * m = NULL;
	pattern_object *curr;
	matrix_object *mobj;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Oo", &_this_zval, CairoPattern_ce_ptr, &m) == FAILURE) {
		return;
	}

	curr = (pattern_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	mobj = (matrix_object *)zend_objects_get_address(m TSRMLS_CC);
	cairo_pattern_set_matrix(curr->pattern, &mobj->matrix);
}
/* }}} setMatrix */


/* {{{ proto void setExtend(int extend)
	*/
PHP_METHOD(CairoPattern, setExtend)
{
	long extend;
	pattern_object *curr;
	zval * _this_zval = NULL;
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ol", &_this_zval, CairoPattern_ce_ptr, &extend) == FAILURE) {
			return;
	}
	curr = (pattern_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_pattern_set_extend(curr->pattern, extend);
	PHP_CAIRO_PATTERN_ERROR(curr->pattern);
	
}

/* }}} setExtend */


/* {{{ proto void getExtend()
	*/
PHP_METHOD(CairoPattern, getExtend)
{
	long extend;
	pattern_object *curr;
	zval * _this_zval = NULL;
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoPattern_ce_ptr) == FAILURE) {
		return;
	}
	curr = (pattern_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	extend = cairo_pattern_get_extend(curr->pattern);
	RETURN_LONG(extend);
}
/* }}} setExtend */


static zend_function_entry CairoPattern_methods[] = {
	PHP_ME(CairoPattern, __construct, NULL, /**/ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(CairoPattern, getMatrix, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoPattern, setMatrix, CairoPattern__set_matrix_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoPattern, getExtend, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoPattern, setExtend, CairoPattern__set_extend_args, /**/ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

/* }}} Methods */

static zend_object_handlers CairoPattern_handlers;

static void CairoPattern_object_dtor(void *object)
{
	pattern_object *pattern = (pattern_object *)object;
	zend_hash_destroy(pattern->std.properties);
	FREE_HASHTABLE(pattern->std.properties);
	if(pattern->pattern){
		cairo_pattern_destroy(pattern->pattern);
	}
	efree(object);
}

static zend_object_value CairoPattern_object_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	pattern_object *pattern;
	zval *temp;
	pattern = emalloc(sizeof(pattern_object));
	memset(pattern,0,sizeof(pattern_object));
	pattern->std.ce = ce;
	ALLOC_HASHTABLE(pattern->std.properties);
	zend_hash_init(pattern->std.properties, 0, NULL, ZVAL_PTR_DTOR,0);
	zend_hash_copy(pattern->std.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref, (void *) &temp, sizeof(zval *));
	retval.handle = zend_objects_store_put(pattern, NULL, (zend_objects_free_object_storage_t)CairoPattern_object_dtor, NULL TSRMLS_CC);
	retval.handlers = &CairoPattern_handlers;
	return retval;
}


void class_init_CairoPattern(TSRMLS_D)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "CairoPattern", CairoPattern_methods);
	CairoPattern_ce_ptr = zend_register_internal_class(&ce TSRMLS_CC);
	CairoPattern_ce_ptr->create_object = CairoPattern_object_new;
	memcpy(&CairoPattern_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	CairoPattern_handlers.clone_obj = NULL;
}

/* }}} Class CairoPattern */

/* {{{ Class CairoGradient */


/* {{{ Methods */


/* {{{ proto void construct()
   */
PHP_METHOD(CairoGradient, __construct)
{

	zval * _this_zval = NULL;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoGradient_ce_ptr) == FAILURE) {
		return;
	}



	php_error(E_WARNING, "Gradient cannot be initialized"); RETURN_FALSE;

}
/* }}} __construct */



/* {{{ proto void addColorStopRgb(float offset, float red, float green, float blue)
   */
PHP_METHOD(CairoGradient, addColorStopRgb)
{

	zval * _this_zval = NULL;
	double offset = 0.0;
	double red = 0.0;
	double green = 0.0;
	double blue = 0.0;
	pattern_object *curr;


	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odddd", &_this_zval, CairoGradient_ce_ptr, &offset, &red, &green, &blue) == FAILURE) {
		return;
	}

	curr = (pattern_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_pattern_add_color_stop_rgb(curr->pattern, offset, red, green, blue);
	PHP_CAIRO_PATTERN_ERROR(curr->pattern);
}
/* }}} addColorStopRgb */



/* {{{ proto void addColorStopRgba(float offset, float red, float green, float blue, float alpha)
   */
PHP_METHOD(CairoGradient, addColorStopRgba)
{

	zval * _this_zval = NULL;
	double offset = 0.0;
	double red = 0.0;
	double green = 0.0;
	double blue = 0.0;
	double alpha = 0.0;
	pattern_object *curr;


	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Oddddd", &_this_zval, CairoGradient_ce_ptr, &offset, &red, &green, &blue, &alpha) == FAILURE) {
		return;
	}

	curr = (pattern_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_pattern_add_color_stop_rgba(curr->pattern, offset, red, green, blue, alpha);
	PHP_CAIRO_PATTERN_ERROR(curr->pattern);
}
/* }}} addColorStopRgba */



static zend_function_entry CairoGradient_methods[] = {
	PHP_ME(CairoGradient, __construct, NULL, /**/ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(CairoGradient, addColorStopRgb, CairoGradient__add_color_stop_rgb_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoGradient, addColorStopRgba, CairoGradient__add_color_stop_rgba_args, /**/ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

/* }}} Methods */

static zend_object_handlers CairoGradient_handlers;

static zend_object_value CairoGradient_object_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	retval = CairoPattern_object_new(ce TSRMLS_CC);
	retval.handlers = &CairoGradient_handlers;
	return retval;
}

void class_init_CairoGradient(TSRMLS_D)
{
	zend_class_entry ce;
	INIT_CLASS_ENTRY(ce, "CairoGradient", CairoGradient_methods);
	CairoGradient_ce_ptr = zend_register_internal_class_ex(&ce, CairoPattern_ce_ptr, "CairoPattern" TSRMLS_CC);
	CairoGradient_ce_ptr->create_object = CairoGradient_object_new;
	memcpy(&CairoGradient_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
}


/* }}} Class CairoGradient */

/* {{{ Class CairoLinearGradient */


/* {{{ Methods */


/* {{{ proto void construct(float x0, float y0, float x1, float y1)
   */
PHP_METHOD(CairoLinearGradient, __construct)
{
	zval * _this_zval;

	double x0 = 0.0;
	double y0 = 0.0;
	double x1 = 0.0;
	double y1 = 0.0;
	pattern_object *curr;


	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dddd", &x0, &y0, &x1, &y1) == FAILURE) {
		return;
	}

	_this_zval = getThis();
	curr = (pattern_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	curr->pattern = cairo_pattern_create_linear(x0, y0, x1, y1);

}
/* }}} __construct */



/* {{{ proto array getLinearPoints()
   */
PHP_METHOD(CairoLinearGradient, getLinearPoints)
{

	zval * _this_zval = NULL;
	double x0, y0, x1, y1;
	pattern_object *curr;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoLinearGradient_ce_ptr) == FAILURE) {
		return;
	}

	curr = (pattern_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_pattern_get_linear_points(curr->pattern, &x0, &y0, &x1, &y1);

	array_init(return_value);
	add_assoc_double(return_value, "x0", x0);
	add_assoc_double(return_value, "y0", y0);
	add_assoc_double(return_value, "x1", x1);
	add_assoc_double(return_value, "y1", y1);

}
/* }}} getLinearPoints */


static zend_function_entry CairoLinearGradient_methods[] = {
	PHP_ME(CairoLinearGradient, __construct, CairoLinearGradient____construct_args, /**/ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(CairoLinearGradient, getLinearPoints, NULL, /**/ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

/* }}} Methods */

static zend_object_handlers CairoLinearGradient_handlers;

static zend_object_value CairoLinearGradient_object_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	retval = CairoGradient_object_new(ce TSRMLS_CC);
	retval.handlers = &CairoLinearGradient_handlers;
	return retval;
}

void class_init_CairoLinearGradient(TSRMLS_D)
{
	zend_class_entry ce;
	INIT_CLASS_ENTRY(ce, "CairoLinearGradient", CairoLinearGradient_methods);
	CairoLinearGradient_ce_ptr = zend_register_internal_class_ex(&ce, CairoGradient_ce_ptr, "CairoGradient" TSRMLS_CC);
	CairoLinearGradient_ce_ptr->create_object = CairoLinearGradient_object_new;
	memcpy(&CairoLinearGradient_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
}


/* }}} Class CairoLinearGradient */

/* {{{ Class CairoRadialGradient */


/* {{{ Methods */


/* {{{ proto void construct(float cx0, float cy0, float radius0, float cx1, float cy1, float radius1)
   */
PHP_METHOD(CairoRadialGradient, __construct)
{

	zval * _this_zval = NULL;
	double cx0 = 0.0;
	double cy0 = 0.0;
	double radius0 = 0.0;
	double cx1 = 0.0;
	double cy1 = 0.0;
	double radius1 = 0.0;
	pattern_object *curr;


	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odddddd", &_this_zval, CairoRadialGradient_ce_ptr, &cx0, &cy0, &radius0, &cx1, &cy1, &radius1) == FAILURE) {
		return;
	}

	curr = (pattern_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	curr->pattern = cairo_pattern_create_radial(cx0, cy0, radius0, cx1, cy1, radius1);

}
/* }}} __construct */



/* {{{ proto array getRadialCircles()
   */
PHP_METHOD(CairoRadialGradient, getRadialCircles)
{

	zval * _this_zval = NULL;
	double x0, y0, r0, x1, y1, r1;
	pattern_object *curr;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoRadialGradient_ce_ptr) == FAILURE) {
		return;
	}

	curr = (pattern_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_pattern_get_radial_circles(curr->pattern, &x0, &y0, &r0, &x1, &y1, &r1);

	array_init(return_value);
	add_assoc_double(return_value, "x0", x0);
	add_assoc_double(return_value, "y0", y0);
	add_assoc_double(return_value, "r0", r0);
	add_assoc_double(return_value, "x1", x1);
	add_assoc_double(return_value, "y1", y1);
	add_assoc_double(return_value, "r1", r1);

}
/* }}} getRadialCircles */


static zend_function_entry CairoRadialGradient_methods[] = {
	PHP_ME(CairoRadialGradient, __construct, CairoRadialGradient____constuct_args, /**/ZEND_ACC_PUBLIC| ZEND_ACC_CTOR)
	PHP_ME(CairoRadialGradient, getRadialCircles, NULL, /**/ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

/* }}} Methods */

static zend_object_handlers CairoRadialGradient_handlers;

static zend_object_value CairoRadialGradient_object_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	retval = CairoGradient_object_new(ce TSRMLS_CC);
	retval.handlers = &CairoRadialGradient_handlers;
	return retval;
}

void class_init_CairoRadialGradient(TSRMLS_D)
{
	zend_class_entry ce;
	INIT_CLASS_ENTRY(ce, "CairoRadialGradient", CairoRadialGradient_methods);
	CairoRadialGradient_ce_ptr = zend_register_internal_class_ex(&ce, CairoGradient_ce_ptr, "CairoGradient" TSRMLS_CC);
	CairoRadialGradient_ce_ptr->create_object = CairoRadialGradient_object_new;
	memcpy(&CairoRadialGradient_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
}

/* }}} Class CairoRadialGradient */

/* {{{ Class CairoSolidPattern */


/* {{{ Methods */


/* {{{ proto void construct(float r, float g, float b [, float a])
   */
PHP_METHOD(CairoSolidPattern, __construct)
{
	zval * _this_zval;

	double r = 0.0;
	double g = 0.0;
	double b = 0.0;
	double a = 1.0;
	pattern_object *curr;


	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ddd|d", &r, &g, &b, &a) == FAILURE) {
		return;
	}

	_this_zval = getThis();
	curr = (pattern_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	curr->pattern = cairo_pattern_create_rgba(r, g, b, a);

}
/* }}} __construct */



/* {{{ proto array getRgba()
   */
PHP_METHOD(CairoSolidPattern, getRgba)
{

	zval * _this_zval = NULL;
	double r,g,b,a;
	pattern_object *curr;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoSolidPattern_ce_ptr) == FAILURE) {
		return;
	}

	curr = (pattern_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_pattern_get_rgba(curr->pattern, &r, &g, &b, &a);

	array_init(return_value);
	add_assoc_double(return_value, "red", r);
	add_assoc_double(return_value, "green", g);
	add_assoc_double(return_value, "blue", b);
	add_assoc_double(return_value, "alpha", a);

}
/* }}} getRgba */


static zend_function_entry CairoSolidPattern_methods[] = {
	PHP_ME(CairoSolidPattern, __construct, CairoSolidPattern____construct_args, /**/ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(CairoSolidPattern, getRgba, NULL, /**/ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

/* }}} Methods */

static zend_object_handlers CairoSolidPattern_handlers;

static zend_object_value CairoSolidPattern_object_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	retval = CairoPattern_object_new(ce TSRMLS_CC);
	retval.handlers = &CairoSolidPattern_handlers;
	return retval;

}

void class_init_CairoSolidPattern(TSRMLS_D)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "CairoSolidPattern", CairoSolidPattern_methods);
	CairoSolidPattern_ce_ptr = zend_register_internal_class_ex(&ce, CairoPattern_ce_ptr, "CairoPattern" TSRMLS_CC);
	CairoSolidPattern_ce_ptr->create_object = CairoSolidPattern_object_new;
	memcpy(&CairoSolidPattern_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
}

/* }}} Class CairoSolidPattern */

/* {{{ Class CairoSurfacePattern */


/* {{{ Methods */


/* {{{ proto void construct(object s)
   */
PHP_METHOD(CairoSurfacePattern, __construct)
{
	zval * _this_zval;

	zval * s = NULL;
	pattern_object *curr;
	surface_object *sobj;


	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "o", &s) == FAILURE) {
		return;
	}

	_this_zval = getThis();
	curr = (pattern_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	sobj = (surface_object *)zend_objects_get_address(s TSRMLS_CC);
	curr->pattern = cairo_pattern_create_for_surface(sobj->surface);
	
}
/* }}} __construct */


/* {{{ proto int getFilter()
   */
PHP_METHOD(CairoSurfacePattern, getFilter)
{
	zval * _this_zval = NULL;
	pattern_object *curr;


	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoSurfacePattern_ce_ptr) == FAILURE) {
		return;
	}

	curr = (pattern_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	RETURN_LONG(cairo_pattern_get_filter(curr->pattern));
}
/* }}} getFilter */



/* {{{ proto object getSurface()
   */
PHP_METHOD(CairoSurfacePattern, getSurface)
{
	zend_class_entry *surface_ce;
	cairo_surface_t *surface;
	zval * _this_zval = NULL;
	pattern_object *curr;
	surface_object *sobj;


	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoSurfacePattern_ce_ptr) == FAILURE) {
		return;
	}

	curr = (pattern_object *)zend_objects_get_address(_this_zval TSRMLS_CC);	
	cairo_pattern_get_surface(curr->pattern, &surface);
	surface_ce = get_CairoSurface_ce_ptr(surface);

	object_init_ex(return_value,surface_ce);
	sobj = (surface_object *)zend_objects_get_address(return_value TSRMLS_CC);
	sobj->surface = cairo_surface_reference(surface);
}
/* }}} getSurface */




/* {{{ proto void setFilter(int filter)
   */
PHP_METHOD(CairoSurfacePattern, setFilter)
{

	zval * _this_zval = NULL;
	long filter = 0;
	pattern_object *curr;


	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ol", &_this_zval, CairoSurfacePattern_ce_ptr, &filter) == FAILURE) {
		return;
	}
	
	curr = (pattern_object *)zend_objects_get_address(_this_zval TSRMLS_CC);

	cairo_pattern_set_filter(curr->pattern, filter);
}
/* }}} setFilter */


static zend_function_entry CairoSurfacePattern_methods[] = {
	PHP_ME(CairoSurfacePattern, __construct, NULL, /**/ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(CairoSurfacePattern, getFilter, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoSurfacePattern, getSurface, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoSurfacePattern, setFilter, CairoSurfacePattern__set_filter_args, /**/ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

/* }}} Methods */

static zend_object_handlers CairoSurfacePattern_handlers;

static zend_object_value CairoSurfacePattern_object_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	retval = CairoPattern_object_new(ce TSRMLS_CC);
	retval.handlers = &CairoSurfacePattern_handlers;
	return retval;
}

void class_init_CairoSurfacePattern(TSRMLS_D)
{
	zend_class_entry ce;
	INIT_CLASS_ENTRY(ce, "CairoSurfacePattern", CairoSurfacePattern_methods);
	CairoSurfacePattern_ce_ptr = zend_register_internal_class_ex(&ce, CairoPattern_ce_ptr, "CairoPattern" TSRMLS_CC);
	CairoSurfacePattern_ce_ptr->create_object = CairoSurfacePattern_object_new;
	memcpy(&CairoSurfacePattern_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
}


/* }}} Class CairoSurfacePattern */ 

/* {{{ Helper functions */

zend_class_entry *
get_CairoPattern_ce_ptr(cairo_pattern_t *pattern)
{
	zend_class_entry *type;
	if(pattern == NULL)
		return NULL;
	switch(cairo_pattern_get_type(pattern)) {
		case CAIRO_PATTERN_TYPE_SOLID:
			type = CairoSolidPattern_ce_ptr;
			break;
		case CAIRO_PATTERN_TYPE_SURFACE:
			type = CairoSurfacePattern_ce_ptr;
			break;
		case CAIRO_PATTERN_TYPE_LINEAR:
			type = CairoLinearGradient_ce_ptr;
			break;
		case CAIRO_PATTERN_TYPE_RADIAL:
			type = CairoRadialGradient_ce_ptr;
			break;
		default:
			php_error(E_WARNING,"Unsupported Pattern");
			return NULL;
	}
	return type;
}
/* }}} Helper functions */	

