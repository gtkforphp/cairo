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
  |         Michael Maclean <mgdm@php.net>
  |         Akshat Gupta <g.akshat@gmail.com>                            |                              |
  +----------------------------------------------------------------------+
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#if defined(CAIRO_HAS_FT_FONT) && defined(HAVE_FREETYPE)
#include <ft2build.h>
#include FT_FREETYPE_H
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_cairo.h"

zend_class_entry *cairo_ce_cairo;
zend_object_handlers cairo_std_object_handlers;

#if defined(CAIRO_HAS_FT_FONT) && defined(HAVE_FREETYPE)

const php_cairo_ft_error php_cairo_ft_errors[] =
#include FT_ERRORS_H

#endif

/* Cairo Functions */
ZEND_BEGIN_ARG_INFO(cairo_status_to_string_args, ZEND_SEND_BY_VAL)
  ZEND_ARG_INFO(0, status)
ZEND_END_ARG_INFO()

/* Cairo Context Functions */
ZEND_BEGIN_ARG_INFO(cairo_create_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, surface, CairoSurface, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_context_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, context, CairoContext, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_push_group_with_content_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, context, CairoContext, 0)
	ZEND_ARG_INFO(0, content)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_set_source_rgb_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, context, CairoContext, 0)
	ZEND_ARG_INFO(0, red)
	ZEND_ARG_INFO(0, green)
	ZEND_ARG_INFO(0, blue)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_set_source_rgba_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, context, CairoContext, 0)
	ZEND_ARG_INFO(0, red)
	ZEND_ARG_INFO(0, green)
	ZEND_ARG_INFO(0, blue)
	ZEND_ARG_INFO(0, alpha)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_set_source_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, context, CairoContext, 0)
	ZEND_ARG_OBJ_INFO(0, pattern, CairoPattern, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(cairo_set_source_surface_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
	ZEND_ARG_OBJ_INFO(0, context, CairoContext, 0)
	ZEND_ARG_OBJ_INFO(0, surface, CairoSurface, 0)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(cairo_set_antialias_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_OBJ_INFO(0, context, CairoContext, 0)
	ZEND_ARG_INFO(0, antialias)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(cairo_set_dash_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
	ZEND_ARG_OBJ_INFO(0, context, CairoContext, 0)
	ZEND_ARG_ARRAY_INFO(0, dashes, 0)
	ZEND_ARG_INFO(0, offset)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_set_fill_rule_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, context, CairoContext, 0)
	ZEND_ARG_INFO(0, setting)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(cairo_set_line_width_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
	ZEND_ARG_OBJ_INFO(0, context, CairoContext, 0)
	ZEND_ARG_INFO(0, width)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(cairo_set_miter_limit_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
	ZEND_ARG_OBJ_INFO(0, context, CairoContext, 0)
	ZEND_ARG_INFO(0, limit)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(cairo_set_tolerance_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
	ZEND_ARG_OBJ_INFO(0, context, CairoContext, 0)
	ZEND_ARG_INFO(0, tolerance)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(cairo_paint_with_alpha_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
	ZEND_ARG_OBJ_INFO(0, context, CairoContext, 0)
	ZEND_ARG_INFO(0, alpha)
ZEND_END_ARG_INFO()

/* Context Transformations */
ZEND_BEGIN_ARG_INFO(cairo_translate_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, context, CairoContext, 0)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_rotate_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, context, CairoContext, 0)
	ZEND_ARG_INFO(0, angle)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_transform_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, context, CairoContext, 0)
	ZEND_ARG_OBJ_INFO(0, matrix, CairoMatrix, 0)
ZEND_END_ARG_INFO()

/* Context and Path */
ZEND_BEGIN_ARG_INFO(cairo_append_path_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, context, CairoContext, 0)
	ZEND_ARG_OBJ_INFO(0, path, CairoPath, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_arc_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, context, CairoContext, 0)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
	ZEND_ARG_INFO(0, radius)
	ZEND_ARG_INFO(0, angle1)
	ZEND_ARG_INFO(0, angle2)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_in_clip_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, context, CairoContext, 0)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_curve_to_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, context, CairoContext, 0)
	ZEND_ARG_INFO(0, x1)
	ZEND_ARG_INFO(0, y1)
	ZEND_ARG_INFO(0, x2)
	ZEND_ARG_INFO(0, y2)
	ZEND_ARG_INFO(0, x3)
	ZEND_ARG_INFO(0, y3)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_line_to_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, context, CairoContext, 0)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_rectangle_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, context, CairoContext, 0)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
	ZEND_ARG_INFO(0, width)
	ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_glyph_path_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, context, CairoContext, 0)
	ZEND_ARG_ARRAY_INFO(0, glyphs, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_text_path_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, context, CairoContext, 0)
	ZEND_ARG_INFO(0, text)
ZEND_END_ARG_INFO()

/* Text functions */
ZEND_BEGIN_ARG_INFO_EX(cairo_select_font_face_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
	ZEND_ARG_OBJ_INFO(0, context, CairoContext, 0)
	ZEND_ARG_INFO(0, family)
	ZEND_ARG_INFO(0, slant)
	ZEND_ARG_INFO(0, weight)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_set_font_size_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, context, CairoContext, 0)
	ZEND_ARG_INFO(0, size)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_set_font_matrix_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, context, CairoContext, 0)
	ZEND_ARG_OBJ_INFO(0, matrix, CairoMatrix, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_set_font_options_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, context, CairoContext, 0)
	ZEND_ARG_OBJ_INFO(0, fontoptions, CairoFontOptions, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_set_font_face_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, context, CairoContext, 0)
	ZEND_ARG_OBJ_INFO(0, fontface, CairoFontFace, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_set_scaled_font_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, context, CairoContext, 0)
	ZEND_ARG_OBJ_INFO(0, scaledfont, CairoScaledFont, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_show_text_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, context, CairoContext, 0)
	ZEND_ARG_INFO(0, text)
ZEND_END_ARG_INFO()

/* Pattern Functions */
ZEND_BEGIN_ARG_INFO(cairo_pattern_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, pattern, CairoPattern, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(cairo_pattern_set_matrix_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_OBJ_INFO(0, pattern, CairoPattern, 0)
	ZEND_ARG_OBJ_INFO(0, matrix, CairoMatrix, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_pattern_create_rgb_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, red)
	ZEND_ARG_INFO(0, green)
	ZEND_ARG_INFO(0, blue)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_pattern_create_rgba_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, red)
	ZEND_ARG_INFO(0, green)
	ZEND_ARG_INFO(0, blue)
	ZEND_ARG_INFO(0, alpha)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_solidpattern_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, pattern, CairoSolidPattern, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_surfacepattern_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, pattern, CairoSurfacePattern, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(cairo_pattern_set_filter_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_OBJ_INFO(0, pattern, CairoSurfacePattern, 0)
	ZEND_ARG_INFO(0, filter)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_pattern_set_extend_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, pattern)
	ZEND_ARG_INFO(0, extend)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_pattern_get_extend_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, pattern)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_pattern_add_color_stop_rgb_args, ZEND_SEND_BY_VAL)
  ZEND_ARG_OBJ_INFO(0, pattern, CairoGradientPattern, 0)
  ZEND_ARG_INFO(0, offset)
  ZEND_ARG_INFO(0, red)
  ZEND_ARG_INFO(0, green)
  ZEND_ARG_INFO(0, blue)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_pattern_add_color_stop_rgba_args, ZEND_SEND_BY_VAL)
  ZEND_ARG_OBJ_INFO(0, pattern, CairoGradientPattern, 0)
  ZEND_ARG_INFO(0, offset)
  ZEND_ARG_INFO(0, red)
  ZEND_ARG_INFO(0, green)
  ZEND_ARG_INFO(0, blue)
  ZEND_ARG_INFO(0, alpha)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_pattern_get_color_stop_rgba_args, ZEND_SEND_BY_VAL)
  ZEND_ARG_OBJ_INFO(0, pattern, CairoGradientPattern, 0)
  ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_gradientpattern_args, ZEND_SEND_BY_VAL)
  ZEND_ARG_OBJ_INFO(0, pattern, CairoGradientPattern, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_pattern_create_linear_args, ZEND_SEND_BY_VAL)
  ZEND_ARG_INFO(0, x0)
  ZEND_ARG_INFO(0, y0)
  ZEND_ARG_INFO(0, x1)
  ZEND_ARG_INFO(0, y1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_lineargradient_args, ZEND_SEND_BY_VAL)
  ZEND_ARG_OBJ_INFO(0, pattern, CairoLinearGradient, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_pattern_create_radial_args, ZEND_SEND_BY_VAL)
  ZEND_ARG_INFO(0, x0)
  ZEND_ARG_INFO(0, y0)
  ZEND_ARG_INFO(0, r0)
  ZEND_ARG_INFO(0, x1)
  ZEND_ARG_INFO(0, y1)
  ZEND_ARG_INFO(0, r1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_radialgradient_args, ZEND_SEND_BY_VAL)
  ZEND_ARG_OBJ_INFO(0, pattern, CairoRadialGradient, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_mesh_pattern_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, pattern, CairoMeshPattern, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_mesh_pattern_get_path_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, pattern, CairoMeshPattern, 0)
	ZEND_ARG_INFO(0, patch)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_mesh_pattern_get_control_point_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, pattern, CairoMeshPattern, 0)
	ZEND_ARG_INFO(0, patch)
	ZEND_ARG_INFO(0, corner)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_mesh_pattern_get_corner_color_rgba_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, pattern, CairoMeshPattern, 0)
	ZEND_ARG_INFO(0, patch)
	ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_mesh_pattern_translate_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, pattern, CairoMeshPattern, 0)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_mesh_pattern_curve_to_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, pattern, CairoMeshPattern, 0)
	ZEND_ARG_INFO(0, x1)
	ZEND_ARG_INFO(0, y1)
	ZEND_ARG_INFO(0, x2)
	ZEND_ARG_INFO(0, y2)
	ZEND_ARG_INFO(0, x3)
	ZEND_ARG_INFO(0, y3)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_mesh_pattern_set_control_point_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, pattern, CairoMeshPattern, 0)
	ZEND_ARG_INFO(0, point)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_mesh_pattern_set_corner_color_rgb_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, pattern, CairoMeshPattern, 0)
	ZEND_ARG_INFO(0, point)
	ZEND_ARG_INFO(0, r)
	ZEND_ARG_INFO(0, g)
	ZEND_ARG_INFO(0, b)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_mesh_pattern_set_corner_color_rgba_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, pattern, CairoMeshPattern, 0)
	ZEND_ARG_INFO(0, point)
	ZEND_ARG_INFO(0, r)
	ZEND_ARG_INFO(0, g)
	ZEND_ARG_INFO(0, b)
	ZEND_ARG_INFO(0, a)
ZEND_END_ARG_INFO()


/* Matrix Functions */
ZEND_BEGIN_ARG_INFO_EX(cairo_matrix_init_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
  ZEND_ARG_INFO(0, yx)
  ZEND_ARG_INFO(0, xy)
  ZEND_ARG_INFO(0, yy)
  ZEND_ARG_INFO(0, x0)
  ZEND_ARG_INFO(0, y0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_matrix_init_translate_args, ZEND_SEND_BY_VAL)
  ZEND_ARG_INFO(0, tx)
  ZEND_ARG_INFO(0, ty)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_matrix_init_scale_args, ZEND_SEND_BY_VAL)
  ZEND_ARG_INFO(0, sx)
  ZEND_ARG_INFO(0, sy)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_matrix_init_rotate_args, ZEND_SEND_BY_VAL)
  ZEND_ARG_INFO(0, radians)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_matrix_translate_args, ZEND_SEND_BY_VAL)
  ZEND_ARG_OBJ_INFO(0, matrix, CairoMatrix, 0)
  ZEND_ARG_INFO(0, tx)
  ZEND_ARG_INFO(0, ty)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_matrix_scale_args, ZEND_SEND_BY_VAL)
  ZEND_ARG_OBJ_INFO(0, matrix, CairoMatrix, 0)
  ZEND_ARG_INFO(0, sx)
  ZEND_ARG_INFO(0, sy)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_matrix_rotate_args, ZEND_SEND_BY_VAL)
  ZEND_ARG_OBJ_INFO(0, matrix, CairoMatrix, 0)
  ZEND_ARG_INFO(0, radians)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_matrix_invert_args, ZEND_SEND_BY_VAL)
  ZEND_ARG_OBJ_INFO(0, matrix, CairoMatrix, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_matrix_multiply_args, ZEND_SEND_BY_VAL)
  ZEND_ARG_OBJ_INFO(0, matrix1, CairoMatrix, 1)
  ZEND_ARG_OBJ_INFO(0, matrix2, CairoMatrix, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_matrix_transform_args, ZEND_SEND_BY_VAL)
  ZEND_ARG_OBJ_INFO(0, matrix, CairoMatrix, 0)
  ZEND_ARG_INFO(0, dx)
  ZEND_ARG_INFO(0, dy)
ZEND_END_ARG_INFO()

/* Font Options functions */
ZEND_BEGIN_ARG_INFO(cairo_font_options_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, options, CairoFontOptions, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_font_options_two_args, ZEND_SEND_BY_VAL)
    ZEND_ARG_OBJ_INFO(0, options, CairoFontOptions, 0)
	ZEND_ARG_OBJ_INFO(0, other, CairoFontOptions, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_font_options_set_antialias_args, ZEND_SEND_BY_VAL)
    ZEND_ARG_OBJ_INFO(0, options, CairoFontOptions, 0)
	ZEND_ARG_INFO(0, antialias)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_font_options_set_subpixel_order_args, ZEND_SEND_BY_VAL)
    ZEND_ARG_OBJ_INFO(0, options, CairoFontOptions, 0)
	ZEND_ARG_INFO(0, subpixel_order)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_font_options_set_hint_style_args, ZEND_SEND_BY_VAL)
    ZEND_ARG_OBJ_INFO(0, options, CairoFontOptions, 0)
	ZEND_ARG_INFO(0, hint_style)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_font_options_set_hint_metrics_args, ZEND_SEND_BY_VAL)
    ZEND_ARG_OBJ_INFO(0, options, CairoFontOptions, 0)
	ZEND_ARG_INFO(0, hint_metrics)
ZEND_END_ARG_INFO()

/* Font Face functions */
ZEND_BEGIN_ARG_INFO(cairo_font_face_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, fontface, CairoFontFace, 0)
ZEND_END_ARG_INFO()

/* Scaled Font functions */
ZEND_BEGIN_ARG_INFO(cairo_scaled_font_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, scaledfont, CairoScaledFont, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(cairo_scaled_font_create_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_OBJ_INFO(0, fontface, CairoFontFace, 0)
	ZEND_ARG_OBJ_INFO(0, matrix, CairoMatrix, 0)
	ZEND_ARG_OBJ_INFO(0, ctm, CairoMatrix, 0)
	ZEND_ARG_OBJ_INFO(0, fontoptions, CairoFontOptions, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_scaled_font_text_extents_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, scaledfont, CairoScaledFont, 0)
	ZEND_ARG_INFO(0, text)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_scaled_font_glyph_extents_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, scaledfont, CairoScaledFont, 0)
	ZEND_ARG_INFO(0, glyphs)
ZEND_END_ARG_INFO()

#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 8, 0)
/* Toy Font Face functions */
ZEND_BEGIN_ARG_INFO_EX(cairo_toy_font_face_create_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_INFO(0, family)
	ZEND_ARG_INFO(0, slant)
	ZEND_ARG_INFO(0, weight)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_toy_font_face_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, fontface, CairoToyFontFace, 0)
ZEND_END_ARG_INFO()
#endif

/* Surface Functions */
ZEND_BEGIN_ARG_INFO(cairo_surface_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, surface, CairoSurface, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_surface_create_similar_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, surface, CairoSurface, 0)
	ZEND_ARG_INFO(0, content)
	ZEND_ARG_INFO(0, width)
	ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()

#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 10, 0)
ZEND_BEGIN_ARG_INFO(cairo_surface_create_for_rectangle_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, surface, CairoSurface, 0)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
	ZEND_ARG_INFO(0, width)
	ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()
#endif

ZEND_BEGIN_ARG_INFO(cairo_surface_mark_dirty_rectangle_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, surface, CairoSurface, 0)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
	ZEND_ARG_INFO(0, width)
	ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_surface_set_fallback_resolution_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, surface, CairoSurface, 0)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_surface_write_to_png_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, surface, CairoSurface, 0)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

/* Image Surface Functions */
ZEND_BEGIN_ARG_INFO(cairo_image_create_surface_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, format)
	ZEND_ARG_INFO(0, width)
	ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_format_stride_for_width_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, format)
	ZEND_ARG_INFO(0, width)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(cairo_image_surface_create_for_data_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 4)
	ZEND_ARG_INFO(0, data)
	ZEND_ARG_INFO(0, format)
	ZEND_ARG_INFO(0, width)
	ZEND_ARG_INFO(0, height)
	ZEND_ARG_INFO(0, stride)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_image_surface_create_from_png_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, file)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_image_surface_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, surface, CairoImageSurface, 0)
ZEND_END_ARG_INFO()

/* SVG surface functions */
ZEND_BEGIN_ARG_INFO(cairo_svg_surface_create_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, file)
	ZEND_ARG_INFO(0, width)
	ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_svg_surface_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, surface, CairoSvgSurface, 0)
	ZEND_ARG_INFO(0, version)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_svg_surface_version_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, version)
ZEND_END_ARG_INFO()

/* PDF surface functions */
ZEND_BEGIN_ARG_INFO(cairo_pdf_surface_create_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, file)
	ZEND_ARG_INFO(0, width)
	ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_pdf_surface_set_size_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, surface, CairoPdfSurface, 0)
	ZEND_ARG_INFO(0, width)
	ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()

/* PS surface functions */
ZEND_BEGIN_ARG_INFO(cairo_ps_surface_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, surface, CairoPsSurface, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_ps_surface_create_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, file)
	ZEND_ARG_INFO(0, width)
	ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_ps_surface_set_size_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, surface, CairoPsSurface, 0)
	ZEND_ARG_INFO(0, width)
	ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_ps_surface_restrict_to_level_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, surface, CairoPsSurface, 0)
	ZEND_ARG_INFO(0, level)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_ps_surface_set_eps_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, surface, CairoPsSurface, 0)
	ZEND_ARG_INFO(0, level)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_ps_level_to_string_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, level)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(cairo_ps_surface_dsc_comment_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, surface, CairoPsSurface, 0)
	ZEND_ARG_INFO(0, comment)
ZEND_END_ARG_INFO()

/* Recording surface args */
ZEND_BEGIN_ARG_INFO(cairo_recording_surface_create_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, content)
	ZEND_ARG_INFO(0, extents)
ZEND_END_ARG_INFO()


#if defined(CAIRO_HAS_FT_FONT) && defined(HAVE_FREETYPE)

const char* php_cairo_get_ft_error(int error TSRMLS_DC) {

	const php_cairo_ft_error *current_error = php_cairo_ft_errors;

	while (current_error->err_msg != NULL) {
		if (current_error->err_code == error) {
			return current_error->err_msg;
		}
		current_error++;
	}
	return NULL;
}

#endif	

/* {{{ proto int cairo_version(void) 
       Returns an integer version number of the cairo library being used */
PHP_FUNCTION(cairo_version)
{
	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	RETURN_LONG(cairo_version());
}
/* }}} */

/* {{{ proto int Cairo::version(void)
       Returns an integer version number of the cairo library being used */
PHP_METHOD(Cairo, version)
{
	PHP_CAIRO_ERROR_HANDLING(TRUE)
	if (zend_parse_parameters_none() == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(TRUE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(TRUE)

	RETURN_LONG(cairo_version());
}
/* }}} */

/* {{{ proto string cairo_version_string(void)
       Returns a string version of the cairo library being used */
PHP_FUNCTION(cairo_version_string)
{
	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	RETURN_STRING(cairo_version_string(), 1);
}
/* }}} */

/* {{{ proto string Cairo::versionString(void)
       Returns a string version of the cairo library being used */
PHP_METHOD(Cairo, versionString)
{
	PHP_CAIRO_ERROR_HANDLING(TRUE)
	if (zend_parse_parameters_none() == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(TRUE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(TRUE)

	RETURN_STRING(cairo_version_string(), 1);
}
/* }}} */

/* {{{ proto array cairo_available_surfaces(void)
       Returns an array of available Cairo backend surfaces */
PHP_FUNCTION(cairo_available_surfaces)
{
	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	array_init(return_value);
	add_next_index_string(return_value,"IMAGE",1);
#ifdef CAIRO_HAS_PNG_FUNCTIONS
	add_next_index_string(return_value,"PNG",1);
#endif
#ifdef CAIRO_HAS_PDF_SURFACE
	add_next_index_string(return_value,"PDF",1);
#endif
#ifdef CAIRO_HAS_PS_SURFACE
	add_next_index_string(return_value,"PS",1);
#endif
#ifdef CAIRO_HAS_SVG_SURFACE
	add_next_index_string(return_value,"SVG",1);
#endif
#ifdef CAIRO_HAS_XLIB_SURFACE
	add_next_index_string(return_value,"XLIB",1);
#endif
#ifdef CAIRO_HAS_QUARTZ_SURFACE
	add_next_index_string(return_value,"QUARTZ",1);
#endif
#ifdef CAIRO_HAS_WIN32_SURFACE
	add_next_index_string(return_value,"WIN32",1);
#endif
}
/* }}} */

/* {{{ proto array cairo_available_surfaces(void)
       Returns an array of available Cairo backend surfaces */
PHP_METHOD(Cairo, availableSurfaces)
{
	PHP_CAIRO_ERROR_HANDLING(TRUE)
	if (zend_parse_parameters_none() == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(TRUE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(TRUE)

	array_init(return_value);
	add_next_index_string(return_value,"IMAGE",1);
#ifdef CAIRO_HAS_PNG_FUNCTIONS
	add_next_index_string(return_value,"PNG",1);
#endif
#ifdef CAIRO_HAS_PDF_SURFACE
	add_next_index_string(return_value,"PDF",1);
#endif
#ifdef CAIRO_HAS_PS_SURFACE
	add_next_index_string(return_value,"PS",1);
#endif
#ifdef CAIRO_HAS_SVG_SURFACE
	add_next_index_string(return_value,"SVG",1);
#endif
#ifdef CAIRO_HAS_XLIB_SURFACE
	add_next_index_string(return_value,"XLIB",1);
#endif
#ifdef CAIRO_HAS_QUARTZ_SURFACE
	add_next_index_string(return_value,"QUARTZ",1);
#endif
#ifdef CAIRO_HAS_WIN32_SURFACE
	add_next_index_string(return_value,"WIN32",1);
#endif
#ifdef CAIRO_HAS_RECORDING_SURFACE
	add_next_index_string(return_value,"RECORDING",1);
#endif
}
/* }}} */

/* {{{ proto array cairo_available_fonts(void)
       Returns an array of available Cairo font backends */
PHP_FUNCTION(cairo_available_fonts)
{
	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	array_init(return_value);
#if defined(CAIRO_HAS_FT_FONT) && defined(HAVE_FREETYPE)
	add_next_index_string(return_value,"FREETYPE",1);
#endif
#ifdef CAIRO_HAS_QUARTZ_FONT
	add_next_index_string(return_value,"QUARTZ",1);
#endif
#ifdef CAIRO_HAS_WIN32_FONT
	add_next_index_string(return_value,"WIN32",1);
#endif
#ifdef CAIRO_HAS_USER_FONT
	add_next_index_string(return_value,"USER",1);
#endif
}
/* }}} */

/* {{{ proto array Cairo::availableFonts(void)
       Returns an array of available Cairo font backends */
PHP_METHOD(Cairo, availableFonts)
{
	PHP_CAIRO_ERROR_HANDLING(TRUE)
	if (zend_parse_parameters_none() == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(TRUE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(TRUE)

	array_init(return_value);
#if defined(CAIRO_HAS_FT_FONT) && defined(HAVE_FREETYPE)
	add_next_index_string(return_value,"FREETYPE",1);
#endif
#ifdef CAIRO_HAS_QUARTZ_FONT
	add_next_index_string(return_value,"QUARTZ",1);
#endif
#ifdef CAIRO_HAS_WIN32_FONT
	add_next_index_string(return_value,"WIN32",1);
#endif
#ifdef CAIRO_HAS_USER_FONT
	add_next_index_string(return_value,"USER",1);
#endif
}
/* }}} */

/* {{{ proto string cairo_status_to_string(int status)
       Returns a string interpretation of the integer status passed */
PHP_FUNCTION(cairo_status_to_string)
{
	long status;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &status) == FAILURE) {
		return;
	}

	RETURN_STRING(cairo_status_to_string(status), 1);
}
/* }}} cairo_status_to_string */


/* {{{ proto string Cairo::statusToString(int status)
       Returns a string interpretation of the integer status passed */
PHP_METHOD(Cairo, statusToString)
{
	long status;

	PHP_CAIRO_ERROR_HANDLING(TRUE)
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &status) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(TRUE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(TRUE)

	RETURN_STRING(cairo_status_to_string(status), 1);
}
/* }}} */

/* {{{ cairo_functions[] */
static const zend_function_entry cairo_functions[] = {
	/* Cairo Functions */
	PHP_FE(cairo_version, NULL)
	PHP_FE(cairo_version_string, NULL)
	PHP_FE(cairo_available_surfaces, NULL)
	PHP_FE(cairo_available_fonts, NULL)
	PHP_FE(cairo_status_to_string, cairo_status_to_string_args)

	/* Context Functions */
	PHP_FE(cairo_create, cairo_create_args)
	PHP_FE(cairo_status, cairo_context_args)
	PHP_FE(cairo_save, cairo_context_args)
	PHP_FE(cairo_restore, cairo_context_args)
	PHP_FE(cairo_get_target, cairo_context_args)
	PHP_FE(cairo_push_group, cairo_context_args)
	PHP_FE(cairo_push_group_with_content, cairo_push_group_with_content_args)
	PHP_FE(cairo_pop_group, cairo_context_args)
	PHP_FE(cairo_pop_group_to_source, cairo_context_args)
	PHP_FE(cairo_get_group_target, cairo_context_args)
	PHP_FE(cairo_set_source_rgb, cairo_set_source_rgb_args)
	PHP_FE(cairo_set_source_rgba, cairo_set_source_rgba_args)
	PHP_FE(cairo_set_source, cairo_set_source_args)
	PHP_FE(cairo_set_source_surface, cairo_set_source_surface_args)
	PHP_FE(cairo_get_source, cairo_context_args)
	PHP_FE(cairo_set_antialias, cairo_set_antialias_args)
	PHP_FE(cairo_get_antialias, cairo_context_args)
	PHP_FE(cairo_set_dash, cairo_set_dash_args)
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 4, 0)
	PHP_FE(cairo_get_dash_count, cairo_context_args)
	PHP_FE(cairo_get_dash, cairo_context_args)
#endif
	PHP_FE(cairo_set_fill_rule, cairo_set_fill_rule_args)
	PHP_FE(cairo_get_fill_rule, cairo_context_args)
	PHP_FE(cairo_set_line_cap, cairo_set_fill_rule_args)
	PHP_FE(cairo_get_line_cap, cairo_context_args)
	PHP_FE(cairo_set_line_join, cairo_set_fill_rule_args)
	PHP_FE(cairo_get_line_join, cairo_context_args)
	PHP_FE(cairo_set_line_width, cairo_set_line_width_args)
	PHP_FE(cairo_get_line_width, cairo_context_args)
	PHP_FE(cairo_set_miter_limit, cairo_set_miter_limit_args)
	PHP_FE(cairo_get_miter_limit, cairo_context_args)
	PHP_FE(cairo_set_operator, cairo_set_fill_rule_args)
	PHP_FE(cairo_get_operator, cairo_context_args)
	PHP_FE(cairo_set_tolerance, cairo_set_tolerance_args)
	PHP_FE(cairo_get_tolerance, cairo_context_args)
	PHP_FE(cairo_clip, cairo_context_args)
	PHP_FE(cairo_clip_preserve, cairo_context_args)
	PHP_FE(cairo_reset_clip, cairo_context_args)
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 10, 0)
	PHP_FE(cairo_in_clip, cairo_in_clip_args)
#endif
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 4, 0)
	PHP_FE(cairo_clip_extents, cairo_context_args)
	PHP_FE(cairo_clip_rectangle_list, cairo_context_args)
#endif
	PHP_FE(cairo_fill, cairo_context_args)
	PHP_FE(cairo_fill_preserve, cairo_context_args)
	PHP_FE(cairo_fill_extents, cairo_context_args)
	PHP_FE(cairo_in_fill, cairo_translate_args)
	PHP_FE(cairo_mask, cairo_set_source_args)
	PHP_FE(cairo_mask_surface, cairo_set_source_surface_args)
	PHP_FE(cairo_paint, cairo_context_args)
	PHP_FE(cairo_paint_with_alpha, cairo_paint_with_alpha_args)
	PHP_FE(cairo_stroke, cairo_context_args)
	PHP_FE(cairo_stroke_preserve, cairo_context_args)
	PHP_FE(cairo_stroke_extents, cairo_context_args)
	PHP_FE(cairo_in_stroke, cairo_translate_args)
	PHP_FE(cairo_copy_page, cairo_context_args)
	PHP_FE(cairo_show_page, cairo_context_args)

	/* Context Transformations */
	PHP_FE(cairo_translate, cairo_translate_args)
	PHP_FE(cairo_scale, cairo_translate_args)
	PHP_FE(cairo_rotate, cairo_rotate_args)
	PHP_FE(cairo_transform, cairo_transform_args)
	PHP_FE(cairo_set_matrix, cairo_transform_args)
	PHP_FE(cairo_get_matrix, cairo_context_args)
	PHP_FE(cairo_identity_matrix, cairo_context_args)
	PHP_FE(cairo_user_to_device, cairo_translate_args)
	PHP_FE(cairo_user_to_device_distance, cairo_translate_args)
	PHP_FE(cairo_device_to_user, cairo_translate_args)
	PHP_FE(cairo_device_to_user_distance, cairo_translate_args)

	/* Context and Paths */
	PHP_FE(cairo_copy_path, cairo_context_args)
	PHP_FE(cairo_copy_path_flat, cairo_context_args)
	PHP_FE(cairo_append_path, cairo_append_path_args)
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 6, 0)
	PHP_FE(cairo_has_current_point, cairo_context_args)
#endif
	PHP_FE(cairo_get_current_point, cairo_context_args)
	PHP_FE(cairo_new_path, cairo_context_args)
	PHP_FE(cairo_new_sub_path, cairo_context_args)
	PHP_FE(cairo_close_path, cairo_context_args)
	PHP_FE(cairo_arc, cairo_arc_args)
	PHP_FE(cairo_arc_negative, cairo_arc_args)
	PHP_FE(cairo_curve_to, cairo_curve_to_args)
	PHP_FE(cairo_line_to, cairo_line_to_args)
	PHP_FE(cairo_move_to, cairo_line_to_args)
	PHP_FE(cairo_rectangle, cairo_rectangle_args)
	PHP_FE(cairo_glyph_path, cairo_glyph_path_args)
	PHP_FE(cairo_text_path, cairo_text_path_args)
	PHP_FE(cairo_rel_curve_to, cairo_curve_to_args)
	PHP_FE(cairo_rel_line_to, cairo_line_to_args)
	PHP_FE(cairo_rel_move_to, cairo_line_to_args)
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 6, 0)
	PHP_FE(cairo_path_extents, cairo_context_args)
#endif

	/* Text Functions */
	PHP_FE(cairo_select_font_face, cairo_select_font_face_args)
	PHP_FE(cairo_set_font_size, cairo_set_font_size_args)
	PHP_FE(cairo_set_font_matrix, cairo_set_font_matrix_args)
	PHP_FE(cairo_get_font_matrix, cairo_context_args)
	PHP_FE(cairo_set_font_options, cairo_set_font_options_args)
	PHP_FE(cairo_get_font_options, cairo_context_args)
	PHP_FE(cairo_set_font_face, cairo_set_font_face_args)
	PHP_FE(cairo_get_font_face, cairo_context_args)
	PHP_FE(cairo_set_scaled_font, cairo_set_scaled_font_args)
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 4, 0)
	PHP_FE(cairo_get_scaled_font, cairo_context_args)
#endif
	PHP_FE(cairo_show_text, cairo_show_text_args)
	PHP_FE(cairo_text_extents, cairo_context_args)
	PHP_FE(cairo_font_extents, cairo_context_args)

	/* Pattern Functions */
	PHP_FE(cairo_pattern_get_type, cairo_pattern_args)
	PHP_FE(cairo_pattern_status, cairo_pattern_args)
	PHP_FE(cairo_pattern_get_matrix, cairo_pattern_args)
	PHP_FE(cairo_pattern_set_matrix, cairo_pattern_set_matrix_args)
	PHP_FE(cairo_pattern_create_rgb, cairo_pattern_create_rgb_args)
	PHP_FE(cairo_pattern_create_rgba, cairo_pattern_create_rgba_args)
	PHP_FE(cairo_pattern_create_for_surface, cairo_create_args)
	PHP_FE(cairo_pattern_set_filter, cairo_pattern_set_filter_args)
	PHP_FE(cairo_pattern_get_filter, cairo_surfacepattern_args)
	PHP_FE(cairo_pattern_set_extend, cairo_pattern_set_extend_args)
	PHP_FE(cairo_pattern_get_extend, cairo_pattern_get_extend_args)
	PHP_FE(cairo_pattern_add_color_stop_rgb, cairo_pattern_add_color_stop_rgb_args)
	PHP_FE(cairo_pattern_add_color_stop_rgba, cairo_pattern_add_color_stop_rgba_args)
	PHP_FE(cairo_pattern_create_linear, cairo_pattern_create_linear_args)
	PHP_FE(cairo_pattern_create_radial, cairo_pattern_create_radial_args)
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 12, 0)
	PHP_FE(cairo_pattern_create_mesh, NULL)
	PHP_FE(cairo_mesh_pattern_begin_patch, cairo_mesh_pattern_args)
	PHP_FE(cairo_mesh_pattern_end_patch, cairo_mesh_pattern_args)
	PHP_FE(cairo_mesh_pattern_move_to, cairo_mesh_pattern_translate_args)
	PHP_FE(cairo_mesh_pattern_line_to, cairo_mesh_pattern_translate_args)
	PHP_FE(cairo_mesh_pattern_curve_to, cairo_mesh_pattern_curve_to_args)
	PHP_FE(cairo_mesh_pattern_set_control_point, cairo_mesh_pattern_set_control_point_args)
	PHP_FE(cairo_mesh_pattern_set_corner_color_rgb, cairo_mesh_pattern_set_corner_color_rgb_args)
	PHP_FE(cairo_mesh_pattern_set_corner_color_rgba, cairo_mesh_pattern_set_corner_color_rgba_args)
	PHP_FE(cairo_mesh_pattern_get_patch_count, cairo_mesh_pattern_args)
	PHP_FE(cairo_mesh_pattern_get_path, cairo_mesh_pattern_get_path_args)
	PHP_FE(cairo_mesh_pattern_get_control_point, cairo_mesh_pattern_get_control_point_args)
	PHP_FE(cairo_mesh_pattern_get_corner_color_rgba, cairo_mesh_pattern_get_corner_color_rgba_args)
#endif
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 4, 0)
	PHP_FE(cairo_pattern_get_color_stop_count, cairo_gradientpattern_args)
	PHP_FE(cairo_pattern_get_surface, cairo_surfacepattern_args)
	PHP_FE(cairo_pattern_get_rgba, cairo_solidpattern_args)
	PHP_FE(cairo_pattern_get_color_stop_rgba, cairo_pattern_get_color_stop_rgba_args)
	PHP_FE(cairo_pattern_get_linear_points, cairo_lineargradient_args)
	PHP_FE(cairo_pattern_get_radial_circles, cairo_radialgradient_args)
#endif

	/* Matrix Functions */
	PHP_FE(cairo_matrix_init, cairo_matrix_init_args)
	PHP_FE(cairo_matrix_init_identity, NULL)
	PHP_FE(cairo_matrix_init_translate, cairo_matrix_init_translate_args)
	PHP_FE(cairo_matrix_init_scale, cairo_matrix_init_scale_args)
	PHP_FE(cairo_matrix_init_rotate, cairo_matrix_init_rotate_args)
	PHP_FE(cairo_matrix_translate, cairo_matrix_translate_args)
	PHP_FE(cairo_matrix_scale, cairo_matrix_scale_args)
	PHP_FE(cairo_matrix_rotate, cairo_matrix_rotate_args)
	PHP_FE(cairo_matrix_invert, cairo_matrix_invert_args)
	PHP_FE(cairo_matrix_multiply, cairo_matrix_multiply_args)
	PHP_FE(cairo_matrix_transform_distance, cairo_matrix_transform_args)
	PHP_FE(cairo_matrix_transform_point, cairo_matrix_transform_args)

	/* Font Options Functions */
	PHP_FE(cairo_font_options_create, NULL)
	PHP_FE(cairo_font_options_status, cairo_font_options_args)
	PHP_FE(cairo_font_options_merge, cairo_font_options_two_args)
	PHP_FE(cairo_font_options_hash, cairo_font_options_args)
	PHP_FE(cairo_font_options_equal, cairo_font_options_two_args)
	PHP_FE(cairo_font_options_set_antialias, cairo_font_options_set_antialias_args)
	PHP_FE(cairo_font_options_get_antialias, cairo_font_options_args)
	PHP_FE(cairo_font_options_set_subpixel_order, cairo_font_options_set_subpixel_order_args)
	PHP_FE(cairo_font_options_get_subpixel_order, cairo_font_options_args)
	PHP_FE(cairo_font_options_set_hint_style, cairo_font_options_set_hint_style_args)
	PHP_FE(cairo_font_options_get_hint_style, cairo_font_options_args)
	PHP_FE(cairo_font_options_set_hint_metrics, cairo_font_options_set_hint_metrics_args)
	PHP_FE(cairo_font_options_get_hint_metrics, cairo_font_options_args)

#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 8, 0)
	/* Toy font face functions */
	PHP_FE(cairo_toy_font_face_create, cairo_toy_font_face_create_args)
	PHP_FE(cairo_toy_font_face_get_family, cairo_toy_font_face_args)
	PHP_FE(cairo_toy_font_face_get_weight, cairo_toy_font_face_args)
	PHP_FE(cairo_toy_font_face_get_slant, cairo_toy_font_face_args)
#endif

	/* Font Face Functions */
	PHP_FE(cairo_font_face_status, cairo_font_face_args)
	PHP_FE(cairo_font_face_get_type, cairo_font_face_args)

	/* Scaled Font Functions */
	PHP_FE(cairo_scaled_font_create, cairo_scaled_font_create_args)
	PHP_FE(cairo_scaled_font_status, cairo_scaled_font_args)
	PHP_FE(cairo_scaled_font_extents, cairo_scaled_font_args)
	PHP_FE(cairo_scaled_font_text_extents, cairo_scaled_font_text_extents_args)
	PHP_FE(cairo_scaled_font_glyph_extents, cairo_scaled_font_glyph_extents_args)
	PHP_FE(cairo_scaled_font_get_font_face, cairo_scaled_font_args)
	PHP_FE(cairo_scaled_font_get_font_options, cairo_scaled_font_args)
	PHP_FE(cairo_scaled_font_get_font_matrix, cairo_scaled_font_args)
	PHP_FE(cairo_scaled_font_get_ctm, cairo_scaled_font_args)
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 8, 0)
	PHP_FE(cairo_scaled_font_get_scale_matrix, cairo_scaled_font_args)
#endif
	PHP_FE(cairo_scaled_font_get_type, cairo_scaled_font_args)

	/* User Font Functions 
#ifdef CAIRO_HAS_USER_FONT
	PHP_FE(cairo_user_font_face_create, cairo_user_font_face_create_args)
	PHP_FE(cairo_user_font_face_set_init_func, cairo_user_font_face_set_init_func_args)
	PHP_FE(cairo_user_font_face_get_init_func, cairo_user_font_face_get_init_func_args)
	PHP_FE(cairo_user_font_face_set_render_glyph_func, cairo_user_font_face_set_render_glyph_func_args)
	PHP_FE(cairo_user_font_face_get_render_glyph_func, cairo_user_font_face_get_render_glyph_func_args)
	cairo_user_font_face_set_unicode_to_glyph_func
	cairo_user_font_face_get_unicode_to_glyph_func
	cairo_user_font_face_set_text_to_glyphs_func
	cairo_user_font_face_get_text_to_glyphs_func
#endif */

#if defined(CAIRO_HAS_FT_FONT) && defined(HAVE_FREETYPE)
	PHP_FE(cairo_ft_font_face_create, NULL)
#endif
#if defined(CAIRO_HAS_WIN32_FONT) && defined(HAVE_WIN32_FONT)
	PHP_FE(cairo_win32_font_face_create, NULL)
#endif

	/* Generic Surface Functions */
	PHP_FE(cairo_surface_create_similar, cairo_surface_create_similar_args)
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 10, 0)
	PHP_FE(cairo_surface_create_for_rectangle, cairo_surface_create_similar_args)
#endif
	PHP_FE(cairo_surface_status, cairo_surface_args)
	PHP_FE(cairo_surface_finish, cairo_surface_args)
	PHP_FE(cairo_surface_flush, cairo_surface_args)
	PHP_FE(cairo_surface_get_font_options, cairo_surface_args)
	PHP_FE(cairo_surface_get_content, cairo_surface_args)
	PHP_FE(cairo_surface_mark_dirty, cairo_surface_args)
	PHP_FE(cairo_surface_mark_dirty_rectangle, cairo_surface_mark_dirty_rectangle_args)
	PHP_FE(cairo_surface_set_device_offset, cairo_surface_set_fallback_resolution_args)
	PHP_FE(cairo_surface_get_device_offset, cairo_surface_args)
	PHP_FE(cairo_surface_set_fallback_resolution, cairo_surface_set_fallback_resolution_args)
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 8, 0)
	PHP_FE(cairo_surface_get_fallback_resolution, cairo_surface_args)
#endif
	PHP_FE(cairo_surface_get_type, cairo_surface_args)
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 6, 0)
	PHP_FE(cairo_surface_copy_page, cairo_surface_args)
	PHP_FE(cairo_surface_show_page, cairo_surface_args)
#endif
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 8, 0)
	PHP_FE(cairo_surface_has_show_text_glyphs, cairo_surface_args)
#endif

	/* Image Surface Functions */
	PHP_FE(cairo_image_surface_create, cairo_image_create_surface_args)
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 6, 0)
	PHP_FE(cairo_format_stride_for_width, cairo_format_stride_for_width_args)
#endif
	PHP_FE(cairo_image_surface_create_for_data, cairo_image_surface_create_for_data_args)
	PHP_FE(cairo_image_surface_get_data, cairo_image_surface_args)
	PHP_FE(cairo_image_surface_get_format, cairo_image_surface_args)
	PHP_FE(cairo_image_surface_get_width, cairo_image_surface_args)
	PHP_FE(cairo_image_surface_get_height, cairo_image_surface_args)
	PHP_FE(cairo_image_surface_get_stride, cairo_image_surface_args)

	/* PNG support Functions */
#ifdef CAIRO_HAS_PNG_FUNCTIONS
	PHP_FE(cairo_image_surface_create_from_png, cairo_image_surface_create_from_png_args)
	PHP_FE(cairo_surface_write_to_png, cairo_surface_write_to_png_args)  
#endif

	/* SVG Surface Functions */
#ifdef CAIRO_HAS_SVG_SURFACE
	PHP_FE(cairo_svg_surface_create, cairo_svg_surface_create_args)
	PHP_FE(cairo_svg_surface_restrict_to_version, cairo_svg_surface_args)
	PHP_FE(cairo_svg_get_versions, NULL)
	PHP_FE(cairo_svg_version_to_string, cairo_svg_surface_version_args)    
#endif

	/* PDF Surface Functions */
#ifdef CAIRO_HAS_PDF_SURFACE
	PHP_FE(cairo_pdf_surface_create, cairo_pdf_surface_create_args)
	PHP_FE(cairo_pdf_surface_set_size, cairo_pdf_surface_set_size_args)  
#endif

	/* PS Surface Functions */
#ifdef CAIRO_HAS_PS_SURFACE
	PHP_FE(cairo_ps_surface_create, cairo_ps_surface_create_args)
	PHP_FE(cairo_ps_surface_set_size, cairo_ps_surface_set_size_args)
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 6, 0)
	PHP_FE(cairo_ps_surface_restrict_to_level, cairo_ps_surface_restrict_to_level_args)
	PHP_FE(cairo_ps_level_to_string, cairo_ps_level_to_string_args)
	PHP_FE(cairo_ps_get_levels, NULL)
	PHP_FE(cairo_ps_surface_set_eps, cairo_ps_surface_set_eps_args)
	PHP_FE(cairo_ps_surface_get_eps, cairo_ps_surface_args)
#endif
	PHP_FE(cairo_ps_surface_dsc_begin_setup, cairo_ps_surface_args)
	PHP_FE(cairo_ps_surface_dsc_begin_page_setup, cairo_ps_surface_args)
	PHP_FE(cairo_ps_surface_dsc_comment, cairo_ps_surface_dsc_comment_args)
#endif

	/* Win32 Surface Functions 
#ifdef CAIRO_HAS_WIN32_SURFACE
	PHP_FE(cairo_win32_surface_create, NULL)
	PHP_FE(cairo_win32_surface_create_with_dib, NULL)
	PHP_FE(cairo_win32_surface_create_with_ddb, NULL)
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 6, 0)
	PHP_FE(cairo_win32_printing_surface_create, NULL)
#endif
	PHP_FE(cairo_win32_surface_get_dc, NULL)
	PHP_FE(cairo_win32_surface_get_image, NULL)    
#endif*/

	/* Recording surface functions */
#ifdef CAIRO_HAS_RECORDING_SURFACE
	PHP_FE(cairo_recording_surface_create, cairo_recording_surface_create_args)
#endif

	/* Compatibility with old cairo-wrapper extension */
#if PHP_VERSION_ID >= 50300
	ZEND_FENTRY(cairo_matrix_create_scale, ZEND_FN(cairo_matrix_init_scale), cairo_matrix_init_scale_args, ZEND_ACC_DEPRECATED)
	ZEND_FENTRY(cairo_matrix_create_translate, ZEND_FN(cairo_matrix_init_translate), cairo_matrix_init_translate_args, ZEND_ACC_DEPRECATED)
#else
	PHP_FALIAS(cairo_matrix_create_scale, cairo_matrix_init_scale, cairo_matrix_init_scale_args)
	PHP_FALIAS(cairo_matrix_create_translate, cairo_matrix_init_translate, cairo_matrix_init_translate_args)
#endif

	{ NULL, NULL, NULL }
};
/* }}} */

/* {{{ cairo_class_functions[] */
const zend_function_entry cairo_methods[] = {
	PHP_ME(Cairo, version, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Cairo, versionString, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Cairo, availableSurfaces, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Cairo, availableFonts, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Cairo, statusToString, cairo_status_to_string_args, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	{NULL, NULL, NULL}
};
/* }}} */

/* {{{ cairo_module_entry */
zend_module_entry cairo_module_entry = {
	STANDARD_MODULE_HEADER,
	"cairo",
	cairo_functions,
	PHP_MINIT(cairo),
	NULL, //PHP_MSHUTDOWN(cairo),
	NULL,
	NULL,
	PHP_MINFO(cairo),
	PHP_CAIRO_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_CAIRO
ZEND_GET_MODULE(cairo)
#endif

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(cairo)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "Cairo", cairo_methods);
	cairo_ce_cairo = zend_register_internal_class(&ce TSRMLS_CC);
	cairo_ce_cairo->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS | ZEND_ACC_FINAL_CLASS;

	memcpy(&cairo_std_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	cairo_std_object_handlers.clone_obj = NULL;


	PHP_MINIT(cairo_error)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_MINIT(cairo_context)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_MINIT(cairo_matrix)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_MINIT(cairo_pattern)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_MINIT(cairo_path)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_MINIT(cairo_font_options)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_MINIT(cairo_font_face)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_MINIT(cairo_scaled_font)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_MINIT(cairo_font)(INIT_FUNC_ARGS_PASSTHRU); /* must be after font_face */

#if defined(CAIRO_HAS_FT_FONT) && defined(HAVE_FREETYPE)
	PHP_MINIT(cairo_ft_font)(INIT_FUNC_ARGS_PASSTHRU);
#endif
#if defined(CAIRO_HAS_WIN32_FONT) && defined(HAVE_WIN32_FONT)
	PHP_MINIT(cairo_win32_font)(INIT_FUNC_ARGS_PASSTHRU);
#endif
/*
#ifdef CAIRO_HAS_QUARTZ_FONT
	PHP_MINIT(cairo_quartz_font)(INIT_FUNC_ARGS_PASSTHRU);
#endif
#ifdef CAIRO_HAS_USER_FONT
	PHP_MINIT(cairo_svg_surface)(INIT_FUNC_ARGS_PASSTHRU);
#endif */

	PHP_MINIT(cairo_surface)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_MINIT(cairo_image_surface)(INIT_FUNC_ARGS_PASSTHRU);
#ifdef CAIRO_HAS_PDF_SURFACE
	PHP_MINIT(cairo_pdf_surface)(INIT_FUNC_ARGS_PASSTHRU);
#endif
#ifdef CAIRO_HAS_PS_SURFACE
	PHP_MINIT(cairo_ps_surface)(INIT_FUNC_ARGS_PASSTHRU);
#endif
/*
#ifdef CAIRO_HAS_WIN32_SURFACE
	PHP_MINIT(cairo_win32_surface)(INIT_FUNC_ARGS_PASSTHRU);
#endif */
#ifdef CAIRO_HAS_SVG_SURFACE
	PHP_MINIT(cairo_svg_surface)(INIT_FUNC_ARGS_PASSTHRU);
#endif

#ifdef CAIRO_HAS_RECORDING_SURFACE
	PHP_MINIT(cairo_recording_surface)(INIT_FUNC_ARGS_PASSTHRU);
#endif

#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 10, 0)
	PHP_MINIT(cairo_sub_surface)(INIT_FUNC_ARGS_PASSTHRU);
#endif

/*
#ifdef CAIRO_HAS_QUARTZ_SURFACE
	PHP_MINIT(cairo_quartz_surface)(INIT_FUNC_ARGS_PASSTHRU);
#endif
#ifdef CAIRO_HAS_XLIB_SURFACE
	PHP_MINIT(cairo_xlib_surface)(INIT_FUNC_ARGS_PASSTHRU);
#endif */

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION */
PHP_MSHUTDOWN_FUNCTION(cairo)
{
#if defined(ZEND_DEBUG) && ZEND_DEBUG == 1
	cairo_debug_reset_static_data();
#endif

	return SUCCESS;
}

/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(cairo)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "Cairo Graphics Library Bindings", "enabled");
	php_info_print_table_colspan_header(2,
#ifdef COMPILE_DL_CAIRO
		"compiled as dynamic module"
#else
		"compiled as static module"
#endif
        );
	php_info_print_table_row(2, "Cairo Library Version", CAIRO_VERSION_STRING);
	php_info_print_table_row(2, "Extension Version", PHP_CAIRO_VERSION);
	php_info_print_table_colspan_header(2, "Surface Backends Available");
	php_info_print_table_row(2, "Image Surface", "enabled");
	php_info_print_table_row(2, "PNG Support",
#ifdef CAIRO_HAS_PNG_FUNCTIONS
		"enabled"
#else
		"disabled"
#endif
		);
	php_info_print_table_row(2, "PDF Surface",
#ifdef CAIRO_HAS_PDF_SURFACE
		"enabled"
#else
		"disabled"
#endif
		);
	php_info_print_table_row(2, "PS Surface",
#ifdef CAIRO_HAS_PS_SURFACE
		"enabled"
#else
		"disabled"
#endif
		);
	php_info_print_table_row(2, "Xlib (X11, X.org) Surface",
#ifdef CAIRO_HAS_XLIB_SURFACE
		"enabled"
#else
		"disabled"
#endif
		);
	php_info_print_table_row(2, "Quartz (MacOSX) Surface",
#ifdef CAIRO_HAS_QUARTZ_SURFACE
		"enabled"
#else
		"disabled"
#endif
		);
	php_info_print_table_row(2, "SVG Surface",
#ifdef CAIRO_HAS_SVG_SURFACE
		"enabled"
#else
		"disabled"
#endif
		);
	php_info_print_table_row(2, "Win32 Surface",
#ifdef CAIRO_HAS_WIN32_SURFACE
		"enabled"
#else
		"disabled"
#endif
		);
	php_info_print_table_row(2, "Recording Surface",
#ifdef CAIRO_HAS_RECORDING_SURFACE
		"enabled"
#else
		"disabled"
#endif
		);
	php_info_print_table_colspan_header(2, "Font Backends Available");
	php_info_print_table_row(2, "Freetype Fonts",
#if defined(CAIRO_HAS_FT_FONT) && defined(HAVE_FREETYPE)
		"enabled"
#else
		"disabled"
#endif
		);
	php_info_print_table_row(2, "Quartz Fonts",
#ifdef CAIRO_HAS_QUARTZ_FONT
		"enabled"
#else
		"disabled"
#endif
		);
	php_info_print_table_row(2, "Win32 Fonts",
#ifdef CAIRO_HAS_WIN32_FONT
		"enabled"
#else
		"disabled"
#endif
		);
	php_info_print_table_row(2, "User Fonts",
#ifdef CAIRO_HAS_USER_FONT
		"enabled"
#else
		"disabled"
#endif
		);
	php_info_print_table_end();
}
/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
