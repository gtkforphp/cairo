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

#include "php_cairo.h"
#include "php_cairo_internal.h"


zend_class_entry *ce_cairo_fontface;
zend_class_entry *ce_cairo_fonttype;

static zend_object_handlers cairo_font_face_object_handlers; 

//typedef struct _cairo_font_face_object {
//	cairo_font_face_t *font_face;
//        zend_object std;
//} cairo_font_face_object;

cairo_font_face_object *cairo_font_face_fetch_object(zend_object *object)
{
    return (cairo_font_face_object *) ((char*)(object) - XtOffsetOf(cairo_font_face_object, std));
}

//#define Z_CAIRO_FONT_FACE_P(zv) cairo_font_face_fetch_object(Z_OBJ_P(zv))

static inline cairo_font_face_object *cairo_font_face_object_get(zval *zv)
{
	cairo_font_face_object *object = Z_CAIRO_FONT_FACE_P(zv);
	if(object->font_face == NULL) {
		zend_throw_exception_ex(ce_cairo_exception, 0,
			"Internal font face object missing in %s, you must call parent::__construct in extended classes",
			ZSTR_VAL(Z_OBJCE_P(zv)->name));
		return NULL;
	}
	return object;
}

/* ----------------------------------------------------------------
    Cairo\FontOptions Object management
------------------------------------------------------------------*/

/* {{{ */
static void cairo_font_face_free_obj(zend_object *object)
{
    cairo_font_face_object *intern = cairo_font_face_fetch_object(object);

    if(!intern) {
            return;
    }

    if (intern->font_face) {
            cairo_font_face_destroy(intern->font_face);
    }
    intern->font_face = NULL;

    zend_object_std_dtor(&intern->std);
}

/* {{{ */
static zend_object* cairo_font_face_obj_ctor(zend_class_entry *ce, cairo_font_face_object **intern)
{
	cairo_font_face_object *object = ecalloc(1, sizeof(cairo_font_face_object) + zend_object_properties_size(ce));
        
        object->font_face = NULL;
        
	zend_object_std_init(&object->std, ce);
	object->std.handlers = &cairo_font_face_object_handlers;
	*intern = object;

	return &object->std;
}
/* }}} */

/* {{{ */
zend_object* cairo_font_face_create_object(zend_class_entry *ce)
{
	cairo_font_face_object *font_face_obj = NULL;
	zend_object *return_value = cairo_font_face_obj_ctor(ce, &font_face_obj);

	object_properties_init(&(font_face_obj->std), ce);
	return return_value;
}
/* }}} */

/* ----------------------------------------------------------------
    Cairo\FontOptions C API
------------------------------------------------------------------*/

zend_class_entry * php_cairo_get_fontface_ce()
{
	return ce_cairo_fontface;
}


/* ----------------------------------------------------------------
    Cairo\FontOptions Class API
------------------------------------------------------------------*/
/* {{{ proto void CairoFontFace->__contruct()
   CairoFontFace CANNOT be extended in userspace, this will throw an exception on use */
PHP_METHOD(CairoFontFace, __construct)
{
	zend_throw_exception(ce_cairo_exception, "CairoFontFace cannot be constructed", 0);
}
/* }}} */

/* {{{ proto long CairoFontFace->status()
       Returns the current integer status of the CairoFontFace */
PHP_METHOD(CairoFontFace, status)
{
	cairo_font_face_object *font_face_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }

        font_face_object = Z_CAIRO_FONT_FACE_P(getThis());
	if(!font_face_object) {
            return;
        }
        
	RETURN_LONG(cairo_font_face_status(font_face_object->font_face));
}
/* }}} */

/* {{{ proto long CairoFontFace->getType()
       Returns the current integer type of the CairoFontFace backend */
PHP_METHOD(CairoFontFace, getType)
{
	cairo_font_face_object *font_face_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
            return;
        }

        font_face_object = Z_CAIRO_FONT_FACE_P(getThis());
	if(!font_face_object) {
            return;
        }
        
	RETURN_LONG(cairo_font_face_get_type(font_face_object->font_face));
}
/* }}} */

/* ----------------------------------------------------------------
    Cairo\FontOptions Definition and registration
------------------------------------------------------------------*/

/* {{{ cairo_font_face_methods[] */
const zend_function_entry cairo_font_face_methods[] = {
	PHP_ME(CairoFontFace, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(CairoFontFace, status, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CairoFontFace, getType, NULL, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};
/* }}} */

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(cairo_font_face)
{
	zend_class_entry fontface_ce;
	zend_class_entry fonttype_ce;

        memcpy(&cairo_font_face_object_handlers,
                    zend_get_std_object_handlers(),
                    sizeof(zend_object_handlers));

        /* FontFace */
        cairo_font_face_object_handlers.offset = XtOffsetOf(cairo_font_face_object, std);
        cairo_font_face_object_handlers.free_obj = cairo_font_face_free_obj;
        
	INIT_NS_CLASS_ENTRY(fontface_ce, CAIRO_NAMESPACE, "FontFace", cairo_font_face_methods);
        ce_cairo_fontface = zend_register_internal_class(&fontface_ce);
        ce_cairo_fontface->create_object = cairo_font_face_create_object;
	ce_cairo_fontface->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS;
        
        /* FontType */
	INIT_CLASS_ENTRY(fonttype_ce, "FontType", NULL);
	ce_cairo_fonttype = zend_register_internal_class(&fonttype_ce);
        ce_cairo_fonttype->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS | ZEND_ACC_FINAL;
        
        #define CAIRO_FONTTYPE_DECLARE_ENUM(name) \
            zend_declare_class_constant_long(ce_cairo_fonttype, #name, \
            sizeof(#name)-1, CAIRO_FONT_TYPE_## name);
        
	CAIRO_FONTTYPE_DECLARE_ENUM(TOY);
	CAIRO_FONTTYPE_DECLARE_ENUM(FT);
	CAIRO_FONTTYPE_DECLARE_ENUM(WIN32);
	CAIRO_FONTTYPE_DECLARE_ENUM(QUARTZ);
	CAIRO_FONTTYPE_DECLARE_ENUM(USER);

	return SUCCESS;
}
