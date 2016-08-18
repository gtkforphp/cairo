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

zend_class_entry *ce_cairo_context;
zend_class_entry *ce_cairo_fillrule;
zend_class_entry *ce_cairo_linecap;
zend_class_entry *ce_cairo_linejoin;
zend_class_entry *ce_cairo_operator;


//typedef struct _cairo_context_object {
//	zval *surface;
//	zval *matrix;
//	zval *pattern;
//	zval *font_face;
//	zval *font_matrix;
//	zval *font_options;
//	zval *scaled_font;
//	cairo_t *context;
//        zend_object std;
//} cairo_context_object;

static zend_object_handlers cairo_context_object_handlers; 

cairo_context_object *cairo_context_fetch_object(zend_object *object)
{
    return (cairo_context_object *) ((char*)(object) - XtOffsetOf(cairo_context_object, std));
}

//#define cairo_context_object_get(zv) cairo_context_fetch_object(Z_OBJ_P(zv))

cairo_context_object *cairo_context_object_get(zval *zv)
{
	cairo_context_object *object = Z_CAIRO_CONTEXT_P(zv);
	if(object->context == NULL) {
		zend_throw_exception_ex(ce_cairo_exception, 0,
			"Internal context object missing in %s, you must call parent::__construct in extended classes",
			ZSTR_VAL(Z_OBJCE_P(zv)->name));
		return NULL;
	}
	return object;
}


/* ----------------------------------------------------------------
    Cairo\Context C API
------------------------------------------------------------------*/

/* {{{ */
cairo_t *cairo_context_object_get_context(zval *zv)
{
	cairo_context_object *context_object = cairo_context_object_get(zv);
	return context_object->context;
}
/* }}} */

zend_class_entry* php_cairo_get_context_ce()
{
	return ce_cairo_context;
}

extern cairo_t * php_cairo_context_reference(cairo_t *context)
{
	return cairo_reference(context);
}


/* ----------------------------------------------------------------
    Cairo\Context Object management
------------------------------------------------------------------*/

/* {{{ */
static void cairo_context_free_obj(zend_object *object)
{
    cairo_context_object *intern = cairo_context_fetch_object(object);

    if(!intern) {
            return;
    }

//    if(intern->surface) {
//            Z_DELREF_P(intern->surface);
//            intern->surface = NULL;
//    }
//    if(intern->matrix) {
//            Z_DELREF_P(intern->matrix);
//            intern->matrix = NULL;
//    }
//    if(intern->pattern) {
//            Z_DELREF_P(intern->pattern);
//            intern->pattern = NULL;
//    }
//    if(intern->font_face) {
//            Z_DELREF_P(intern->font_face);
//            intern->font_face = NULL;
//    }
//    if(intern->font_matrix) {
//            Z_DELREF_P(intern->font_matrix);
//            intern->font_matrix = NULL;
//    }
//    if(intern->font_options) {
//            Z_DELREF_P(intern->font_options);
//            intern->font_options = NULL;
//    }
//    if(intern->scaled_font) {
//            Z_DELREF_P(intern->scaled_font);
//            intern->scaled_font = NULL;
//    }

    if(intern->context){
            cairo_destroy(intern->context);
    }

    zend_object_std_dtor(&intern->std);
}
/* }}} */

/* {{{ */
static zend_object* cairo_context_obj_ctor(zend_class_entry *ce, cairo_context_object **intern)
{
	cairo_context_object *object = ecalloc(1, sizeof(cairo_context_object) + zend_object_properties_size(ce));
        
        object->surface = NULL;
	object->matrix = NULL;
	object->pattern = NULL;
	object->font_face = NULL;
	object->font_matrix = NULL;
	object->scaled_font = NULL;
        
	zend_object_std_init(&object->std, ce);
	object->std.handlers = &cairo_context_object_handlers;
	*intern = object;

	return &object->std;
}
/* }}} */

/* {{{ */
zend_object* cairo_context_create_object(zend_class_entry *ce)
{
	cairo_context_object *context = NULL;
	zend_object *return_value = cairo_context_obj_ctor(ce, &context);

	object_properties_init(&(context->std), ce);
	return return_value;
}
/* }}} */

/* ----------------------------------------------------------------
    Cairo\Context Class API
------------------------------------------------------------------*/

/* Basic Context */
ZEND_BEGIN_ARG_INFO(CairoContext___construct_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(1, surface, Cairo\\Surface, 0)
ZEND_END_ARG_INFO()

/* {{{ proto void __construct(object surface) 
   Returns new CairoContext object on the requested surface */
PHP_METHOD(CairoContext, __construct)
{
	zval *surface_zval = NULL;
	cairo_context_object *context_object;
	cairo_surface_object *surface_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "z/", &surface_zval) == FAILURE) {
		return;
	}
        
        surface_object = cairo_surface_object_get( surface_zval );
        if(!surface_object) {
            return;
        }
        
        context_object = Z_CAIRO_CONTEXT_P(getThis());
	if(!context_object) {
            return;
        }
        
	context_object->context = cairo_create(surface_object->surface);
	php_cairo_throw_exception(cairo_status(context_object->context));

	/* we need to be able to get this zval out later, so ref and store */
	context_object->surface = surface_zval;
        //Z_ADDREF_P(surface_zval);
}
/* }}} */

/* {{{ proto long CairoContext->getStatus()
   Returns the current integer status of the CairoContext */
PHP_METHOD(CairoContext, getStatus)
{
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }

        context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
        object_init_ex(return_value, ce_cairo_status);
        php_eos_datastructures_set_enum_value(return_value, cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto void CairoContext->save()
   Makes a copy of the current state of the context and saves it on an internal stack of saved states */
PHP_METHOD(CairoContext, save)
{
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }

        context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	cairo_save(context_object->context);
	php_cairo_throw_exception(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto void CairoContext->restore()
   Restores the context to the state saved and removes that state from the stack of saved states */
PHP_METHOD(CairoContext, restore)
{
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }

        context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	cairo_restore(context_object->context);
	php_cairo_throw_exception(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto void CairoContext->pushGroup()
   Temporarily redirects drawing to an intermediate surface known as a group. */
PHP_METHOD(CairoContext, pushGroup)
{
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }

        context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	cairo_push_group(context_object->context);
	php_cairo_throw_exception(cairo_status(context_object->context));
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoContext_pushGroupWithContent_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, content)
ZEND_END_ARG_INFO()

/* {{{ proto void CairoContext->pushGroupWithContent(int content)
   Temporarily redirects drawing to an intermediate surface known as a group. */
PHP_METHOD(CairoContext, pushGroupWithContent)
{
	/* should be cairo_content_t but we need a long */
        zend_long content;
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "l", &content) == FAILURE) {
		return;
	}
	
        context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	cairo_push_group_with_content(context_object->context, content);
	php_cairo_throw_exception(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto CairoPattern object CairoContext->popGroup()
   Terminates the redirection and returns a new pattern containing the results of all drawing operations performed to the group. */
PHP_METHOD(CairoContext, popGroup)
{
	cairo_pattern_t *pattern;
	cairo_context_object *context_object;
	cairo_pattern_object *pattern_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }

        context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	pattern = cairo_pop_group(context_object->context);
	php_cairo_throw_exception(cairo_status(context_object->context));

	object_init_ex(return_value, php_cairo_get_pattern_ce(pattern));
	pattern_object = Z_CAIRO_PATTERN_P(return_value);
	pattern_object->pattern = pattern;
        cairo_pattern_reference(pattern_object->pattern);
}
/* }}} */

/* {{{ proto void CairoContext->popGroupToSource()
   Terminates the redirection and installs the resulting pattern as the source pattern in the given cairo context. */
PHP_METHOD(CairoContext, popGroupToSource)
{
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }

        context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	cairo_pop_group_to_source(context_object->context);
	php_cairo_throw_exception(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto CairoSurface object CairoContext->getGroupSurface()
   renamed from getGroupTarget()
   Gets the current destination surface for the context */
PHP_METHOD(CairoContext, getGroupSurface)
{
	cairo_surface_t *surface;
	cairo_context_object *context_object;
	cairo_surface_object *surface_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }

        context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	surface = cairo_get_group_target(context_object->context);
	php_cairo_throw_exception(cairo_status(context_object->context));

	object_init_ex(return_value, php_cairo_get_surface_ce(surface));
	surface_object = Z_CAIRO_SURFACE_P(return_value);
	surface_object->surface = cairo_get_group_target(context_object->context);
	cairo_surface_reference(surface_object->surface);
}
/* }}} */


ZEND_BEGIN_ARG_INFO(CairoContext_setSourceRGB_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, red)
	ZEND_ARG_INFO(0, green)
	ZEND_ARG_INFO(0, blue)
ZEND_END_ARG_INFO()

/* {{{ proto void CairoContext->setSourceRGB(float red, float green, float blue)
   Sets the source pattern within context to an opaque color. This opaque color will then be used for any subsequent drawing operation until a new source pattern is set.  */
PHP_METHOD(CairoContext, setSourceRGB)
{
	double red = 0.0, green = 0.0, blue = 0.0;
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "ddd", &red, &green, &blue) == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	cairo_set_source_rgb(context_object->context, red, green, blue);
	php_cairo_throw_exception(cairo_status(context_object->context));
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoContext_setSourceRGBA_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, red)
	ZEND_ARG_INFO(0, green)
	ZEND_ARG_INFO(0, blue)
	ZEND_ARG_INFO(0, alpha)
ZEND_END_ARG_INFO()

/* {{{ proto void CairoContext->setSourceRGBA(float red, float green, float blue, float alpha)
   Sets the source pattern within context to an translucent  color. This opaque color will then be used for any subsequent drawing operation until a new source pattern is set.  */
PHP_METHOD(CairoContext, setSourceRGBA)
{
	double red = 0.0, green = 0.0, blue = 0.0, alpha = 1.0;
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "dddd", &red, &green, &blue, &alpha) == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	cairo_set_source_rgba(context_object->context, red, green, blue, alpha);
	php_cairo_throw_exception(cairo_status(context_object->context));
}
/* }}} */

ZEND_BEGIN_ARG_INFO_EX(CairoContext_setSurface_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_OBJ_INFO(1, surface, Cairo\\Surface, 0)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

/* {{{ proto void CairoContext->setSurface(object surface [,float x, float y])
       renamed from setSourceSurface()
       This is a convenience function for creating a pattern from surface and setting it as the source
   */
PHP_METHOD(CairoContext, setSurface)
{
	zval *surface_zval = NULL;
	cairo_context_object *context_object;
	cairo_surface_object *surface_object;
	double x = 0.0, y = 0.0;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "z/|dd", &surface_zval, &x, &y) == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	surface_object = Z_CAIRO_SURFACE_P(surface_zval);
        
	cairo_set_source_surface(context_object->context, surface_object->surface, x, y);
	php_cairo_throw_exception(cairo_status(context_object->context));

	/* If there's already a pattern, then we deref and remove it because we just overwrote it */
	if(context_object->pattern) {
//		Z_DELREF_P(context_object->pattern);
		context_object->pattern = NULL;
	}
        
        /* If there's already a surface, then we deref and remove it */
	if(context_object->surface) {
//		Z_DELREF_P(context_object->surface);
		context_object->surface = NULL;
	}

	/* we need to be able to get this zval out later, so ref and store */
	context_object->surface = surface_zval;
	//Z_ADDREF_P(surface_zval);
}
/* }}} */


/* {{{ proto CairoSurface object CairoContext->getSurface
   renamed from getTarget()
   Gets the target surface for the cairo context that was set on creation */
PHP_METHOD(CairoContext, getSurface)
{
	cairo_surface_t *surface;
	cairo_context_object *context_object;
	cairo_surface_object *surface_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }

        context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	/* Grab the surface properly */
	surface = cairo_get_target(context_object->context);
	php_cairo_throw_exception(cairo_status(context_object->context));

	/* If we have a surface stored, grab that zval to use */
	if(context_object->surface != NULL) {
		zval_dtor(return_value);
		*return_value = *context_object->surface;
		zval_copy_ctor(return_value);
//		Z_SET_REFCOUNT_P(return_value, 1);
	/* Otherwise we spawn a new object */
	} else {
		object_init_ex(return_value, php_cairo_get_surface_ce(surface));
	}
	
	/* Get the surface_object and replace the internal surface pointer with what we fetched (should be the same) */
	surface_object = Z_CAIRO_SURFACE_P(return_value);
        
	/* if there IS a value in surface, destroy it cause we're getting a new one */
	if (surface_object->surface != NULL) {
		cairo_surface_destroy(surface_object->surface);
	}
        
	surface_object->surface = surface;
	cairo_surface_reference(surface_object->surface);
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoContext_setPattern_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(1, pattern, Cairo\\Pattern, 0)
ZEND_END_ARG_INFO()

/* {{{ proto void CairoContext->setPattern(CairoPattern object)
   renamed from setSource()
   Sets the source pattern within context to source. 
   This pattern will then be used for any subsequent drawing operation until a new source pattern is set. */
PHP_METHOD(CairoContext, setPattern)
{
	zval *pattern_zval = NULL;
	cairo_context_object *context_object;
	cairo_pattern_object *pattern_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "z/", &pattern_zval) == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	pattern_object = Z_CAIRO_PATTERN_P(pattern_zval);
	cairo_set_source(context_object->context, pattern_object->pattern);
	php_cairo_throw_exception(cairo_status(context_object->context));

	/* If there's already a pattern, then we deref and remove it */
	if(context_object->pattern) {
//		Z_DELREF_P(context_object->pattern);
		context_object->pattern = NULL;
	}

	/* we need to be able to get this zval out later, so ref and store */
	context_object->pattern = pattern_zval;
//	Z_ADDREF_P(pattern_zval);
}
/* }}} */

/* {{{ proto CairoPattern object CairoContext->getPattern()
   renamed from getSource()
   Gets the current source pattern for the context. */
PHP_METHOD(CairoContext, getPattern)
{
	cairo_pattern_t *pattern;
	cairo_context_object *context_object;
	cairo_pattern_object *pattern_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }

        context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	pattern = cairo_get_source(context_object->context);
	php_cairo_throw_exception(cairo_status(context_object->context));

	/* If we have a patter/source object stored, grab that zval to use */
	if(context_object->pattern) {
		zval_dtor(return_value);
		*return_value = *context_object->pattern;
		zval_copy_ctor(return_value);
//		Z_SET_REFCOUNT_P(return_value, 1);
	/* Otherwise we spawn a new object */
	} else {
		object_init_ex(return_value, php_cairo_get_pattern_ce(pattern));
	}
	
	/* Get the pattern object and replace the internal pattern pointer with what we fetched (should be the same) */
	pattern_object = Z_CAIRO_PATTERN_P(return_value);
        
	/* if there IS a value in pattern, destroy it cause we're getting a new one */
	if (pattern_object->pattern != NULL) {
		cairo_pattern_destroy(pattern_object->pattern);
	}
        
	pattern_object->pattern = pattern;
	cairo_pattern_reference(pattern_object->pattern);
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoContext_setAntialias_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, antialias)
ZEND_END_ARG_INFO()

/* {{{ proto void CairoContext->setAntialias([int antialias])
   Set the antialiasing mode of the rasterizer used for drawing shapes. */
PHP_METHOD(CairoContext, setAntialias)
{
	cairo_context_object *context_object;
        zend_long antialias = CAIRO_ANTIALIAS_DEFAULT;
        zval *antialias_enum;

	if (zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET|ZEND_PARSE_PARAMS_THROW,
		ZEND_NUM_ARGS(), "O", &antialias_enum, ce_cairo_antialias) == FAILURE) {
		if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "|l", &antialias) == FAILURE) {
			return;
		} else {
			if(!php_eos_datastructures_check_value(ce_cairo_antialias, antialias)) {
				return;
			}
		}
	} else {
		antialias = php_eos_datastructures_get_enum_value(antialias_enum);
	}
        
	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	cairo_set_antialias(context_object->context, antialias);
	php_cairo_throw_exception(cairo_status(context_object->context));	
}
/* }}} */

/* {{{ proto int CairoContext->getAntialias()
   Gets the current shape antialiasing mode */
PHP_METHOD(CairoContext, getAntialias)
{
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }

        context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
        object_init_ex(return_value, ce_cairo_antialias);
        php_eos_datastructures_set_enum_value(return_value, cairo_get_antialias(context_object->context));
}
/* }}} */

ZEND_BEGIN_ARG_INFO_EX(CairoContext_setDash_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_INFO(0, dashes)
	ZEND_ARG_INFO(0, offset)
ZEND_END_ARG_INFO()

/* {{{ proto void CairoContext->setDash(array dashes [, float offset])
   Sets the dash pattern to be used by cairo_stroke() */
PHP_METHOD(CairoContext, setDash)
{
	cairo_context_object *context_object;
	double offset = 0.0;
	long num_dashes = 0;
	double *dashes_array;
	zval * dashes = NULL, *pzval;
	HashTable *dashes_hash = NULL;
	int i = 0;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "a/|d", &dashes, &offset) == FAILURE) {
		return;
	}

	/* Grab the zend hash and see how big our array will be */
	dashes_hash = Z_ARRVAL_P(dashes);
	num_dashes = zend_hash_num_elements(dashes_hash);
	dashes_array = emalloc(num_dashes * sizeof(double));

	/* iterate the array, make sure we JUGGLE the value to a double */
        ZEND_HASH_FOREACH_VAL(dashes_hash, pzval) {
            if (Z_TYPE_P(pzval) != IS_DOUBLE) {
                    convert_to_double(pzval);
            }
            dashes_array[i++] = Z_DVAL_P(pzval);
        } ZEND_HASH_FOREACH_END();
        
	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	/* we use i in case we had a bad issue while iterating the array */
	cairo_set_dash(context_object->context, dashes_array, i, offset);
	efree(dashes_array);
	php_cairo_throw_exception(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto int CairoContext->getDashCount()
   This function returns the length of the dash array or 0 */
PHP_METHOD(CairoContext, getDashCount)
{
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }

        context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	RETURN_LONG(cairo_get_dash_count(context_object->context));
}
/* }}} */

/* {{{ proto array CairoContext->getDash()
   Gets the current dash array and offset */
PHP_METHOD(CairoContext, getDash)
{
	zval sub_array;
	cairo_context_object *context_object;
	double *dashes = NULL;
	double offset = 0;
	int num_dashes, i;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }

        context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	/* Setup container for dashes */
	num_dashes = cairo_get_dash_count(context_object->context);
	dashes = emalloc(num_dashes * sizeof(double));

	/* Get dashes and push into PHP array */
	cairo_get_dash(context_object->context, dashes, &offset);

	array_init(&sub_array);
	for(i = 0; i < num_dashes; i++) {
		add_next_index_double(&sub_array, dashes[i]);
	}
	efree(dashes);
	
	/* Put dashes and offset into return */
	array_init(return_value);
	add_assoc_zval(return_value, "dashes", &sub_array);
	add_assoc_double(return_value, "offset", offset);
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoContext_setFillRule_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, fillrule)
ZEND_END_ARG_INFO()

/* {{{ proto void CairoContext->setFillRule(int setting)
   Set the current fill rule within the cairo context. The fill rule is used
   to determine which regions are inside or outside a complex path */
PHP_METHOD(CairoContext, setFillRule)
{
	cairo_context_object *context_object;
	zend_long fillrule = 0;
	zval *fillrule_enum;

	if (zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET|ZEND_PARSE_PARAMS_THROW,
		ZEND_NUM_ARGS(), "O", &fillrule_enum, ce_cairo_fillrule) == FAILURE) {
		if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "l", &fillrule) == FAILURE) {
			return;
		} else {
			if(!php_eos_datastructures_check_value(ce_cairo_fillrule, fillrule)) {
				return;
			}
		}
	} else {
		fillrule = php_eos_datastructures_get_enum_value(fillrule_enum);
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	cairo_set_fill_rule(context_object->context, fillrule);
	php_cairo_throw_exception(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto int CairoContext->getFillRule()
   Gets the current fill rule */
PHP_METHOD(CairoContext, getFillRule)
{
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }

        context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
        object_init_ex(return_value, ce_cairo_fillrule);
        php_eos_datastructures_set_enum_value(return_value, cairo_get_fill_rule(context_object->context));
}
/* }}}  */

ZEND_BEGIN_ARG_INFO(CairoContext_setLineCap_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, linecap)
ZEND_END_ARG_INFO()

/* {{{ proto void CairoContext->setLineCap(int linecap)
   Sets the current line cap style within the cairo context. */
PHP_METHOD(CairoContext, setLineCap)
{
	cairo_context_object *context_object;
	zend_long linecap = 0;
	zval *linecap_enum;

	if (zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET|ZEND_PARSE_PARAMS_THROW,
		ZEND_NUM_ARGS(), "O", &linecap_enum, ce_cairo_linecap) == FAILURE) {
		if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "l", &linecap) == FAILURE) {
			return;
		} else {
			if(!php_eos_datastructures_check_value(ce_cairo_linecap, linecap)) {
				return;
			}
		}
	} else {
		linecap = php_eos_datastructures_get_enum_value(linecap_enum);
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	cairo_set_line_cap(context_object->context, linecap);
	php_cairo_throw_exception(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto int CairoContext->getLineCap()
   Gets the current line cap style */
PHP_METHOD(CairoContext, getLineCap)
{
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }

        context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
        object_init_ex(return_value, ce_cairo_linecap);
        php_eos_datastructures_set_enum_value(return_value, cairo_get_line_cap(context_object->context));
}
/* }}}  */

ZEND_BEGIN_ARG_INFO(CairoContext_setLineJoin_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, linejoin)
ZEND_END_ARG_INFO()

/* {{{ proto void CairoContext->setLineJoin(int setting)
   Sets the current line join style within the cairo context. */
PHP_METHOD(CairoContext, setLineJoin)
{
	cairo_context_object *context_object;
	zend_long linejoin = 0;
	zval *linejoin_enum;

	if (zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET|ZEND_PARSE_PARAMS_THROW,
		ZEND_NUM_ARGS(), "O", &linejoin_enum, ce_cairo_linejoin) == FAILURE) {
		if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "l", &linejoin) == FAILURE) {
			return;
		} else {
			if(!php_eos_datastructures_check_value(ce_cairo_linejoin, linejoin)) {
				return;
			}
		}
	} else {
		linejoin = php_eos_datastructures_get_enum_value(linejoin_enum);
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	cairo_set_line_join(context_object->context, linejoin);
	php_cairo_throw_exception(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto int CairoContext->getLineJoin()
   Gets the current line join style */
PHP_METHOD(CairoContext, getLineJoin)
{
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }

        context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
        object_init_ex(return_value, ce_cairo_linejoin);
        php_eos_datastructures_set_enum_value(return_value, cairo_get_line_join(context_object->context));
}
/* }}}  */

ZEND_BEGIN_ARG_INFO(CairoContext_setLineWidth_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, width)
ZEND_END_ARG_INFO()

/* {{{ proto void CairoContext->setLineWidth(float width)
   Sets the current line width within the cairo context. The line width value
   specifies the diameter of a pen that is circular in user space */
PHP_METHOD(CairoContext, setLineWidth)
{
	cairo_context_object *context_object;
	double width = 0.0;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "d", &width) == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	cairo_set_line_width(context_object->context, width);
	php_cairo_throw_exception(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto double CairoContext->getLineWidth()
   This function returns the current line width value exactly as set by cairo_set_line_width() */
PHP_METHOD(CairoContext, getLineWidth)
{
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }

        context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	RETURN_DOUBLE(cairo_get_line_width(context_object->context));
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoContext_setMiterLimit_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, limit)
ZEND_END_ARG_INFO()

/* {{{ proto void CairoContext->setMiterLimit(float limit)
   Sets the current miter limit within the cairo context. */
PHP_METHOD(CairoContext, setMiterLimit)
{
	cairo_context_object *context_object;
	double limit = 0.0;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "d", &limit) == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	cairo_set_miter_limit(context_object->context, limit);
	php_cairo_throw_exception(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto double CairoContext->getMiterLimit()
   Gets the current miter limit */
PHP_METHOD(CairoContext, getMiterLimit)
{
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }

        context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	RETURN_DOUBLE(cairo_get_miter_limit(context_object->context));
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoPattern_setOperator_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, operator)
ZEND_END_ARG_INFO()

/* {{{ proto void CairoContext->setOperator(int setting)
   Sets the compositing operator to be used for all drawing operations. */
PHP_METHOD(CairoContext, setOperator)
{
	cairo_context_object *context_object;
	zend_long operator = 0;
	zval *operator_enum;

	if (zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET|ZEND_PARSE_PARAMS_THROW,
		ZEND_NUM_ARGS(), "O", &operator_enum, ce_cairo_operator) == FAILURE) {
		if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "l", &operator) == FAILURE) {
			return;
		} else {
			if(!php_eos_datastructures_check_value(ce_cairo_operator, operator)) {
				return;
			}
		}
	} else {
		operator = php_eos_datastructures_get_enum_value(operator_enum);
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	cairo_set_operator(context_object->context, operator);
	php_cairo_throw_exception(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto int CairoContext->getOperator()
   Gets the current compositing operator for a cairo context. */
PHP_METHOD(CairoContext, getOperator)
{
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }

        context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
        object_init_ex(return_value, ce_cairo_operator);
        php_eos_datastructures_set_enum_value(return_value, cairo_get_operator(context_object->context));
}
/* }}}  */

ZEND_BEGIN_ARG_INFO(CairoContext_setTolerance_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, tolerance)
ZEND_END_ARG_INFO()

/* {{{ proto void CairoContext->setTolerance(float tolerance)
   Sets the tolerance used when converting paths into trapezoids. */
PHP_METHOD(CairoContext, setTolerance)
{
	cairo_context_object *context_object;
	double tolerance = 0.1;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "d", &tolerance) == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	cairo_set_tolerance(context_object->context, tolerance);
	php_cairo_throw_exception(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto double CairoContext->getTolerance()
   Gets the current tolerance value */
PHP_METHOD(CairoContext, getTolerance)
{
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }

        context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	RETURN_DOUBLE(cairo_get_tolerance(context_object->context));
}
/* }}} */

/* {{{ proto void CairoContext->clip()
   Establishes a new clip region by intersecting the current clip region with the current path as it
   would be filled by cairo_fill() and according to the current fill rule */
PHP_METHOD(CairoContext, clip)
{
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }

        context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	cairo_clip(context_object->context);
	php_cairo_throw_exception(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto boolean CairoContext->inClip(double x, double y)
   Tests whether the given point is inside the area that would be visible 
   through the current clip
*/
PHP_METHOD(CairoContext, inClip)
{
	cairo_context_object *context_object;
	double x = 0.0, y = 0.0;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "dd", &x, &y) == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	RETURN_BOOL(cairo_in_clip(context_object->context, x, y));
}
/* }}} */

/* {{{ proto void CairoContext->clipPreserve()
   Establishes a new clip region by intersecting the current clip region with the current path as it
   would be filled by cairo_fill() and according to the current fill rule
   Unlike cairo_clip(), cairo_clip_preserve() preserves the path within the cairo context. */
PHP_METHOD(CairoContext, clipPreserve)
{
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }

        context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	cairo_clip_preserve(context_object->context);
	php_cairo_throw_exception(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto void CairoContext->resetClip()
   Reset the current clip region to its original, unrestricted state. */
PHP_METHOD(CairoContext, resetClip)
{
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }

        context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	cairo_reset_clip(context_object->context);
	php_cairo_throw_exception(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto array CairoContext->clipExtents()
   Computes a bounding box in user coordinates covering the area inside the current clip. */
PHP_METHOD(CairoContext, clipExtents)
{
	cairo_context_object *context_object;
	double x1, y1, x2, y2;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }

        context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	cairo_clip_extents(context_object->context, &x1, &y1, &x2, &y2);
	php_cairo_throw_exception(cairo_status(context_object->context));

	array_init(return_value);
	add_next_index_double(return_value, x1);
	add_next_index_double(return_value, y1);
	add_next_index_double(return_value, x2);
	add_next_index_double(return_value, y2);
}
/* }}} */

/* {{{ proto array CairoContext->clipRectangleList()
   Gets the current stroke region as a list of rectangles in user coordinates. */
PHP_METHOD(CairoContext, clipRectangleList)
{
	cairo_context_object *context_object;
	cairo_rectangle_list_t *rectangles;
        zval new_array;
	int i;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }

        context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	rectangles = cairo_copy_clip_rectangle_list(context_object->context);
	php_cairo_throw_exception(rectangles->status);

	/* walk our rectangles, create array, push it onto return */
	array_init(return_value);

	for (i = 0; i < rectangles->num_rectangles; i++) {
		cairo_rectangle_t rectangle = rectangles->rectangles[i];
                
		array_init(&new_array);
		add_assoc_double(&new_array, "x", rectangle.x);
		add_assoc_double(&new_array, "y", rectangle.y);
		add_assoc_double(&new_array, "width", rectangle.width);
		add_assoc_double(&new_array, "height", rectangle.height);
		add_next_index_zval(return_value, &new_array);
	}

	/* don't forget to clean up */
	cairo_rectangle_list_destroy(rectangles);
}
/* }}} */

/* {{{ proto void CairoContext->fill()
   A drawing operator that fills the current path according to the current fill rule,
   (each sub-path is implicitly closed before being filled). */
PHP_METHOD(CairoContext, fill)
{
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }

        context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	cairo_fill(context_object->context);
	php_cairo_throw_exception(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto void CairoContext->fillPreserve()
   A drawing operator that fills the current path according to the current fill rule,
   (each sub-path is implicitly closed before being filled). Unlike cairo_fill(),
   cairo_fill_preserve() preserves the path within the cairo context.  */
PHP_METHOD(CairoContext, fillPreserve)
{
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }

        context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	cairo_fill_preserve(context_object->context);
	php_cairo_throw_exception(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto array CairoContext->fillExtents()
   Computes a bounding box in user coordinates covering the area that would be affected,
   (the "inked" area), by a cairo_fill() operation given the current path and fill parameters. */
PHP_METHOD(CairoContext, fillExtents)
{
	cairo_context_object *context_object;
	double x1, y1, x2, y2;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }

        context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	cairo_fill_extents(context_object->context, &x1, &y1, &x2, &y2);
	php_cairo_throw_exception(cairo_status(context_object->context));

	array_init(return_value);
	add_next_index_double(return_value, x1);
	add_next_index_double(return_value, y1);
	add_next_index_double(return_value, x2);
	add_next_index_double(return_value, y2);
}
/* }}} */

/* {{{ proto bool CairoContext->inFill(int x, int y)
   Tests whether the given point is inside the area that would be affected by a cairo_fill()
   operation given the current path and filling parameters. */
PHP_METHOD(CairoContext, inFill)
{
	cairo_context_object *context_object;
	double x = 0.0, y = 0.0;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "dd", &x, &y) == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	RETURN_BOOL(cairo_in_fill(context_object->context, x, y));
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoContext_mask_args, ZEND_SEND_BY_VAL)
	//ZEND_ARG_INFO(0, pattern)
	ZEND_ARG_OBJ_INFO(1, pattern, Cairo\\Pattern, 0)
ZEND_END_ARG_INFO()

/* {{{ proto void CairoContext->mask(CairoPattern object)
   A drawing operator that paints the current source using the alpha channel of pattern as a mask.  */
PHP_METHOD(CairoContext, mask)
{
	zval *pattern_zval = NULL;
	cairo_context_object *context_object;
	cairo_pattern_object *pattern_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "z/", &pattern_zval) == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	pattern_object = Z_CAIRO_PATTERN_P(pattern_zval);
	cairo_mask(context_object->context, pattern_object->pattern);
	php_cairo_throw_exception(cairo_status(context_object->context));
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoContext_maskSurface_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(1, surface, Cairo\\Surface, 0)
        ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

/* {{{ proto void CairoContext->maskSurface(object surface [,float x, float y])
       A drawing operator that paints the current source using the alpha channel of surface as a mask.
   */
PHP_METHOD(CairoContext, maskSurface)
{
	zval *surface_zval = NULL;
	cairo_context_object *context_object;
	cairo_surface_object *surface_object;
	double x = 0.0, y = 0.0;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "z/|dd", &surface_zval, &x, &y) == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	surface_object = Z_CAIRO_SURFACE_P(surface_zval);
	cairo_mask_surface(context_object->context, surface_object->surface, x, y);
	php_cairo_throw_exception(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto void CairoContext->paint()
   A drawing operator that paints the current source everywhere within the current clip region. */
PHP_METHOD(CairoContext, paint)
{
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }

        context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	cairo_paint(context_object->context);
	php_cairo_throw_exception(cairo_status(context_object->context));
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoContext_paintWithAlpha_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, alpha)
ZEND_END_ARG_INFO()

/* {{{ proto void CairoContext->paintWithAlpha(float alpha)
   A drawing operator that paints the current source everywhere within the current clip region using a mask of constant alpha value alpha. */
PHP_METHOD(CairoContext, paintWithAlpha)
{
	cairo_context_object *context_object;
	double alpha = 0.0;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "d", &alpha) == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	cairo_paint_with_alpha(context_object->context, alpha);
	php_cairo_throw_exception(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto void CairoContext->stroke()
   A drawing operator that strokes the current path according to the current line width, line join, line cap, and dash settings. */
PHP_METHOD(CairoContext, stroke)
{
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }

        context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	cairo_stroke(context_object->context);
	php_cairo_throw_exception(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto void CairoContext->strokePreserve()
   A drawing operator that strokes the current path according to the current line width, line join, line cap, and dash settings.
   Unlike cairo_stroke(), cairo_stroke_preserve() preserves the path within the cairo context.  */
PHP_METHOD(CairoContext, strokePreserve)
{
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }

        context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	cairo_stroke_preserve(context_object->context);
	php_cairo_throw_exception(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto array CairoContext->strokeExtents()
   Computes a bounding box in user coordinates covering the area that would be affected, (the "inked" area), by a cairo_stroke()
   operation operation given the current path and stroke parameters. */
PHP_METHOD(CairoContext, strokeExtents)
{
	cairo_context_object *context_object;
	double x1, y1, x2, y2;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }

        context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	cairo_stroke_extents(context_object->context, &x1, &y1, &x2, &y2);
	php_cairo_throw_exception(cairo_status(context_object->context));

	array_init(return_value);
	add_next_index_double(return_value, x1);
	add_next_index_double(return_value, y1);
	add_next_index_double(return_value, x2);
	add_next_index_double(return_value, y2);
}
/* }}} */

/* {{{ proto bool CairoContext->inStroke(int x, int y)
   Tests whether the given point is inside the area that would be affected by a cairo_stroke()
   operation given the current path and stroking parameters.  */
PHP_METHOD(CairoContext, inStroke)
{
	cairo_context_object *context_object;
	double x = 0.0, y = 0.0;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "dd", &x, &y) == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	RETURN_BOOL(cairo_in_stroke(context_object->context, x, y));
}
/* }}} */

/* {{{ proto void CairoContext->copyPage()
   Emits the current page for backends that support multiple pages, but doesn't clear it,
   so, the contents of the current page will be retained for the next page too.*/
PHP_METHOD(CairoContext, copyPage)
{
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }

        context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	cairo_copy_page(context_object->context);
	php_cairo_throw_exception(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto void CairoContext->showPage()
   Emits and clears the current page for backends that support multiple pages.
   Use cairo_copy_page() if you don't want to clear the page. */
PHP_METHOD(CairoContext, showPage)
{
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }

        context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	cairo_show_page(context_object->context);
	php_cairo_throw_exception(cairo_status(context_object->context));
}
/* }}} */

/* Transformations */
ZEND_BEGIN_ARG_INFO(CairoContext_translate_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

/* {{{ proto void CairoContext->translate(float x, float y)
   Modifies the current transformation matrix by translating the user-space origin by (x, y) */
PHP_METHOD(CairoContext, translate)
{
	double x = 0.0, y = 0.0;
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "dd", &x, &y) == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	cairo_translate(context_object->context, x, y);
	php_cairo_throw_exception(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto void CairoContext->scale(float x, float y)
   Modifies the current transformation matrix by scaling the X and Y user-space axes by x and y respectively */
PHP_METHOD(CairoContext, scale)
{
	double x = 0.0, y = 0.0;
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "dd", &x, &y) == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	cairo_scale(context_object->context, x, y);
	php_cairo_throw_exception(cairo_status(context_object->context));
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoContext_rotate_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, angle)
ZEND_END_ARG_INFO()

/* {{{ proto void CairoContext->rotate(float angle)
   Modifies the current transformation matrix by rotating the user-space axes by angle radians */
PHP_METHOD(CairoContext, rotate)
{
	double angle = 0.0;
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "d", &angle) == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
	cairo_rotate(context_object->context, angle);
	php_cairo_throw_exception(cairo_status(context_object->context));
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoContext_transform_args, ZEND_SEND_BY_VAL)
	//ZEND_ARG_INFO(0, matrix)
        ZEND_ARG_OBJ_INFO(1, matrix, Cairo\\Matrix, 0)
ZEND_END_ARG_INFO()

/* {{{ proto void CairoContext->transform(CairoMatrix matrix)
   Modifies the current transformation matrix by applying a matrix as an additional transformation */
PHP_METHOD(CairoContext, transform)
{
	zval *matrix_zval = NULL;
	cairo_context_object *context_object;
	cairo_matrix_object *matrix_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "z/", &matrix_zval) == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	matrix_object = Z_CAIRO_MATRIX_P(matrix_zval);
	cairo_transform(context_object->context, matrix_object->matrix);
	php_cairo_throw_exception(cairo_status(context_object->context));
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoContext_setMatrix_args, ZEND_SEND_BY_VAL)
        //ZEND_ARG_INFO(0, matrix)
	ZEND_ARG_OBJ_INFO(1, matrix, Cairo\\Matrix, 0)
ZEND_END_ARG_INFO()

/* {{{ proto void CairoContext->setMatrix(CairoMatrix matrix)
   Sets the current transformation matrix */
PHP_METHOD(CairoContext, setMatrix)
{
	zval *matrix_zval = NULL;
	cairo_context_object *context_object;
	cairo_matrix_object *matrix_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "z/", &matrix_zval) == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	matrix_object = Z_CAIRO_MATRIX_P(matrix_zval);
	cairo_set_matrix(context_object->context, matrix_object->matrix);
	php_cairo_throw_exception(cairo_status(context_object->context));

	/* If there's already a matrix, then we deref and remove it */
	if(context_object->matrix) {
//		Z_DELREF_P(context_object->matrix);
		context_object->matrix = NULL;
	}
        
	/* we need to be able to get this zval out later, so ref and store */
	context_object->matrix = matrix_zval;
//	Z_ADDREF_P(matrix_zval);
}
/* }}} */

/* {{{ proto CairoMatrix matrix CairoContext->getMatrix()
   Returns the current transformation matrix */
PHP_METHOD(CairoContext, getMatrix)
{
	cairo_context_object *context_object;
	cairo_matrix_object *matrix_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
                return;
        }

        context_object = cairo_context_object_get(getThis());
	if(!context_object) {
                return;
        }
        
	/* If we have a matrix object stored, grab that zval to use */
	if(context_object->matrix) {
		zval_dtor(return_value);
		*return_value = *context_object->matrix;
		zval_copy_ctor(return_value);
//		Z_SET_REFCOUNT_P(return_value, 1);
	/* Otherwise we spawn a new object */
	} else {
		object_init_ex(return_value, ce_cairo_matrix);	
	}

	matrix_object = Z_CAIRO_MATRIX_P(return_value);
	matrix_object->matrix = ecalloc(sizeof(cairo_matrix_t), 1); 
	cairo_get_matrix(context_object->context, matrix_object->matrix);
}
/* }}} */

/* {{{ proto void CairoContext->identityMatrix()
   Resets the current transformation matrix by setting it equal to the identity matrix */
PHP_METHOD(CairoContext, identityMatrix)
{
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }

        context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	cairo_identity_matrix(context_object->context);
	php_cairo_throw_exception(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto array cairo_user_to_device(CairoContext object, int x, int y)
   proto array CairoContext->userToDevice(int x, int y)
   Transform a coordinate from user space to device space by multiplying the given point by the current transformation matrix */
PHP_METHOD(CairoContext, userToDevice)
{
	double x = 0.0, y = 0.0;
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "dd", &x, &y) == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	cairo_user_to_device(context_object->context, &x, &y);
	php_cairo_throw_exception(cairo_status(context_object->context));

	array_init(return_value);
	add_next_index_double(return_value, x);
	add_next_index_double(return_value, y);
}
/* }}} */

/* {{{ proto array CairoContext->userToDeviceDistance(int x, int y)
   Transform a coordinate from user space to device space by multiplying the
   given point by the current transformation matrix except that the translation components
   are ignored */
PHP_METHOD(CairoContext, userToDeviceDistance)
{
	double x = 0.0, y = 0.0;
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "dd", &x, &y) == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	cairo_user_to_device_distance(context_object->context, &x, &y);
	php_cairo_throw_exception(cairo_status(context_object->context));

	array_init(return_value);
	add_next_index_double(return_value, x);
	add_next_index_double(return_value, y);
}
/* }}} */

/* {{{ proto array CairoContext->deviceToUser(int x, int y)
   Transform a coordinate from device space to user space by multiplying the given
   point by the inverse of the current transformation matrix */
PHP_METHOD(CairoContext, deviceToUser)
{
	double x = 0.0, y = 0.0;
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "dd", &x, &y) == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	cairo_device_to_user(context_object->context, &x, &y);
	php_cairo_throw_exception(cairo_status(context_object->context));

	array_init(return_value);
	add_next_index_double(return_value, x);
	add_next_index_double(return_value, y);
}
/* }}} */

/* {{{ proto void CairoContext->deviceToUserDistance(int x, int y)
   Transform a distance vector from device space to user space. */
PHP_METHOD(CairoContext, deviceToUserDistance)
{
	double x = 0.0, y = 0.0;
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "dd", &x, &y) == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }

	cairo_device_to_user_distance(context_object->context, &x, &y);
	php_cairo_throw_exception(cairo_status(context_object->context));

	array_init(return_value);
	add_next_index_double(return_value, x);
	add_next_index_double(return_value, y);
}
/* }}} */

/* {{{ proto CairoPath object CairoContext->copyPath()
   Creates a copy of the current path and returns it to the user as a CairoPath object */
PHP_METHOD(CairoContext, copyPath)
{
	cairo_path_object *path_object;
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	object_init_ex(return_value, php_cairo_get_path_ce());
	path_object = Z_CAIRO_PATH_P(return_value);
	path_object->path = cairo_copy_path(context_object->context);
	php_cairo_throw_exception(path_object->path->status);
}
/* }}} */

/* {{{ proto CairoPath object CairoContext->copyPathFlat()
   Creates a copy of the current path and returns it to the user as a CairoPath object
   any curves in the path will be approximated with piecewise-linear approximations*/
PHP_METHOD(CairoContext, copyPathFlat)
{
	cairo_path_object *path_object;
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	object_init_ex(return_value, php_cairo_get_path_ce());
	path_object = Z_CAIRO_PATH_P(return_value);
	path_object->path = cairo_copy_path_flat(context_object->context);
	php_cairo_throw_exception(path_object->path->status);
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoContext_appendPath_args, ZEND_SEND_BY_VAL)
	//ZEND_ARG_INFO(0, path)
        ZEND_ARG_OBJ_INFO(1, path, Cairo\\Path, 0)
ZEND_END_ARG_INFO()

/* {{{ proto void CairoContext->appendPath(CairoPath object)
   Append the path onto the current path.  */
PHP_METHOD(CairoContext, appendPath)
{
	zval *path_zval = NULL;
	const cairo_path_t *path;
	cairo_path_object *path_object;
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "z/", &path_zval) == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	path_object = Z_CAIRO_PATH_P(path_zval);
	path = path_object->path;
	cairo_append_path(context_object->context, path); 
	php_cairo_throw_exception(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto bool CairoContext->hasCurrentPoint()
   Returns whether a current point is defined on the current path.  */
PHP_METHOD(CairoContext, hasCurrentPoint)
{
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	RETURN_BOOL(cairo_has_current_point(context_object->context)); 
}
/* }}} */

/* {{{ proto array CairoContext->getCurrentPoint()
   Gets the current point of the current path, which is conceptually the final point reached by the path so far.  */
PHP_METHOD(CairoContext, getCurrentPoint)
{
	double x, y;
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	php_cairo_throw_exception(cairo_status(context_object->context));

	cairo_get_current_point(context_object->context, &x, &y);
	array_init(return_value);
	add_next_index_double(return_value, x);
	add_next_index_double(return_value, y);
}
/* }}} */

/* {{{ proto void CairoContext->newPath()
   Clears the current path. After this call there will be no path and no current point. */
PHP_METHOD(CairoContext, newPath)
{
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	cairo_new_path(context_object->context); 
	php_cairo_throw_exception(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto void CairoContext->newSubPath()
   Begin a new sub-path. Note that the existing path is not affected. After this call there will be no current point.  */
PHP_METHOD(CairoContext, newSubPath)
{
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	cairo_new_sub_path(context_object->context); 
	php_cairo_throw_exception(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto void CairoContext->closePath()
   Adds a line segment to the path from the current point to the beginning of the current sub-path,
   and closes this sub-path. After this call the current point will be at the joined endpoint of the sub-path.   */
PHP_METHOD(CairoContext, closePath)
{
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	cairo_close_path(context_object->context); 
	php_cairo_throw_exception(cairo_status(context_object->context));
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoContext_arc_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
	ZEND_ARG_INFO(0, radius)
	ZEND_ARG_INFO(0, angle1)
	ZEND_ARG_INFO(0, angle2)
ZEND_END_ARG_INFO()

/* {{{ proto void CairoContext->arc(float x, float y, float radius, float angle1, float angle2)
   Adds a circular arc of the given radius to the current path.
   The arc is centered at (x, y), begins at angle1 and proceeds in the direction of increasing angles to end at angle2*/
PHP_METHOD(CairoContext, arc)
{
	double x = 0.0, y = 0.0, radius = 0.0, angle1 = 0.0, angle2 = 0.0;
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "ddddd", &x, &y, &radius, &angle1, &angle2) == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	cairo_arc(context_object->context, x, y, radius, angle1, angle2); 
	php_cairo_throw_exception(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto void CairoContext->arcNegative(float x, float y, float radius, float angle1, float angle2)
   Adds a circular arc of the given radius to the current path.
   The arc is centered at (x, y), begins at angle1 and proceeds in the direction of decreasing angles to end at angle2.*/
PHP_METHOD(CairoContext, arcNegative)
{
	double x = 0.0, y = 0.0, radius = 0.0, angle1 = 0.0, angle2 = 0.0;
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "ddddd", &x, &y, &radius, &angle1, &angle2) == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	cairo_arc_negative(context_object->context, x, y, radius, angle1, angle2); 
	php_cairo_throw_exception(cairo_status(context_object->context));
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoContext_curveTo_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, x1)
	ZEND_ARG_INFO(0, y1)
	ZEND_ARG_INFO(0, x2)
	ZEND_ARG_INFO(0, y2)
	ZEND_ARG_INFO(0, x3)
	ZEND_ARG_INFO(0, y3)
ZEND_END_ARG_INFO()

/* {{{ proto void cairo_curve_to(CairoContext object, float x1, float y1, float x2, float y2, float x3, float y3)
   proto void CairoContext->curveTo(float x1, float y1, float x2, float y2, float x3, float y3)
   Adds a cubic Bézier spline to the path from the current point to position (x3, y3) in user-space coordinates, using (x1, y1) and (x2, y2) as the control points.
   After this call the current point will be (x3, y3).  */
PHP_METHOD(CairoContext, curveTo)
{
	double x1 = 0.0, y1 = 0.0, x2 = 0.0, y2 = 0.0, x3 = 0.0, y3 = 0.0;
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "dddddd", &x1, &y1, &x2, &y2, &x3, &y3) == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	cairo_curve_to(context_object->context, x1, y1, x2, y2, x3, y3); 
	php_cairo_throw_exception(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto void cairo_line_to(CairoContext object, float x, float y)
   proto void CairoContext->lineTo(float x, float y)
   Adds a line to the path from the current point to position (x, y) in user-space coordinates. After this call the current point will be (x, y). */
PHP_METHOD(CairoContext, lineTo)
{
	double x = 0.0, y = 0.0;
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "dd", &x, &y) == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
	cairo_line_to(context_object->context, x, y); 
	php_cairo_throw_exception(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto void cairo_move_to(CairoContext object, float x, float y)
   proto void CairoContext->moveTo(float x, float y)
   Begin a new sub-path. After this call the current point will be (x, y) */
PHP_METHOD(CairoContext, moveTo)
{
	double x = 0.0, y = 0.0;
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "dd", &x, &y) == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	cairo_move_to(context_object->context, x, y); 
	php_cairo_throw_exception(cairo_status(context_object->context));
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoContext_rectangle_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
	ZEND_ARG_INFO(0, width)
	ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()

/* {{{ proto void CairoContext->rectangle(float x, float y, float width, float height)
   Adds a closed sub-path rectangle of the given size to the current path at position (x, y) in user-space coordinates.  */
PHP_METHOD(CairoContext, rectangle)
{
	double x = 0.0, y = 0.0, width = 0.0, height = 0.0;
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "dddd", &x, &y, &width, &height) == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	cairo_rectangle(context_object->context, x, y, width, height); 
	php_cairo_throw_exception(cairo_status(context_object->context));
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoContext_glyphPath_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_ARRAY_INFO(1, glyphs, 0)
ZEND_END_ARG_INFO()

/* {{{ proto void CairoContext->glyphPath(array glyphs)
   Adds closed paths for the glyphs to the current path. */
PHP_METHOD(CairoContext, glyphPath)
{
	cairo_context_object *context_object;
	const cairo_glyph_t *glyphs = NULL;
	long num_glyphs = 0;
	zval *php_glyphs = NULL, *pzval;
	HashTable *glyphs_hash = NULL;
        int i = 0;
        
	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "z/", &php_glyphs) == FAILURE) {
		return;
	}
        
        context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }

	/* Grab the zend hash */
	glyphs_hash = Z_ARRVAL_P(php_glyphs);

	/* iterate the array, each value inside MUST be an instance of CairoGlyph */
        ZEND_HASH_FOREACH_VAL(glyphs_hash, pzval) {
            /*  TODO: check here for is object and instanceof CairoGlyph, 
                then rip the internal glyph out and stick it in the array
                then increment the glyph count
            */
            /*
            if (Z_TYPE_P(pzval) == IS_OBJECT) {
                    glyphs[i++] = ...;
            }
            */
        } ZEND_HASH_FOREACH_END();
        
	num_glyphs = zend_hash_num_elements(glyphs_hash);

	cairo_glyph_path(context_object->context, glyphs, num_glyphs);
	php_cairo_throw_exception(cairo_status(context_object->context));
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoContext_textPath_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, string)
ZEND_END_ARG_INFO()

/* {{{ proto void CairoContext->textPath(string text)
   Adds closed paths for text to the current path
   NOTE: text must be UTF-8 charset or results will be unexpected */
PHP_METHOD(CairoContext, textPath)
{
	const char *string;
	size_t str_len;
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "s", &string, &str_len) == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	cairo_text_path(context_object->context, string); 
	php_cairo_throw_exception(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto void CairoContext->relCurveTo(float x1, float y1, float x2, float y2, float x3, float y3)
   Adds a cubic Bézier spline to the path from the current point to a point offset from the current point by (x3, y3),
   using points offset by (x1, y1) and (x2, y2) as the control points. */
PHP_METHOD(CairoContext, relCurveTo)
{
	double x1 = 0.0, y1 = 0.0, x2 = 0.0, y2 = 0.0, x3 = 0.0, y3 = 0.0;
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "dddddd", &x1, &y1, &x2, &y2, &x3, &y3) == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	cairo_rel_curve_to(context_object->context, x1, y1, x2, y2, x3, y3); 
	php_cairo_throw_exception(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto void CairoContext->relLineTo(float x, float y)
   Adds a line to the path from the current point to a point that is offset from the current point by (x, y) in user space */
PHP_METHOD(CairoContext, relLineTo)
{
	double x = 0.0, y = 0.0;
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "dd", &x, &y) == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	cairo_rel_line_to(context_object->context, x, y); 
	php_cairo_throw_exception(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto void CairoContext->relMoveTo(float x, float y)
   Begin a new sub-path. After this call the current point will offset by (x, y). */
PHP_METHOD(CairoContext, relMoveTo)
{
	double x = 0.0, y = 0.0;
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "dd", &x, &y) == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	cairo_rel_move_to(context_object->context, x, y); 
	php_cairo_throw_exception(cairo_status(context_object->context));
}
/* }}} */

/* {{{ proto array CairoContext->pathExtents()
   Computes a bounding box in user-space coordinates covering the points on the current path */
PHP_METHOD(CairoContext, pathExtents)
{
	double x1, y1, x2, y2;
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	php_cairo_throw_exception(cairo_status(context_object->context));

	cairo_path_extents(context_object->context, &x1, &y1, &x2, &y2);
	array_init(return_value);
	add_next_index_double(return_value, x1);
	add_next_index_double(return_value, y1);
	add_next_index_double(return_value, x2);
	add_next_index_double(return_value, y2);
}
/* }}} */

/* Text items */

ZEND_BEGIN_ARG_INFO_EX(CairoContext_selectFontFace_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_INFO(0, family)
	ZEND_ARG_INFO(0, slant)
	ZEND_ARG_INFO(0, weight)
ZEND_END_ARG_INFO()

/* {{{ proto void CairoContext->selectFontFace(string family, CairoFontSlant slant, CairoFontWeight weight)
        Selects a family and style of font from a simplified description as a family name, slant and weight. */
PHP_METHOD(CairoContext, selectFontFace)
{
	long slant = CAIRO_FONT_SLANT_NORMAL, weight = CAIRO_FONT_WEIGHT_NORMAL;
        size_t family_len;
	char *family, *cairo_family;
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "s|ll", &family, &family_len, &slant, &weight) == FAILURE) {
		return;
	}
        
        context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }

	cairo_family = estrdup(family);		
	cairo_select_font_face(context_object->context, family, slant, weight);
	efree(cairo_family);
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoContext_setFontSize_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, size)
ZEND_END_ARG_INFO()

/* {{{ proto void CairoContext->setFontSize(double size)
        Sets the current font matrix to a scale by a factor of size, replacing any font matrix previously 
        set with cairo_set_font_size() or cairo_set_font_matrix() */
PHP_METHOD(CairoContext, setFontSize)
{
	double size;
	cairo_context_object *context_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "d", &size ) == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	cairo_set_font_size(context_object->context, size);

	/* If there's a font matrix stored, we've just reset it */
	if(context_object->font_matrix) {
//		Z_DELREF_P(context_object->font_matrix);
		context_object->font_matrix = NULL;
	}
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoContext_setFontMatrix_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(1, matrix, Cairo\\Matrix, 0)
	//ZEND_ARG_INFO(0, matrix)
ZEND_END_ARG_INFO()

/* {{{ proto void CairoContext->setFontMatrix(CairoMatrix matrix)
   Sets the current transformation matrix for fonts */
PHP_METHOD(CairoContext, setFontMatrix)
{
	zval *matrix_zval = NULL;
	cairo_context_object *context_object;
	cairo_matrix_object *matrix_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "z/", &matrix_zval) == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	matrix_object = Z_CAIRO_MATRIX_P(matrix_zval);
	cairo_set_font_matrix(context_object->context, matrix_object->matrix);
	php_cairo_throw_exception(cairo_status(context_object->context));

	/* If there's already a matrix, then we deref and remove it */
	if(context_object->font_matrix) {
//		Z_DELREF_P(context_object->font_matrix);
		context_object->font_matrix = NULL;
	}

	/* we need to be able to get this zval out later, so ref and store */
	context_object->font_matrix = matrix_zval;
//	Z_ADDREF_P(matrix_zval);
}
/* }}} */

/* {{{ proto CairoMatrix matrix CairoContext->getFontMatrix()
   Returns the current transformation matrix fot the font*/
PHP_METHOD(CairoContext, getFontMatrix)
{
	cairo_context_object *context_object;
	cairo_matrix_object *matrix_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
                return;
        }
        
	/* If we have a matrix object stored, grab that zval to use */
	if(context_object->font_matrix) {
		zval_dtor(return_value);
		*return_value = *context_object->font_matrix;
		zval_copy_ctor(return_value);
//		Z_SET_REFCOUNT_P(return_value, 1);
	/* Otherwise we spawn a new object */
	} else {
		object_init_ex(return_value, ce_cairo_matrix);	
	}

	matrix_object = Z_CAIRO_MATRIX_P(return_value);
	//matrix_object->matrix = ecalloc(sizeof(cairo_matrix_t), 1); 
	cairo_get_font_matrix(context_object->context, matrix_object->matrix);
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoContext_setFontOptions_args, ZEND_SEND_BY_VAL)
	//ZEND_ARG_INFO(0, fontoptions)
        ZEND_ARG_OBJ_INFO(1, fontoptions, Cairo\\FontOptions, 0)
ZEND_END_ARG_INFO()

/* {{{ proto void CairoContext->setFontOptions(CairoFontOptions object)
       Sets the font options to be used with the context  */
PHP_METHOD(CairoContext, setFontOptions)
{
	zval *font_options_zval = NULL;
	cairo_context_object *context_object;
	cairo_font_options_object *font_options_object;
	
	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "z/",  &font_options_zval) == FAILURE) {
		return;
	}
	
	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	font_options_object = Z_CAIRO_FONT_OPTIONS_P(font_options_zval);
	cairo_set_font_options(context_object->context, font_options_object->font_options);
	php_cairo_throw_exception(cairo_status(context_object->context));

	/* If there's already a font_options stored, then we deref and remove it */
	if(context_object->font_options) {
//		Z_DELREF_P(context_object->font_options);
		context_object->font_options = NULL;
	}

	/* we need to be able to get this zval out later, so ref and store */
	context_object->font_options = font_options_zval;
//	Z_ADDREF_P(font_options_zval);
}
/* }}} */

/* {{{ proto CairoFontOptions object CairoContext->getFontOptions()
       Retrieves the font options selected by the context. 
       If no font options have been selected or set then the default options will be returned. */
PHP_METHOD(CairoContext, getFontOptions)
{
	cairo_context_object *context_object;
	cairo_font_options_object *font_options_object;
	cairo_font_options_t *font_options = NULL;
	
	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	/* Grab the font options properly */
	cairo_get_font_options(context_object->context, font_options);
	php_cairo_throw_exception(cairo_status(context_object->context));

	/* If we have a font face object stored, grab that zval to use */
	if(context_object->font_options) {
		zval_dtor(return_value);
		*return_value = *context_object->font_options;
		zval_copy_ctor(return_value);
//		Z_SET_REFCOUNT_P(return_value, 1);
	/* Otherwise we spawn a new object */
	} else {
		object_init_ex(return_value, ce_cairo_fontoptions);	
	}

	font_options_object = Z_CAIRO_FONT_OPTIONS_P(return_value);
	font_options_object->font_options = font_options;
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoContext_setFontFace_args, ZEND_SEND_BY_VAL)
	//ZEND_ARG_INFO(0, fontface)
        ZEND_ARG_OBJ_INFO(1, fontface, Cairo\\FontFace, 0)
ZEND_END_ARG_INFO()

/* {{{ proto void CairoContext->setFontFace(CairoFontFace object)
       Sets the font face to be used with the context  */
PHP_METHOD(CairoContext, setFontFace)
{
	zval *font_face_zval = NULL;
	cairo_context_object *context_object;
	cairo_font_face_object *font_face_object;
	
	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "z/",  &font_face_zval) == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	font_face_object = Z_CAIRO_FONT_FACE_P(font_face_zval);
	cairo_set_font_face(context_object->context, font_face_object->font_face);
	php_cairo_throw_exception(cairo_status(context_object->context));

	/* If there's already a font face stored, then we deref and remove it */
	if(context_object->font_face) {
//		Z_DELREF_P(context_object->font_face);
		context_object->font_face = NULL;
	}

	/* we need to be able to get this zval out later, so ref and store */
	context_object->font_face = font_face_zval;
//	Z_ADDREF_P(font_face_zval);
}
/* }}} */

/* {{{ proto CairoFontFace object CairoContext->getFontFace()
       Retrieves the font face selected by the context.  If no font face has been selected or set then the default face
       will be returned.  */
PHP_METHOD(CairoContext, getFontFace)
{
	cairo_context_object *context_object;
	cairo_font_face_object *font_face_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	/* If we have a font face object stored, grab that zval to use */
	if(context_object->font_face) {
		zval_dtor(return_value);
		*return_value = *context_object->font_face;
		zval_copy_ctor(return_value);
//		Z_SET_REFCOUNT_P(return_value, 1);
	/* Otherwise we spawn a new object */
	} else {
		object_init_ex(return_value, ce_cairo_toyfontface);
	}

	font_face_object = Z_CAIRO_FONT_FACE_P(return_value);
        
	/* if there IS a value in font_face_object, destroy it cause we're getting a new one */
	if (font_face_object->font_face != NULL) {
		cairo_font_face_destroy(font_face_object->font_face);
	}
	font_face_object->font_face = cairo_get_font_face(context_object->context);
	cairo_font_face_reference(font_face_object->font_face);
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoContext_setScaledFont_args, ZEND_SEND_BY_VAL)
	//ZEND_ARG_INFO(0, scaledfont)
        ZEND_ARG_OBJ_INFO(1, scaledfont, Cairo\\ScaledFont, 0)
ZEND_END_ARG_INFO()

/* {{{ proto void CairoContext->setScaledFont(CairoScaledFont object)
       Replaces the current font face, font matrix, and font options in the context with those of the scaled font.  */
PHP_METHOD(CairoContext, setScaledFont)
{
	zval *scaled_font_zval = NULL;
	cairo_context_object *context_object;
	cairo_scaled_font_object *scaled_font_object;
	
	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "z/",  &scaled_font_zval) == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	scaled_font_object = Z_CAIRO_SCALED_FONT_P(scaled_font_zval);
	cairo_set_scaled_font(context_object->context, scaled_font_object->scaled_font);
	php_cairo_throw_exception(cairo_status(context_object->context));

	/* If there's already a font face, font matrix, scaled font, and or font options stored, then we deref and remove them */
	if(context_object->font_face) {
//		Z_DELREF_P(context_object->font_face);
		context_object->font_face = NULL;
	}
	if(context_object->font_matrix) {
//		Z_DELREF_P(context_object->font_matrix);
		context_object->font_matrix = NULL;
	}
	if(context_object->font_options) {
//		Z_DELREF_P(context_object->font_options);
		context_object->font_options = NULL;
	}
	if(context_object->scaled_font) {
//		Z_DELREF_P(context_object->scaled_font);
		context_object->scaled_font = NULL;
	}

	/* if the scaled font has a font_face, matrix, or option zvals stored, move them to context as well and ref again */
	if(scaled_font_object->font_face) {
		context_object->font_face = scaled_font_object->font_face;
//		Z_ADDREF_P(context_object->font_face);
	}
	if(scaled_font_object->matrix) {
		context_object->font_matrix = scaled_font_object->matrix;
//		Z_ADDREF_P(context_object->font_matrix);
	}
	if(scaled_font_object->font_options) {
		context_object->font_options = scaled_font_object->font_options;
//		Z_ADDREF_P(context_object->font_options);
	}

	/* we need to be able to get this zval out later, so ref and store */
	context_object->scaled_font = scaled_font_zval;
//	Z_ADDREF_P(scaled_font_zval);
}
/* }}} */

/* {{{ proto CairoScaledFont object CairoContext->getScaledFont()
       Retrieves the scaled font face selected by the context.  
       If no scaled font has been selected or set then the default face will be returned.  */
PHP_METHOD(CairoContext, getScaledFont)
{
	cairo_context_object *context_object;
	cairo_scaled_font_object *scaled_font_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	/* If we have a scaled font object stored, grab that zval to use */
	if(context_object->scaled_font) {
		zval_dtor(return_value);
		*return_value = *context_object->scaled_font;
		zval_copy_ctor(return_value);
//		Z_SET_REFCOUNT_P(return_value, 1);
	/* Otherwise we spawn a new object */
	} else {
		object_init_ex(return_value, ce_cairo_scaled_font);
	}

	scaled_font_object = Z_CAIRO_SCALED_FONT_P(return_value);
        
	/* if there IS a value in scaled_font_object, destroy it cause we're getting a new one */
	if (scaled_font_object->scaled_font != NULL) {
		cairo_scaled_font_destroy(scaled_font_object->scaled_font);
	}
	scaled_font_object->scaled_font = cairo_get_scaled_font(context_object->context);
	cairo_scaled_font_reference(scaled_font_object->scaled_font);
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoContext_text_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, text)
ZEND_END_ARG_INFO()

/* {{{ proto array CairoContext->showText(string text)
   A drawing operator that generates the shape from a string of UTF-8 characters,
   rendered according to the current font_face, font_size (font_matrix), and font_options. */
PHP_METHOD(CairoContext, showText)
{
	char *text, *cairo_text;
	size_t text_len;
	cairo_context_object *context_object;
	
	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "s", &text, &text_len ) == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	cairo_text = estrdup(text);
	cairo_show_text(context_object->context, text);
	efree(cairo_text);
}
/* }}} */

/* {{{ proto array CairoContext->fontExtents()
       Gets the metrics for a font in an assoc array. */
PHP_METHOD(CairoContext, fontExtents)
{
	cairo_context_object *context_object;
	cairo_font_extents_t extents;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
	cairo_font_extents(context_object->context, &extents);

	array_init(return_value);
	add_assoc_double(return_value, "ascent", extents.ascent);
	add_assoc_double(return_value, "descent", extents.descent);
	add_assoc_double(return_value, "height", extents.height);
	add_assoc_double(return_value, "max_x_advance", extents.max_x_advance);
	add_assoc_double(return_value, "max_y_advance", extents.max_y_advance);
}
/* }}} */

/* {{{ proto array CairoContext->textExtents(string text)
   Gets the extents for a string of text.
   */
PHP_METHOD(CairoContext, textExtents)
{
	char *text, *cairo_text;
	size_t text_len;
	cairo_context_object *context_object;
	cairo_text_extents_t extents;
	
	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "s", &text, &text_len ) == FAILURE) {
		return;
	}

	context_object = cairo_context_object_get(getThis());
	if(!context_object) {
            return;
        }
        
        cairo_text = estrdup(text);
	cairo_text_extents(context_object->context, cairo_text, &extents);
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


/* ----------------------------------------------------------------
    Cairo\Context Definition and registration
------------------------------------------------------------------*/

/* {{{ cairo_context_methods[] */
const zend_function_entry cairo_context_methods[] = {
        PHP_ME(CairoContext, __construct, CairoContext___construct_args, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
        PHP_ME(CairoContext, getStatus, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, save, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, restore, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, pushGroup, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, pushGroupWithContent, CairoContext_pushGroupWithContent_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, popGroup, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, popGroupToSource, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, setSourceRGB, CairoContext_setSourceRGB_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, setSourceRGBA, CairoContext_setSourceRGBA_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, setSurface, CairoContext_setSurface_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, getSurface, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, getGroupSurface, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, setPattern, CairoContext_setPattern_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, getPattern, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, setAntialias, CairoContext_setAntialias_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, getAntialias, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, setDash, CairoContext_setDash_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, getDashCount, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, getDash, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, setFillRule, CairoContext_setFillRule_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, getFillRule, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, setLineCap, CairoContext_setLineCap_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, getLineCap, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, setLineJoin, CairoContext_setLineJoin_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, getLineJoin, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, setLineWidth, CairoContext_setLineWidth_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, getLineWidth, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, setMiterLimit, CairoContext_setMiterLimit_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, getMiterLimit, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, setOperator, CairoPattern_setOperator_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, getOperator, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, setTolerance, CairoContext_setTolerance_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, getTolerance, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, clip, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, inClip, CairoContext_translate_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, clipPreserve, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, resetClip, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, clipExtents, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, clipRectangleList, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, fill, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, fillPreserve, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, fillExtents, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, inFill, CairoContext_translate_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, mask, CairoContext_mask_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, maskSurface, CairoContext_maskSurface_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, paint, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, paintWithAlpha, CairoContext_paintWithAlpha_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, stroke, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, strokePreserve, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, strokeExtents, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, inStroke, CairoContext_translate_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, copyPage, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, showPage, NULL, ZEND_ACC_PUBLIC)
	/* Transformations */
        PHP_ME(CairoContext, translate, CairoContext_translate_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, scale, CairoContext_translate_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, rotate, CairoContext_rotate_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, transform, CairoContext_transform_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, setMatrix, CairoContext_setMatrix_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, getMatrix, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, identityMatrix, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, userToDevice, CairoContext_translate_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, userToDeviceDistance, CairoContext_translate_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, deviceToUser, CairoContext_translate_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, deviceToUserDistance, CairoContext_translate_args, ZEND_ACC_PUBLIC)
	/* Paths */
        PHP_ME(CairoContext, copyPath, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, copyPathFlat, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, appendPath, CairoContext_appendPath_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, hasCurrentPoint, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, getCurrentPoint, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, newPath, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, newSubPath, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, closePath, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, arc, CairoContext_arc_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, arcNegative, CairoContext_arc_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, curveTo, CairoContext_curveTo_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, lineTo, CairoContext_translate_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, moveTo, CairoContext_translate_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, rectangle, CairoContext_rectangle_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, glyphPath, CairoContext_glyphPath_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, textPath, CairoContext_textPath_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, relCurveTo, CairoContext_curveTo_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, relLineTo, CairoContext_translate_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, relMoveTo, CairoContext_translate_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, pathExtents, NULL, ZEND_ACC_PUBLIC)
	/* Text */
        PHP_ME(CairoContext, selectFontFace, CairoContext_selectFontFace_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, setFontSize, CairoContext_setFontSize_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, setFontMatrix, CairoContext_setFontMatrix_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, getFontMatrix, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, setFontOptions, CairoContext_setFontOptions_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, getFontOptions, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, setFontFace, CairoContext_setFontFace_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, getFontFace, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, setScaledFont, CairoContext_setScaledFont_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, getScaledFont, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, showText, CairoContext_text_args, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, fontExtents, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(CairoContext, textExtents, CairoContext_text_args, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};
/* }}} */

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(cairo_context)
{
	zend_class_entry context_ce, fillrule_ce, linecap_ce, linejoin_ce, operator_ce;

        //memcpy(&cairo_context_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
        memcpy(&cairo_context_object_handlers, zend_get_std_object_handlers(), sizeof(cairo_context_object_handlers));
        
        /* Context */
        cairo_context_object_handlers.offset = XtOffsetOf(cairo_context_object, std);
        cairo_context_object_handlers.free_obj = cairo_context_free_obj;
        
	INIT_NS_CLASS_ENTRY(context_ce, CAIRO_NAMESPACE, "Context", cairo_context_methods);
	ce_cairo_context = zend_register_internal_class(&context_ce);
	ce_cairo_context->create_object = cairo_context_create_object;
        
        /* FillRule */
        INIT_NS_CLASS_ENTRY(fillrule_ce, CAIRO_NAMESPACE, "FillRule", NULL);
        ce_cairo_fillrule = zend_register_internal_class_ex(&fillrule_ce, php_eos_datastructures_get_enum_ce());
        ce_cairo_fillrule->ce_flags |= ZEND_ACC_FINAL;

        #define CAIRO_FILLRULE_DECLARE_ENUM(name) \
            zend_declare_class_constant_long(ce_cairo_fillrule, #name, \
            sizeof(#name)-1, CAIRO_FILL_RULE_## name);

        CAIRO_FILLRULE_DECLARE_ENUM(WINDING);
        CAIRO_FILLRULE_DECLARE_ENUM(EVEN_ODD);
        
        
        /* LineCap */
        INIT_NS_CLASS_ENTRY(linecap_ce, CAIRO_NAMESPACE, "LineCap", NULL);
        ce_cairo_linecap = zend_register_internal_class_ex(&linecap_ce, php_eos_datastructures_get_enum_ce());
        ce_cairo_linecap->ce_flags |= ZEND_ACC_FINAL;

        #define CAIRO_LINECAP_DECLARE_ENUM(name) \
            zend_declare_class_constant_long(ce_cairo_linecap, #name, \
            sizeof(#name)-1, CAIRO_LINE_CAP_## name);

        CAIRO_LINECAP_DECLARE_ENUM(BUTT);
        CAIRO_LINECAP_DECLARE_ENUM(ROUND);
        CAIRO_LINECAP_DECLARE_ENUM(SQUARE);
        

        /* LineJoin */
	INIT_NS_CLASS_ENTRY(linejoin_ce, CAIRO_NAMESPACE, "LineJoin", NULL);
	ce_cairo_linejoin = zend_register_internal_class_ex(&linejoin_ce, php_eos_datastructures_get_enum_ce());
	ce_cairo_linejoin->ce_flags |= ZEND_ACC_FINAL;

	#define CAIRO_LINEJOIN_DECLARE_ENUM(name) \
            zend_declare_class_constant_long(ce_cairo_linejoin, #name, \
            sizeof(#name)-1, CAIRO_LINE_JOIN_## name);

	CAIRO_LINEJOIN_DECLARE_ENUM(MITER);
	CAIRO_LINEJOIN_DECLARE_ENUM(ROUND);
	CAIRO_LINEJOIN_DECLARE_ENUM(BEVEL);
        
        
        /* Operator */
	INIT_NS_CLASS_ENTRY(operator_ce, CAIRO_NAMESPACE, "Operator", NULL);
	ce_cairo_operator = zend_register_internal_class_ex(&operator_ce, php_eos_datastructures_get_enum_ce());
	ce_cairo_operator->ce_flags |= ZEND_ACC_FINAL;

	#define CAIRO_OPERATOR_DECLARE_ENUM(name) \
            zend_declare_class_constant_long(ce_cairo_operator, #name, \
            sizeof(#name)-1, CAIRO_OPERATOR_## name);

	CAIRO_OPERATOR_DECLARE_ENUM(CLEAR);
	CAIRO_OPERATOR_DECLARE_ENUM(SOURCE);
	CAIRO_OPERATOR_DECLARE_ENUM(OVER);
	CAIRO_OPERATOR_DECLARE_ENUM(IN);
	CAIRO_OPERATOR_DECLARE_ENUM(OUT);
	CAIRO_OPERATOR_DECLARE_ENUM(ATOP);
	CAIRO_OPERATOR_DECLARE_ENUM(DEST);
	CAIRO_OPERATOR_DECLARE_ENUM(DEST_OVER);
	CAIRO_OPERATOR_DECLARE_ENUM(DEST_IN);
	CAIRO_OPERATOR_DECLARE_ENUM(DEST_OUT);
	CAIRO_OPERATOR_DECLARE_ENUM(DEST_ATOP);
	CAIRO_OPERATOR_DECLARE_ENUM(XOR);
	CAIRO_OPERATOR_DECLARE_ENUM(ADD);
	CAIRO_OPERATOR_DECLARE_ENUM(SATURATE);
	CAIRO_OPERATOR_DECLARE_ENUM(MULTIPLY);
	CAIRO_OPERATOR_DECLARE_ENUM(SCREEN);
	CAIRO_OPERATOR_DECLARE_ENUM(OVERLAY);
	CAIRO_OPERATOR_DECLARE_ENUM(DARKEN);
	CAIRO_OPERATOR_DECLARE_ENUM(LIGHTEN);
	CAIRO_OPERATOR_DECLARE_ENUM(COLOR_DODGE);
	CAIRO_OPERATOR_DECLARE_ENUM(COLOR_BURN);
	CAIRO_OPERATOR_DECLARE_ENUM(HARD_LIGHT);
	CAIRO_OPERATOR_DECLARE_ENUM(SOFT_LIGHT);
	CAIRO_OPERATOR_DECLARE_ENUM(DIFFERENCE);
	CAIRO_OPERATOR_DECLARE_ENUM(EXCLUSION);
	CAIRO_OPERATOR_DECLARE_ENUM(HSL_HUE);
	CAIRO_OPERATOR_DECLARE_ENUM(HSL_SATURATION);
	CAIRO_OPERATOR_DECLARE_ENUM(HSL_COLOR);
	CAIRO_OPERATOR_DECLARE_ENUM(HSL_LUMINOSITY);

	return SUCCESS;
}
/* }}} */