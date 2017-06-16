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

#ifndef PHP_CAIRO_INTERNAL_H
#define PHP_CAIRO_INTERNAL_H

#include <php.h>
#include <cairo.h>

extern zend_class_entry *ce_cairo_exception;
extern zend_class_entry *ce_cairo_status;
extern zend_class_entry *ce_cairo_matrix;

extern zend_class_entry *ce_cairo_context;
extern zend_class_entry *ce_cairo_fillrule;
extern zend_class_entry *ce_cairo_linecap;
extern zend_class_entry *ce_cairo_linejoin;
extern zend_class_entry *ce_cairo_operator;

extern zend_class_entry *ce_cairo_surface;
extern zend_class_entry *ce_cairo_content;
extern zend_class_entry *ce_cairo_surfacetype;
extern zend_class_entry *ce_cairo_imagesurface;
extern zend_class_entry *ce_cairo_format;
extern zend_class_entry *ce_cairo_svgsurface;
extern zend_class_entry *ce_cairo_svgversion;
extern zend_class_entry *ce_cairo_pdfsurface;
extern zend_class_entry *ce_cairo_pssurface;
extern zend_class_entry *ce_cairo_pslevel;
extern zend_class_entry *ce_cairo_recordingsurface;
extern zend_class_entry *ce_cairo_subsurface;

extern zend_class_entry *ce_cairo_fontface;
extern zend_class_entry *ce_cairo_fonttype;
extern zend_class_entry *ce_cairo_scaled_font;

extern zend_class_entry *ce_cairo_fontoptions;
extern zend_class_entry *ce_cairo_subpixelorder;
extern zend_class_entry *ce_cairo_hintstyle;
extern zend_class_entry *ce_cairo_hintmetrics;
extern zend_class_entry *ce_cairo_antialias;

extern zend_class_entry *ce_cairo_fontslant;
extern zend_class_entry *ce_cairo_fontweight;
extern zend_class_entry *ce_cairo_toyfontface;

extern zend_class_entry *ce_cairo_ftfont;

extern zend_class_entry *ce_cairo_path;

extern zend_class_entry* php_cairo_get_pattern_ce(cairo_pattern_t *pattern);
extern zend_class_entry* php_cairo_get_surface_ce(cairo_surface_t *surface);
extern zend_class_entry* php_cairo_get_fontoptions_ce();
extern zend_class_entry* php_cairo_get_fontface_ce();
extern zend_class_entry* php_cairo_get_path_ce();

/* Pattern */
typedef struct _cairo_pattern_object {
        cairo_pattern_t *pattern;
        zval surface;
	zend_object std;
} cairo_pattern_object;
extern cairo_pattern_object *cairo_pattern_fetch_object(zend_object *object);
#define Z_CAIRO_PATTERN_P(zv) cairo_pattern_fetch_object(Z_OBJ_P(zv))

/* Matrix */
typedef struct _cairo_matrix_object {
	cairo_matrix_t *matrix;
	zend_object std;
} cairo_matrix_object;

#define Z_CAIRO_MATRIX_P(zv) cairo_matrix_fetch_object(Z_OBJ_P(zv))
extern cairo_matrix_object *cairo_matrix_fetch_object(zend_object *object);
extern cairo_matrix_object *cairo_matrix_object_get(zval *zv);
cairo_matrix_t *cairo_matrix_object_get_matrix(zval *zv);

/* FontOptions */
typedef struct _cairo_font_options_object {
	cairo_font_options_t *font_options;
        zend_object std;
} cairo_font_options_object;

extern cairo_font_options_object *cairo_font_options_fetch_object(zend_object *object);
cairo_font_options_t *cairo_font_options_object_get_font_options(zval *zv);

/* Surface */
typedef struct _stream_closure {
    php_stream *stream;
    zend_bool owned_stream;
} stream_closure;

typedef struct _cairo_surface_object {
	cairo_surface_t *surface;
        char * buffer;
	stream_closure *closure;
	zval *parent_zval;
	zend_object std;
} cairo_surface_object;

#define Z_CAIRO_SURFACE_P(zv) cairo_surface_fetch_object(Z_OBJ_P(zv))
extern cairo_surface_object *cairo_surface_fetch_object(zend_object *object);
extern zend_object* cairo_surface_create_object(zend_class_entry *ce);
extern cairo_surface_object *cairo_surface_object_get(zval *zv);
extern cairo_status_t php_cairo_write_func(void *closure, const unsigned char *data, unsigned int length);
extern cairo_status_t php_cairo_read_func(void *closure, const unsigned char *data, unsigned int length);

/* Font + FontFace */
typedef struct _cairo_font_face_object {
	cairo_font_face_t *font_face;
        stream_closure *closure;
	cairo_user_data_key_t key;
        zend_object std;
} cairo_font_face_object;

extern zend_object* cairo_font_face_create_object(zend_class_entry *ce);
extern cairo_font_face_object *cairo_font_face_fetch_object(zend_object *object);
extern cairo_font_face_object *cairo_font_face_object_get(zval *zv);
#define Z_CAIRO_FONT_FACE_P(zv) cairo_font_face_fetch_object(Z_OBJ_P(zv))
cairo_font_face_t *cairo_font_face_object_get_font_face(zval *zv);

/* ScaledFont */
typedef struct _cairo_scaled_font_object {
	zval font_face;
	zval font_options;
	zval matrix;
	zval ctm;
	cairo_scaled_font_t *scaled_font;
        zend_object std;
} cairo_scaled_font_object;

extern cairo_scaled_font_object *cairo_scaled_font_fetch_object(zend_object *object);
#define Z_CAIRO_SCALED_FONT_P(zv) cairo_scaled_font_fetch_object(Z_OBJ_P(zv))

/* Fon-Options */
#define Z_CAIRO_FONT_OPTIONS_P(zv) cairo_font_options_fetch_object(Z_OBJ_P(zv))
extern cairo_font_options_object *cairo_font_options_fetch_object(zend_object *object);

/* Path */
typedef struct _cairo_path_object {
	cairo_path_t *path;
        zend_object std;
} cairo_path_object;

extern cairo_path_object *cairo_path_fetch_object(zend_object *object);
#define Z_CAIRO_PATH_P(zv) cairo_path_fetch_object(Z_OBJ_P(zv));

/* Freetype */
#if defined(CAIRO_HAS_FT_FONT) && defined(HAVE_FREETYPE)

#include <ft2build.h>
#include FT_FREETYPE_H
#include <cairo-ft.h>

typedef struct _pecl_ft_container {
        FT_Library ft_lib;
        FT_Face ft_face;
        FT_Stream ft_stream;
} pecl_ft_container;

typedef struct _php_cairo_ft_error {
	int err_code;
	const char *err_msg;
} php_cairo_ft_error;

extern const php_cairo_ft_error php_cairo_ft_errors[];

/* Helper for getting FreeType error strings */
const char* php_cairo_get_ft_error(int error);

#undef __FTERRORS_H__
#define FT_ERRORDEF( e, v, s )  { e, s },
#define FT_ERROR_START_LIST     {
#define FT_ERROR_END_LIST { 0, 0 } };

#endif

/* Context */
typedef struct _cairo_context_object {
	zval surface;
	zval matrix;
	zval pattern;
	zval font_face;
	zval font_matrix;
	zval font_options;
	zval scaled_font;
	cairo_t *context;
        zend_object std;
} cairo_context_object;

extern cairo_context_object *cairo_context_fetch_object(zend_object *object);
#define Z_CAIRO_CONTEXT_P(zv) cairo_context_fetch_object(Z_OBJ_P(zv))


/* Classes to register */
PHP_MINIT_FUNCTION(cairo_pattern);
PHP_MINIT_FUNCTION(cairo_region);
PHP_MINIT_FUNCTION(cairo_matrix);
PHP_MINIT_FUNCTION(cairo_exception);
PHP_MINIT_FUNCTION(cairo_rectangle);
PHP_MINIT_FUNCTION(cairo_font_face);
PHP_MINIT_FUNCTION(cairo_font);
PHP_MINIT_FUNCTION(cairo_font_options);
PHP_MINIT_FUNCTION(cairo_scaled_font);
#if defined(CAIRO_HAS_FT_FONT) && defined(HAVE_FREETYPE)
PHP_MINIT_FUNCTION(cairo_ft_font);
#endif
#if defined(CAIRO_HAS_QUARTZ_FONT)
PHP_MINIT_FUNCTION(cairo_quartz_font);
#endif
#if defined(CAIRO_HAS_WIN32_FONT) && defined(HAVE_WIN32_FONT)
PHP_MINIT_FUNCTION(cairo_win32_font);
#endif
PHP_MINIT_FUNCTION(cairo_surface);
PHP_MINIT_FUNCTION(cairo_image_surface);
PHP_MINIT_FUNCTION(cairo_sub_surface);
PHP_MINIT_FUNCTION(cairo_recording_surface);
PHP_MINIT_FUNCTION(cairo_pdf_surface);
PHP_MINIT_FUNCTION(cairo_svg_surface);
PHP_MINIT_FUNCTION(cairo_ps_surface);
PHP_MINIT_FUNCTION(cairo_path);
PHP_MINIT_FUNCTION(cairo_context);

#endif /* PHP_CAIRO_INTERNAL_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
