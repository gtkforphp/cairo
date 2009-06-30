/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2009 The PHP Group                                |
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
  |         Akshat Gupta <g.akshat@gmail.com>                            |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "zend_exceptions.h"
#include "php_cairo.h"

zend_class_entry *cairo_ce_cairoscaledfont;

/* {{{ proto void contruct()
   CairoFontFace CANNOT be extended in userspace, this will throw an exception on use */
PHP_METHOD(CairoFontFace, __construct)
{
	zend_throw_exception(cairo_ce_cairoexception, "CairoFontFace cannot be constructed", 0 TSRMLS_CC);
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
       Retrieves the default font rendering options for the surface.  */
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
		object_init_ex(return_value, cairo_ce_cairoscaledfont);	
	}

	font_face_object = (cairo_font_face_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	font_face_object->font_face = font_face;
	cairo_surface_reference(font_face_object->font_face);
}
/* }}} */

/* {{{ proto CairoFontOptions object cairo_scaled_font_get_font_options(CairoScaledFont object)
       proto CairoFontOptions object CairoScaledFont->getFontOptions()
       Retrieves the font options used when the scaled font was created.  */
PHP_FUNCTION(cairo_scaled_font_get_font_options)
{
	zval *scaled_font_zval = NULL;
	cairo_scaled_font_object *scaled_font_object;
	cairo_font_options_object *font_options_object;
	cairo_font_options_t *font_face;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &scaled_font_zval, cairo_ce_cairoscaledfont) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	scaled_font_object = (cairo_scaled_font_object *) cairo_scaled_font_object_get(scaled_font_zval TSRMLS_CC);

	/* Grab the font options properly */
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
		object_init_ex(return_value, cairo_ce_cairoscaledfont);	
	}

	font_face_object = (cairo_font_face_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	font_face_object->font_face = font_face;
	cairo_surface_reference(font_face_object->font_face);
}
/* }}} */


/* {{{ proto long cairo_font_face_get_type(CairoFontFace object)
   proto long CairoFontFace::getType()
   Returns the current integer type of the CairoFontFace backend */
PHP_FUNCTION(cairo_font_face_get_type)
{
	zval *font_face_zval = NULL;
	cairo_font_face_object *font_face_object;

	PHP_CAIRO_ERROR_HANDLING
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &font_face_zval, cairo_ce_cairofontface) == FAILURE) {
		return;
	}

	font_face_object = (cairo_font_face_object *) cairo_font_face_object_get(font_face_zval TSRMLS_CC);
	RETURN_LONG(cairo_font_face_get_type(font_face_object->font_face));
}
/* }}} */

/* {{{ cairo_font_face_methods[] */
const zend_function_entry cairo_font_face_methods[] = {
	PHP_ME_MAPPING(status, cairo_font_face_status, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(getType, cairo_font_face_get_type, NULL, ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};
/* }}} */

static void cairo_font_face_object_destroy(void *object TSRMLS_DC)
{
	cairo_font_face_object *font_face = (cairo_font_face_object *)object;
	zend_hash_destroy(font_face->std.properties);
	FREE_HASHTABLE(font_face->std.properties);
	if(font_face->font_face){
		cairo_font_face_destroy(font_face->font_face);
	}
	efree(object);
}

static zend_object_value cairo_scaled_font_object_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	cairo_scaled_font_object *scaled_font;
	zval *temp;

	scaled_font = ecalloc(1, sizeof(cairo_scaled_font_object));

	scaled_font->std.ce = ce;

	ALLOC_HASHTABLE(scaled_font->std.properties);
	zend_hash_init(scaled_font->std.properties, 0, NULL, ZVAL_PTR_DTOR, 0);
	zend_hash_copy(scaled_font->std.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref,(void *) &temp, sizeof(zval *));
	retval.handle = zend_objects_store_put(scaled_font, NULL, (zend_objects_free_object_storage_t)cairo_scaled_font_object_destroy, NULL TSRMLS_CC);
	retval.handlers = zend_get_std_object_handlers();
	return retval;
}

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(cairo_scaled_font)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "CairoScaledFont", CairoScaledFont_methods);
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
