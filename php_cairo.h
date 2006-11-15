/*
   +----------------------------------------------------------------------+
   | This library is free software; you can redistribute it and/or        |
   | modify it under the terms of the GNU Lesser General Public           |
   | License as published by the Free Software Foundation; either         |
   | version 2.1 of the License, or (at your option) any later version.   | 
   |                                                                      |
   | This library is distributed in the hope that it will be useful,      |
   | but WITHOUT ANY WARRANTY; without even the implied warranty of       |
   | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU    |
   | Lesser General Public License for more details.                      | 
   |                                                                      |
   | You should have received a copy of the GNU Lesser General Public     |
   | License in the file LICENSE along with this library;                 |
   | if not, write to the                                                 | 
   |                                                                      |
   |   Free Software Foundation, Inc.,                                    |
   |   59 Temple Place, Suite 330,                                        |
   |   Boston, MA  02111-1307  USA                                        |
   +----------------------------------------------------------------------+
   | Authors: Hartmut Holzgraefe <hartmut@php.net>                        |
   +----------------------------------------------------------------------+
*/

/* $ Id: $ */ 

#ifndef PHP_CAIRO_H
#define PHP_CAIRO_H

#ifdef  __cplusplus
extern "C" {
#endif

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>

#ifdef HAVE_CAIRO

#include <php_ini.h>
#include <SAPI.h>
#include <ext/standard/info.h>
#include <Zend/zend_extensions.h>
#ifdef  __cplusplus
} // extern "C" 
#endif
#include <cairo.h>
#ifdef  __cplusplus
extern "C" {
#endif

extern zend_module_entry cairo_module_entry;
#define phpext_cairo_ptr &cairo_module_entry

#ifdef PHP_WIN32
#define PHP_CAIRO_API __declspec(dllexport)
#else
#define PHP_CAIRO_API
#endif

PHP_MINIT_FUNCTION(cairo);
PHP_MSHUTDOWN_FUNCTION(cairo);
PHP_RINIT_FUNCTION(cairo);
PHP_RSHUTDOWN_FUNCTION(cairo);
PHP_MINFO_FUNCTION(cairo);

#ifdef ZTS
#include "TSRM.h"
#endif

#define FREE_RESOURCE(resource) zend_list_delete(Z_LVAL_P(resource))

#define PROP_GET_LONG(name)    Z_LVAL_P(zend_read_property(_this_ce, _this_zval, #name, strlen(#name), 1 TSRMLS_CC))
#define PROP_SET_LONG(name, l) zend_update_property_long(_this_ce, _this_zval, #name, strlen(#name), l TSRMLS_CC)

#define PROP_GET_DOUBLE(name)    Z_DVAL_P(zend_read_property(_this_ce, _this_zval, #name, strlen(#name), 1 TSRMLS_CC))
#define PROP_SET_DOUBLE(name, d) zend_update_property_double(_this_ce, _this_zval, #name, strlen(#name), d TSRMLS_CC)

#define PROP_GET_STRING(name)    Z_STRVAL_P(zend_read_property(_this_ce, _this_zval, #name, strlen(#name), 1 TSRMLS_CC))
#define PROP_GET_STRLEN(name)    Z_STRLEN_P(zend_read_property(_this_ce, _this_zval, #name, strlen(#name), 1 TSRMLS_CC))
#define PROP_SET_STRING(name, s) zend_update_property_string(_this_ce, _this_zval, #name, strlen(#name), s TSRMLS_CC)
#define PROP_SET_STRINGL(name, s, l) zend_update_property_string(_this_ce, _this_zval, #name, strlen(#name), s, l TSRMLS_CC)


PHP_FUNCTION(cairo_image_surface_create);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_image_surface_create_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 3)
  ZEND_ARG_INFO(0, format)
  ZEND_ARG_INFO(0, x)
  ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_image_surface_create_arg_info NULL
#endif

PHP_FUNCTION(cairo_surface_destroy);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_surface_destroy_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, surface)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_surface_destroy_arg_info NULL
#endif

PHP_FUNCTION(cairo_create);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_create_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, surface)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_create_arg_info NULL
#endif

PHP_FUNCTION(cairo_destroy);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_destroy_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, cr)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_destroy_arg_info NULL
#endif

PHP_FUNCTION(cairo_pattern_create_linear);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_pattern_create_linear_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 4)
  ZEND_ARG_INFO(0, x0)
  ZEND_ARG_INFO(0, y0)
  ZEND_ARG_INFO(0, x1)
  ZEND_ARG_INFO(0, y1)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_pattern_create_linear_arg_info NULL
#endif

PHP_FUNCTION(cairo_pattern_create_radial);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_pattern_create_radial_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 6)
  ZEND_ARG_INFO(0, cx0)
  ZEND_ARG_INFO(0, cy0)
  ZEND_ARG_INFO(0, radius0)
  ZEND_ARG_INFO(0, cx1)
  ZEND_ARG_INFO(0, cy1)
  ZEND_ARG_INFO(0, radius1)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_pattern_create_radial_arg_info NULL
#endif

PHP_FUNCTION(cairo_pattern_create_for_surface);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_pattern_create_for_surface_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, surface)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_pattern_create_for_surface_arg_info NULL
#endif

PHP_FUNCTION(cairo_pattern_create_rgb);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_pattern_create_rgb_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 3)
  ZEND_ARG_INFO(0, red)
  ZEND_ARG_INFO(0, green)
  ZEND_ARG_INFO(0, blue)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_pattern_create_rgb_arg_info NULL
#endif

PHP_FUNCTION(cairo_pattern_create_rgba);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_pattern_create_rgba_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 4)
  ZEND_ARG_INFO(0, red)
  ZEND_ARG_INFO(0, green)
  ZEND_ARG_INFO(0, blue)
  ZEND_ARG_INFO(0, alpha)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_pattern_create_rgba_arg_info NULL
#endif

PHP_FUNCTION(cairo_pattern_destroy);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_pattern_destroy_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, cr)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_pattern_destroy_arg_info NULL
#endif

PHP_FUNCTION(cairo_path_destroy);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_path_destroy_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, cr)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_path_destroy_arg_info NULL
#endif

PHP_FUNCTION(cairo_select_font_face);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_select_font_face_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 4)
  ZEND_ARG_INFO(0, cr)
  ZEND_ARG_INFO(0, fontname)
  ZEND_ARG_INFO(0, slant)
  ZEND_ARG_INFO(0, weight)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_select_font_face_arg_info NULL
#endif

PHP_FUNCTION(cairo_set_font_size);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_set_font_size_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, cr)
  ZEND_ARG_INFO(0, size)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_set_font_size_arg_info NULL
#endif

PHP_FUNCTION(cairo_set_source_rgb);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_set_source_rgb_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 4)
  ZEND_ARG_INFO(0, cr)
  ZEND_ARG_INFO(0, red)
  ZEND_ARG_INFO(0, green)
  ZEND_ARG_INFO(0, blue)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_set_source_rgb_arg_info NULL
#endif

PHP_FUNCTION(cairo_set_source_rgba);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_set_source_rgba_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 5)
  ZEND_ARG_INFO(0, cr)
  ZEND_ARG_INFO(0, red)
  ZEND_ARG_INFO(0, green)
  ZEND_ARG_INFO(0, blue)
  ZEND_ARG_INFO(0, alpha)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_set_source_rgba_arg_info NULL
#endif

PHP_FUNCTION(cairo_move_to);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_move_to_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 3)
  ZEND_ARG_INFO(0, cr)
  ZEND_ARG_INFO(0, x)
  ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_move_to_arg_info NULL
#endif

PHP_FUNCTION(cairo_rel_move_to);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_rel_move_to_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 3)
  ZEND_ARG_INFO(0, cr)
  ZEND_ARG_INFO(0, dx)
  ZEND_ARG_INFO(0, dy)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_rel_move_to_arg_info NULL
#endif

PHP_FUNCTION(cairo_show_text);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_show_text_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, cr)
  ZEND_ARG_INFO(0, text)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_show_text_arg_info NULL
#endif

#if CAIRO_HAS_PNG_FUNCTIONS
PHP_FUNCTION(cairo_surface_show_png);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_surface_show_png_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, surface)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_surface_show_png_arg_info NULL
#endif

#endif /* CAIRO_HAS_PNG_FUNCTIONS */
#if CAIRO_HAS_PNG_FUNCTIONS
PHP_FUNCTION(cairo_surface_write_to_png);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_surface_write_to_png_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, surface)
  ZEND_ARG_INFO(0, path)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_surface_write_to_png_arg_info NULL
#endif

#endif /* CAIRO_HAS_PNG_FUNCTIONS */
#if CAIRO_HAS_PNG_FUNCTIONS
PHP_FUNCTION(cairo_image_surface_create_from_png);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_image_surface_create_from_png_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, path)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_image_surface_create_from_png_arg_info NULL
#endif

#endif /* CAIRO_HAS_PNG_FUNCTIONS */
#if CAIRO_HAS_PDF_SURFACE
PHP_FUNCTION(cairo_pdf_surface_create);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_pdf_surface_create_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 3)
  ZEND_ARG_INFO(0, path)
  ZEND_ARG_INFO(0, width_in_points)
  ZEND_ARG_INFO(0, height_in_points)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_pdf_surface_create_arg_info NULL
#endif

#endif /* CAIRO_HAS_PDF_SURFACE */
#if CAIRO_HAS_PDF_SURFACE
PHP_FUNCTION(cairo_pdf_surface_set_size);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_pdf_surface_set_size_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 3)
  ZEND_ARG_INFO(0, surface)
  ZEND_ARG_INFO(0, width_in_points)
  ZEND_ARG_INFO(0, height_in_points)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_pdf_surface_set_size_arg_info NULL
#endif

#endif /* CAIRO_HAS_PDF_SURFACE */
#if CAIRO_HAS_PS_SURFACE
PHP_FUNCTION(cairo_ps_surface_create);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_ps_surface_create_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 3)
  ZEND_ARG_INFO(0, path)
  ZEND_ARG_INFO(0, width_in_points)
  ZEND_ARG_INFO(0, height_in_points)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_ps_surface_create_arg_info NULL
#endif

#endif /* CAIRO_HAS_PS_SURFACE */
#if CAIRO_HAS_PS_SURFACE
PHP_FUNCTION(cairo_ps_surface_set_size);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_ps_surface_set_size_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 3)
  ZEND_ARG_INFO(0, surface)
  ZEND_ARG_INFO(0, width_in_points)
  ZEND_ARG_INFO(0, height_in_points)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_ps_surface_set_size_arg_info NULL
#endif

#endif /* CAIRO_HAS_PS_SURFACE */
#if CAIRO_HAS_PS_SURFACE
PHP_FUNCTION(cairo_ps_surface_dsc_begin_setup);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_ps_surface_dsc_begin_setup_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, surface)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_ps_surface_dsc_begin_setup_arg_info NULL
#endif

#endif /* CAIRO_HAS_PS_SURFACE */
#if CAIRO_HAS_PS_SURFACE
PHP_FUNCTION(cairo_ps_surface_dsc_begin_page_setup);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_ps_surface_dsc_begin_page_setup_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, surface)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_ps_surface_dsc_begin_page_setup_arg_info NULL
#endif

#endif /* CAIRO_HAS_PS_SURFACE */
#if CAIRO_HAS_PS_SURFACE
PHP_FUNCTION(cairo_ps_surface_dsc_comment);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_ps_surface_dsc_comment_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, surface)
  ZEND_ARG_INFO(0, comment)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_ps_surface_dsc_comment_arg_info NULL
#endif

#endif /* CAIRO_HAS_PS_SURFACE */
PHP_FUNCTION(cairo_stroke);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_stroke_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, cr)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_stroke_arg_info NULL
#endif

PHP_FUNCTION(cairo_stroke_preserve);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_stroke_preserve_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, cr)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_stroke_preserve_arg_info NULL
#endif

PHP_FUNCTION(cairo_arc);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_arc_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 6)
  ZEND_ARG_INFO(0, cr)
  ZEND_ARG_INFO(0, xc)
  ZEND_ARG_INFO(0, yc)
  ZEND_ARG_INFO(0, radius)
  ZEND_ARG_INFO(0, angle1)
  ZEND_ARG_INFO(0, angle2)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_arc_arg_info NULL
#endif

PHP_FUNCTION(cairo_arc_negative);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_arc_negative_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 6)
  ZEND_ARG_INFO(0, cr)
  ZEND_ARG_INFO(0, xc)
  ZEND_ARG_INFO(0, yc)
  ZEND_ARG_INFO(0, radius)
  ZEND_ARG_INFO(0, angle1)
  ZEND_ARG_INFO(0, angle2)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_arc_negative_arg_info NULL
#endif

PHP_FUNCTION(cairo_fill);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_fill_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, cr)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_fill_arg_info NULL
#endif

PHP_FUNCTION(cairo_fill_preserve);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_fill_preserve_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, cr)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_fill_preserve_arg_info NULL
#endif

PHP_FUNCTION(cairo_set_line_width);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_set_line_width_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, cr)
  ZEND_ARG_INFO(0, width)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_set_line_width_arg_info NULL
#endif

PHP_FUNCTION(cairo_get_line_width);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_get_line_width_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, cr)
  ZEND_ARG_INFO(0, width)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_get_line_width_arg_info NULL
#endif

PHP_FUNCTION(cairo_line_to);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_line_to_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 3)
  ZEND_ARG_INFO(0, cr)
  ZEND_ARG_INFO(0, xc)
  ZEND_ARG_INFO(0, yc)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_line_to_arg_info NULL
#endif

PHP_FUNCTION(cairo_rel_line_to);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_rel_line_to_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 3)
  ZEND_ARG_INFO(0, cr)
  ZEND_ARG_INFO(0, dx)
  ZEND_ARG_INFO(0, dy)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_rel_line_to_arg_info NULL
#endif

PHP_FUNCTION(cairo_pattern_add_color_stop_rgb);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_pattern_add_color_stop_rgb_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 5)
  ZEND_ARG_INFO(0, pattern)
  ZEND_ARG_INFO(0, offset)
  ZEND_ARG_INFO(0, red)
  ZEND_ARG_INFO(0, green)
  ZEND_ARG_INFO(0, blue)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_pattern_add_color_stop_rgb_arg_info NULL
#endif

PHP_FUNCTION(cairo_pattern_add_color_stop_rgba);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_pattern_add_color_stop_rgba_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 6)
  ZEND_ARG_INFO(0, pattern)
  ZEND_ARG_INFO(0, offset)
  ZEND_ARG_INFO(0, red)
  ZEND_ARG_INFO(0, green)
  ZEND_ARG_INFO(0, blue)
  ZEND_ARG_INFO(0, alpha)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_pattern_add_color_stop_rgba_arg_info NULL
#endif

PHP_FUNCTION(cairo_rectangle);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_rectangle_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 5)
  ZEND_ARG_INFO(0, cr)
  ZEND_ARG_INFO(0, x)
  ZEND_ARG_INFO(0, y)
  ZEND_ARG_INFO(0, width)
  ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_rectangle_arg_info NULL
#endif

PHP_FUNCTION(cairo_set_source);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_set_source_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, cr)
  ZEND_ARG_INFO(0, pattern)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_set_source_arg_info NULL
#endif

PHP_FUNCTION(cairo_scale);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_scale_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 3)
  ZEND_ARG_INFO(0, cr)
  ZEND_ARG_INFO(0, width)
  ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_scale_arg_info NULL
#endif

PHP_FUNCTION(cairo_version);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_version_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, )
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_version_arg_info NULL
#endif

PHP_FUNCTION(cairo_version_string);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_version_string_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, )
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_version_string_arg_info NULL
#endif

PHP_FUNCTION(cairo_save);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_save_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, cr)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_save_arg_info NULL
#endif

PHP_FUNCTION(cairo_restore);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_restore_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, cr)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_restore_arg_info NULL
#endif

PHP_FUNCTION(cairo_status);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_status_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, cr)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_status_arg_info NULL
#endif

PHP_FUNCTION(cairo_pattern_status);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_pattern_status_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, pattern)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_pattern_status_arg_info NULL
#endif

PHP_FUNCTION(cairo_status_to_string);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_status_to_string_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, status)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_status_to_string_arg_info NULL
#endif

PHP_FUNCTION(cairo_push_group);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_push_group_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, cr)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_push_group_arg_info NULL
#endif

PHP_FUNCTION(cairo_pop_group);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_pop_group_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, cr)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_pop_group_arg_info NULL
#endif

PHP_FUNCTION(cairo_pop_group_to_source);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_pop_group_to_source_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, cr)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_pop_group_to_source_arg_info NULL
#endif

PHP_FUNCTION(cairo_rotate);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_rotate_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, cr)
  ZEND_ARG_INFO(0, angle)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_rotate_arg_info NULL
#endif

PHP_FUNCTION(cairo_translate);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_translate_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 3)
  ZEND_ARG_INFO(0, cr)
  ZEND_ARG_INFO(0, tx)
  ZEND_ARG_INFO(0, ty)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_translate_arg_info NULL
#endif

PHP_FUNCTION(cairo_curve_to);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_curve_to_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 7)
  ZEND_ARG_INFO(0, cr)
  ZEND_ARG_INFO(0, x1)
  ZEND_ARG_INFO(0, y1)
  ZEND_ARG_INFO(0, x2)
  ZEND_ARG_INFO(0, y2)
  ZEND_ARG_INFO(0, x3)
  ZEND_ARG_INFO(0, y3)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_curve_to_arg_info NULL
#endif

PHP_FUNCTION(cairo_rel_curve_to);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_rel_curve_to_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 7)
  ZEND_ARG_INFO(0, cr)
  ZEND_ARG_INFO(0, dx1)
  ZEND_ARG_INFO(0, dy1)
  ZEND_ARG_INFO(0, dx2)
  ZEND_ARG_INFO(0, dy2)
  ZEND_ARG_INFO(0, dx3)
  ZEND_ARG_INFO(0, dy3)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_rel_curve_to_arg_info NULL
#endif

PHP_FUNCTION(cairo_close_path);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_close_path_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, cr)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_close_path_arg_info NULL
#endif

PHP_FUNCTION(cairo_set_antialias);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_set_antialias_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, cr)
  ZEND_ARG_INFO(0, antialias)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_set_antialias_arg_info NULL
#endif

PHP_FUNCTION(cairo_get_antialias);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_get_antialias_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, cr)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_get_antialias_arg_info NULL
#endif

PHP_FUNCTION(cairo_set_fill_rule);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_set_fill_rule_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, cr)
  ZEND_ARG_INFO(0, fill_rule)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_set_fill_rule_arg_info NULL
#endif

PHP_FUNCTION(cairo_get_fill_rule);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_get_fill_rule_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, cr)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_get_fill_rule_arg_info NULL
#endif

PHP_FUNCTION(cairo_set_line_cap);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_set_line_cap_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, cr)
  ZEND_ARG_INFO(0, line_cap)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_set_line_cap_arg_info NULL
#endif

PHP_FUNCTION(cairo_get_line_cap);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_get_line_cap_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, cr)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_get_line_cap_arg_info NULL
#endif

PHP_FUNCTION(cairo_set_line_join);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_set_line_join_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, cr)
  ZEND_ARG_INFO(0, line_join)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_set_line_join_arg_info NULL
#endif

PHP_FUNCTION(cairo_get_line_join);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_get_line_join_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, cr)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_get_line_join_arg_info NULL
#endif

PHP_FUNCTION(cairo_set_tolerance);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_set_tolerance_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, cr)
  ZEND_ARG_INFO(0, tolerance)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_set_tolerance_arg_info NULL
#endif

PHP_FUNCTION(cairo_get_tolerance);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_get_tolerance_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, cr)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_get_tolerance_arg_info NULL
#endif

PHP_FUNCTION(cairo_set_miter_limit);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_set_miter_limit_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, cr)
  ZEND_ARG_INFO(0, miter_limit)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_set_miter_limit_arg_info NULL
#endif

PHP_FUNCTION(cairo_get_miter_limit);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_get_miter_limit_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, cr)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_get_miter_limit_arg_info NULL
#endif

PHP_FUNCTION(cairo_set_operator);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_set_operator_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, cr)
  ZEND_ARG_INFO(0, operator)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_set_operator_arg_info NULL
#endif

PHP_FUNCTION(cairo_get_operator);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_get_operator_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, cr)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_get_operator_arg_info NULL
#endif

PHP_FUNCTION(cairo_paint);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_paint_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, cr)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_paint_arg_info NULL
#endif

PHP_FUNCTION(cairo_paint_with_alpha);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_paint_with_alpha_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, cr)
  ZEND_ARG_INFO(0, alpha)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_paint_with_alpha_arg_info NULL
#endif

PHP_FUNCTION(cairo_surface_flush);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_surface_flush_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, surface)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_surface_flush_arg_info NULL
#endif

PHP_FUNCTION(cairo_clip);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_clip_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, cr)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_clip_arg_info NULL
#endif

PHP_FUNCTION(cairo_clip_preserve);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_clip_preserve_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, cr)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_clip_preserve_arg_info NULL
#endif

PHP_FUNCTION(cairo_reset_clip);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_reset_clip_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, cr)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_reset_clip_arg_info NULL
#endif

PHP_FUNCTION(cairo_image_surface_get_height);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_image_surface_get_height_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, surface)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_image_surface_get_height_arg_info NULL
#endif

PHP_FUNCTION(cairo_image_surface_get_width);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_image_surface_get_width_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, surface)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_image_surface_get_width_arg_info NULL
#endif

PHP_FUNCTION(cairo_surface_status);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_surface_status_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, surface)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_surface_status_arg_info NULL
#endif

PHP_FUNCTION(cairo_in_fill);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_in_fill_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 3)
  ZEND_ARG_INFO(0, cr)
  ZEND_ARG_INFO(0, x)
  ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_in_fill_arg_info NULL
#endif

PHP_FUNCTION(cairo_in_stroke);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_in_stroke_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 3)
  ZEND_ARG_INFO(0, cr)
  ZEND_ARG_INFO(0, x)
  ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_in_stroke_arg_info NULL
#endif

PHP_FUNCTION(cairo_new_path);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_new_path_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, cr)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_new_path_arg_info NULL
#endif

PHP_FUNCTION(cairo_new_sub_path);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_new_sub_path_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, cr)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_new_sub_path_arg_info NULL
#endif

PHP_FUNCTION(cairo_image_surface_get_type);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_image_surface_get_type_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, surface)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_image_surface_get_type_arg_info NULL
#endif

PHP_FUNCTION(cairo_image_surface_get_format);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_image_surface_get_format_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, surface)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_image_surface_get_format_arg_info NULL
#endif

PHP_FUNCTION(cairo_pattern_set_extend);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_pattern_set_extend_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, pattern)
  ZEND_ARG_INFO(0, extend)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_pattern_set_extend_arg_info NULL
#endif

PHP_FUNCTION(cairo_copy_page);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_copy_page_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, cr)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_copy_page_arg_info NULL
#endif

PHP_FUNCTION(cairo_show_page);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_show_page_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, cr)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_show_page_arg_info NULL
#endif

PHP_FUNCTION(cairo_copy_path);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_copy_path_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, cr)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_copy_path_arg_info NULL
#endif

PHP_FUNCTION(cairo_copy_path_flat);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_copy_path_flat_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, cr)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_copy_path_flat_arg_info NULL
#endif

PHP_FUNCTION(cairo_append_path);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_append_path_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, cr)
  ZEND_ARG_INFO(0, path)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_append_path_arg_info NULL
#endif

PHP_FUNCTION(cairo_get_source);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_get_source_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, cr)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_get_source_arg_info NULL
#endif

PHP_FUNCTION(cairo_mask);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_mask_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, cr)
  ZEND_ARG_INFO(0, pattern)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_mask_arg_info NULL
#endif

PHP_FUNCTION(cairo_mask_surface);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_mask_surface_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 4)
  ZEND_ARG_INFO(0, cr)
  ZEND_ARG_INFO(0, surface)
  ZEND_ARG_INFO(0, surface_x)
  ZEND_ARG_INFO(0, surface_y)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_mask_surface_arg_info NULL
#endif

PHP_FUNCTION(cairo_pattern_get_extend);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_pattern_get_extend_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, pattern)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_pattern_get_extend_arg_info NULL
#endif

PHP_FUNCTION(cairo_pattern_get_filter);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_pattern_get_filter_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, pattern)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_pattern_get_filter_arg_info NULL
#endif

PHP_FUNCTION(cairo_pattern_get_pattern_type);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_pattern_get_pattern_type_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, pattern)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_pattern_get_pattern_type_arg_info NULL
#endif

PHP_FUNCTION(cairo_surface_mark_dirty);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_surface_mark_dirty_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, surface)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_surface_mark_dirty_arg_info NULL
#endif

PHP_FUNCTION(cairo_surface_mark_dirty_rectangle);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_surface_mark_dirty_rectangle_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 5)
  ZEND_ARG_INFO(0, surface)
  ZEND_ARG_INFO(0, x)
  ZEND_ARG_INFO(0, y)
  ZEND_ARG_INFO(0, width)
  ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_surface_mark_dirty_rectangle_arg_info NULL
#endif

PHP_FUNCTION(cairo_surface_set_fallback_resolution);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_surface_set_fallback_resolution_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 3)
  ZEND_ARG_INFO(0, surface)
  ZEND_ARG_INFO(0, x_pixels_per_inch)
  ZEND_ARG_INFO(0, y_pixels_per_inch)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_surface_set_fallback_resolution_arg_info NULL
#endif

PHP_FUNCTION(cairo_surface_set_device_offset);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_surface_set_device_offset_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 3)
  ZEND_ARG_INFO(0, surface)
  ZEND_ARG_INFO(0, x_offset)
  ZEND_ARG_INFO(0, y_offset)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_surface_set_device_offset_arg_info NULL
#endif

PHP_FUNCTION(cairo_set_source_surface);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_set_source_surface_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 4)
  ZEND_ARG_INFO(0, cr)
  ZEND_ARG_INFO(0, surface)
  ZEND_ARG_INFO(0, x)
  ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_set_source_surface_arg_info NULL
#endif

#if CAIRO_HAS_SVG_SURFACE
PHP_FUNCTION(cairo_svg_surface_create);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_svg_surface_create_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 3)
  ZEND_ARG_INFO(0, path)
  ZEND_ARG_INFO(0, width_in_points)
  ZEND_ARG_INFO(0, height_in_points)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_svg_surface_create_arg_info NULL
#endif

#endif /* CAIRO_HAS_SVG_SURFACE */
#if CAIRO_HAS_SVG_SURFACE
PHP_FUNCTION(cairo_svg_surface_restrict_to_version);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_svg_surface_restrict_to_version_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, surface)
  ZEND_ARG_INFO(0, version)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_svg_surface_restrict_to_version_arg_info NULL
#endif

#endif /* CAIRO_HAS_SVG_SURFACE */
#if CAIRO_HAS_SVG_SURFACE
PHP_FUNCTION(cairo_svg_version_to_string);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_svg_version_to_string_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, version)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_svg_version_to_string_arg_info NULL
#endif

#endif /* CAIRO_HAS_SVG_SURFACE */
PHP_FUNCTION(cairo_text_path);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_text_path_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, cr)
  ZEND_ARG_INFO(0, text)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_text_path_arg_info NULL
#endif

PHP_FUNCTION(cairo_get_font_face);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_get_font_face_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, cr)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_get_font_face_arg_info NULL
#endif

PHP_FUNCTION(cairo_font_face_destroy);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_font_face_destroy_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, font_face)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_font_face_destroy_arg_info NULL
#endif

PHP_FUNCTION(cairo_font_face_get_type);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_font_face_get_type_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, font_face)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_font_face_get_type_arg_info NULL
#endif

PHP_FUNCTION(cairo_font_face_status);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_font_face_status_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, font_face)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_font_face_status_arg_info NULL
#endif

PHP_FUNCTION(cairo_set_font_face);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_set_font_face_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, cr)
  ZEND_ARG_INFO(0, font_face)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_set_font_face_arg_info NULL
#endif

PHP_FUNCTION(cairo_font_options_create);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_font_options_create_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, )
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_font_options_create_arg_info NULL
#endif

PHP_FUNCTION(cairo_font_options_copy);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_font_options_copy_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, font_options)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_font_options_copy_arg_info NULL
#endif

PHP_FUNCTION(cairo_font_options_destroy);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_font_options_destroy_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, font_options)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_font_options_destroy_arg_info NULL
#endif

PHP_FUNCTION(cairo_set_font_options);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_set_font_options_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, cr)
  ZEND_ARG_INFO(0, font_options)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_set_font_options_arg_info NULL
#endif

PHP_FUNCTION(cairo_font_options_set_antialias);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_font_options_set_antialias_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, font_options)
  ZEND_ARG_INFO(0, antialias)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_font_options_set_antialias_arg_info NULL
#endif

PHP_FUNCTION(cairo_font_options_set_hint_metrics);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_font_options_set_hint_metrics_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, font_options)
  ZEND_ARG_INFO(0, hint_metrics)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_font_options_set_hint_metrics_arg_info NULL
#endif

PHP_FUNCTION(cairo_font_options_set_hint_style);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_font_options_set_hint_style_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, font_options)
  ZEND_ARG_INFO(0, hint_style)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_font_options_set_hint_style_arg_info NULL
#endif

PHP_FUNCTION(cairo_font_options_set_subpixel_order);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_font_options_set_subpixel_order_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, font_options)
  ZEND_ARG_INFO(0, subpixel_order)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_font_options_set_subpixel_order_arg_info NULL
#endif

PHP_FUNCTION(cairo_font_options_get_antialias);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_font_options_get_antialias_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, font_options)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_font_options_get_antialias_arg_info NULL
#endif

PHP_FUNCTION(cairo_font_options_get_hint_metrics);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_font_options_get_hint_metrics_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, font_options)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_font_options_get_hint_metrics_arg_info NULL
#endif

PHP_FUNCTION(cairo_font_options_get_hint_style);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_font_options_get_hint_style_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, font_options)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_font_options_get_hint_style_arg_info NULL
#endif

PHP_FUNCTION(cairo_font_options_get_subpixel_order);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_font_options_get_subpixel_order_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, font_options)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_font_options_get_subpixel_order_arg_info NULL
#endif

PHP_FUNCTION(cairo_font_options_equal);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_font_options_equal_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, options)
  ZEND_ARG_INFO(0, other)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_font_options_equal_arg_info NULL
#endif

PHP_FUNCTION(cairo_font_options_merge);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_font_options_merge_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, options)
  ZEND_ARG_INFO(0, other)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_font_options_merge_arg_info NULL
#endif

PHP_FUNCTION(cairo_font_options_status);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_font_options_status_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, options)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_font_options_status_arg_info NULL
#endif

PHP_FUNCTION(cairo_get_font_options);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_get_font_options_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, cr)
  ZEND_ARG_INFO(0, options)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_get_font_options_arg_info NULL
#endif

PHP_FUNCTION(cairo_surface_get_font_options);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_surface_get_font_options_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, surface)
  ZEND_ARG_INFO(0, options)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_surface_get_font_options_arg_info NULL
#endif

PHP_FUNCTION(cairo_path_to_array);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_path_to_array_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, path)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_path_to_array_arg_info NULL
#endif

PHP_FUNCTION(cairo_marix_destroy);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_marix_destroy_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, cr)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_marix_destroy_arg_info NULL
#endif

PHP_FUNCTION(cairo_get_matrix);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_get_matrix_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, cr)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_get_matrix_arg_info NULL
#endif

PHP_FUNCTION(cairo_set_matrix);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_set_matrix_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, cr)
  ZEND_ARG_INFO(0, matrix)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_set_matrix_arg_info NULL
#endif

PHP_FUNCTION(cairo_identity_matrix);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_identity_matrix_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, cr)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_identity_matrix_arg_info NULL
#endif

PHP_FUNCTION(cairo_matrix_invert);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_matrix_invert_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, matrix)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_matrix_invert_arg_info NULL
#endif

PHP_FUNCTION(cairo_matrix_create);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_matrix_create_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 6)
  ZEND_ARG_INFO(0, xx)
  ZEND_ARG_INFO(0, yx)
  ZEND_ARG_INFO(0, xy)
  ZEND_ARG_INFO(0, yy)
  ZEND_ARG_INFO(0, x0)
  ZEND_ARG_INFO(0, y0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_matrix_create_arg_info NULL
#endif

PHP_FUNCTION(cairo_matrix_create_identity);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_matrix_create_identity_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, )
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_matrix_create_identity_arg_info NULL
#endif

PHP_FUNCTION(cairo_matrix_create_rotate);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_matrix_create_rotate_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, radians)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_matrix_create_rotate_arg_info NULL
#endif

PHP_FUNCTION(cairo_matrix_create_translate);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_matrix_create_translate_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, dx)
  ZEND_ARG_INFO(0, dy)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_matrix_create_translate_arg_info NULL
#endif

PHP_FUNCTION(cairo_matrix_create_scale);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_matrix_create_scale_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, sx)
  ZEND_ARG_INFO(0, sy)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_matrix_create_scale_arg_info NULL
#endif

PHP_FUNCTION(cairo_matrix_multiply);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_matrix_multiply_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, m1)
  ZEND_ARG_INFO(0, m2)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_matrix_multiply_arg_info NULL
#endif

PHP_FUNCTION(cairo_matrix_rotate);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_matrix_rotate_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, matrix)
  ZEND_ARG_INFO(0, radians)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_matrix_rotate_arg_info NULL
#endif

PHP_FUNCTION(cairo_matrix_translate);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_matrix_translate_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 3)
  ZEND_ARG_INFO(0, matrix)
  ZEND_ARG_INFO(0, dx)
  ZEND_ARG_INFO(0, dy)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_matrix_translate_arg_info NULL
#endif

PHP_FUNCTION(cairo_matrix_scale);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_matrix_scale_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 3)
  ZEND_ARG_INFO(0, matrix)
  ZEND_ARG_INFO(0, sx)
  ZEND_ARG_INFO(0, sy)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_matrix_scale_arg_info NULL
#endif

PHP_FUNCTION(cairo_transform);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_transform_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, cr)
  ZEND_ARG_INFO(0, matrix)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_transform_arg_info NULL
#endif

PHP_FUNCTION(cairo_pattern_get_matrix);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_pattern_get_matrix_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, pattern)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_pattern_get_matrix_arg_info NULL
#endif

PHP_FUNCTION(cairo_pattern_set_matrix);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_pattern_set_matrix_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, pattern)
  ZEND_ARG_INFO(0, matrix)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_pattern_set_matrix_arg_info NULL
#endif

PHP_FUNCTION(cairo_get_font_matrix);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_get_font_matrix_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, cr)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_get_font_matrix_arg_info NULL
#endif

PHP_FUNCTION(cairo_set_font_matrix);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_set_font_matrix_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, cr)
  ZEND_ARG_INFO(0, matrix)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_set_font_matrix_arg_info NULL
#endif

PHP_FUNCTION(cairo_scaled_font_destroy);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_scaled_font_destroy_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, scaled_font)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_scaled_font_destroy_arg_info NULL
#endif

PHP_FUNCTION(cairo_scaled_font_create);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_scaled_font_create_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 4)
  ZEND_ARG_INFO(0, font_face)
  ZEND_ARG_INFO(0, font_matrix)
  ZEND_ARG_INFO(0, ctm)
  ZEND_ARG_INFO(0, options)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_scaled_font_create_arg_info NULL
#endif

PHP_FUNCTION(cairo_scaled_font_get_type);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_scaled_font_get_type_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, scaled_font)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_scaled_font_get_type_arg_info NULL
#endif

PHP_FUNCTION(cairo_scaled_font_status);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_scaled_font_status_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, scaled_font)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_scaled_font_status_arg_info NULL
#endif

PHP_FUNCTION(cairo_scaled_font_get_font_matrix);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_scaled_font_get_font_matrix_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, scaled_font)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_scaled_font_get_font_matrix_arg_info NULL
#endif

PHP_FUNCTION(cairo_scaled_font_get_ctm);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_scaled_font_get_ctm_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, scaled_font)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_scaled_font_get_ctm_arg_info NULL
#endif

PHP_FUNCTION(cairo_scaled_font_get_font_options);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_scaled_font_get_font_options_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, scaled_font)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_scaled_font_get_font_options_arg_info NULL
#endif

PHP_FUNCTION(cairo_scaled_font_get_font_face);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_scaled_font_get_font_face_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, scaled_font)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_scaled_font_get_font_face_arg_info NULL
#endif

PHP_FUNCTION(cairo_set_scaled_font);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_set_scaled_font_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, cr)
  ZEND_ARG_INFO(0, scaled_font)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_set_scaled_font_arg_info NULL
#endif

PHP_FUNCTION(cairo_surface_get_scaled_font_options);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_surface_get_scaled_font_options_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, surface)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_surface_get_scaled_font_options_arg_info NULL
#endif

PHP_FUNCTION(cairo_svg_get_versions);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_svg_get_versions_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, )
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_svg_get_versions_arg_info NULL
#endif

PHP_FUNCTION(cairo_get_current_point);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_get_current_point_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, cr)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_get_current_point_arg_info NULL
#endif

PHP_FUNCTION(cairo_matrix_transform_point);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_matrix_transform_point_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 3)
  ZEND_ARG_INFO(0, matrix)
  ZEND_ARG_INFO(0, x)
  ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_matrix_transform_point_arg_info NULL
#endif

PHP_FUNCTION(cairo_matrix_transform_distance);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_matrix_transform_distance_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 3)
  ZEND_ARG_INFO(0, matrix)
  ZEND_ARG_INFO(0, dx)
  ZEND_ARG_INFO(0, dy)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_matrix_transform_distance_arg_info NULL
#endif

PHP_FUNCTION(cairo_device_to_user);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_device_to_user_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 3)
  ZEND_ARG_INFO(0, cr)
  ZEND_ARG_INFO(0, x)
  ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_device_to_user_arg_info NULL
#endif

PHP_FUNCTION(cairo_device_to_user_distance);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_device_to_user_distance_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 3)
  ZEND_ARG_INFO(0, cr)
  ZEND_ARG_INFO(0, dx)
  ZEND_ARG_INFO(0, dy)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_device_to_user_distance_arg_info NULL
#endif

PHP_FUNCTION(cairo_user_to_device);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_user_to_device_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 3)
  ZEND_ARG_INFO(0, cr)
  ZEND_ARG_INFO(0, x)
  ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_user_to_device_arg_info NULL
#endif

PHP_FUNCTION(cairo_user_to_device_distance);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_user_to_device_distance_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 3)
  ZEND_ARG_INFO(0, cr)
  ZEND_ARG_INFO(0, dx)
  ZEND_ARG_INFO(0, dy)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_user_to_device_distance_arg_info NULL
#endif

PHP_FUNCTION(cairo_surface_get_device_offset);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_surface_get_device_offset_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, surface)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_surface_get_device_offset_arg_info NULL
#endif

PHP_FUNCTION(cairo_fill_extents);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_fill_extents_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, cr)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_fill_extents_arg_info NULL
#endif

PHP_FUNCTION(cairo_stroke_extents);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_stroke_extents_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, cr)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_stroke_extents_arg_info NULL
#endif

PHP_FUNCTION(cairo_text_extends);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_text_extends_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, cr)
  ZEND_ARG_INFO(0, text)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_text_extends_arg_info NULL
#endif

PHP_FUNCTION(cairo_surface_get_content);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_surface_get_content_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, surface)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_surface_get_content_arg_info NULL
#endif

PHP_FUNCTION(cairo_pattern_set_filter);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_pattern_set_filter_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, pattern)
  ZEND_ARG_INFO(0, filter)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_pattern_set_filter_arg_info NULL
#endif

PHP_FUNCTION(cairo_push_group_with_content);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_push_group_with_content_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, cr)
  ZEND_ARG_INFO(0, content)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_push_group_with_content_arg_info NULL
#endif

PHP_FUNCTION(cairo_surface_create_similar);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_surface_create_similar_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 4)
  ZEND_ARG_INFO(0, surface)
  ZEND_ARG_INFO(0, content)
  ZEND_ARG_INFO(0, width)
  ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_surface_create_similar_arg_info NULL
#endif

PHP_FUNCTION(cairo_set_dash);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_set_dash_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 3)
  ZEND_ARG_INFO(0, cr)
#if (PHP_MINOR_VERSION > 0)
  ZEND_ARG_ARRAY_INFO(0, dashes, 1)
#else
  ZEND_ARG_INFO(0, dashes)
#endif
  ZEND_ARG_INFO(0, offset)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_set_dash_arg_info NULL
#endif

PHP_FUNCTION(cairo_font_extents);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_font_extents_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, cr)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_font_extents_arg_info NULL
#endif

PHP_FUNCTION(cairo_scaled_font_extents);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_scaled_font_extents_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, font)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_scaled_font_extents_arg_info NULL
#endif

PHP_FUNCTION(cairo_scaled_font_text_extends);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_scaled_font_text_extends_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, font)
  ZEND_ARG_INFO(0, text)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_scaled_font_text_extends_arg_info NULL
#endif

#ifdef  __cplusplus
} // extern "C" 
#endif

/* 'bottom' header snippets*/
#if CAIRO_HAS_PDF_SURFACE
#include <cairo-pdf.h>
#endif
#if CAIRO_HAS_PS_SURFACE
#include <cairo-ps.h>
#endif
#if CAIRO_HAS_SVG_SURFACE
#include <cairo-svg.h>
#endif

#endif /* PHP_HAVE_CAIRO */

#endif /* PHP_CAIRO_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
