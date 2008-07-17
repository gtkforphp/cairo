/* {{{ Class CairoContext */

PHP_CAIRO_API static zend_class_entry * CairoContext_ce_ptr = NULL;

/* {{{ Methods */


/* {{{ proto void construct(object obj)
   */
PHP_METHOD(CairoContext, __construct)
{
	zend_class_entry * _this_ce;
	zval * _this_zval;

	zval * obj = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|o", &obj) == FAILURE) {
		return;
	}

	_this_zval = getThis();
	_this_ce = Z_OBJCE_P(_this_zval);
    cairo_surface_t *surface;
	//if(obj != NULL) {

		surface_object *sobj = (surface_object *)zend_object_store_get_object(obj TSRMLS_CC);
	//}
	//else {
	//	surface_object *sobj = (surface_object *)malloc(surface_object);
	//}

	surface = sobj->surface;
	context_object *context=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	context->context=cairo_create(surface);

	/*php_error(E_WARNING, "__construct: not yet implemented"); RETURN_FALSE; */

}
/* }}} __construct */



/* {{{ proto void appendPath(object p)
   */
PHP_METHOD(CairoContext, appendPath)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	zval * p = NULL;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Oo", &_this_zval, CairoContext_ce_ptr, &p) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr = (context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	path_object *pobj=(path_object *)zend_objects_get_address(p TSRMLS_CC);
	cairo_append_path(curr->context,pobj->path);
	phpCAIRO_CONTEXT_ERROR(curr->context)

}
/* }}} appendPath */



/* {{{ proto void arc(float xc, float yc, float radius, float angle1, float angle2)
   */
PHP_METHOD(CairoContext, arc)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	double xc = 0.0;
	double yc = 0.0;
	double radius = 0.0;
	double angle1 = 0.0;
	double angle2 = 0.0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Oddddd", &_this_zval, CairoContext_ce_ptr, &xc, &yc, &radius, &angle1, &angle2) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_arc(curr->context,xc,yc,radius,angle1,angle2);
    phpCAIRO_CONTEXT_ERROR(curr->context)

}
/* }}} arc */



/* {{{ proto void arcNegative(float xc, float yc, float radius, float angle1, float angle2)
   */
PHP_METHOD(CairoContext, arcNegative)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	double xc = 0.0;
	double yc = 0.0;
	double radius = 0.0;
	double angle1 = 0.0;
	double angle2 = 0.0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Oddddd", &_this_zval, CairoContext_ce_ptr, &xc, &yc, &radius, &angle1, &angle2) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	
	context_object *curr = (context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);


	cairo_arc_negative(curr->context, xc, yc, radius, angle1, angle2);
	phpCAIRO_CONTEXT_ERROR(curr->context)
	

}
/* }}} arcNegative */



/* {{{ proto void clip()
   */
PHP_METHOD(CairoContext, clip)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoContext_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
    context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_clip(curr->context);
	phpCAIRO_CONTEXT_ERROR(curr->context)
}
/* }}} clip */



/* {{{ proto array clipExtents()
   */
PHP_METHOD(CairoContext, clipExtents)
{
	zend_class_entry * _this_ce;
	
	zval * _this_zval = NULL;

	double x1, y1, x2, y2;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoContext_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
    context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	
	cairo_clip_extents(curr->context, &x1, &y1, &x2, &y2);
    phpCAIRO_CONTEXT_ERROR(curr->context)
	array_init(return_value);
	add_next_index_double(return_value, x1);
	add_next_index_double(return_value, y1);
	add_next_index_double(return_value, x2);
	add_next_index_double(return_value, y2);

}
/* }}} clipExtents */



/* {{{ proto void clipPreserve()
   */
PHP_METHOD(CairoContext, clipPreserve)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoContext_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);

    context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	
	cairo_clip_preserve(curr->context);
    phpCAIRO_CONTEXT_ERROR(curr->context)
}
/* }}} clipPreserve */



/* {{{ proto void closePath()
   */
PHP_METHOD(CairoContext, closePath)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoContext_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
    context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);

	cairo_close_path(curr->context);
    phpCAIRO_CONTEXT_ERROR(curr->context)

}
/* }}} closePath */



/* {{{ proto object copyClipRectangleList()
   */
PHP_METHOD(CairoContext, copyClipRectangleList)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	cairo_rectangle_t *r;
	cairo_rectangle_list_t *rlist;
	zval *arr;
	zval *temp_arr;
	int i;
	
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoContext_ce_ptr) == FAILURE) {
		return;
	}
	_this_ce = Z_OBJCE_P(_this_zval);
    context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	rlist = cairo_copy_clip_rectangle_list(curr->context);
	phpCAIRO_ERROR(rlist->status)
	
	array_init(return_value);
	ALLOC_INIT_ZVAL(temp_arr);
	array_init(temp_arr);

	for(i = 0, r = rlist->rectangles; i < rlist->num_rectangles; i++, r++) {
		//ALLOC_INIT_ZVAL(temp_arr);
		//array_init(temp_arr);
		add_assoc_double(temp_arr,"x",r->x);
		add_assoc_double(temp_arr,"y",r->y);
		add_assoc_double(temp_arr,"width",r->width);
		add_assoc_double(temp_arr,"height",r->height);
		add_next_index_zval(return_value,temp_arr);
	//	zval_ptr_dtor(temp_arr);
	}
	
	
	cairo_rectangle_list_destroy(rlist);

	
}
/* }}} copyClipRectangleList */



/* {{{ proto void copyPage()
   */
PHP_METHOD(CairoContext, copyPage)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoContext_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_copy_page(curr->context);
    phpCAIRO_CONTEXT_ERROR(curr->context)

}
/* }}} copyPage */



/* {{{ proto object copyPath()
   */
PHP_METHOD(CairoContext, copyPath)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoContext_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);

	object_init_ex(return_value, CairoPath_ce_ptr);
	path_object *pobj = (path_object *)zend_objects_get_address(return_value TSRMLS_CC);
	pobj->path = cairo_copy_path(curr->context);
}
/* }}} copyPath */



/* {{{ proto object copyPathFlat()
   */
PHP_METHOD(CairoContext, copyPathFlat)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoContext_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);

	object_init_ex(return_value, CairoPath_ce_ptr);
	path_object *pobj = (path_object *)zend_objects_get_address(return_value TSRMLS_CC);
	pobj->path = cairo_copy_path_flat(curr->context);

}
/* }}} copyPathFlat */



/* {{{ proto void curveTo (float x1, float y1, float x2, float y2, float x3, float y3)
   */
PHP_METHOD(CairoContext, curveTo)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	double x1 = 0.0;
	double y1 = 0.0;
	double x2 = 0.0;
	double y2 = 0.0;
	double x3 = 0.0;
	double y3 = 0.0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odddddd", &_this_zval, CairoContext_ce_ptr, &x1, &y1, &x2, &y2, &x3, &y3) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);

	cairo_curve_to(curr->context, x1, y1, x2, y2, x3, y3);
	phpCAIRO_CONTEXT_ERROR(curr->context)

}
/* }}} curveTo */



/* {{{ proto array deviceToUser(float x, float y)
   */
PHP_METHOD(CairoContext, deviceToUser)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	double x = 0.0;
	double y = 0.0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odd", &_this_zval, CairoContext_ce_ptr, &x, &y) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	
	cairo_device_to_user(curr->context, &x, &y);
	phpCAIRO_CONTEXT_ERROR(curr->context)
	
	array_init(return_value);
	add_assoc_double(return_value, "x", x);
	add_assoc_double(return_value, "y", y);

}
/* }}} deviceToUser */



/* {{{ proto array deviceToUserDistance(float x, float y)
   */
PHP_METHOD(CairoContext, deviceToUserDistance)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	double x = 0.0;
	double y = 0.0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odd", &_this_zval, CairoContext_ce_ptr, &x, &y) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_device_to_user_distance(curr->context, &x, &y);
	phpCAIRO_CONTEXT_ERROR(curr->context)
	array_init(return_value);
	add_assoc_double(return_value, "x", x);
	add_assoc_double(return_value, "y", y);

}
/* }}} deviceToUserDistance */



/* {{{ proto void fill()
   */
PHP_METHOD(CairoContext, fill)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoContext_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_fill(curr->context);
	phpCAIRO_CONTEXT_ERROR(curr->context)


}
/* }}} fill */



/* {{{ proto array fillExtents()
   */
PHP_METHOD(CairoContext, fillExtents)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	cairo_font_extents_t e;


	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoContext_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_font_extents(curr->context, &e);
	
	phpCAIRO_CONTEXT_ERROR(curr->context)
	array_init(return_value);
	add_assoc_double(return_value, "ascent", e.ascent);
	add_assoc_double(return_value, "descent", e.descent);
	add_assoc_double(return_value, "height", e.height);
	add_assoc_double(return_value, "max X advance", e.max_x_advance);
	add_assoc_double(return_value, "max Y advance", e.max_y_advance);
}
/* }}} fillExtents */



/* {{{ proto void fillPreserve()
   */
PHP_METHOD(CairoContext, fillPreserve)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoContext_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_fill_preserve(curr->context);
	phpCAIRO_CONTEXT_ERROR(curr->context)


}
/* }}} fillPreserve */



/* {{{ proto array fontExtents()
   */
PHP_METHOD(CairoContext, fontExtents)
{
	zend_class_entry * _this_ce;
	zval * _this_zval = NULL;
	cairo_font_extents_t e;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoContext_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_font_extents(curr->context, &e);
	phpCAIRO_CONTEXT_ERROR(curr->context)
		
	array_init(return_value);
	add_assoc_double(return_value, "ascent", e.ascent);
	add_assoc_double(return_value, "descent", e.descent);
	add_assoc_double(return_value, "height", e.height);
	add_assoc_double(return_value, "max X advance", e.max_x_advance);
	add_assoc_double(return_value, "max Y advance", e.max_y_advance);

}
/* }}} fontExtents */



/* {{{ proto int getAntialias()
   */
PHP_METHOD(CairoContext, getAntialias)
{
	zend_class_entry * _this_ce;
	zval * _this_zval = NULL;
	long temp;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoContext_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	temp = cairo_get_antialias(curr->context);

	RETURN_LONG(temp);
}
/* }}} getAntialias */



/* {{{ proto array getCurrentPoint()
   */
PHP_METHOD(CairoContext, getCurrentPoint)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	double x,y;
	

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoContext_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_get_current_point(curr->context, &x, &y);
	array_init(return_value);
	add_assoc_double(return_value, "x", x);
	add_assoc_double(return_value, "y", y);
}
/* }}} getCurrentPoint */



/* {{{ proto array getDash()
   */
PHP_METHOD(CairoContext, getDash)
{
	zend_class_entry * _this_ce;
	zval *sub_array;
	zval * _this_zval = NULL;
	double *dashes = NULL, offset;
	int count, i;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoContext_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	count = cairo_get_dash_count(curr->context);
	dashes = emalloc(count* sizeof(double));
	if(dashes==NULL)
		return;
	cairo_get_dashes(curr->context, dashes, &offset);

	MAKE_STD_ZVAL(sub_array);
	array_init(sub_array);
	for(i=0; i<count; i++) {
		add_next_index_double(sub_array,dashes[i]);
	}
	
	array_init(return_value);
	add_assoc_zval(return_value, "Dashes", sub_array);
	add_assoc_double(return_value, "Offset", offset);
}
/* }}} getDash */



/* {{{ proto int getDashCount()
   */
PHP_METHOD(CairoContext, getDashCount)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	long count;


	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoContext_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	count = cairo_get_dash_count(curr->context);
	
	RETURN_LONG(count);
}
/* }}} getDashCount */



/* {{{ proto int getFillRule()
   */
PHP_METHOD(CairoContext, getFillRule)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	long fill;


	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoContext_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	fill = cairo_get_fill_rule(curr->context);

	RETURN_LONG(fill);
}
/* }}} getFillRule */



/* {{{ proto object getFontFace()
   */
PHP_METHOD(CairoContext, getFontFace)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoContext_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);

	object_init_ex(return_value, CairoFontFace_ce_ptr);
	fontface_object *ffobj = (fontface_object *)zend_objects_get_address(return_value TSRMLS_CC);
	ffobj->fontface = cairo_font_face_reference (cairo_get_font_face(curr->context));
}
/* }}} getFontFace */



/* {{{ proto object getFontMatrix()
   */
PHP_METHOD(CairoContext, getFontMatrix)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	cairo_matrix_t matrix;


	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoContext_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_get_font_matrix(curr->context, &matrix);

	object_init_ex(return_value, CairoMatrix_ce_ptr);
	matrix_object *matobj = (matrix_object *)zend_objects_get_address(return_value TSRMLS_CC);
	matobj->matrix = matrix;
}
/* }}} getFontMatrix */



/* {{{ proto object getFontOptions()
   */
PHP_METHOD(CairoContext, getFontOptions)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	cairo_font_options_t *options = cairo_font_options_create();	


	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoContext_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_get_font_options(curr->context, options);
	
	object_init_ex(return_value, CairoFontOptions_ce_ptr);
	fontoptions_object *foobj = (fontoptions_object *)zend_objects_get_address(return_value TSRMLS_CC);
	foobj->fontoptions = options;
	
}
/* }}} getFontOptions */



/* {{{ proto object getGroupTarget()
   */
PHP_METHOD(CairoContext, getGroupTarget)
{
	zend_class_entry * _this_ce, *ce;

	zval * _this_zval = NULL;
	cairo_surface_t *sur;


	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoContext_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
    sur = cairo_get_group_target(curr->context);

	ce = get_CairoSurface_ce_ptr(sur);

	object_init_ex(return_value, ce);
	surface_object *sobj = (surface_object *)zend_objects_get_address(return_value TSRMLS_CC);

	sobj->surface = cairo_surface_reference(sur);
}
/* }}} getGroupTarget */



/* {{{ proto int getLineCap()
   */
PHP_METHOD(CairoContext, getLineCap)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	long line_cap;


	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoContext_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	line_cap = cairo_get_line_cap(curr->context);


	RETURN_LONG(line_cap);
}
/* }}} getLineCap */



/* {{{ proto int getLineJoin()
   */
PHP_METHOD(CairoContext, getLineJoin)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	long line_join;


	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoContext_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);

	line_join = cairo_get_line_join(curr->context);
	RETURN_LONG(line_join);
}
/* }}} getLineJoin */



/* {{{ proto float getLineWidth()
   */
PHP_METHOD(CairoContext, getLineWidth)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;

	double width;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoContext_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	width = cairo_get_line_width(curr->context);

	RETURN_DOUBLE(width);
}
/* }}} getLineWidth */



/* {{{ proto object getMatrix()
   */
PHP_METHOD(CairoContext, getMatrix)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;

	cairo_matrix_t matrix;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoContext_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);

	cairo_get_matrix(curr->context, &matrix);
	object_init_ex(return_value, CairoMatrix_ce_ptr);
	matrix_object *mobj = (matrix_object *)zend_objects_get_address(return_value TSRMLS_CC);
	mobj->matrix = matrix;
}
/* }}} getMatrix */



/* {{{ proto float getMiterLimit()
   */
PHP_METHOD(CairoContext, getMiterLimit)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	double miter;


	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoContext_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	miter = cairo_get_miter_limit(curr->context);

	RETURN_DOUBLE(miter);
}
/* }}} getMiterLimit */



/* {{{ proto int getOperator()
   */
PHP_METHOD(CairoContext, getOperator)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;

	long operator;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoContext_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	operator = cairo_get_operator(curr->context);

	RETURN_LONG(operator);
}
/* }}} getOperator */



/* {{{ proto object getScaledFont()
   */
PHP_METHOD(CairoContext, getScaledFont)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoContext_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);

	object_init_ex(return_value, CairoScaledFont_ce_ptr);
	scaledfont_object *sfobj = (scaledfont_object *)zend_objects_get_address(return_value TSRMLS_CC);
	
	sfobj->scaledfont = cairo_scaled_font_reference(cairo_get_scaled_font(curr->context));

}
/* }}} getScaledFont */



/* {{{ proto object getSource()
   */
PHP_METHOD(CairoContext, getSource)
{
	zend_class_entry * _this_ce, *ce;

	zval * _this_zval = NULL;
	cairo_pattern_t *pat;


	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoContext_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);

    pat = cairo_pattern_reference(cairo_get_source(curr->context));

	ce = get_CairoPattern_ce_ptr(pat);
	object_init_ex(return_value, ce);

	pattern_object *ptobj = (pattern_object *)zend_objects_get_address(return_value TSRMLS_CC);
	ptobj->pattern = cairo_pattern_reference(pat);
}
/* }}} getSource */



/* {{{ proto object getTarget()
   */
PHP_METHOD(CairoContext, getTarget)
{
	zend_class_entry * _this_ce, *ce;

	zval * _this_zval = NULL;
	cairo_surface_t *sur;


	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoContext_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	
    sur = cairo_surface_reference(cairo_get_target(curr->context));

	ce = get_CairoSurface_ce_ptr(sur);
	object_init_ex(return_value, ce);

	surface_object *sobj = (surface_object *)zend_objects_get_address(return_value TSRMLS_CC);
	sobj->surface = cairo_surface_reference(sur);

}
/* }}} getTarget */



/* {{{ proto float getTolerance()
   */
PHP_METHOD(CairoContext, getTolerance)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	double tolerance;


	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoContext_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);

	tolerance = cairo_get_tolerance(curr->context);
	RETURN_DOUBLE(tolerance);
}
/* }}} getTolerance */



/* {{{ proto array glyphExtents(array obj,int num) --need to check
   */
PHP_METHOD(CairoContext, glyphExtents)
{
	zend_class_entry * _this_ce;
	int i;
	zval * _this_zval = NULL, **ppzval;
	zval * obj = NULL;
	long num = -1;
	cairo_glyph_t **glyphs=NULL , **glyph;
	HashTable *obj_hash = NULL;
	cairo_text_extents_t extents;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Oa/l", &_this_zval, CairoContext_ce_ptr, &obj, &num) == FAILURE) {
		return;
	}
	obj_hash = HASH_OF(obj);
	glyphs = emalloc(num*sizeof(cairo_glyph_t));

	for(i=0 , glyph=glyphs; i<num; i++, glyph++) {
		zend_hash_get_current_data(obj_hash, (void **)&glyph);
		zend_hash_move_forward(obj_hash);
	}
	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	
	cairo_glyph_extents(curr->context, glyphs, num, &extents);

	array_init(return_value);
	add_assoc_double(return_value, "x_bearing", extents.x_bearing);
	add_assoc_double(return_value, "y_bearing", extents.y_bearing);
	add_assoc_double(return_value, "width", extents.width);
	add_assoc_double(return_value, "height", extents.height);
	add_assoc_double(return_value, "x_advance", extents.x_advance);
	add_assoc_double(return_value, "y_advance", extents.y_advance);
	efree(glyphs);

}
/* }}} glyphExtents */



/* {{{ proto void glyphPath(array obh , int num])
   */
PHP_METHOD(CairoContext, glyphPath)
{
	zend_class_entry * _this_ce;
	int i;
	zval * _this_zval = NULL;
	zval * obh = NULL;
	long num = 0;
    cairo_glyph_t *glyphs=NULL , *glyph;
	HashTable *obj_hash = NULL;
	cairo_text_extents_t extents;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Oa/l", &_this_zval, CairoContext_ce_ptr, &obh, &num) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	obj_hash = HASH_OF(obh);

    glyphs = emalloc(num*sizeof(cairo_glyph_t));
    for(i=0 , glyph=glyphs; i<num; i++, glyph++) {
        zend_hash_get_current_data(obj_hash, (void **)&glyph);
        zend_hash_move_forward(obj_hash);
    }
	cairo_glyph_path(curr->context, glyphs, num);
	phpCAIRO_CONTEXT_ERROR(curr->context);

}
/* }}} glyphPath */



/* {{{ proto bool hasCurrentPoint() -- Need to remove this and put it in path
   */
PHP_METHOD(CairoContext, hasCurrentPoint)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoContext_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);


	do {
		/* ONLY for CAIRO 1.6 */
	} while (0);
}
/* }}} hasCurrentPoint */



/* {{{ proto void identityMatrix()
   */
PHP_METHOD(CairoContext, identityMatrix)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoContext_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_identity_matrix(curr->context);

	phpCAIRO_CONTEXT_ERROR(curr->context);

}
/* }}} identityMatrix */



/* {{{ proto bool inFill(float x, float y)
   */
PHP_METHOD(CairoContext, inFill)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	double x = 0.0;
	double y = 0.0;
	int result;


	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odd", &_this_zval, CairoContext_ce_ptr, &x, &y) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	
	result = cairo_in_fill(curr->context, x, y);
	
	if(result)
		zval_bool(return_value,1);
	else
		zval_bool(return_value,0);


}
/* }}} inFill */



/* {{{ proto bool inStroke(float x, float y)
   */
PHP_METHOD(CairoContext, inStroke)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	double x = 0.0;
	double y = 0.0;
	int result;
	

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odd", &_this_zval, CairoContext_ce_ptr, &x, &y) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);

	result = cairo_in_stroke(curr->context, x, y);
	
	if(result)
		zval_bool(return_value,1);
	else
		zval_bool(return_value,0);

}
/* }}} inStroke */



/* {{{ proto void lineTo(float x, float y)
   */
PHP_METHOD(CairoContext, lineTo)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	double x = 0.0;
	double y = 0.0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odd", &_this_zval, CairoContext_ce_ptr, &x, &y) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	
	cairo_line_to(curr->context, x, y);
	phpCAIRO_CONTEXT_ERROR(curr->context);
	
}
/* }}} lineTo */



/* {{{ proto void mask(object p)
   */
PHP_METHOD(CairoContext, mask)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	zval * p = NULL;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Oo", &_this_zval, CairoContext_ce_ptr, &p) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);

	pattern_object *ptobj = (pattern_object *)zend_objects_get_address(p TSRMLS_CC);
	cairo_mask(curr->context, ptobj->pattern);
	phpCAIRO_CONTEXT_ERROR(curr->context);

}
/* }}} mask */



/* {{{ proto void maskSurface(object s[,float surface_x, float surface_y])
   */
PHP_METHOD(CairoContext, maskSurface)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	zval * s = NULL;
	double surface_x = 0.0;
	double surface_y = 0.0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Oo|dd", &_this_zval, CairoContext_ce_ptr, &s, &surface_x, &surface_y) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	surface_object *sobj=(surface_object *)zend_objects_get_address(s TSRMLS_CC);
	cairo_mask_surface(curr->context, sobj->surface, surface_x, surface_y);
	phpCAIRO_CONTEXT_ERROR(curr->context);
	

}
/* }}} maskSurface */



/* {{{ proto void moveTo(float x, float y)
   */
PHP_METHOD(CairoContext, moveTo)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	double x = 0.0;
	double y = 0.0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odd", &_this_zval, CairoContext_ce_ptr, &x, &y) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	
	cairo_move_to(curr->context, x, y);
	phpCAIRO_CONTEXT_ERROR(curr->context);
	
}
/* }}} moveTo */



/* {{{ proto void newPath()
   */
PHP_METHOD(CairoContext, newPath)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoContext_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_new_path(curr->context);
	phpCAIRO_CONTEXT_ERROR(curr->context);

}
/* }}} newPath */



/* {{{ proto void newSubPath()
   */
PHP_METHOD(CairoContext, newSubPath)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoContext_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);

	cairo_new_sub_path(curr->context);
	phpCAIRO_CONTEXT_ERROR(curr->context);
}
/* }}} newSubPath */



/* {{{ proto void paint()
   */
PHP_METHOD(CairoContext, paint)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoContext_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_paint(curr->context);
	phpCAIRO_CONTEXT_ERROR(curr->context);


}
/* }}} paint */



/* {{{ proto void paintWithAlpha(float alpha)
   */
PHP_METHOD(CairoContext, paintWithAlpha)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	double alpha = 0.0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Od", &_this_zval, CairoContext_ce_ptr, &alpha) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_paint_with_alpha(curr->context, alpha);
		

}
/* }}} paintWithAlpha */



/* {{{ proto array pathExtents([object path]) --- need to shift it to path --
   */
PHP_METHOD(CairoContext, pathExtents)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	zval * path = NULL;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O|o", &_this_zval, CairoContext_ce_ptr, &path) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);


	array_init(return_value);

	do {
		/* ONLY for CAIRO 1.6 */
	} while (0);
}
/* }}} pathExtents */



/* {{{ proto object popGroup()
   */
PHP_METHOD(CairoContext, popGroup)
{
	zend_class_entry * _this_ce, *ce;

	zval * _this_zval = NULL;
	cairo_pattern_t *pat;


	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoContext_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);

    pat = cairo_pop_group(curr->context);
	ce = get_CairoPattern_ce_ptr(pat);
	object_init_ex(return_value, ce);
	pattern_object *ptobj=(pattern_object *)zend_objects_get_address(return_value TSRMLS_CC);
	ptobj->pattern = pat;

}
/* }}} popGroup */



/* {{{ proto void popGroupToSource()
   */
PHP_METHOD(CairoContext, popGroupToSource)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoContext_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_pop_group_to_source(curr->context);
	phpCAIRO_CONTEXT_ERROR(curr->context);


}
/* }}} popGroupToSource */



/* {{{ proto void pushGroup()
   */
PHP_METHOD(CairoContext, pushGroup)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoContext_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_push_group(curr->context);
	phpCAIRO_CONTEXT_ERROR(curr->context);


}
/* }}} pushGroup */



/* {{{ proto void pushGroupWithContent(int content)
   */
PHP_METHOD(CairoContext, pushGroupWithContent)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	cairo_content_t  content;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ol", &_this_zval, CairoContext_ce_ptr, &content) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_push_group_with_content(curr->context, content);
	phpCAIRO_CONTEXT_ERROR(curr->context);

}
/* }}} pushGroupWithContent */



/* {{{ proto void rectangle(float x, float y, float width, float height)
   */
PHP_METHOD(CairoContext, rectangle)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	double x = 0.0;
	double y = 0.0;
	double width = 0.0;
	double height = 0.0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odddd", &_this_zval, CairoContext_ce_ptr, &x, &y, &width, &height) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_rectangle(curr->context, x, y, width, height);
	phpCAIRO_CONTEXT_ERROR(curr->context);
	

}
/* }}} rectangle */



/* {{{ proto void relCurveTo(float x1, float y1, float x2, float y2, float x3, float y3)
   */
PHP_METHOD(CairoContext, relCurveTo)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	double x1 = 0.0;
	double y1 = 0.0;
	double x2 = 0.0;
	double y2 = 0.0;
	double x3 = 0.0;
	double y3 = 0.0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odddddd", &_this_zval, CairoContext_ce_ptr, &x1, &y1, &x2, &y2, &x3, &y3) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_rel_curve_to(curr->context, x1, y1, x2, y2, x3, y3);
	phpCAIRO_CONTEXT_ERROR(curr->context);

}
/* }}} relCurveTo */



/* {{{ proto void relLineTo(float x, float y)
   */
PHP_METHOD(CairoContext, relLineTo)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	double x = 0.0;
	double y = 0.0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odd", &_this_zval, CairoContext_ce_ptr, &x, &y) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_rel_line_to(curr->context, x, y);
    phpCAIRO_CONTEXT_ERROR(curr->context);

}
/* }}} relLineTo */



/* {{{ proto void relMoveTo(float x, float y)
   */
PHP_METHOD(CairoContext, relMoveTo)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	double x = 0.0;
	double y = 0.0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odd", &_this_zval, CairoContext_ce_ptr, &x, &y) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_rel_move_to(curr->context, x, y);
	phpCAIRO_CONTEXT_ERROR(curr->context);
}
/* }}} relMoveTo */



/* {{{ proto void resetClip()
   */
PHP_METHOD(CairoContext, resetClip)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoContext_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_reset_clip(curr->context);
	phpCAIRO_CONTEXT_ERROR(curr->context);


}
/* }}} resetClip */



/* {{{ proto void restore()
   */
PHP_METHOD(CairoContext, restore)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoContext_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);

	cairo_restore(curr->context);
    phpCAIRO_CONTEXT_ERROR(curr->context);


}
/* }}} restore */



/* {{{ proto void rotate(float angle)
   */
PHP_METHOD(CairoContext, rotate)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	double angle = 0.0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Od", &_this_zval, CairoContext_ce_ptr, &angle) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_rotate(curr->context, angle);
    phpCAIRO_CONTEXT_ERROR(curr->context);
	
}
/* }}} rotate */



/* {{{ proto void save()
   */
PHP_METHOD(CairoContext, save)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoContext_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);

	cairo_save(curr->context);
    phpCAIRO_CONTEXT_ERROR(curr->context);

}
/* }}} save */



/* {{{ proto void scale(float x, float y)
   */
PHP_METHOD(CairoContext, scale)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	double x = 0.0;
	double y = 0.0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odd", &_this_zval, CairoContext_ce_ptr, &x, &y) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);

    cairo_scale(curr->context, x, y);
	phpCAIRO_CONTEXT_ERROR(curr->context);


}
/* }}} scale */



/* {{{ proto void selectFontFace(object string[, int slant, int weight])
   */
PHP_METHOD(CairoContext, selectFontFace)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	const char * family = NULL;
	int family_len = 0;
	cairo_font_slant_t slant = CAIRO_FONT_SLANT_NORMAL;
	cairo_font_weight_t weight = CAIRO_FONT_WEIGHT_NORMAL;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Os|ll", &_this_zval, CairoContext_ce_ptr, &family, &family_len, &slant, &weight) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_select_font_face(curr->context, family, slant, weight);
    phpCAIRO_CONTEXT_ERROR(curr->context);

}
/* }}} selectFontFace */



/* {{{ proto void setAntialias([int antialias])
   */
PHP_METHOD(CairoContext, setAntialias)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	cairo_antialias_t antialias = CAIRO_ANTIALIAS_DEFAULT;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O|l", &_this_zval, CairoContext_ce_ptr, &antialias) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_set_antialias(curr->context, antialias);
    phpCAIRO_CONTEXT_ERROR(curr->context);
		
}
/* }}} setAntialias */



/* {{{ proto void setDash(array dashes, int num_dashes [,float offset])
   */
PHP_METHOD(CairoContext, setDash)
{
	zend_class_entry * _this_ce;
	double *das, **d;
	zval * _this_zval = NULL;
	zval * dashes = NULL, **ppzval;
	long num_dashes = 0;
	HashTable *dashes_hash = NULL;
	double offset = 0.0;
	int i;


	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Oa/l|d", &_this_zval, CairoContext_ce_ptr, &dashes, &num_dashes,  &offset) == FAILURE) {
		return;
	}
	dashes_hash = Z_ARRVAL_P(dashes);
	das = emalloc(num_dashes * sizeof(double));
	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	i = zend_hash_num_elements(dashes_hash);
	if(i!=num_dashes)
		printf("Problem !!!");
	i=0;
	for(zend_hash_internal_pointer_reset(dashes_hash); zend_hash_has_more_elements(dashes_hash) == SUCCESS; zend_hash_move_forward(dashes_hash)) { 
		if (zend_hash_get_current_data(dashes_hash, (void **)&ppzval) == FAILURE) {
        continue; 
        } 
		
		das[i++] = Z_DVAL_PP(ppzval);
		
	}
	cairo_set_dash(curr->context, das, num_dashes, offset);
	phpCAIRO_CONTEXT_ERROR(curr->context);
	efree(das);
	

}
/* }}} setDash */



/* {{{ proto void setFillRule(int fill_rule)
   */
PHP_METHOD(CairoContext, setFillRule)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	cairo_fill_rule_t fill_rule = 0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ol", &_this_zval, CairoContext_ce_ptr, &fill_rule) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_set_fill_rule(curr->context, fill_rule);
	phpCAIRO_CONTEXT_ERROR(curr->context);
}
/* }}} setFillRule */



/* {{{ proto void setFontFace([object obj])
   */
PHP_METHOD(CairoContext, setFontFace)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	zval * obj = NULL;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O|o", &_this_zval, CairoContext_ce_ptr, &obj) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	if (obj != NULL) {
		fontface_object *ffobj = (fontface_object *)zend_objects_get_address(obj TSRMLS_CC);
		cairo_set_font_face(curr->context, ffobj->fontface);
	}
	else
		cairo_set_font_face(curr->context, NULL);
	phpCAIRO_CONTEXT_ERROR(curr->context);
		
	
}
/* }}} setFontFace */



/* {{{ proto void setFontMatrix(object matrix)
   */
PHP_METHOD(CairoContext, setFontMatrix)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	zval * matrix = NULL;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Oo", &_this_zval, CairoContext_ce_ptr, &matrix) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	matrix_object *mobj=(matrix_object *)zend_objects_get_address(matrix TSRMLS_CC);
	cairo_set_font_matrix(curr->context, &mobj->matrix);
	phpCAIRO_CONTEXT_ERROR(curr->context);

}
/* }}} setFontMatrix */



/* {{{ proto void setFontOptions(object options)
   */
PHP_METHOD(CairoContext, setFontOptions)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	zval * options = NULL;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Oo", &_this_zval, CairoContext_ce_ptr, &options) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	fontoptions_object *foobj=(fontoptions_object *)zend_objects_get_address(options TSRMLS_CC);
	cairo_set_font_options(curr->context, foobj->fontoptions);
    phpCAIRO_CONTEXT_ERROR(curr->context);	
	

}
/* }}} setFontOptions */



/* {{{ proto void setFontSize(float size)
   */
PHP_METHOD(CairoContext, setFontSize)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	double size = 0.0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Od", &_this_zval, CairoContext_ce_ptr, &size) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_set_font_size(curr->context, size);
    phpCAIRO_CONTEXT_ERROR(curr->context);

}
/* }}} setFontSize */



/* {{{ proto void setLineCap(int line_cap)
   */
PHP_METHOD(CairoContext, setLineCap)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	long line_cap = 0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ol", &_this_zval, CairoContext_ce_ptr, &line_cap) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_set_line_cap(curr->context, line_cap);
    phpCAIRO_CONTEXT_ERROR(curr->context);



}
/* }}} setLineCap */



/* {{{ proto void setLineJoin(int line_join)
   */
PHP_METHOD(CairoContext, setLineJoin)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	long line_join = 0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ol", &_this_zval, CairoContext_ce_ptr, &line_join) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);

	cairo_set_line_join(curr->context, line_join);
    phpCAIRO_CONTEXT_ERROR(curr->context);

}
/* }}} setLineJoin */



/* {{{ proto void setLineWidth(float width)
   */
PHP_METHOD(CairoContext, setLineWidth)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	double width = 0.0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Od", &_this_zval, CairoContext_ce_ptr, &width) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr = (context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_set_line_width(curr->context, width);
}
/* }}} set_line_width */



/* {{{ proto void setMatrix(object matix)
   */
PHP_METHOD(CairoContext, setMatrix)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	zval * matix = NULL;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Oo", &_this_zval, CairoContext_ce_ptr, &matix) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	matrix_object *mobj=(matrix_object *)zend_objects_get_address(matix TSRMLS_CC);
	cairo_set_matrix(curr->context, &mobj->matrix);
    phpCAIRO_CONTEXT_ERROR(curr->context);

}
/* }}} setMatrix */



/* {{{ proto void setMiterLimit(float limit)
   */
PHP_METHOD(CairoContext, setMiterLimit)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	double limit = 0.0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Od", &_this_zval, CairoContext_ce_ptr, &limit) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_set_miter_limit(curr->context, limit);
    phpCAIRO_CONTEXT_ERROR(curr->context);
	
}
/* }}} setMiterLimit */



/* {{{ proto void setOperator(int op)
   */
PHP_METHOD(CairoContext, setOperator)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	long op = 0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ol", &_this_zval, CairoContext_ce_ptr, &op) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_set_operator(curr->context, op);
    phpCAIRO_CONTEXT_ERROR(curr->context);

}
/* }}} setOperator */



/* {{{ proto void setSource(object p)
   */
PHP_METHOD(CairoContext, setSource)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	zval * p = NULL;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Oo", &_this_zval, CairoContext_ce_ptr, &p) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	pattern_object *ptobj=(pattern_object *)zend_objects_get_address(p TSRMLS_CC);
	cairo_set_source(curr->context, ptobj->pattern);
    phpCAIRO_CONTEXT_ERROR(curr->context);

}
/* }}} setSource */



/* {{{ proto void setSourceRgb(float red, float green, float blue)
   */
PHP_METHOD(CairoContext, setSourceRgb)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	double red = 0.0;
	double green = 0.0;
	double blue = 0.0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Oddd", &_this_zval, CairoContext_ce_ptr, &red, &green, &blue) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_set_source_rgb(curr->context, red, green, blue);
    phpCAIRO_CONTEXT_ERROR(curr->context);

}
/* }}} setSourceRgb */



/* {{{ proto void setSourceRgba(float red, float green, float blue [,float alpha])
   */
PHP_METHOD(CairoContext, setSourceRgba)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	double red = 0.0;
	double green = 0.0;
	double blue = 0.0;
	double alpha = 0.0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Oddd|d", &_this_zval, CairoContext_ce_ptr, &red, &green, &blue, &alpha) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_set_source_rgba(curr->context, red, green, blue, alpha);
    phpCAIRO_CONTEXT_ERROR(curr->context);
	
}
/* }}} setSourceRgba */



/* {{{ proto void setSourceSurface(object surface [,float x, float y])
   */
PHP_METHOD(CairoContext, setSourceSurface)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	zval * surface = NULL;
	double x = 0.0;
	double y = 0.0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Oo|dd", &_this_zval, CairoContext_ce_ptr, &surface, &x, &y) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	surface_object *sobj=(surface_object *)zend_objects_get_address(surface TSRMLS_CC);
	cairo_set_source_surface(curr->context, sobj->surface, x, y);
    phpCAIRO_CONTEXT_ERROR(curr->context);

}
/* }}} setSourceSurface */



/* {{{ proto void setTolerance(float tolerance)
   */
PHP_METHOD(CairoContext, setTolerance)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	double tolerance = 0.0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Od", &_this_zval, CairoContext_ce_ptr, &tolerance) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_set_tolerance(curr->context, tolerance);
    phpCAIRO_CONTEXT_ERROR(curr->context);

}
/* }}} setTolerance */



/* {{{ proto void showGlyphs(array obj ,int num_glyphs)
   */
PHP_METHOD(CairoContext, showGlyphs)
{
	zend_class_entry * _this_ce;
	int i;
	zval * _this_zval = NULL, **ppzval;
	zval * obj = NULL;
	long num_glyphs = 0;
	HashTable *obj_hash = NULL;
	cairo_glyph_t *glyphs=NULL, *glyph;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Oa/l", &_this_zval, CairoContext_ce_ptr, &obj, &num_glyphs) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
    obj_hash = HASH_OF(obj);

	glyphs = emalloc(num_glyphs*sizeof(cairo_glyph_t));
	i=0;
    for(zend_hash_internal_pointer_reset(obj_hash); zend_hash_has_more_elements(obj_hash) == SUCCESS; zend_hash_move_forward(obj_hash)) {
        if (zend_hash_get_current_data(obj_hash, (void **)&ppzval) == FAILURE) {
		        continue; 
	        }
//        glyphs[i++] = Z_RESVAL_PP(ppzval);
    }

	
/*	for(i=0 , glyph=glyphs; i<num_glyphs; i++, glyph++) {
		zend_hash_get_current_data(obj_hash, (void **)&glyph);
        zend_hash_move_forward(obj_hash);
    }
*/
	cairo_show_glyphs(curr->context, glyphs, num_glyphs);
	phpCAIRO_CONTEXT_ERROR(curr->context);

}
/* }}} showGlyphs */



/* {{{ proto void showPage()
   */
PHP_METHOD(CairoContext, showPage)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoContext_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_show_page(curr->context);
    phpCAIRO_CONTEXT_ERROR(curr->context);

}
/* }}} showPage */



/* {{{ proto void showText(string obj)
   */
PHP_METHOD(CairoContext, showText)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	const char * obj = NULL;
	int obj_len = 0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Os", &_this_zval, CairoContext_ce_ptr, &obj, &obj_len) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_show_text(curr->context, obj);
    phpCAIRO_CONTEXT_ERROR(curr->context);
	
}
/* }}} showText */



/* {{{ proto void stroke()
   */
PHP_METHOD(CairoContext, stroke)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoContext_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr = (context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_stroke(curr->context);
    phpCAIRO_CONTEXT_ERROR(curr->context);


}
/* }}} stroke */



/* {{{ proto array strokeExtents()
   */
PHP_METHOD(CairoContext, strokeExtents)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	double x1=0, x2=0, y1=0, y2=0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoContext_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_stroke_extents(curr->context, &x1, &y1, &x2, &y2);

	array_init(return_value);
	add_assoc_double(return_value, "x1", x1);
	add_assoc_double(return_value, "y1", y1);
	add_assoc_double(return_value, "x2", x2);
	add_assoc_double(return_value, "y2", y2);

}
/* }}} strokeExtents */



/* {{{ proto void strokePreserve()
   */
PHP_METHOD(CairoContext, strokePreserve)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoContext_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_stroke_preserve(curr->context);
	phpCAIRO_CONTEXT_ERROR(curr->context);

}
/* }}} strokePreserve */



/* {{{ proto array textExtents(string str)
   */
PHP_METHOD(CairoContext, textExtents)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	const char * str = NULL;
	long str_len=0;
	cairo_text_extents_t extents;


	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Os", &_this_zval, CairoContext_ce_ptr, &str, &str_len) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);

	cairo_text_extents(curr->context, str, &extents);

	array_init(return_value);
	add_assoc_double(return_value, "x_bearing", extents.x_bearing);
	add_assoc_double(return_value, "y_bearing", extents.y_bearing);
	add_assoc_double(return_value, "width", extents.width);
	add_assoc_double(return_value, "height", extents.height);
	add_assoc_double(return_value, "x_advance", extents.x_advance);
	add_assoc_double(return_value, "y_advance", extents.y_advance);

}
/* }}} textExtents */



/* {{{ proto void textPath(string obj)
   */
PHP_METHOD(CairoContext, textPath)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	const char * obj = NULL;
	long obj_len = 0; 



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Os", &_this_zval, CairoContext_ce_ptr, &obj, &obj_len) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_text_path(curr->context, obj);
    phpCAIRO_CONTEXT_ERROR(curr->context);

}
/* }}} textPath */



/* {{{ proto void transform(object matrix)
   */
PHP_METHOD(CairoContext, transform)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	zval * matrix = NULL;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Oo", &_this_zval, CairoContext_ce_ptr, &matrix) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	matrix_object *mobj = (matrix_object *)zend_objects_get_address(matrix TSRMLS_CC);
	cairo_transform(curr->context, &mobj->matrix);
    phpCAIRO_CONTEXT_ERROR(curr->context);
	
}
/* }}} transform */



/* {{{ proto void translate(float tx, float ty)
   */
PHP_METHOD(CairoContext, translate)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	double tx = 0.0;
	double ty = 0.0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odd", &_this_zval, CairoContext_ce_ptr, &tx, &ty) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);

	cairo_translate(curr->context, tx, ty);
    phpCAIRO_CONTEXT_ERROR(curr->context);

}
/* }}} translate */



/* {{{ proto array userToDevice(float x, float y)
   */
PHP_METHOD(CairoContext, userToDevice)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	double x = 0.0;
	double y = 0.0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odd", &_this_zval, CairoContext_ce_ptr, &x, &y) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);

	cairo_user_to_device(curr->context, &x, &y);
    phpCAIRO_CONTEXT_ERROR(curr->context);

	array_init(return_value);
	add_assoc_double(return_value, "x", x);
	add_assoc_double(return_value, "y", y);

}
/* }}} userToDevice */



/* {{{ proto array userToDeviceDistance(float dx, float dy)
   */
PHP_METHOD(CairoContext, userToDeviceDistance)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	double dx = 0.0;
	double dy = 0.0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odd", &_this_zval, CairoContext_ce_ptr, &dx, &dy) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);
	context_object *curr=(context_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_user_to_device_distance(curr->context, &dx, &dy);
    phpCAIRO_CONTEXT_ERROR(curr->context);
	
	array_init(return_value);
	add_assoc_double(return_value, "x", dx);
	add_assoc_double(return_value, "y", dy);

}
/* }}} userToDeviceDistance */


static zend_function_entry CairoContext_methods[] = {
	PHP_ME(CairoContext, __construct, NULL, /**/ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(CairoContext, appendPath, CairoContext__append_path_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, arc, CairoContext__arc_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, arcNegative, CairoContext__arc_negative_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, clip, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, clipExtents, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, clipPreserve, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, closePath, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, copyClipRectangleList, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, copyPage, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, copyPath, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, copyPathFlat, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, curveTo, CairoContext__curve_to_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, deviceToUser, CairoContext__device_to_user_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, deviceToUserDistance, CairoContext__device_to_user_distance_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, fill, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, fillExtents, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, fillPreserve, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, fontExtents, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, getAntialias, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, getCurrentPoint, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, getDash, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, getDashCount, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, getFillRule, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, getFontFace, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, getFontMatrix, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, getFontOptions, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, getGroupTarget, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, getLineCap, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, getLineJoin, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, getLineWidth, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, getMatrix, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, getMiterLimit, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, getOperator, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, getScaledFont, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, getSource, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, getTarget, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, getTolerance, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, glyphExtents, CairoContext__glyph_extents_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, glyphPath, CairoContext__glyph_path_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, hasCurrentPoint, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, identityMatrix, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, inFill, CairoContext__in_fill_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, inStroke, CairoContext__in_stroke_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, lineTo, CairoContext__line_to_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, mask, CairoContext__mask_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, maskSurface, CairoContext__mask_surface_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, moveTo, CairoContext__move_to_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, newPath, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, newSubPath, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, paint, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, paintWithAlpha, CairoContext__paint_with_alpha_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, pathExtents, CairoContext__path_extents_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, popGroup, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, popGroupToSource, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, pushGroup, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, pushGroupWithContent, CairoContext__push_group_with_content_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, rectangle, CairoContext__rectangle_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, relCurveTo, CairoContext__rel_curve_to_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, relLineTo, CairoContext__rel_line_to_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, relMoveTo, CairoContext__rel_move_to_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, resetClip, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, restore, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, rotate, CairoContext__rotate_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, save, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, scale, CairoContext__scale_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, selectFontFace, CairoContext__select_font_face_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, setAntialias, CairoContext__set_antialias_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, setDash, CairoContext__set_dash_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, setFillRule, CairoContext__set_fill_rule_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, setFontFace, CairoContext__set_font_face_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, setFontMatrix, CairoContext__set_font_matrix_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, setFontOptions, CairoContext__set_font_options_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, setFontSize, CairoContext__set_font_size_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, setLineCap, CairoContext__set_line_cap_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, setLineJoin, CairoContext__set_line_join_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, setLineWidth, CairoContext__set_line_width_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, setMatrix, CairoContext__set_matrix_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, setMiterLimit, CairoContext__set_miter_limit_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, setOperator, CairoContext__set_operator_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, setSource, CairoContext__set_source_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, setSourceRgb, CairoContext__set_source_rgb_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, setSourceRgba, CairoContext__set_source_rgba_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, setSourceSurface, CairoContext__set_source_surface_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, setTolerance, CairoContext__set_tolerance_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, showGlyphs, CairoContext__show_glyphs_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, showPage, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, showText, CairoContext__show_text_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, stroke, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, strokeExtents, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, strokePreserve, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, textExtents, CairoContext__text_extents_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, textPath, CairoContext__text_path_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, transform, CairoContext__transform_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, translate, CairoContext__translate_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, userToDevice, CairoContext__user_to_device_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoContext, userToDeviceDistance, CairoContext__user_to_device_distance_args, /**/ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

/* }}} Methods */

static zend_object_handlers CairoContext_handlers;

/*
typedef struct _context_object {
	zend_object std;
	cairo_t *context;
} context_object;
*/

static void CairoContext_object_dtor(void *object)
{
    context_object *context = (context_object *)object;
	zend_hash_destroy(context->std.properties);
	FREE_HASHTABLE(context->std.properties);

	if(context->context){
		cairo_destroy(context->context);
	}
	efree(object);
}

static zend_object_value CairoContext_object_new(zend_class_entry *ce)
{
	zend_object_value retval;
	context_object *context;
	zval *temp;

	context=emalloc(sizeof(context_object));
	memset(context,0,sizeof(context_object));
	context->std.ce = ce;
    ALLOC_HASHTABLE(context->std.properties);
    zend_hash_init(context->std.properties, 0, NULL, ZVAL_PTR_DTOR,0);
    zend_hash_copy(context->std.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref, (void *) &temp, sizeof(zval *));
    retval.handle = zend_objects_store_put(context, NULL, (zend_objects_free_object_storage_t)CairoContext_object_dtor, NULL TSRMLS_CC);
    retval.handlers = &CairoContext_handlers;
    return retval;
}



static void class_init_CairoContext(void)
{
	zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "CairoContext", CairoContext_methods);
    CairoContext_ce_ptr = zend_register_internal_class(&ce);
    CairoContext_ce_ptr->create_object = CairoContext_object_new;
    memcpy(&CairoContext_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    CairoContext_handlers.clone_obj=NULL;
}

/* }}} Class CairoContext */

zend_class_entry* get_CairoContext_ce_ptr()
{
	return CairoContext_ce_ptr;
}
