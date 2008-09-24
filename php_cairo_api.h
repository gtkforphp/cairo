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

#ifdef CAIRO_EXPORTS 
#define PHP_CAIRO_API __declspec(dllexport)
#else
#define PHP_CAIRO_API
#endif

#include <php.h>
#include <cairo.h>

typedef struct _cairo_context_object {
	zend_object std;
	cairo_t *context;
} cairo_context_object;

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
	cairo_matrix_t matrix;
} cairo_matrix_object;

typedef struct _cairo_pattern_object {
	zend_object std;
	cairo_pattern_t *pattern;
} cairo_pattern_object;

typedef struct _cairo_scaledfont_object {
	zend_object std;
	cairo_scaled_font_t *scaledfont;
} cairo_scaledfont_object;


PHP_CAIRO_API extern zend_class_entry* get_CairoSurface_ce_ptr(cairo_surface_t *);
PHP_CAIRO_API extern zend_class_entry* get_CairoContext_ce_ptr();
PHP_CAIRO_API extern zend_class_entry* get_CairoPattern_ce_ptr(cairo_pattern_t *);
PHP_CAIRO_API extern zend_class_entry* get_CairoPath_ce_ptr();
PHP_CAIRO_API extern zend_class_entry* get_CairoMatrix_ce_ptr();
PHP_CAIRO_API extern zend_class_entry* get_CairoFontOptions_ce_ptr();
PHP_CAIRO_API extern zend_class_entry* get_CairoFontFace_ce_ptr();
PHP_CAIRO_API extern zend_class_entry* get_CairoScaledFont_ce_ptr();
PHP_CAIRO_API extern void cairo_throw_exception(cairo_status_t TSRMLS_DC);


/* Specifically for php-gtk */
PHP_CAIRO_API extern cairo_font_options_t* cairo_copy_fontoptions(cairo_font_options_t *); 
PHP_CAIRO_API extern void php_cairo_context_reference(cairo_t *);

/* Error macros */
#define PHP_CAIRO_CONTEXT_ERROR(context) \
	cairo_throw_exception(cairo_status(context) TSRMLS_CC);

#define PHP_CAIRO_PATTERN_ERROR(pattern) \
	cairo_throw_exception(cairo_pattern_status(pattern) TSRMLS_CC);
	
#define PHP_CAIRO_SURFACE_ERROR(surface) \
	cairo_throw_exception(cairo_surface_status(surface) TSRMLS_CC);

#define PHP_CAIRO_SCALEDFONT_ERROR(sc_font) \
	cairo_throw_exception(cairo_scaled_font_status(sc_font) TSRMLS_CC);

#define PHP_CAIRO_FONTOPTIONS_ERROR(font_opt) \
	cairo_throw_exception(cairo_font_options_status(font_opt) TSRMLS_CC);

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw = 4 ts = 4 fdm = marker
 * vim<600: noet sw = 4 ts = 4
 */