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

#ifndef PHP_CAIRO_H
#define PHP_CAIRO_H

#define PHP_CAIRO_VERSION "0.3.2-beta"

extern zend_module_entry cairo_module_entry;
#define phpext_cairo_ptr &cairo_module_entry

#ifdef PHP_WIN32
#	define PHP_CAIRO_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_CAIRO_API __attribute__ ((visibility("default")))
#else
#	define PHP_CAIRO_API
#endif

/* Silly compilers */
#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

/* 5.2 is stupid and needs some additional stuff */
#ifndef zend_parse_parameters_none
#define zend_parse_parameters_none()										\
	zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "")
#endif

/* refcount macros */
#ifndef Z_ADDREF_P
#define Z_ADDREF_P(pz)                (pz)->refcount++
#endif

#ifndef Z_DELREF_P
#define Z_DELREF_P(pz)                (pz)->refcount--
#endif

#ifndef Z_SET_REFCOUNT_P
#define Z_SET_REFCOUNT_P(pz, rc)      (pz)->refcount = rc
#endif

#include <cairo.h>

#if defined(CAIRO_HAS_FT_FONT) && defined(HAVE_FREETYPE)
#include <ft2build.h>
#include FT_FREETYPE_H
#endif

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

#if defined(CAIRO_HAS_FT_FONT) && defined(HAVE_FREETYPE)
typedef struct _pecl_ft_container {
	FT_Library ft_lib;
    FT_Face ft_face;
    FT_Stream ft_stream;
} pecl_ft_container;
#endif

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

#if defined(CAIRO_HAS_FT_FONT) && defined(HAVE_FREETYPE)
typedef struct _cairo_ft_font_face_object {
	zend_object std;
	cairo_font_face_t *font_face;
    stream_closure *closure;
	cairo_user_data_key_t key;
} cairo_ft_font_face_object;
#endif

#if defined(CAIRO_HAS_WIN32_FONT) && defined(HAVE_WIN32_FONT)
typedef struct _cairo_win32_font_face_object {
	zend_object std;
	cairo_font_face_t *font_face;
} cairo_win32_font_face_object;
#endif

typedef struct _cairo_font_options_object {
	zend_object std;
	cairo_font_options_t *font_options;
} cairo_font_options_object;

/* Lifecycle functions */
PHP_MINIT_FUNCTION(cairo);
PHP_MINFO_FUNCTION(cairo);
PHP_MSHUTDOWN_FUNCTION(cairo);

#if defined(CAIRO_HAS_FT_FONT) && defined(HAVE_FREETYPE)

typedef struct _php_cairo_ft_error {
	int err_code;
	const char *err_msg;
} php_cairo_ft_error;

extern const php_cairo_ft_error php_cairo_ft_errors[];

/* Helper for getting FreeType error strings */
const char* php_cairo_get_ft_error(int error TSRMLS_DC);

#undef __FTERRORS_H__
#define FT_ERRORDEF( e, v, s )  { e, s },
#define FT_ERROR_START_LIST     {
#define FT_ERROR_END_LIST       { 0, 0 } };

#endif

PHP_MINIT_FUNCTION(cairo_matrix);
PHP_MINIT_FUNCTION(cairo_error);
PHP_MINIT_FUNCTION(cairo_context);
PHP_MINIT_FUNCTION(cairo_path);
PHP_MINIT_FUNCTION(cairo_font_options);
PHP_MINIT_FUNCTION(cairo_font_face);
PHP_MINIT_FUNCTION(cairo_scaled_font);
PHP_MINIT_FUNCTION(cairo_font);
PHP_MINIT_FUNCTION(cairo_pattern);
PHP_MINIT_FUNCTION(cairo_surface);
PHP_MINIT_FUNCTION(cairo_image_surface);
PHP_MINIT_FUNCTION(cairo_svg_surface);
PHP_MINIT_FUNCTION(cairo_pdf_surface);
PHP_MINIT_FUNCTION(cairo_ps_surface);
PHP_MINIT_FUNCTION(cairo_recording_surface);
PHP_MINIT_FUNCTION(cairo_sub_surface);
PHP_MINIT_FUNCTION(cairo_ft_font);
PHP_MINIT_FUNCTION(cairo_win32_font);

/* cairo functions */
PHP_FUNCTION(cairo_version);
PHP_FUNCTION(cairo_version_string);
PHP_FUNCTION(cairo_available_surfaces);
PHP_FUNCTION(cairo_available_fonts);
PHP_FUNCTION(cairo_status_to_string);

/* Context Functions */
PHP_FUNCTION(cairo_create);
PHP_FUNCTION(cairo_status);
PHP_FUNCTION(cairo_save);
PHP_FUNCTION(cairo_restore);
PHP_FUNCTION(cairo_get_target);
PHP_FUNCTION(cairo_push_group);
PHP_FUNCTION(cairo_push_group_with_content);
PHP_FUNCTION(cairo_pop_group);
PHP_FUNCTION(cairo_pop_group_to_source);
PHP_FUNCTION(cairo_get_group_target);
PHP_FUNCTION(cairo_set_source_rgb);
PHP_FUNCTION(cairo_set_source_rgba);
PHP_FUNCTION(cairo_set_source);
PHP_FUNCTION(cairo_set_source_surface);
PHP_FUNCTION(cairo_get_source);
PHP_FUNCTION(cairo_set_antialias);
PHP_FUNCTION(cairo_get_antialias);
PHP_FUNCTION(cairo_set_dash);
PHP_FUNCTION(cairo_get_dash_count);
PHP_FUNCTION(cairo_get_dash);
PHP_FUNCTION(cairo_set_fill_rule);
PHP_FUNCTION(cairo_get_fill_rule);
PHP_FUNCTION(cairo_set_line_cap);
PHP_FUNCTION(cairo_get_line_cap);
PHP_FUNCTION(cairo_set_line_cap);
PHP_FUNCTION(cairo_set_line_join);
PHP_FUNCTION(cairo_get_line_join);
PHP_FUNCTION(cairo_set_line_width);
PHP_FUNCTION(cairo_get_line_width);
PHP_FUNCTION(cairo_set_miter_limit);
PHP_FUNCTION(cairo_get_miter_limit);
PHP_FUNCTION(cairo_set_operator);
PHP_FUNCTION(cairo_get_operator);
PHP_FUNCTION(cairo_set_tolerance);
PHP_FUNCTION(cairo_get_tolerance);
PHP_FUNCTION(cairo_clip);
PHP_FUNCTION(cairo_clip_preserve);
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 10, 0)
PHP_FUNCTION(cairo_in_clip);
#endif
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 4, 0)
PHP_FUNCTION(cairo_clip_extents);
PHP_FUNCTION(cairo_clip_rectangle_list);
#endif
PHP_FUNCTION(cairo_reset_clip);
PHP_FUNCTION(cairo_fill);
PHP_FUNCTION(cairo_fill_preserve);
PHP_FUNCTION(cairo_fill_extents);
PHP_FUNCTION(cairo_in_fill);
PHP_FUNCTION(cairo_mask);
PHP_FUNCTION(cairo_mask_surface);
PHP_FUNCTION(cairo_paint);
PHP_FUNCTION(cairo_paint_with_alpha);
PHP_FUNCTION(cairo_stroke);
PHP_FUNCTION(cairo_stroke_preserve);
PHP_FUNCTION(cairo_stroke_extents);
PHP_FUNCTION(cairo_in_stroke);
PHP_FUNCTION(cairo_copy_page);
PHP_FUNCTION(cairo_show_page);

/* Context Transformations */
PHP_FUNCTION(cairo_translate);
PHP_FUNCTION(cairo_scale);
PHP_FUNCTION(cairo_rotate);
PHP_FUNCTION(cairo_transform);
PHP_FUNCTION(cairo_set_matrix);
PHP_FUNCTION(cairo_get_matrix);
PHP_FUNCTION(cairo_identity_matrix);
PHP_FUNCTION(cairo_user_to_device);
PHP_FUNCTION(cairo_user_to_device_distance);
PHP_FUNCTION(cairo_device_to_user);
PHP_FUNCTION(cairo_device_to_user_distance);

/* Context and Paths */
PHP_FUNCTION(cairo_copy_path);
PHP_FUNCTION(cairo_copy_path_flat);
PHP_FUNCTION(cairo_append_path);
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 6, 0)
PHP_FUNCTION(cairo_has_current_point);
#endif
PHP_FUNCTION(cairo_get_current_point);
PHP_FUNCTION(cairo_new_path);
PHP_FUNCTION(cairo_new_sub_path);
PHP_FUNCTION(cairo_close_path);
PHP_FUNCTION(cairo_arc);
PHP_FUNCTION(cairo_arc_negative);
PHP_FUNCTION(cairo_curve_to);
PHP_FUNCTION(cairo_line_to);
PHP_FUNCTION(cairo_move_to);
PHP_FUNCTION(cairo_rectangle);
PHP_FUNCTION(cairo_glyph_path);
PHP_FUNCTION(cairo_text_path);
PHP_FUNCTION(cairo_rel_curve_to);
PHP_FUNCTION(cairo_rel_line_to);
PHP_FUNCTION(cairo_rel_move_to);
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 6, 0)
PHP_FUNCTION(cairo_path_extents);
#endif
/* Text Functions */
PHP_FUNCTION(cairo_select_font_face);
PHP_FUNCTION(cairo_set_font_size);
PHP_FUNCTION(cairo_set_font_matrix);
PHP_FUNCTION(cairo_get_font_matrix);
PHP_FUNCTION(cairo_set_font_options);
PHP_FUNCTION(cairo_get_font_options);
PHP_FUNCTION(cairo_set_font_face);
PHP_FUNCTION(cairo_get_font_face);
PHP_FUNCTION(cairo_set_scaled_font);
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 4, 0)
PHP_FUNCTION(cairo_get_scaled_font);
#endif
PHP_FUNCTION(cairo_show_text);
PHP_FUNCTION(cairo_text_extents);
PHP_FUNCTION(cairo_font_extents);

/* Pattern Functions */
PHP_FUNCTION(cairo_pattern_get_type);
PHP_FUNCTION(cairo_pattern_status);
PHP_FUNCTION(cairo_pattern_get_matrix);
PHP_FUNCTION(cairo_pattern_set_matrix);
PHP_FUNCTION(cairo_pattern_create_rgb);
PHP_FUNCTION(cairo_pattern_create_rgba);
PHP_FUNCTION(cairo_pattern_create_for_surface);
PHP_FUNCTION(cairo_pattern_set_filter);
PHP_FUNCTION(cairo_pattern_get_filter);
PHP_FUNCTION(cairo_pattern_set_extend);
PHP_FUNCTION(cairo_pattern_get_extend);
PHP_FUNCTION(cairo_pattern_add_color_stop_rgb);
PHP_FUNCTION(cairo_pattern_add_color_stop_rgba);
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 4, 0)
PHP_FUNCTION(cairo_pattern_get_color_stop_count);
PHP_FUNCTION(cairo_pattern_get_surface);
PHP_FUNCTION(cairo_pattern_get_linear_points);
PHP_FUNCTION(cairo_pattern_get_radial_circles);
PHP_FUNCTION(cairo_pattern_get_rgba);
PHP_FUNCTION(cairo_pattern_get_color_stop_rgba);
#endif
PHP_FUNCTION(cairo_pattern_create_linear);
PHP_FUNCTION(cairo_pattern_create_radial);
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 12, 0)
PHP_FUNCTION(cairo_pattern_create_mesh);
PHP_FUNCTION(cairo_mesh_pattern_begin_patch);
PHP_FUNCTION(cairo_mesh_pattern_end_patch);
PHP_FUNCTION(cairo_mesh_pattern_move_to);
PHP_FUNCTION(cairo_mesh_pattern_line_to);
PHP_FUNCTION(cairo_mesh_pattern_curve_to);
PHP_FUNCTION(cairo_mesh_pattern_set_control_point);
PHP_FUNCTION(cairo_mesh_pattern_set_corner_color_rgb);
PHP_FUNCTION(cairo_mesh_pattern_set_corner_color_rgba);
PHP_FUNCTION(cairo_mesh_pattern_get_patch_count);
PHP_FUNCTION(cairo_mesh_pattern_get_path);
PHP_FUNCTION(cairo_mesh_pattern_get_corner_color_rgba);
PHP_FUNCTION(cairo_mesh_pattern_get_control_point);
#endif

/* Matrix Functions */
PHP_FUNCTION(cairo_matrix_init);
PHP_FUNCTION(cairo_matrix_init_identity);
PHP_FUNCTION(cairo_matrix_init_translate);
PHP_FUNCTION(cairo_matrix_init_scale);
PHP_FUNCTION(cairo_matrix_init_rotate);
PHP_FUNCTION(cairo_matrix_translate);
PHP_FUNCTION(cairo_matrix_scale);
PHP_FUNCTION(cairo_matrix_rotate);
PHP_FUNCTION(cairo_matrix_invert);
PHP_FUNCTION(cairo_matrix_multiply);
PHP_FUNCTION(cairo_matrix_transform_distance);
PHP_FUNCTION(cairo_matrix_transform_point);

/* Font Options Functions */
PHP_FUNCTION(cairo_font_options_create);
PHP_FUNCTION(cairo_font_options_status);
PHP_FUNCTION(cairo_font_options_merge);
PHP_FUNCTION(cairo_font_options_hash);
PHP_FUNCTION(cairo_font_options_equal);
PHP_FUNCTION(cairo_font_options_set_antialias);
PHP_FUNCTION(cairo_font_options_get_antialias);
PHP_FUNCTION(cairo_font_options_set_subpixel_order);
PHP_FUNCTION(cairo_font_options_get_subpixel_order);
PHP_FUNCTION(cairo_font_options_set_hint_style);
PHP_FUNCTION(cairo_font_options_get_hint_style);
PHP_FUNCTION(cairo_font_options_set_hint_metrics);
PHP_FUNCTION(cairo_font_options_get_hint_metrics);

/* Font Face Functions */
PHP_FUNCTION(cairo_font_face_status);
PHP_FUNCTION(cairo_font_face_get_type);

/* Toy Font Face Functions */
PHP_FUNCTION(cairo_toy_font_face_create);
PHP_FUNCTION(cairo_toy_font_face_get_family);
PHP_FUNCTION(cairo_toy_font_face_get_weight);
PHP_FUNCTION(cairo_toy_font_face_get_slant);

/* Scaled Font Functiosn */
PHP_FUNCTION(cairo_scaled_font_create);
PHP_FUNCTION(cairo_scaled_font_status);
PHP_FUNCTION(cairo_scaled_font_extents);
PHP_FUNCTION(cairo_scaled_font_text_extents);
PHP_FUNCTION(cairo_scaled_font_glyph_extents);
PHP_FUNCTION(cairo_scaled_font_get_font_face);
PHP_FUNCTION(cairo_scaled_font_get_font_options);
PHP_FUNCTION(cairo_scaled_font_get_font_matrix);
PHP_FUNCTION(cairo_scaled_font_get_ctm);
PHP_FUNCTION(cairo_scaled_font_get_scale_matrix);
PHP_FUNCTION(cairo_scaled_font_get_type);

/* Generic Surface Functions */
PHP_FUNCTION(cairo_surface_create_similar);
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 10, 0)
PHP_FUNCTION(cairo_surface_create_for_rectangle);
#endif
PHP_FUNCTION(cairo_surface_status);
PHP_FUNCTION(cairo_surface_finish);
PHP_FUNCTION(cairo_surface_flush);
PHP_FUNCTION(cairo_surface_get_font_options);
PHP_FUNCTION(cairo_surface_get_content);
PHP_FUNCTION(cairo_surface_mark_dirty);
PHP_FUNCTION(cairo_surface_mark_dirty_rectangle);
PHP_FUNCTION(cairo_surface_set_device_offset);
PHP_FUNCTION(cairo_surface_get_device_offset);
PHP_FUNCTION(cairo_surface_set_fallback_resolution);
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 8, 0)
PHP_FUNCTION(cairo_surface_get_fallback_resolution);
#endif
PHP_FUNCTION(cairo_surface_get_type);
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 6, 0)
PHP_FUNCTION(cairo_surface_copy_page);
PHP_FUNCTION(cairo_surface_show_page);
#endif
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 8, 0)
PHP_FUNCTION(cairo_surface_has_show_text_glyphs);
#endif

/* Image Surface Functions */
PHP_FUNCTION(cairo_image_surface_create);
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 6, 0)
	PHP_FUNCTION(cairo_format_stride_for_width);
#endif
PHP_FUNCTION(cairo_image_surface_create_for_data);
PHP_FUNCTION(cairo_image_surface_get_data);
PHP_FUNCTION(cairo_image_surface_get_format);
PHP_FUNCTION(cairo_image_surface_get_width);
PHP_FUNCTION(cairo_image_surface_get_height);
PHP_FUNCTION(cairo_image_surface_get_stride);

/* PNG support Functions */
#ifdef CAIRO_HAS_PNG_FUNCTIONS
PHP_FUNCTION(cairo_image_surface_create_from_png);
PHP_FUNCTION(cairo_surface_write_to_png);
#endif

/* Font Face Functions */
PHP_FUNCTION(cairo_font_face_status);
PHP_FUNCTION(cairo_font_face_get_type);
#ifdef CAIRO_HAS_QUARTZ_FONT
	PHP_FUNCTION(cairo_quartz_font_face_create_for_atsu_font_id);
	PHP_FUNCTION(cairo_quartz_font_face_create_for_cgfont);
#endif
#if defined(CAIRO_HAS_FT_FONT) && defined(HAVE_FREETYPE)
	PHP_FUNCTION(cairo_ft_font_face_create);
#endif
#if defined(CAIRO_HAS_WIN32_FONT) && defined(HAVE_WIN32_FONT)
	PHP_FUNCTION(cairo_win32_font_face_create);
#endif

/* SVG Surface Functiosn */
#ifdef CAIRO_HAS_SVG_SURFACE
	PHP_FUNCTION(cairo_svg_surface_create);
	PHP_FUNCTION(cairo_svg_surface_restrict_to_version);
	PHP_FUNCTION(cairo_svg_get_versions);
	PHP_FUNCTION(cairo_svg_version_to_string);
#endif

	/* PDF Surface Functions */
#ifdef CAIRO_HAS_PDF_SURFACE
	PHP_FUNCTION(cairo_pdf_surface_create);
	PHP_FUNCTION(cairo_pdf_surface_set_size);
#endif

	/* PS Surface Functions */
#ifdef CAIRO_HAS_PS_SURFACE
	PHP_FUNCTION(cairo_ps_surface_create);
	PHP_FUNCTION(cairo_ps_surface_set_size);
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 6, 0)
	PHP_FUNCTION(cairo_ps_surface_restrict_to_level);
	PHP_FUNCTION(cairo_ps_surface_set_eps);
	PHP_FUNCTION(cairo_ps_surface_get_eps);
	PHP_FUNCTION(cairo_ps_get_levels);
	PHP_FUNCTION(cairo_ps_level_to_string);
#endif
	PHP_FUNCTION(cairo_ps_surface_dsc_begin_setup);
	PHP_FUNCTION(cairo_ps_surface_dsc_begin_page_setup);
	PHP_FUNCTION(cairo_ps_surface_dsc_comment);
#endif

/* Recording surface functions */
#ifdef CAIRO_HAS_RECORDING_SURFACE
	PHP_FUNCTION(cairo_recording_surface_create);
#endif

extern zend_object_handlers cairo_std_object_handlers;
extern zend_class_entry *cairo_ce_cairoexception;
extern zend_class_entry *cairo_ce_cairocontext;
extern zend_class_entry *cairo_ce_cairosurface;
extern zend_class_entry *cairo_ce_cairopattern;
extern zend_class_entry *cairo_ce_cairomatrix;
extern zend_class_entry *cairo_ce_cairopath;
extern zend_class_entry *cairo_ce_cairoimagesurface;
extern zend_class_entry *cairo_ce_cairosvgsurface;
extern zend_class_entry *cairo_ce_cairopdfsurface;
extern zend_class_entry *cairo_ce_cairopssurface;
extern zend_class_entry *cairo_ce_cairorecordingsurface;
extern zend_class_entry *cairo_ce_cairosubsurface;
extern zend_class_entry *cairo_ce_cairocontent;
extern zend_class_entry *cairo_ce_cairofontoptions;
extern zend_class_entry *cairo_ce_cairofontface;
extern zend_class_entry *cairo_ce_cairofonttype;
extern zend_class_entry *cairo_ce_cairofontslant;
extern zend_class_entry *cairo_ce_cairofontweight;
extern zend_class_entry *cairo_ce_cairotoyfontface;
extern zend_class_entry *cairo_ce_cairoscaledfont;
extern zend_class_entry *cairo_ce_cairoftfontface;

extern zend_object_value cairo_surface_object_new(zend_class_entry *ce TSRMLS_DC);
extern cairo_status_t php_cairo_read_func(void *closure, const unsigned char *data, unsigned int length);
extern cairo_status_t php_cairo_write_func(void *closure, const unsigned char *data, unsigned int length);
#if defined(CAIRO_HAS_FT_FONT) && defined(HAVE_FREETYPE)
static unsigned long php_cairo_ft_read_func(FT_Stream stream, unsigned long offset, unsigned char* buffer, unsigned long count);
#endif

extern zend_object_value cairo_font_face_object_new(zend_class_entry *ce TSRMLS_DC);

/* Exported functions for PHP Cairo API */
PHP_CAIRO_API extern void php_cairo_throw_exception(cairo_status_t status TSRMLS_DC);
PHP_CAIRO_API extern void php_cairo_trigger_error(cairo_status_t status TSRMLS_DC);
PHP_CAIRO_API extern zend_class_entry* php_cairo_get_surface_ce(cairo_surface_t *surface TSRMLS_DC);
PHP_CAIRO_API extern zend_class_entry* php_cairo_get_pattern_ce(cairo_pattern_t *pattern TSRMLS_DC);
PHP_CAIRO_API extern zend_class_entry* php_cairo_get_context_ce();
PHP_CAIRO_API extern zend_class_entry* php_cairo_get_fontface_ce();
PHP_CAIRO_API extern zend_class_entry* php_cairo_get_fontoptions_ce();
PHP_CAIRO_API extern zend_class_entry* php_cairo_get_path_ce();

/* Wrapped internal cairo functionality to avoid having to link against cairo lib as well as this extension */
PHP_CAIRO_API extern cairo_font_options_t* php_cairo_font_options_copy(const cairo_font_options_t *);
PHP_CAIRO_API extern cairo_t * php_cairo_context_reference(cairo_t *context);

#define ALLOCATE_MATRIX(matrix_value) if (!matrix_value) { matrix_value = ecalloc(sizeof(cairo_matrix_t), 1); }

/* turn error handling to exception mode and restore */
#if PHP_VERSION_ID >= 50300
/* 5.3 version of the macros */
#define PHP_CAIRO_ERROR_HANDLING(force_exceptions) \
	zend_error_handling error_handling; \
	if(force_exceptions || getThis()) { \
		zend_replace_error_handling(EH_THROW, cairo_ce_cairoexception, &error_handling TSRMLS_CC); \
	}

#define PHP_CAIRO_RESTORE_ERRORS(force_exceptions) \
	if(force_exceptions || getThis()) { \
		zend_restore_error_handling(&error_handling TSRMLS_CC); \
	}

#else
/* 5.2 versions of the macros */
#define PHP_CAIRO_ERROR_HANDLING(force_exceptions) \
	if(force_exceptions || getThis()) { \
		php_set_error_handling(EH_THROW, cairo_ce_cairoexception TSRMLS_CC); \
	}

#define PHP_CAIRO_RESTORE_ERRORS(force_exceptions) \
	if(force_exceptions || getThis()) { \
		php_std_error_handling(); \
	}

#endif

/* do error or exception based on "are we in method or in function" */
#define PHP_CAIRO_ERROR(status) \
	if(!getThis()) { \
		php_cairo_trigger_error(status TSRMLS_CC); \
	} else { \
		php_cairo_throw_exception(status TSRMLS_CC); \
	}

/* a bunch of inline functions to deal with checking for the proper internal object, makes extending classes work */
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

#endif /* PHP_CAIRO_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
