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
#include <zend_exceptions.h>

#include <ext/eos_datastructures/php_eos_datastructures_api.h>

#include "php_cairo.h"
#include "php_cairo_internal.h"


zend_class_entry *ce_cairo_scaled_font;

static zend_object_handlers cairo_scaled_font_object_handlers; 

//typedef struct _cairo_scaled_font_object {
//	zval *font_face;
//	zval *font_options;
//	zval *matrix;
//	zval *ctm;
//	cairo_scaled_font_t *scaled_font;
//        zend_object std;
//} cairo_scaled_font_object;

cairo_scaled_font_object *cairo_scaled_font_fetch_object(zend_object *object)
{
    return (cairo_scaled_font_object *) ((char*)(object) - XtOffsetOf(cairo_scaled_font_object, std));
}

//#define Z_CAIRO_SCALED_FONT_P(zv) cairo_scaled_font_fetch_object(Z_OBJ_P(zv))

static inline cairo_scaled_font_object *cairo_scaled_font_object_get(zval *zv)
{
	cairo_scaled_font_object *object = Z_CAIRO_SCALED_FONT_P(zv);
	if(object->scaled_font == NULL) {
		zend_throw_exception_ex(ce_cairo_exception, 0,
			"Internal scaled_font object missing in %s, you must call parent::__construct in extended classes",
			ZSTR_VAL(Z_OBJCE_P(zv)->name));
		return NULL;
	}
	return object;
}

/* ----------------------------------------------------------------
    Cairo\FontOptions Object management
------------------------------------------------------------------*/

/* {{{ */
static void cairo_scaled_font_free_obj(zend_object *object)
{
    cairo_scaled_font_object *intern = cairo_scaled_font_fetch_object(object);

    if(!intern) {
            return;
    }

    if(intern->font_face != NULL) {
            Z_TRY_DELREF_P(intern->font_face);
    }
    intern->font_face = NULL;
    
    if(intern->font_options != NULL) {
            Z_TRY_DELREF_P(intern->font_options);
    }
    intern->font_options = NULL;
    
    if(intern->matrix != NULL) {
            Z_TRY_DELREF_P(intern->matrix);
    }
    intern->matrix = NULL;
    
    if(intern->ctm != NULL) {
            Z_TRY_DELREF_P(intern->ctm);
    }
    intern->ctm = NULL;
    
    if(intern->scaled_font){
            cairo_scaled_font_destroy(intern->scaled_font);
    }
    intern->scaled_font = NULL;

    zend_object_std_dtor(&intern->std);
}

/* {{{ */
static zend_object* cairo_scaled_font_obj_ctor(zend_class_entry *ce, cairo_scaled_font_object **intern)
{
	cairo_scaled_font_object *object = ecalloc(1, sizeof(cairo_scaled_font_object) + zend_object_properties_size(ce));
        
        object->font_face = NULL;
	object->font_options = NULL;
        object->matrix = NULL;
	object->ctm = NULL;
        object->scaled_font = NULL;
        
	zend_object_std_init(&object->std, ce);
	object->std.handlers = &cairo_scaled_font_object_handlers;
	*intern = object;

	return &object->std;
}
/* }}} */

/* {{{ */
static zend_object* cairo_scaled_font_create_object(zend_class_entry *ce)
{
	cairo_scaled_font_object *scaled_font_obj = NULL;
	zend_object *return_value = cairo_scaled_font_obj_ctor(ce, &scaled_font_obj);

	object_properties_init(&(scaled_font_obj->std), ce);
	return return_value;
}
/* }}} */

/* ----------------------------------------------------------------
    Cairo\FontOptions C API
------------------------------------------------------------------*/

zend_class_entry * php_cairo_get_scaled_font_ce()
{
	return ce_cairo_scaled_font;
}


/* ----------------------------------------------------------------
    Cairo\FontOptions Class API
------------------------------------------------------------------*/

ZEND_BEGIN_ARG_INFO_EX(CairoScaledFont___construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_INFO(0, font_face)
	ZEND_ARG_INFO(0, matrix)
	ZEND_ARG_INFO(0, ctm)
	ZEND_ARG_INFO(0, options)
ZEND_END_ARG_INFO()

/* {{{ proto void __construct(CairoFontFace font_face[, CairoMatrix matrix, CairoMatrix ctm, CairoFontOptions options]) 
       Creates a CairoScaledFont object from a font face and matrices that describe the size of the font and the environment in which it will be used */
PHP_METHOD(CairoScaledFont, __construct)
{
	zval *font_face_zval, *matrix_zval, *ctm_zval, *font_options_zval;
	cairo_scaled_font_object *scaled_font_object;
//	cairo_font_face_object *font_face_object;
//	cairo_matrix_object *matrix_object, *ctm_object;
//	cairo_font_options_object *font_options_object;
        
	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "OOOO", 
                &font_face_zval, ce_cairo_fontface,
                &matrix_zval, ce_cairo_matrix,
                &ctm_zval, ce_cairo_matrix,
                &font_options_zval, ce_cairo_fontoptions) == FAILURE) {
		return;
	}
        
	//font_face_object = (cairo_font_face_object *)Z_CAIRO_FONT_FACE_P(font_face_zval);
	//matrix_object = (cairo_matrix_object *)Z_CAIRO_MATRIX_P(matrix_zval);
	//ctm_object = (cairo_matrix_object *)Z_CAIRO_MATRIX_P(ctm_zval);
	//font_options_object = (cairo_font_options_object *)Z_CAIRO_FONT_OPTIONS_P(font_options_zval);
	
        scaled_font_object = Z_CAIRO_SCALED_FONT_P(getThis());
	if(!scaled_font_object) {
            return;
        }
        
        //scaled_font_object->scaled_font = cairo_scaled_font_create(font_face_object->font_face, matrix_object->matrix, ctm_object->matrix, font_options_object->font_options);
	scaled_font_object->scaled_font = cairo_scaled_font_create(
                cairo_font_face_object_get_font_face(font_face_zval), 
                cairo_matrix_object_get_matrix(matrix_zval), 
                cairo_matrix_object_get_matrix(ctm_zval), 
                cairo_font_options_object_get_font_options(font_options_zval)
        );
	php_cairo_throw_exception(cairo_scaled_font_status(scaled_font_object->scaled_font));
        
	/* we need to be able to get these zvals out later, so ref and store */
	scaled_font_object->font_face = font_face_zval;
//	Z_ADDREF_P(font_face_zval);
	scaled_font_object->matrix = matrix_zval;
//	Z_ADDREF_P(matrix_zval);
	scaled_font_object->ctm = ctm_zval;
//	Z_ADDREF_P(ctm_zval);
	scaled_font_object->font_options = font_options_zval;
//	Z_ADDREF_P(font_options_zval);
}
/* }}} */

/* {{{ proto long CairoScaledFont->getStatus()
       Returns the current integer status of the CairoScaledFont */
PHP_METHOD(CairoScaledFont, getStatus)
{
	cairo_scaled_font_object *scaled_font_object;

        if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }
        
	scaled_font_object = Z_CAIRO_SCALED_FONT_P(getThis());
	if(!scaled_font_object) {
            return;
        }
        
        object_init_ex(return_value, ce_cairo_status);
        php_eos_datastructures_set_enum_value(return_value, cairo_scaled_font_status(scaled_font_object->scaled_font));
}
/* }}} */

/* {{{ proto array CairoScaledFont->getExtents()
       Gets the metrics for a scaled font in an assoc array
*/
PHP_METHOD(CairoScaledFont, getExtents)
{
	cairo_scaled_font_object *scaled_font_object;
	cairo_font_extents_t extents;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }
        
	scaled_font_object = Z_CAIRO_SCALED_FONT_P(getThis());
	if(!scaled_font_object) {
            return;
        }
        
	cairo_scaled_font_extents(scaled_font_object->scaled_font, &extents);

	array_init(return_value);
	add_assoc_double(return_value, "ascent", extents.ascent);
	add_assoc_double(return_value, "descent", extents.descent);
	add_assoc_double(return_value, "height", extents.height);
	add_assoc_double(return_value, "max_x_advance", extents.max_x_advance);
	add_assoc_double(return_value, "max_y_advance", extents.max_y_advance);
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoScaledFont_textExtents_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, text)
ZEND_END_ARG_INFO()

/* {{{ proto array CairoScaledFont->textExtents(string text)
       Gets the extents for a string of UTF8 text.
*/
PHP_METHOD(CairoScaledFont, textExtents)
{
	cairo_scaled_font_object *scaled_font_object;
	char *text, *cairo_text;
	size_t text_len;
	cairo_text_extents_t extents;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "s", &text, &text_len ) == FAILURE) {
		return;
	}

	scaled_font_object = Z_CAIRO_SCALED_FONT_P(getThis());
	if(!scaled_font_object) {
            return;
        }
        
        cairo_text = estrdup(text);
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

ZEND_BEGIN_ARG_INFO(CairoScaledFont_glyphExtents_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, glyphs)
ZEND_END_ARG_INFO()

/* {{{ proto array CairoScaledFont->glyphExtents(array glyphs)
       Gets the extents for an array of glyphs. The extents describe a user-space rectangle that encloses the "inked" portion of the glyphs. */
PHP_METHOD(CairoScaledFont, glyphExtents)
{
	cairo_scaled_font_object *scaled_font_object;
	const cairo_glyph_t *glyphs = NULL;
	int num_glyphs = 0;
	cairo_text_extents_t extents;

	zval * php_glyphs = NULL, *hash_zval;
	HashTable *glyphs_hash = NULL;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "a", &php_glyphs) == FAILURE) {
		return;
	}
        
        scaled_font_object = Z_CAIRO_SCALED_FONT_P(getThis());
	if(!scaled_font_object) {
            return;
        }
        
	/* Grab the zend hash */
	glyphs_hash = Z_ARRVAL_P(php_glyphs);

	/* iterate the array, each value inside MUST be an instance of CairoGlyph */
        ZEND_HASH_FOREACH_VAL(glyphs_hash, hash_zval) {
                /* TODO: check here for is object and instanceof CairoGlyph, then rip the internal glyph out and stick it in the array
		then increment the glyph count
		if (Z_TYPE_P(val) != IS_DOUBLE) {
			convert_to_double(hash_zval);
		}
		dashes_array[i++] = Z_DVAL_P(hash_zval);*/
        } ZEND_HASH_FOREACH_END();

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

/* {{{ proto CairoFontFace object CairoScaledFont->getFontFace()
       Retrieves the font face used to create the scaled font.  */
PHP_METHOD(CairoScaledFont, getFontFace)
{
	cairo_scaled_font_object *scaled_font_object;
	cairo_font_face_object *font_face_object;
	cairo_font_face_t *font_face;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }
        
	scaled_font_object = Z_CAIRO_SCALED_FONT_P(getThis());
	if(!scaled_font_object) {
            return;
        }
        
	/* Grab the font face properly */
	font_face = cairo_scaled_font_get_font_face(scaled_font_object->scaled_font);
	php_cairo_throw_exception(cairo_scaled_font_status(scaled_font_object->scaled_font));
        
	/* If we have a font face object stored, grab that zval to use */
	if(scaled_font_object->font_face) {
		zval_dtor(return_value);
		*return_value = *scaled_font_object->font_face;
		zval_copy_ctor(return_value);
		Z_SET_REFCOUNT_P(return_value, 1);
	/* Otherwise we spawn a new object */
	} else {
		object_init_ex(return_value, ce_cairo_toyfontface);	
	}

	font_face_object = Z_CAIRO_FONT_FACE_P(return_value);
	font_face_object->font_face = font_face;
}
/* }}} */

/* {{{ proto CairoFontOptions object CairoScaledFont->getFontOptions()
       Retrieves the font options used to create the scaled font.  */
PHP_METHOD(CairoScaledFont, getFontOptions)
{
	cairo_scaled_font_object *scaled_font_object;
	cairo_font_options_object *font_options_object;
	cairo_font_options_t *font_options = NULL;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }
        
	scaled_font_object = Z_CAIRO_SCALED_FONT_P(getThis());
	if(!scaled_font_object) {
            return;
        }
        
	/* Grab the font options properly */
	cairo_scaled_font_get_font_options(scaled_font_object->scaled_font, font_options);
	php_cairo_throw_exception(cairo_scaled_font_status(scaled_font_object->scaled_font));

	/* If we have a font options object stored, grab that zval to use */
	if(scaled_font_object->font_options) {
		zval_dtor(return_value);
		*return_value = *scaled_font_object->font_options;
		zval_copy_ctor(return_value);
		Z_SET_REFCOUNT_P(return_value, 1);
	/* Otherwise we spawn a new object */
	} else {
		object_init_ex(return_value, ce_cairo_fontoptions);	
	}

	font_options_object = Z_CAIRO_FONT_OPTIONS_P(return_value);
	font_options_object->font_options = font_options;
}
/* }}} */

/* {{{ proto CairoMatrix object CairoScaledFont->getFontMatrix()
       Returns the font matrix used when creating the scaled font */
PHP_METHOD(CairoScaledFont, getFontMatrix)
{
	cairo_scaled_font_object *scaled_font_object;
	cairo_matrix_object *matrix_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }
        
	scaled_font_object = Z_CAIRO_SCALED_FONT_P(getThis());
	if(!scaled_font_object) {
            return;
        }
        
	/* If we have a matrix object stored, grab that zval to use */
	if(scaled_font_object->matrix) {
		zval_dtor(return_value);
		*return_value = *scaled_font_object->matrix;
		zval_copy_ctor(return_value);
		Z_SET_REFCOUNT_P(return_value, 1);
	/* Otherwise we spawn a new object */
	} else {
		object_init_ex(return_value, ce_cairo_matrix);	
	}

	matrix_object = Z_CAIRO_MATRIX_P(return_value);
	matrix_object->matrix = ecalloc(sizeof(cairo_matrix_t), 1); 
	cairo_scaled_font_get_font_matrix(scaled_font_object->scaled_font, matrix_object->matrix);
}
/* }}} */

/* {{{ proto CairoMatrix object CairoScaledFont->getCtm()
        Returns the ctm matrix used when creating the scaled font */
PHP_METHOD(CairoScaledFont, getCtm)
{
	cairo_scaled_font_object *scaled_font_object;
	cairo_matrix_object *matrix_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }
        
	scaled_font_object = Z_CAIRO_SCALED_FONT_P(getThis());
	if(!scaled_font_object) {
            return;
        }
        
	/* If we have a matrix object stored, grab that zval to use */
	if(scaled_font_object->ctm) {
		zval_dtor(return_value);
		*return_value = *scaled_font_object->ctm;
		zval_copy_ctor(return_value);
		Z_SET_REFCOUNT_P(return_value, 1);
	/* Otherwise we spawn a new object */
	} else {
		object_init_ex(return_value, ce_cairo_matrix);	
	}

	matrix_object = Z_CAIRO_MATRIX_P(return_value);
	matrix_object->matrix = ecalloc(sizeof(cairo_matrix_t), 1); 
	cairo_scaled_font_get_ctm(scaled_font_object->scaled_font, matrix_object->matrix);
}
/* }}} */

/* {{{ proto CairoMatrix object CairoScaledFont->getScaleMatrix()
       The scale matrix is product of the font matrix and the ctm associated with the scaled font, 
       and hence is the matrix mapping from font space to device space */
PHP_METHOD(CairoScaledFont, getScaleMatrix)
{
	cairo_scaled_font_object *scaled_font_object;
	cairo_matrix_object *matrix_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }
        
	scaled_font_object = Z_CAIRO_SCALED_FONT_P(getThis());
	if(!scaled_font_object) {
            return;
        }
        
	/* This is never stored in the object, but created every time */
	object_init_ex(return_value, ce_cairo_matrix);	

	matrix_object = Z_CAIRO_MATRIX_P(return_value);
	matrix_object->matrix = ecalloc(sizeof(cairo_matrix_t), 1); 
	cairo_scaled_font_get_scale_matrix(scaled_font_object->scaled_font, matrix_object->matrix);
}
/* }}} */

/* {{{ proto long CairoScaledFont->getType()
       Returns the current integer type of the CairoScaledFont backend */
PHP_METHOD(CairoScaledFont, getType)
{
	cairo_scaled_font_object *scaled_font_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }
        
	scaled_font_object = Z_CAIRO_SCALED_FONT_P(getThis());
	if(!scaled_font_object) {
            return;
        }
        
        object_init_ex(return_value, ce_cairo_fonttype);
        php_eos_datastructures_set_enum_value(return_value, cairo_scaled_font_get_type(scaled_font_object->scaled_font));
}
/* }}} */

/* ----------------------------------------------------------------
    Cairo\FontOptions Definition and registration
------------------------------------------------------------------*/

/* {{{ cairo_scaled_font_methods[] */
const zend_function_entry cairo_scaled_font_methods[] = {
	PHP_ME(CairoScaledFont, __construct, CairoScaledFont___construct_args, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(CairoScaledFont, getStatus, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CairoScaledFont, getExtents, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CairoScaledFont, textExtents, CairoScaledFont_textExtents_args, ZEND_ACC_PUBLIC)
	PHP_ME(CairoScaledFont, glyphExtents, CairoScaledFont_glyphExtents_args, ZEND_ACC_PUBLIC)
	PHP_ME(CairoScaledFont, getFontFace, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CairoScaledFont, getFontOptions, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CairoScaledFont, getFontMatrix , NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CairoScaledFont, getCtm, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CairoScaledFont, getScaleMatrix, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CairoScaledFont, getType, NULL, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};
/* }}} */

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(cairo_scaled_font)
{
	zend_class_entry scaled_font_ce;

        memcpy(&cairo_scaled_font_object_handlers,
                    zend_get_std_object_handlers(),
                    sizeof(zend_object_handlers));
        
        /* ScaledFont */
        cairo_scaled_font_object_handlers.offset = XtOffsetOf(cairo_scaled_font_object, std);
        cairo_scaled_font_object_handlers.free_obj = cairo_scaled_font_free_obj;
        
        INIT_NS_CLASS_ENTRY(scaled_font_ce, CAIRO_NAMESPACE, "ScaledFont", cairo_scaled_font_methods);
        scaled_font_ce.create_object = cairo_scaled_font_create_object;
        ce_cairo_scaled_font = zend_register_internal_class(&scaled_font_ce);

	return SUCCESS;
}
/* }}} */

