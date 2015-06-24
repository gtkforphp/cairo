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
  |         Akshat Gupta <g.akshat@gmail.com>                            |
  +----------------------------------------------------------------------+
*/

#ifndef PHP_CAIRO_API_H
#define PHP_CAIRO_API_H

/* Public C api for use by other extensions */

#include <php.h>
#include <cairo.h>

#define PHP_CAIRO_API_VERSION "1.0.0"

/* Cairo object stuff */
typedef struct _stream_closure {
	php_stream *stream;
    zend_bool owned_stream;
#ifdef ZTS
	TSRMLS_D;
#endif
} stream_closure;

typedef struct _cairo_glyph_object {
	zend_object std;
	cairo_glyph_t *glyph;
} cairo_glyph_object;

typedef struct _cairo_context_object {
	zend_object std;
	zval *surface;
	zval *matrix;
	zval *pattern;
	zval *font_face;
	zval *font_matrix;
	zval *font_options;
	zval *scaled_font;
	cairo_t *context;
} cairo_context_object;

typedef struct _cairo_pattern_object {
	zend_object std;
	zval *matrix;
	zval *surface;
	cairo_pattern_t *pattern;
} cairo_pattern_object;

typedef struct _cairo_surface_object {
	zend_object std;
	cairo_surface_t *surface;
	char * buffer;
	stream_closure *closure;
	zval *parent_zval;
} cairo_surface_object;

typedef struct _cairo_matrix_object {
	zend_object std;
	cairo_matrix_t *matrix;
} cairo_matrix_object;

typedef struct _cairo_path_object {
	zend_object std;
	cairo_path_t *path;
} cairo_path_object;

typedef struct _cairo_scaled_font_object {
	zend_object std;
	zval *font_face;
	zval *font_options;
	zval *matrix;
	zval *ctm;
	cairo_scaled_font_t *scaled_font;
} cairo_scaled_font_object;

typedef struct _cairo_font_face_object {
	zend_object std;
	cairo_font_face_t *font_face;
} cairo_font_face_object;

typedef struct _cairo_font_options_object {
	zend_object std;
	cairo_font_options_t *font_options;
} cairo_font_options_object;



/* Exported functions for PHP Cairo API */
extern void php_cairo_throw_exception(cairo_status_t status TSRMLS_DC);
extern void php_cairo_trigger_error(cairo_status_t status TSRMLS_DC);
extern zend_class_entry* php_cairo_get_surface_ce(cairo_surface_t *surface TSRMLS_DC);
extern zend_class_entry* php_cairo_get_pattern_ce(cairo_pattern_t *pattern TSRMLS_DC);
extern zend_class_entry* php_cairo_get_context_ce();
extern zend_class_entry* php_cairo_get_fontface_ce();
extern zend_class_entry* php_cairo_get_fontoptions_ce();
extern zend_class_entry* php_cairo_get_path_ce();

/* Wrapped internal cairo functionality to avoid having to link against cairo lib as well as this extension */
extern cairo_font_options_t* php_cairo_font_options_copy(const cairo_font_options_t *);
extern cairo_t * php_cairo_context_reference(cairo_t *context);

/* Helper for FreeType etc */
#if defined(CAIRO_HAS_FT_FONT) && defined(HAVE_FREETYPE)
const char* php_cairo_get_ft_error(int error);
#endif

/* Helpers to make fetching internal objects work right with extended classes */
static inline cairo_context_object* cairo_context_object_get(zval *zobj TSRMLS_DC)
{
    cairo_context_object *pobj = zend_object_store_get_object(zobj TSRMLS_CC);
    if (pobj->context == NULL) {
		php_error(E_ERROR, "Internal context object missing in %s wrapper, you must call parent::__construct in extended classes", Z_OBJCE_P(zobj)->name);
    }
    return pobj;
}

static inline cairo_path_object* cairo_path_object_get(zval *zobj TSRMLS_DC)
{
    cairo_path_object *pobj = zend_object_store_get_object(zobj TSRMLS_CC);
    if (pobj->path == NULL) {
		php_error(E_ERROR, "Internal path object missing in %s wrapper, you must call parent::__construct in extended classes", Z_OBJCE_P(zobj)->name);
    }
    return pobj;
}

static inline cairo_pattern_object* cairo_pattern_object_get(zval *zobj TSRMLS_DC)
{
    cairo_pattern_object *pobj = zend_object_store_get_object(zobj TSRMLS_CC);
    if (pobj->pattern == NULL) {
        php_error(E_ERROR, "Internal pattern object missing in %s wrapper, you must call parent::__construct in extended classes", Z_OBJCE_P(zobj)->name);
    }
    return pobj;
}

static inline cairo_matrix_object* cairo_matrix_object_get(zval *zobj TSRMLS_DC)
{
    cairo_matrix_object *mobj = zend_object_store_get_object(zobj TSRMLS_CC);
    if (mobj->matrix == NULL) {
        php_error(E_ERROR, "Internal matrix object missing in %s wrapper, you must call parent::__construct in extended classes", Z_OBJCE_P(zobj)->name);
    }
    return mobj;
}

static inline cairo_surface_object* cairo_surface_object_get(zval *zobj TSRMLS_DC)
{
    cairo_surface_object *pobj = zend_object_store_get_object(zobj TSRMLS_CC);
    if (pobj->surface == NULL) {
        php_error(E_ERROR, "Internal surface object missing in %s wrapper, you must call parent::__construct in extended classes", Z_OBJCE_P(zobj)->name);
    }
    return pobj;
}

static inline cairo_font_face_object* cairo_font_face_object_get(zval *zobj TSRMLS_DC)
{
    cairo_font_face_object *pobj = zend_object_store_get_object(zobj TSRMLS_CC);
    if (pobj->font_face == NULL) {
        php_error(E_ERROR, "Internal font face object missing in %s wrapper, you must call parent::__construct in extended classes", Z_OBJCE_P(zobj)->name);
    }
    return pobj;
}

static inline cairo_scaled_font_object* cairo_scaled_font_object_get(zval *zobj TSRMLS_DC)
{
    cairo_scaled_font_object *pobj = zend_object_store_get_object(zobj TSRMLS_CC);
    if (pobj->scaled_font == NULL) {
        php_error(E_ERROR, "Internal scaled font object missing in %s wrapper, you must call parent::__construct in extended classes", Z_OBJCE_P(zobj)->name);
    }
    return pobj;
}

static inline cairo_font_options_object* cairo_font_options_object_get(zval *zobj TSRMLS_DC)
{
    cairo_font_options_object *pobj = zend_object_store_get_object(zobj TSRMLS_CC);
    if (pobj->font_options == NULL) {
        php_error(E_ERROR, "Internal font options object missing in %s wrapper, you must call parent::__construct in extended classes", Z_OBJCE_P(zobj)->name);
    }
    return pobj;
}

#endif /* PHP_CAIRO_API_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
