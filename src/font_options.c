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

zend_class_entry *ce_cairo_fontoptions;
zend_class_entry *ce_cairo_subpixelorder;
zend_class_entry *ce_cairo_hintstyle;
zend_class_entry *ce_cairo_hintmetrics;


static zend_object_handlers cairo_font_options_object_handlers; 

typedef struct _cairo_font_options_object {
	cairo_font_options_t *font_options;
        zend_object std;
} cairo_font_options_object;

static inline cairo_font_options_object *cairo_font_options_fetch_object(zend_object *object)
{
    return (cairo_font_options_object *) ((char*)(object) - XtOffsetOf(cairo_font_options_object, std));
}

#define Z_CAIRO_FONT_OPTIONS_P(zv) cairo_font_options_fetch_object(Z_OBJ_P(zv))

static inline cairo_font_options_object *cairo_font_options_object_get(zval *zv)
{
	cairo_font_options_object *object = Z_CAIRO_FONT_OPTIONS_P(zv);
	if(object->font_options == NULL) {
		zend_throw_exception_ex(ce_cairo_exception, 0,
			"Internal font_options object missing in %s, you must call parent::__construct in extended classes",
			ZSTR_VAL(Z_OBJCE_P(zv)->name));
		return NULL;
	}
	return object;
}


/* ----------------------------------------------------------------
    Cairo\FontOptions C API
------------------------------------------------------------------*/

zend_class_entry * php_cairo_get_fontoptions_ce()
{
	return ce_cairo_fontoptions;
}


/* ----------------------------------------------------------------
    Cairo\FontOptions Class API
------------------------------------------------------------------*/