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
  |         Mark Skilbeck <markskilbeck@php.net>                         |
  +----------------------------------------------------------------------+
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "zend_exceptions.h"
#include "php_cairo.h"

zend_class_entry *cairo_ce_cairoscaledfont;

ZEND_BEGIN_ARG_INFO_EX(CairoScaledFont___construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_INFO(0, font_face)
	ZEND_ARG_INFO(0, matrix)
	ZEND_ARG_INFO(0, ctm)
	ZEND_ARG_INFO(0, options)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoScaledFont_textExtents_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, text)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoScaledFont_glyphExtents_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, glyphs)
ZEND_END_ARG_INFO()


/* {{{ proto CairoScaledFont cairo_scaled_font_create(CairoFontFace font_face[, CairoMatrix matrix, CairoMatrix ctm, CairoFontOptions options])
      Creates a CairoScaledFont object from a font face and matrices that describe the size of the font and the environment in which it will be used */
PHP_FUNCTION(cairo_scaled_font_create)
{
	zval *font_face_zval, *matrix_zval, *ctm_zval, *font_options_zval;
	cairo_scaled_font_object *scaled_font_object;
	cairo_font_face_object *font_face_object;
	cairo_matrix_object *matrix_object, *ctm_object;
	cairo_font_options_object *font_options_object;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "OOOO", &font_face_zval, cairo_ce_cairofontface,
		                                                          &matrix_zval, cairo_ce_cairomatrix,
																  &ctm_zval, cairo_ce_cairomatrix,
																  &font_options_zval, cairo_ce_cairofontoptions) == FAILURE) {
		return;
	}

	font_face_object = (cairo_font_face_object *)cairo_font_face_object_get(font_face_zval TSRMLS_CC);
	matrix_object = (cairo_matrix_object *)cairo_matrix_object_get(matrix_zval TSRMLS_CC);
	ctm_object = (cairo_matrix_object *)cairo_matrix_object_get(ctm_zval TSRMLS_CC);
	font_options_object = (cairo_font_options_object *)cairo_font_options_object_get(font_options_zval TSRMLS_CC);

	object_init_ex(return_value, cairo_ce_cairoscaledfont);
	scaled_font_object = (cairo_scaled_font_object *)zend_object_store_get_object(return_value TSRMLS_CC);

	scaled_font_object->scaled_font = cairo_scaled_font_create(font_face_object->font_face, matrix_object->matrix, ctm_object->matrix, font_options_object->font_options);
	php_cairo_trigger_error(cairo_scaled_font_status(scaled_font_object->scaled_font) TSRMLS_CC);

	/* we need to be able to get these zvals out later, so ref and store */
	scaled_font_object->font_face = font_face_zval;
	Z_ADDREF_P(font_face_zval);
	scaled_font_object->matrix = matrix_zval;
	Z_ADDREF_P(matrix_zval);
	scaled_font_object->ctm = ctm_zval;
	Z_ADDREF_P(ctm_zval);
	scaled_font_object->font_options = font_options_zval;
	Z_ADDREF_P(font_options_zval);
}
/* }}} */

/* {{{ proto void __construct(CairoFontFace font_face[, CairoMatrix matrix, CairoMatrix ctm, CairoFontOptions options]) 
       Creates a CairoScaledFont object from a font face and matrices that describe the size of the font and the environment in which it will be used */
PHP_METHOD(CairoScaledFont, __construct)
{
	zval *font_face_zval, *matrix_zval, *ctm_zval, *font_options_zval;
	cairo_scaled_font_object *scaled_font_object;
	cairo_font_face_object *font_face_object;
	cairo_matrix_object *matrix_object, *ctm_object;
	cairo_font_options_object *font_options_object;

	PHP_CAIRO_ERROR_HANDLING(TRUE)
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "OOOO", &font_face_zval, cairo_ce_cairofontface,
		                                                          &matrix_zval, cairo_ce_cairomatrix,
																  &ctm_zval, cairo_ce_cairomatrix,
																  &font_options_zval, cairo_ce_cairofontoptions) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(TRUE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(TRUE)

	font_face_object = (cairo_font_face_object *)cairo_font_face_object_get(font_face_zval TSRMLS_CC);
	matrix_object = (cairo_matrix_object *)cairo_matrix_object_get(matrix_zval TSRMLS_CC);
	ctm_object = (cairo_matrix_object *)cairo_matrix_object_get(ctm_zval TSRMLS_CC);
	font_options_object = (cairo_font_options_object *)cairo_font_options_object_get(font_options_zval TSRMLS_CC);
	
	scaled_font_object = (cairo_scaled_font_object *)zend_object_store_get_object(getThis() TSRMLS_CC);

	scaled_font_object->scaled_font = cairo_scaled_font_create(font_face_object->font_face, matrix_object->matrix, ctm_object->matrix, font_options_object->font_options);
	php_cairo_throw_exception(cairo_scaled_font_status(scaled_font_object->scaled_font) TSRMLS_CC);

	/* we need to be able to get these zvals out later, so ref and store */
	scaled_font_object->font_face = font_face_zval;
	Z_ADDREF_P(font_face_zval);
	scaled_font_object->matrix = matrix_zval;
	Z_ADDREF_P(matrix_zval);
	scaled_font_object->ctm = ctm_zval;
	Z_ADDREF_P(ctm_zval);
	scaled_font_object->font_options = font_options_zval;
	Z_ADDREF_P(font_options_zval);
}
/* }}} */

/* {{{ proto long cairo_scaled_font_status(CairoScaledFont object)
       proto long CairoScaledFont->status()
       Returns the current integer status of the CairoScaledFont */
PHP_FUNCTION(cairo_scaled_font_status)
{
	zval *scaled_font_zval = NULL;
	cairo_scaled_font_object *scaled_font_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &scaled_font_zval, cairo_ce_cairoscaledfont) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	scaled_font_object = (cairo_scaled_font_object *) cairo_scaled_font_object_get(scaled_font_zval TSRMLS_CC);
	RETURN_LONG(cairo_scaled_font_status(scaled_font_object->scaled_font));
}
/* }}} */

/* {{{ proto array cairo_scaled_font_extents(CairoScaledFont object)
       proto array CairoScaledFont->extents()
       Gets the metrics for a scaled font in an assoc array
*/
PHP_FUNCTION(cairo_scaled_font_extents)
{
	zval *scaled_font_zval = NULL;
	cairo_scaled_font_object *scaled_font_object;
	cairo_font_extents_t extents;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", 
				&scaled_font_zval, cairo_ce_cairoscaledfont) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	scaled_font_object = (cairo_scaled_font_object *) cairo_scaled_font_object_get(scaled_font_zval TSRMLS_CC);
	cairo_scaled_font_extents(scaled_font_object->scaled_font, &extents);

	array_init(return_value);
	add_assoc_double(return_value, "ascent", extents.ascent);
	add_assoc_double(return_value, "descent", extents.descent);
	add_assoc_double(return_value, "height", extents.height);
	add_assoc_double(return_value, "max_x_advance", extents.max_x_advance);
	add_assoc_double(return_value, "max_y_advance", extents.max_y_advance);
}
/* }}} */

/* {{{ proto array cairo_scaled_font_text_extents(CairoScaledFont object, string text)
       proto array CairoScaledFont->textExtents(string text)
       Gets the extents for a string of UTF8 text.
*/
PHP_FUNCTION(cairo_scaled_font_text_extents)
{
	zval *scaled_font_zval = NULL;
	cairo_scaled_font_object *scaled_font_object;
	char *text, *cairo_text;
	int text_len;
	cairo_text_extents_t extents;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Os", 
				&scaled_font_zval, cairo_ce_cairoscaledfont,
				&text, &text_len ) == FAILURE) {
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	cairo_text = estrdup(text);

	scaled_font_object = (cairo_scaled_font_object *) cairo_scaled_font_object_get(scaled_font_zval TSRMLS_CC);
	cairo_scaled_font_text_extents(scaled_font_object->scaled_font, cairo_text, &extents);
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

/* {{{ proto array cairo_scaled_font_glyph_extents(CairoScaledFont object, array glyphs)
       proto array CairoScaledFont->glyphPath(array glyphs)
       Gets the extents for an array of glyphs. The extents describe a user-space rectangle that encloses the "inked" portion of the glyphs. */
PHP_FUNCTION(cairo_scaled_font_glyph_extents)
{
	zval *scaled_font_zval = NULL;
	cairo_scaled_font_object *scaled_font_object;
	const cairo_glyph_t *glyphs = NULL;
	long num_glyphs = 0;
	cairo_text_extents_t extents;

	zval * php_glyphs = NULL, **ppzval;
	HashTable *glyphs_hash = NULL;
	int i = 0;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Oa", &scaled_font_zval, cairo_ce_cairoscaledfont, &php_glyphs) == FAILURE) {
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

	scaled_font_object = (cairo_scaled_font_object *) cairo_scaled_font_object_get(scaled_font_zval TSRMLS_CC);
	cairo_scaled_font_glyph_extents(scaled_font_object->scaled_font, glyphs, num_glyphs, &extents);

	array_init(return_value);
	add_assoc_double(return_value, "x_bearing", extents.x_bearing);
	add_assoc_double(return_value, "y_bearing", extents.y_bearing);
	add_assoc_double(return_value, "width", extents.width);
	add_assoc_double(return_value, "height", extents.height);
	add_assoc_double(return_value, "x_advance", extents.x_advance);
	add_assoc_double(return_value, "y_advance", extents.y_advance);
}
/* }}} */

/* {{{ proto CairoFontFace object cairo_scaled_font_get_font_face(CairoScaledFont object)
       proto CairoFontFace object CairoScaledFont->getFontFace()
       Retrieves the font face used to create the scaled font.  */
PHP_FUNCTION(cairo_scaled_font_get_font_face)
{
	zval *scaled_font_zval = NULL;
	cairo_scaled_font_object *scaled_font_object;
	cairo_font_face_object *font_face_object;
	cairo_font_face_t *font_face;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &scaled_font_zval, cairo_ce_cairoscaledfont) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	scaled_font_object = (cairo_scaled_font_object *) cairo_scaled_font_object_get(scaled_font_zval TSRMLS_CC);

	/* Grab the font face properly */
	font_face = cairo_scaled_font_get_font_face(scaled_font_object->scaled_font);
	PHP_CAIRO_ERROR(cairo_scaled_font_status(scaled_font_object->scaled_font));

	/* If we have a font face object stored, grab that zval to use */
	if(scaled_font_object->font_face) {
		zval_dtor(return_value);
		*return_value = *scaled_font_object->font_face;
		zval_copy_ctor(return_value);
		Z_SET_REFCOUNT_P(return_value, 1);
	/* Otherwise we spawn a new object */
	} else {
		object_init_ex(return_value, cairo_ce_cairotoyfontface);	
	}

	font_face_object = (cairo_font_face_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	font_face_object->font_face = font_face;
}
/* }}} */

/* {{{ proto CairoFontOptions object cairo_scaled_font_get_font_options(CairoScaledFont object)
       proto CairoFontOptions object CairoScaledFont->getFontOptions()
       Retrieves the font options used to create the scaled font.  */
PHP_FUNCTION(cairo_scaled_font_get_font_options)
{
	zval *scaled_font_zval = NULL;
	cairo_scaled_font_object *scaled_font_object;
	cairo_font_options_object *font_options_object;
	cairo_font_options_t *font_options = NULL;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &scaled_font_zval, cairo_ce_cairoscaledfont) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	scaled_font_object = (cairo_scaled_font_object *) cairo_scaled_font_object_get(scaled_font_zval TSRMLS_CC);

	/* Grab the font options properly */
	cairo_scaled_font_get_font_options(scaled_font_object->scaled_font, font_options);
	PHP_CAIRO_ERROR(cairo_scaled_font_status(scaled_font_object->scaled_font));

	/* If we have a font options object stored, grab that zval to use */
	if(scaled_font_object->font_options) {
		zval_dtor(return_value);
		*return_value = *scaled_font_object->font_options;
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

/* {{{ proto CairoMatrix object cairo_scaled_font_get_font_matrix(CairoScaledFont object)
       proto CairoMatrix object CairoScaledFont->getFontMatrix()
       Returns the font matrix used when creating the scaled font */
PHP_FUNCTION(cairo_scaled_font_get_font_matrix)
{
	zval *scaled_font_zval = NULL;
	cairo_scaled_font_object *scaled_font_object;
	cairo_matrix_object *matrix_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &scaled_font_zval, cairo_ce_cairoscaledfont) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	scaled_font_object = (cairo_scaled_font_object *) cairo_scaled_font_object_get(scaled_font_zval TSRMLS_CC);

	/* If we have a matrix object stored, grab that zval to use */
	if(scaled_font_object->matrix) {
		zval_dtor(return_value);
		*return_value = *scaled_font_object->matrix;
		zval_copy_ctor(return_value);
		Z_SET_REFCOUNT_P(return_value, 1);
	/* Otherwise we spawn a new object */
	} else {
		object_init_ex(return_value, cairo_ce_cairomatrix);	
	}

	matrix_object = (cairo_matrix_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	matrix_object->matrix = ecalloc(sizeof(cairo_matrix_t), 1); 
	cairo_scaled_font_get_font_matrix(scaled_font_object->scaled_font, matrix_object->matrix);
}
/* }}} */

/* {{{ proto CairoMatrix object cairo_scaled_font_get_ctm (CairoScaledFont object)
       proto CairoMatrix object CairoScaledFont->getCtm()
        Returns the ctm matrix used when creating the scaled font */
PHP_FUNCTION(cairo_scaled_font_get_ctm)
{
	zval *scaled_font_zval = NULL;
	cairo_scaled_font_object *scaled_font_object;
	cairo_matrix_object *matrix_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &scaled_font_zval, cairo_ce_cairoscaledfont) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	scaled_font_object = (cairo_scaled_font_object *) cairo_scaled_font_object_get(scaled_font_zval TSRMLS_CC);

	/* If we have a matrix object stored, grab that zval to use */
	if(scaled_font_object->ctm) {
		zval_dtor(return_value);
		*return_value = *scaled_font_object->ctm;
		zval_copy_ctor(return_value);
		Z_SET_REFCOUNT_P(return_value, 1);
	/* Otherwise we spawn a new object */
	} else {
		object_init_ex(return_value, cairo_ce_cairomatrix);	
	}

	matrix_object = (cairo_matrix_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	matrix_object->matrix = ecalloc(sizeof(cairo_matrix_t), 1); 
	cairo_scaled_font_get_ctm(scaled_font_object->scaled_font, matrix_object->matrix);
}
/* }}} */

#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 8, 0)
/* {{{ proto CairoMatrix object cairo_scaled_font_get_scale_matrix (CairoScaledFont object)
       proto CairoMatrix object CairoScaledFont->getScaleMatrix()
       The scale matrix is product of the font matrix and the ctm associated with the scaled font, and hence is the matrix mapping from font space to device space */
PHP_FUNCTION(cairo_scaled_font_get_scale_matrix)
{
	zval *scaled_font_zval = NULL;
	cairo_scaled_font_object *scaled_font_object;
	cairo_matrix_object *matrix_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &scaled_font_zval, cairo_ce_cairoscaledfont) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	scaled_font_object = (cairo_scaled_font_object *) cairo_scaled_font_object_get(scaled_font_zval TSRMLS_CC);

	/* This is never stored in the object, but created every time */
	object_init_ex(return_value, cairo_ce_cairomatrix);	

	matrix_object = (cairo_matrix_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	matrix_object->matrix = ecalloc(sizeof(cairo_matrix_t), 1); 
	cairo_scaled_font_get_scale_matrix(scaled_font_object->scaled_font, matrix_object->matrix);
}
/* }}} */
#endif

/* {{{ proto long cairo_scaled_font_get_type(CairoScaledFont object)
       proto long CairoScaledFont->getType()
       Returns the current integer type of the CairoScaledFont backend */
PHP_FUNCTION(cairo_scaled_font_get_type)
{
	zval *scaled_font_zval = NULL;
	cairo_scaled_font_object *scaled_font_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &scaled_font_zval, cairo_ce_cairoscaledfont) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	scaled_font_object = (cairo_scaled_font_object *) cairo_scaled_font_object_get(scaled_font_zval TSRMLS_CC);
	RETURN_LONG(cairo_scaled_font_get_type(scaled_font_object->scaled_font));
}
/* }}} */

/* {{{ cairo_scaled_font_methods[] */
const zend_function_entry cairo_scaled_font_methods[] = {
	PHP_ME(CairoScaledFont, __construct, CairoScaledFont___construct_args, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME_MAPPING(status, cairo_scaled_font_status, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(extents, cairo_scaled_font_extents, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(textExtents, cairo_scaled_font_text_extents, CairoScaledFont_textExtents_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(glyphExtents, cairo_scaled_font_glyph_extents, CairoScaledFont_glyphExtents_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(getFontFace, cairo_scaled_font_get_font_face, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(getFontOptions, cairo_scaled_font_get_font_options, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(getFontMatrix,  cairo_scaled_font_get_font_matrix , NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(getCtm, cairo_scaled_font_get_ctm, NULL, ZEND_ACC_PUBLIC)
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 8, 0)
	PHP_ME_MAPPING(getScaleMatrix, cairo_scaled_font_get_scale_matrix, NULL, ZEND_ACC_PUBLIC)
#endif
	PHP_ME_MAPPING(getType, cairo_scaled_font_get_type , NULL, ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};
/* }}} */

static void cairo_scaled_font_object_destroy(void *object TSRMLS_DC)
{
	cairo_scaled_font_object *scaled_font = (cairo_scaled_font_object *)object;
	zend_hash_destroy(scaled_font->std.properties);
	FREE_HASHTABLE(scaled_font->std.properties);

	if(scaled_font->font_face != NULL) {
		Z_DELREF_P(scaled_font->font_face);
		scaled_font->font_face = NULL;
	}
	if(scaled_font->matrix != NULL) {
		Z_DELREF_P(scaled_font->matrix);
		scaled_font->matrix = NULL;
	}
	if(scaled_font->ctm != NULL) {
		Z_DELREF_P(scaled_font->ctm);
		scaled_font->ctm = NULL;
	}
	if(scaled_font->font_options != NULL) {
		Z_DELREF_P(scaled_font->font_options);
		scaled_font->font_options = NULL;
	}

	if(scaled_font->scaled_font){
		cairo_scaled_font_destroy(scaled_font->scaled_font);
	}
	efree(object);
}

static zend_object_value cairo_scaled_font_object_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	cairo_scaled_font_object *scaled_font;
#if PHP_VERSION_ID < 50399
	zval *temp;
#endif

	scaled_font = ecalloc(1, sizeof(cairo_scaled_font_object));

	scaled_font->std.ce = ce;
	scaled_font->font_face = NULL;
	scaled_font->matrix = NULL;
	scaled_font->ctm = NULL;
	scaled_font->font_options = NULL;

	ALLOC_HASHTABLE(scaled_font->std.properties);
	zend_hash_init(scaled_font->std.properties, 0, NULL, ZVAL_PTR_DTOR, 0);
#if PHP_VERSION_ID < 50399
	zend_hash_copy(scaled_font->std.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref,(void *) &temp, sizeof(zval *));
#else
	object_properties_init(&scaled_font->std, ce);
#endif
	retval.handle = zend_objects_store_put(scaled_font, NULL, (zend_objects_free_object_storage_t)cairo_scaled_font_object_destroy, NULL TSRMLS_CC);
	retval.handlers = zend_get_std_object_handlers();
	return retval;
}

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(cairo_scaled_font)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "CairoScaledFont", cairo_scaled_font_methods);
	cairo_ce_cairoscaledfont = zend_register_internal_class(&ce TSRMLS_CC);
	cairo_ce_cairoscaledfont->create_object = cairo_scaled_font_object_new;

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
