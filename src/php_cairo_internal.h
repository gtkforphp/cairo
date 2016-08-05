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

extern zend_class_entry *ce_cairo_surface;
extern zend_class_entry *ce_cairo_content;
extern zend_class_entry *ce_cairo_surfacetype;
extern zend_class_entry *ce_cairo_imagesurface;
extern zend_class_entry *ce_cairo_format;
//extern zend_class_entry *ce_cairo_svgsurface;
extern zend_class_entry *ce_cairo_pdfsurface;
//extern zend_class_entry *ce_cairo_pssurface;
extern zend_class_entry *ce_cairo_recordingsurface;
extern zend_class_entry *ce_cairo_subsurface;

extern zend_class_entry *ce_cairo_fontface;
extern zend_class_entry *ce_cairo_fonttype;

extern zend_class_entry *ce_cairo_fontoptions;
extern zend_class_entry *ce_cairo_subpixelorder;
extern zend_class_entry *ce_cairo_hintstyle;
extern zend_class_entry *ce_cairo_hintmetrics;

extern zend_class_entry *ce_cairo_fontslant;
extern zend_class_entry *ce_cairo_fontweight;
extern zend_class_entry *ce_cairo_toyfontface;

extern zend_class_entry *ce_cairo_path;

extern zend_class_entry* php_cairo_get_pattern_ce(cairo_pattern_t *pattern);
extern zend_class_entry* php_cairo_get_surface_ce(cairo_surface_t *surface);
extern zend_class_entry* php_cairo_get_fontoptions_ce();
extern zend_class_entry* php_cairo_get_fontface_ce();
extern zend_class_entry* php_cairo_get_path_ce();

/* Matrix */
typedef struct _cairo_matrix_object {
	cairo_matrix_t *matrix;
	zend_object std;
} cairo_matrix_object;

#define Z_CAIRO_MATRIX_P(zv) cairo_matrix_fetch_object(Z_OBJ_P(zv))
extern cairo_matrix_object *cairo_matrix_fetch_object(zend_object *object);
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
extern cairo_status_t php_cairo_write_func(void *closure, const unsigned char *data, unsigned int length);
extern cairo_status_t php_cairo_read_func(void *closure, const unsigned char *data, unsigned int length);

/* Font + FontFace */
typedef struct _cairo_font_face_object {
	cairo_font_face_t *font_face;
        zend_object std;
} cairo_font_face_object;

extern zend_object* cairo_font_face_create_object(zend_class_entry *ce);
extern cairo_font_face_object *cairo_font_face_fetch_object(zend_object *object);
#define Z_CAIRO_FONT_FACE_P(zv) cairo_font_face_fetch_object(Z_OBJ_P(zv))
cairo_font_face_t *cairo_font_face_object_get_font_face(zval *zv);

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
PHP_MINIT_FUNCTION(cairo_surface);
PHP_MINIT_FUNCTION(cairo_image_surface);
PHP_MINIT_FUNCTION(cairo_sub_surface);
PHP_MINIT_FUNCTION(cairo_recording_surface);
PHP_MINIT_FUNCTION(cairo_pdf_surface);
PHP_MINIT_FUNCTION(cairo_path);

#endif /* PHP_CAIRO_INTERNAL_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
