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
  | Author: Akshat Gupta <g.akshat@gmail.com>                            |
  |         Elizabeth Smith <auroraeosrose@php.net>                      |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

/* THIS IS NOT USED IN THE EXTENSION - it's provided as an easy way to use cairo in other PHP extensions */

#include <php.h>
#include <cairo.h>

typedef struct _cairo_context_object {
	zend_object std;
	cairo_t *context;
} cairo_context_object;

typedef struct _cairo_pattern_object {
	zend_object std;
	cairo_pattern_t *pattern;
} cairo_pattern_object;

typedef struct _cairo_surface_object {
	zend_object std;
	cairo_surface_t *surface;
} cairo_surface_object;

typedef struct _cairo_path_object {
	zend_object std;
	cairo_path_t *path;
} cairo_path_object;

typedef struct _cairo_fontoptions_object {
	zend_object std;
	cairo_font_options_t *fontoptions;
} cairo_fontoptions_object;

typedef struct _cairo_fontface_object {
	zend_object std;
	cairo_font_face_t *fontface;
} cairo_fontface_object;

typedef struct _cairo_matrix_object {
	zend_object std;
	cairo_matrix_t *matrix;
} cairo_matrix_object;

typedef struct _cairo_scaledfont_object {
	zend_object std;
	cairo_scaled_font_t *scaledfont;
} cairo_scaledfont_object;

extern void php_cairo_throw_exception(cairo_status_t status TSRMLS_DC);
extern void php_cairo_trigger_error(cairo_status_t status TSRMLS_DC);

extern zend_class_entry* php_cairo_get_surface_ce(cairo_surface_t *surface TSRMLS_DC);
extern zend_class_entry* php_cairo_get_pattern_ce(cairo_pattern_t *pattern TSRMLS_DC);
extern zend_class_entry* php_cairo_get_context_ce();
extern zend_class_entry* php_cairo_get_fontface_ce();
extern zend_class_entry* php_cairo_get_fontoptions_ce();
extern zend_class_entry* php_cairo_get_path_ce();

extern zend_class_entry* get_CairoPath_ce_ptr();
extern zend_class_entry* get_CairoMatrix_ce_ptr();
extern zend_class_entry* get_CairoScaledFont_ce_ptr();

/* Wrapped internal cairo functionally to avoid having to link against cairo too */
extern cairo_font_options_t* php_cairo_font_options_copy(const cairo_font_options_t *); 
extern cairo_t * php_cairo_context_reference(cairo_t *context);

/* Helpers to make fetching internal objects work right with extended classes */
static inline cairo_context_object* cairo_context_object_get(zval *zobj TSRMLS_DC)
{
    cairo_context_object *pobj = zend_object_store_get_object(zobj TSRMLS_CC);
    if (pobj->context == NULL) {
		php_error(E_ERROR, "Internal context object missing in %s wrapper, you must call parent::__construct in extended classes", Z_OBJCE_P(zobj)->name);
    }
    return pobj;
}

static inline cairo_fontoptions_object* cairo_fontoptions_object_get(zval *zobj TSRMLS_DC)
{
    cairo_fontoptions_object *pobj = zend_object_store_get_object(zobj TSRMLS_CC);
    if (pobj->fontoptions == NULL) {
        php_error(E_ERROR, "Internal font options object missing in %s wrapper, you must call parent::__construct in extended classes", Z_OBJCE_P(zobj)->name);
    }
    return pobj;
}
/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */