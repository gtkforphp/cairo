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

#include "php_cairo_api.h"
#include "php_cairo_internal.h"
#include <zend_exceptions.h>

static zend_class_entry * CairoFontFace_ce_ptr = NULL;
static zend_class_entry * CairoFontOptions_ce_ptr = NULL;
static zend_class_entry * CairoScaledFont_ce_ptr = NULL;

/* Helper Functions */

PHP_CAIRO_API zend_class_entry * get_CairoFontFace_ce_ptr()
{
	return CairoFontFace_ce_ptr;
}

PHP_CAIRO_API zend_class_entry * get_CairoFontOptions_ce_ptr()
{
	return CairoFontOptions_ce_ptr;
}

PHP_CAIRO_API cairo_font_options_t * cairo_copy_fontoptions(cairo_font_options_t *fo)
{
	return cairo_font_options_copy(fo);
}

PHP_CAIRO_API zend_class_entry * get_CairoScaledFont_ce_ptr()
{
	return CairoScaledFont_ce_ptr;
}

/* {{{ arginfo */
ZEND_BEGIN_ARG_INFO_EX(CairoFontOptions__set_antialias_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
  ZEND_ARG_INFO(0, aa)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(CairoFontOptions__set_hint_metrics_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
  ZEND_ARG_INFO(0, hm)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(CairoFontOptions__set_hint_style_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
  ZEND_ARG_INFO(0, hs)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(CairoFontOptions__set_subpixel_order_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
  ZEND_ARG_INFO(0, so)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(CairoScaledFont____construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 3)
  ZEND_ARG_OBJ_INFO(0, mx1, CairoMatrix, 1)
  ZEND_ARG_OBJ_INFO(0, mx2, CairoMatrix, 1)
  ZEND_ARG_OBJ_INFO(0, fo, CairoFontOptions, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(CairoScaledFont__text_extents_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, str)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ Class CairoFontFace */



/* {{{ Methods */


/* {{{ proto void construct()
   */
PHP_METHOD(CairoFontFace, __construct)
{
	zend_throw_exception(CairoException_ce_ptr, "CairoFontFace cannot be constructed, please use CairoContext::getFontFace", 0 TSRMLS_CC);
}
/* }}} __construct */

static zend_function_entry CairoFontFace_methods[] = {
	PHP_ME(CairoFontFace, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	{ NULL, NULL, NULL }
};

/* }}} Methods */

static zend_object_handlers CairoFontFace_handlers;

static void CairoFontFace_object_dtor(void *object TSRMLS_DC)
{
	cairo_fontface_object *fontface = (cairo_fontface_object *)object;
	zend_hash_destroy(fontface->std.properties);
	FREE_HASHTABLE(fontface->std.properties);
		
	if(fontface->fontface){
		cairo_font_face_destroy(fontface->fontface);
	}	
	efree(object);
}	

static zend_object_value CairoFontFace_object_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	cairo_fontface_object *fontface;
	zval *temp;
	fontface = emalloc(sizeof(cairo_fontface_object));
	memset(fontface,0,sizeof(cairo_fontface_object));
	fontface->std.ce = ce;
	ALLOC_HASHTABLE(fontface->std.properties);
	zend_hash_init(fontface->std.properties, 0, NULL, ZVAL_PTR_DTOR,0);
	zend_hash_copy(fontface->std.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref, (void *) &temp, sizeof(zval *));
	retval.handle = zend_objects_store_put(fontface, NULL, (zend_objects_free_object_storage_t)CairoFontFace_object_dtor, NULL TSRMLS_CC);
	retval.handlers = &CairoFontFace_handlers;
	return retval;
}


void class_init_CairoFontFace(TSRMLS_D)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "CairoFontFace", CairoFontFace_methods);
	CairoFontFace_ce_ptr = zend_register_internal_class(&ce TSRMLS_CC);
	CairoFontFace_ce_ptr->create_object = CairoFontFace_object_new;
	memcpy(&CairoFontFace_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	CairoFontFace_handlers.clone_obj = NULL;
}

/* }}} Class CairoFontFace */


/* {{{ Class CairoFontOptions */



/* {{{ Methods */


/* {{{ proto void construct()
   */
PHP_METHOD(CairoFontOptions, __construct)
{
	zval * _this_zval;
	cairo_fontoptions_object *curr;


	if (ZEND_NUM_ARGS()>0)	{
		WRONG_PARAM_COUNT;
	}
	_this_zval = getThis();
	curr = (cairo_fontoptions_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	curr->fontoptions = cairo_font_options_create();

}
/* }}} __construct */



/* {{{ proto int getAntialias()
   */
PHP_METHOD(CairoFontOptions, getAntialias)
{

	zval * _this_zval = NULL;
	cairo_fontoptions_object *curr;	

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoFontOptions_ce_ptr) == FAILURE) {
		return;
	}

	curr = (cairo_fontoptions_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	RETURN_LONG(cairo_font_options_get_antialias(curr->fontoptions));

}
/* }}} getAntialias */



/* {{{ proto int getHintMetrics()
   */
PHP_METHOD(CairoFontOptions, getHintMetrics)
{

	zval * _this_zval = NULL;
	cairo_fontoptions_object *curr;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoFontOptions_ce_ptr) == FAILURE) {
		return;
	}


	curr = (cairo_fontoptions_object *)zend_objects_get_address(_this_zval TSRMLS_CC);

	RETURN_LONG(cairo_font_options_get_hint_metrics(curr->fontoptions));
}
/* }}} getHintMetrics */



/* {{{ proto int getHintStyle()
   */
PHP_METHOD(CairoFontOptions, getHintStyle)
{

	zval * _this_zval = NULL;
	cairo_fontoptions_object *curr;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoFontOptions_ce_ptr) == FAILURE) {
		return;
	}

	curr = (cairo_fontoptions_object *)zend_objects_get_address(_this_zval TSRMLS_CC);

	RETURN_LONG(cairo_font_options_get_hint_style(curr->fontoptions));
}
/* }}} getHintStyle */



/* {{{ proto int getSubpixelOrder()
   */
PHP_METHOD(CairoFontOptions, getSubpixelOrder)
{

	zval * _this_zval = NULL;
	cairo_fontoptions_object *curr;


	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoFontOptions_ce_ptr) == FAILURE) {
		return;
	}

	curr = (cairo_fontoptions_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	
	RETURN_LONG(cairo_font_options_get_subpixel_order(curr->fontoptions));
}
/* }}} getSubpixelOrder */



/* {{{ proto void setAntialias([int aa])
   */
PHP_METHOD(CairoFontOptions, setAntialias)
{

	zval * _this_zval = NULL;
	cairo_antialias_t aa = CAIRO_ANTIALIAS_DEFAULT;
	cairo_fontoptions_object *curr;


	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O|l", &_this_zval, CairoFontOptions_ce_ptr, &aa) == FAILURE) {
		return;
	}

	curr = (cairo_fontoptions_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_font_options_set_antialias(curr->fontoptions, aa);
	PHP_CAIRO_FONTOPTIONS_ERROR(curr->fontoptions);

}
/* }}} setAntialias */



/* {{{ proto void setHintMetrics([int hm])
   */
PHP_METHOD(CairoFontOptions, setHintMetrics)
{

	zval * _this_zval = NULL;
	cairo_hint_metrics_t hm = CAIRO_HINT_METRICS_DEFAULT;
	cairo_fontoptions_object *curr;


	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O|l", &_this_zval, CairoFontOptions_ce_ptr, &hm) == FAILURE) {
		return;
	}


	curr = (cairo_fontoptions_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_font_options_set_hint_metrics(curr->fontoptions, hm);
	PHP_CAIRO_FONTOPTIONS_ERROR(curr->fontoptions);

}
/* }}} setHintMetrics */



/* {{{ proto void setHintStyle([int hs])
   */
PHP_METHOD(CairoFontOptions, setHintStyle)
{

	zval * _this_zval = NULL;
	cairo_hint_style_t hs = CAIRO_HINT_STYLE_DEFAULT;
	cairo_fontoptions_object *curr;


	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O|l", &_this_zval, CairoFontOptions_ce_ptr, &hs) == FAILURE) {
		return;
	}

	curr = (cairo_fontoptions_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_font_options_set_hint_style(curr->fontoptions, hs);
	PHP_CAIRO_FONTOPTIONS_ERROR(curr->fontoptions);

}
/* }}} setHintStyle */



/* {{{ proto void setSubpixelOrder([int so])
   */
PHP_METHOD(CairoFontOptions, setSubpixelOrder)
{

	zval * _this_zval = NULL;
	cairo_subpixel_order_t so = CAIRO_SUBPIXEL_ORDER_DEFAULT;
	cairo_fontoptions_object *curr;


	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O|l", &_this_zval, CairoFontOptions_ce_ptr, &so) == FAILURE) {
		return;
	}

	curr = (cairo_fontoptions_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_font_options_set_subpixel_order(curr->fontoptions, so);
	PHP_CAIRO_FONTOPTIONS_ERROR(curr->fontoptions);

}
/* }}} setSubpixelOrder */


static zend_function_entry CairoFontOptions_methods[] = {
	PHP_ME(CairoFontOptions, __construct, NULL, /**/ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(CairoFontOptions, getAntialias, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoFontOptions, getHintMetrics, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoFontOptions, getHintStyle, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoFontOptions, getSubpixelOrder, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoFontOptions, setAntialias, CairoFontOptions__set_antialias_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoFontOptions, setHintMetrics, CairoFontOptions__set_hint_metrics_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoFontOptions, setHintStyle, CairoFontOptions__set_hint_style_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoFontOptions, setSubpixelOrder, CairoFontOptions__set_subpixel_order_args, /**/ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

/* }}} Methods */


static zend_object_handlers CairoFontOptions_handlers;

static void CairoFontOptions_object_dtor(void *object TSRMLS_DC)
{
	cairo_fontoptions_object *fontoptions = (cairo_fontoptions_object *)object;
	zend_hash_destroy(fontoptions->std.properties);
	FREE_HASHTABLE(fontoptions->std.properties);
	
	if(fontoptions->fontoptions){
		cairo_font_options_destroy(fontoptions->fontoptions);
	}	
	efree(object);
}	

static zend_object_value CairoFontOptions_object_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	cairo_fontoptions_object *fontoptions;
	zval *temp;
	fontoptions = emalloc(sizeof(cairo_fontoptions_object));
	memset(fontoptions,0,sizeof(cairo_fontoptions_object));
	fontoptions->std.ce = ce;
	ALLOC_HASHTABLE(fontoptions->std.properties);
	zend_hash_init(fontoptions->std.properties, 0, NULL, ZVAL_PTR_DTOR,0);
	zend_hash_copy(fontoptions->std.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref, (void *) &temp, sizeof(zval *));
	retval.handle = zend_objects_store_put(fontoptions, NULL, (zend_objects_free_object_storage_t)CairoFontOptions_object_dtor, NULL TSRMLS_CC);
	retval.handlers = &CairoFontOptions_handlers;
	return retval;
}


void class_init_CairoFontOptions(TSRMLS_D)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "CairoFontOptions", CairoFontOptions_methods);
	CairoFontOptions_ce_ptr = zend_register_internal_class(&ce TSRMLS_CC);
	CairoFontOptions_ce_ptr->create_object = CairoFontOptions_object_new;
	memcpy(&CairoFontOptions_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	CairoFontOptions_handlers.clone_obj = NULL;
}


/* }}} Class CairoFontOptions */


/* {{{ Class CairoScaledFont */



/* {{{ Methods */


/* {{{ proto void construct(object ff, object mx1, object mx2, object fo)
   */
PHP_METHOD(CairoScaledFont, __construct)
{
	zval * _this_zval;

	zval * ff = NULL;
	zval * mx1 = NULL;
	zval * mx2 = NULL;
	zval * fo = NULL;
	cairo_fontface_object *ffobj;
	cairo_scaledfont_object *curr;
	cairo_matrix_object *mobj1, *mobj2;
	cairo_fontoptions_object *foobj;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "oooo", &ff, &mx1, &mx2, &fo) == FAILURE) {
		return;
	}

	_this_zval = getThis();
	curr = (cairo_scaledfont_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	ffobj = (cairo_fontface_object *)zend_objects_get_address(ff TSRMLS_CC);
	mobj1 = (cairo_matrix_object *)zend_objects_get_address(mx1 TSRMLS_CC);
	mobj2 = (cairo_matrix_object *)zend_objects_get_address(mx2 TSRMLS_CC);
	foobj = (cairo_fontoptions_object *)zend_objects_get_address(fo TSRMLS_CC);
	curr->scaledfont = cairo_scaled_font_create(ffobj->fontface, &mobj1->matrix, &mobj2->matrix, foobj->fontoptions);

}
/* }}} __construct */



/* {{{ proto array extents()
   */
PHP_METHOD(CairoScaledFont, extents)
{

	zval * _this_zval = NULL;

	cairo_font_extents_t e;
	cairo_scaledfont_object *curr;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoScaledFont_ce_ptr) == FAILURE) {
		return;
	}

	curr = (cairo_scaledfont_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_scaled_font_extents(curr->scaledfont, &e);
	
	PHP_CAIRO_SCALEDFONT_ERROR(curr->scaledfont);
	array_init(return_value);
	add_assoc_double(return_value, "ascent", e.ascent);
	add_assoc_double(return_value, "descent", e.descent);
	add_assoc_double(return_value, "height", e.height);
	add_assoc_double(return_value, "max_x_advance", e.max_x_advance);
	add_assoc_double(return_value, "max_y_advance", e.max_y_advance);

}
/* }}} extents */



/* {{{ proto object getFontFace()
   */
PHP_METHOD(CairoScaledFont, getFontFace)
{

	zval * _this_zval = NULL;
	cairo_scaledfont_object *curr;
	cairo_fontface_object *ffobj;


	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoScaledFont_ce_ptr) == FAILURE) {
		return;
	}

	curr = (cairo_scaledfont_object *)zend_objects_get_address(_this_zval TSRMLS_CC);

	object_init_ex(return_value, CairoFontFace_ce_ptr);
	ffobj = (cairo_fontface_object *)zend_objects_get_address(return_value TSRMLS_CC);
	ffobj->fontface = cairo_font_face_reference(cairo_scaled_font_get_font_face(curr->scaledfont));

}
/* }}} getFontFace */



/* {{{ proto array textExtents(string str)
   */
PHP_METHOD(CairoScaledFont, textExtents)
{

	zval * _this_zval = NULL;
	const char * str = NULL;
	int str_len = 0;
	cairo_text_extents_t extents;
	cairo_scaledfont_object *curr;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Os", &_this_zval, CairoScaledFont_ce_ptr, &str, &str_len) == FAILURE) {
		return;
	}

	curr = (cairo_scaledfont_object *)zend_objects_get_address(_this_zval TSRMLS_CC);

	cairo_scaled_font_text_extents(curr->scaledfont, str, &extents);
	PHP_CAIRO_SCALEDFONT_ERROR(curr->scaledfont);

	array_init(return_value);
	add_assoc_double(return_value, "x_bearing", extents.x_bearing);
	add_assoc_double(return_value, "y_bearing", extents.y_bearing);
	add_assoc_double(return_value, "width", extents.width);
	add_assoc_double(return_value, "height", extents.height);
	add_assoc_double(return_value, "x_advance", extents.x_advance);
	add_assoc_double(return_value, "y_advance", extents.y_advance);

}
/* }}} textExtents */


static zend_function_entry CairoScaledFont_methods[] = {
	PHP_ME(CairoScaledFont, __construct, CairoScaledFont____construct_args, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(CairoScaledFont, extents, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CairoScaledFont, getFontFace, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CairoScaledFont, textExtents, CairoScaledFont__text_extents_args, ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

/* }}} Methods */


static zend_object_handlers CairoScaledFont_handlers;

static void CairoScaledFont_object_dtor(void *object TSRMLS_DC)
{
	cairo_scaledfont_object *scaledfont = (cairo_scaledfont_object *)object;
	zend_hash_destroy(scaledfont->std.properties);
	FREE_HASHTABLE(scaledfont->std.properties);
			
	if(scaledfont->scaledfont){
		cairo_scaled_font_destroy(scaledfont->scaledfont);
	}	
	efree(object);
}	

static zend_object_value CairoScaledFont_object_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	cairo_scaledfont_object *scaledfont;
	zval *temp;
	scaledfont = emalloc(sizeof(cairo_scaledfont_object));
	memset(scaledfont,0,sizeof(cairo_scaledfont_object));
	scaledfont->std.ce = ce;
	ALLOC_HASHTABLE(scaledfont->std.properties);
	zend_hash_init(scaledfont->std.properties, 0, NULL, ZVAL_PTR_DTOR,0);
	zend_hash_copy(scaledfont->std.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref, (void *) &temp, sizeof(zval *));
	retval.handle = zend_objects_store_put(scaledfont, NULL, (zend_objects_free_object_storage_t)CairoScaledFont_object_dtor, NULL TSRMLS_CC);
	retval.handlers = &CairoScaledFont_handlers;
	return retval;
}


void class_init_CairoScaledFont(TSRMLS_D)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "CairoScaledFont", CairoScaledFont_methods);
	CairoScaledFont_ce_ptr = zend_register_internal_class(&ce TSRMLS_CC);
	CairoScaledFont_ce_ptr->create_object = CairoScaledFont_object_new;
	memcpy(&CairoScaledFont_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	CairoScaledFont_handlers.clone_obj = NULL;
}
/* }}} Class CairoScaledFont */
	
/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw = 4 ts = 4 fdm = marker
 * vim<600: noet sw = 4 ts = 4
 */