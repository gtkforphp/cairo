/*
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt.                                 |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Authors: Akshat Gupta <g.akshat@gmail.com>                           |
   +----------------------------------------------------------------------+
*/

/* $ Id: $ */ 

#define PHP_CAIRO_VERSION "1.01"

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
#ifdef  __cplusplus
extern "C" {
#endif

extern zend_module_entry phpCairo_module_entry;
#define phpext_phpCairo_ptr &phpCairo_module_entry

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
#define PROP_SET_STRINGL(name, s, l) zend_update_property_stringl(_this_ce, _this_zval, #name, strlen(#name), s, l TSRMLS_CC)


PHP_FUNCTION(cairoVersion);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_version_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_version_arg_info NULL
#endif

PHP_FUNCTION(cairoVersionString);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(cairo_version_string_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define cairo_version_string_arg_info NULL
#endif

PHP_METHOD(CairoContext, __construct);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext____construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
	ZEND_ARG_OBJ_INFO(0, obj, CairoSurface, 1)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext____construct_args NULL
#endif

PHP_METHOD(CairoContext, appendPath);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__append_path_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_OBJ_INFO(0, p, CairoPath, 1)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__append_path_args NULL
#endif

PHP_METHOD(CairoContext, arc);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__arc_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 5)
  ZEND_ARG_INFO(0, xc)
  ZEND_ARG_INFO(0, yc)
  ZEND_ARG_INFO(0, radius)
  ZEND_ARG_INFO(0, angle1)
  ZEND_ARG_INFO(0, angle2)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__arc_args NULL
#endif

PHP_METHOD(CairoContext, arcNegative);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__arc_negative_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 5)
  ZEND_ARG_INFO(0, xc)
  ZEND_ARG_INFO(0, yc)
  ZEND_ARG_INFO(0, radius)
  ZEND_ARG_INFO(0, angle1)
  ZEND_ARG_INFO(0, angle2)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__arc_negative_args NULL
#endif

PHP_METHOD(CairoContext, clip);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__clip_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__clip_args NULL
#endif

PHP_METHOD(CairoContext, clipExtents);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__clip_extents_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__clip_extents_args NULL
#endif

PHP_METHOD(CairoContext, clipPreserve);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__clip_preserve_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__clip_preserve_args NULL
#endif

PHP_METHOD(CairoContext, closePath);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__close_path_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__close_path_args NULL
#endif

PHP_METHOD(CairoContext, copyClipRectangleList);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__copy_clip_rectangle_list_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__copy_clip_rectangle_list_args NULL
#endif

PHP_METHOD(CairoContext, copyPage);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__copy_page_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__copy_page_args NULL
#endif

PHP_METHOD(CairoContext, copyPath);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__copy_path_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__copy_path_args NULL
#endif

PHP_METHOD(CairoContext, copyPathFlat);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__copy_path_flat_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__copy_path_flat_args NULL
#endif

PHP_METHOD(CairoContext, curveTo);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__curve_to_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 6)
  ZEND_ARG_INFO(0, x1)
  ZEND_ARG_INFO(0, y1)
  ZEND_ARG_INFO(0, x2)
  ZEND_ARG_INFO(0, y2)
  ZEND_ARG_INFO(0, x3)
  ZEND_ARG_INFO(0, y3)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__curve_to_args NULL
#endif

PHP_METHOD(CairoContext, deviceToUser);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__device_to_user_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, x)
  ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__device_to_user_args NULL
#endif

PHP_METHOD(CairoContext, deviceToUserDistance);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__device_to_user_distance_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, x)
  ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__device_to_user_distance_args NULL
#endif

PHP_METHOD(CairoContext, fill);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__fill_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__fill_args NULL
#endif

PHP_METHOD(CairoContext, fillExtents);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__fill_extents_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__fill_extents_args NULL
#endif

PHP_METHOD(CairoContext, fillPreserve);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__fill_preserve_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__fill_preserve_args NULL
#endif

PHP_METHOD(CairoContext, fontExtents);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__font_extents_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__font_extents_args NULL
#endif

PHP_METHOD(CairoContext, getAntialias);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__get_antialias_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__get_antialias_args NULL
#endif

PHP_METHOD(CairoContext, getCurrentPoint);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__get_current_point_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__get_current_point_args NULL
#endif

PHP_METHOD(CairoContext, getDash);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__get_dash_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__get_dash_args NULL
#endif

PHP_METHOD(CairoContext, getDashCount);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__get_dash_count_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__get_dash_count_args NULL
#endif

PHP_METHOD(CairoContext, getFillRule);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__get_fill_rule_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__get_fill_rule_args NULL
#endif

PHP_METHOD(CairoContext, getFontFace);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__get_font_face_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__get_font_face_args NULL
#endif

PHP_METHOD(CairoContext, getFontMatrix);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__get_font_matrix_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__get_font_matrix_args NULL
#endif

PHP_METHOD(CairoContext, getFontOptions);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__get_font_options_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__get_font_options_args NULL
#endif

PHP_METHOD(CairoContext, getGroupTarget);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__get_group_target_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__get_group_target_args NULL
#endif

PHP_METHOD(CairoContext, getLineCap);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__get_line_cap_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__get_line_cap_args NULL
#endif

PHP_METHOD(CairoContext, getLineJoin);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__get_line_join_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__get_line_join_args NULL
#endif

PHP_METHOD(CairoContext, getLineWidth);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__get_line_width_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__get_line_width_args NULL
#endif

PHP_METHOD(CairoContext, getMatrix);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__get_matrix_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__get_matrix_args NULL
#endif

PHP_METHOD(CairoContext, getMiterLimit);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__get_miter_limit_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__get_miter_limit_args NULL
#endif

PHP_METHOD(CairoContext, getOperator);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__get_operator_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__get_operator_args NULL
#endif

PHP_METHOD(CairoContext, getScaledFont);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__get_scaled_font_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__get_scaled_font_args NULL
#endif

PHP_METHOD(CairoContext, getSource);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__get_source_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__get_source_args NULL
#endif

PHP_METHOD(CairoContext, getTarget);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__get_target_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__get_target_args NULL
#endif

PHP_METHOD(CairoContext, getTolerance);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__get_tolerance_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__get_tolerance_args NULL
#endif

PHP_METHOD(CairoContext, glyphExtents);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__glyph_extents_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
#if (PHP_MINOR_VERSION > 0)  
  ZEND_ARG_ARRAY_INFO(0, obj, 1)
#else
  ZEND_ARG_INFO(O, obj)
#endif
  ZEND_ARG_INFO(0, num)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__glyph_extents_args NULL
#endif

PHP_METHOD(CairoContext, glyphPath);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__glyph_path_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
#if (PHP_MINOR_VERSION > 0)
  ZEND_ARG_ARRAY_INFO(0, obh, 1)
#else
  ZEND_ARG_INFO(0, obh);
#endif
  ZEND_ARG_INFO(0, num)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__glyph_path_args NULL
#endif

PHP_METHOD(CairoContext, hasCurrentPoint);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__has_current_point_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__has_current_point_args NULL
#endif

PHP_METHOD(CairoContext, identityMatrix);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__identity_matrix_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__identity_matrix_args NULL
#endif

PHP_METHOD(CairoContext, inFill);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__in_fill_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, x)
  ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__in_fill_args NULL
#endif

PHP_METHOD(CairoContext, inStroke);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__in_stroke_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, x)
  ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__in_stroke_args NULL
#endif

PHP_METHOD(CairoContext, lineTo);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__line_to_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, x)
  ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__line_to_args NULL
#endif

PHP_METHOD(CairoContext, mask);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__mask_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_OBJ_INFO(0, p, CairoPattern, 1)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__mask_args NULL
#endif

PHP_METHOD(CairoContext, maskSurface);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__mask_surface_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_OBJ_INFO(0, s, CairoSurface, 1)
  ZEND_ARG_INFO(0, surface_x)
  ZEND_ARG_INFO(0, surface_y)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__mask_surface_args NULL
#endif

PHP_METHOD(CairoContext, moveTo);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__move_to_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, x)
  ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__move_to_args NULL
#endif

PHP_METHOD(CairoContext, newPath);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__new_path_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__new_path_args NULL
#endif

PHP_METHOD(CairoContext, newSubPath);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__new_sub_path_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__new_sub_path_args NULL
#endif

PHP_METHOD(CairoContext, paint);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__paint_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__paint_args NULL
#endif

PHP_METHOD(CairoContext, paintWithAlpha);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__paint_with_alpha_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, alpha)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__paint_with_alpha_args NULL
#endif

PHP_METHOD(CairoContext, pathExtents);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__path_extents_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
  ZEND_ARG_OBJ_INFO(0, path, CairoPath, 1)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__path_extents_args NULL
#endif

PHP_METHOD(CairoContext, popGroup);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__pop_group_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__pop_group_args NULL
#endif

PHP_METHOD(CairoContext, popGroupToSource);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__pop_group_to_source_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__pop_group_to_source_args NULL
#endif

PHP_METHOD(CairoContext, pushGroup);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__push_group_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__push_group_args NULL
#endif

PHP_METHOD(CairoContext, pushGroupWithContent);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__push_group_with_content_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, content)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__push_group_with_content_args NULL
#endif

PHP_METHOD(CairoContext, rectangle);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__rectangle_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 4)
  ZEND_ARG_INFO(0, x)
  ZEND_ARG_INFO(0, y)
  ZEND_ARG_INFO(0, width)
  ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__rectangle_args NULL
#endif

PHP_METHOD(CairoContext, relCurveTo);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__rel_curve_to_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 6)
  ZEND_ARG_INFO(0, x1)
  ZEND_ARG_INFO(0, y1)
  ZEND_ARG_INFO(0, x2)
  ZEND_ARG_INFO(0, y2)
  ZEND_ARG_INFO(0, x3)
  ZEND_ARG_INFO(0, y3)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__rel_curve_to_args NULL
#endif

PHP_METHOD(CairoContext, relLineTo);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__rel_line_to_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, x)
  ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__rel_line_to_args NULL
#endif

PHP_METHOD(CairoContext, relMoveTo);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__rel_move_to_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, x)
  ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__rel_move_to_args NULL
#endif

PHP_METHOD(CairoContext, resetClip);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__reset_clip_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__reset_clip_args NULL
#endif

PHP_METHOD(CairoContext, restore);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__restore_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__restore_args NULL
#endif

PHP_METHOD(CairoContext, rotate);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__rotate_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, angle)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__rotate_args NULL
#endif

PHP_METHOD(CairoContext, save);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__save_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__save_args NULL
#endif

PHP_METHOD(CairoContext, scale);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__scale_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, x)
  ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__scale_args NULL
#endif

PHP_METHOD(CairoContext, selectFontFace);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__select_font_face_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, family)
  ZEND_ARG_INFO(0, slant)
  ZEND_ARG_INFO(0, weight)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__select_font_face_args NULL
#endif

PHP_METHOD(CairoContext, setAntialias);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__set_antialias_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
  ZEND_ARG_INFO(0, antialias)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__set_antialias_args NULL
#endif

PHP_METHOD(CairoContext, setDash);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__set_dash_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
#if (PHP_MINOR_VERSION > 0)
  ZEND_ARG_ARRAY_INFO(0, dashes, 1)
#else
  ZEND_ARG_INFO(0, dashes)
#endif
  ZEND_ARG_INFO(0, num_dashes)
  ZEND_ARG_INFO(0, offset)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__set_dash_args NULL
#endif

PHP_METHOD(CairoContext, setFillRule);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__set_fill_rule_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, fill_rule)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__set_fill_rule_args NULL
#endif

PHP_METHOD(CairoContext, setFontFace);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__set_font_face_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
  ZEND_ARG_OBJ_INFO(0, obj, CairoFontFace, 1)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__set_font_face_args NULL
#endif

PHP_METHOD(CairoContext, setFontMatrix);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__set_font_matrix_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_OBJ_INFO(0, matrix, CairoMatrix, 1)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__set_font_matrix_args NULL
#endif

PHP_METHOD(CairoContext, setFontOptions);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__set_font_options_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_OBJ_INFO(0, options, CairoFontOptions, 1)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__set_font_options_args NULL
#endif

PHP_METHOD(CairoContext, setFontSize);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__set_font_size_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, size)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__set_font_size_args NULL
#endif

PHP_METHOD(CairoContext, setLineCap);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__set_line_cap_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, line_cap)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__set_line_cap_args NULL
#endif

PHP_METHOD(CairoContext, setLineJoin);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__set_line_join_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, line_join)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__set_line_join_args NULL
#endif

PHP_METHOD(CairoContext, setLineWidth);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__set_line_width_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, width)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__set_line_width_args NULL
#endif

PHP_METHOD(CairoContext, setMatrix);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__set_matrix_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_OBJ_INFO(0, matix, CairoMatrix, 1)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__set_matrix_args NULL
#endif

PHP_METHOD(CairoContext, setMiterLimit);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__set_miter_limit_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, limit)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__set_miter_limit_args NULL
#endif

PHP_METHOD(CairoContext, setOperator);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__set_operator_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, op)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__set_operator_args NULL
#endif

PHP_METHOD(CairoContext, setSource);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__set_source_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
  ZEND_ARG_OBJ_INFO(0, p, CairoPattern, 1)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__set_source_args NULL
#endif

PHP_METHOD(CairoContext, setSourceRgb);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__set_source_rgb_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 3)
  ZEND_ARG_INFO(0, red)
  ZEND_ARG_INFO(0, green)
  ZEND_ARG_INFO(0, blue)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__set_source_rgb_args NULL
#endif

PHP_METHOD(CairoContext, setSourceRgba);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__set_source_rgba_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 3)
  ZEND_ARG_INFO(0, red)
  ZEND_ARG_INFO(0, green)
  ZEND_ARG_INFO(0, blue)
  ZEND_ARG_INFO(0, alpha)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__set_source_rgba_args NULL
#endif

PHP_METHOD(CairoContext, setSourceSurface);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__set_source_surface_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_OBJ_INFO(0, surface, CairoSurface, 1)
  ZEND_ARG_INFO(0, x)
  ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__set_source_surface_args NULL
#endif

PHP_METHOD(CairoContext, setTolerance);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__set_tolerance_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, tolerance)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__set_tolerance_args NULL
#endif

PHP_METHOD(CairoContext, showGlyphs);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__show_glyphs_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
#if (PHP_MINOR_VERSION > 0)
  ZEND_ARG_ARRAY_INFO(0, obj, 1)
#else
  ZEND_ARG_INFO(0, obj)
#endif
  ZEND_ARG_INFO(0, num_glyphs)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__show_glyphs_args NULL
#endif

PHP_METHOD(CairoContext, showPage);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__show_page_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__show_page_args NULL
#endif

PHP_METHOD(CairoContext, showText);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__show_text_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, obj)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__show_text_args NULL
#endif

PHP_METHOD(CairoContext, stroke);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__stroke_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__stroke_args NULL
#endif

PHP_METHOD(CairoContext, strokeExtents);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__stroke_extents_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__stroke_extents_args NULL
#endif

PHP_METHOD(CairoContext, strokePreserve);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__stroke_preserve_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__stroke_preserve_args NULL
#endif

PHP_METHOD(CairoContext, textExtents);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__text_extents_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, str)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__text_extents_args NULL
#endif

PHP_METHOD(CairoContext, textPath);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__text_path_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, obj)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__text_path_args NULL
#endif

PHP_METHOD(CairoContext, transform);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__transform_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_OBJ_INFO(0, matrix, CairoMatrix, 1)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__transform_args NULL
#endif

PHP_METHOD(CairoContext, translate);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__translate_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, tx)
  ZEND_ARG_INFO(0, ty)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__translate_args NULL
#endif

PHP_METHOD(CairoContext, userToDevice);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__user_to_device_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, x)
  ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__user_to_device_args NULL
#endif

PHP_METHOD(CairoContext, userToDeviceDistance);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoContext__user_to_device_distance_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, dx)
  ZEND_ARG_INFO(0, dy)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoContext__user_to_device_distance_args NULL
#endif

PHP_METHOD(CairoFontFace, __construct);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoFontFace____construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoFontFace____construct_args NULL
#endif

PHP_METHOD(CairoFontOptions, __construct);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoFontOptions____construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoFontOptions____construct_args NULL
#endif

PHP_METHOD(CairoFontOptions, getAntialias);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoFontOptions__get_antialias_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoFontOptions__get_antialias_args NULL
#endif

PHP_METHOD(CairoFontOptions, getHintMetrics);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoFontOptions__get_hint_metrics_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoFontOptions__get_hint_metrics_args NULL
#endif

PHP_METHOD(CairoFontOptions, getHintStyle);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoFontOptions__get_hint_style_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoFontOptions__get_hint_style_args NULL
#endif

PHP_METHOD(CairoFontOptions, getSubpixelOrder);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoFontOptions__get_subpixel_order_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoFontOptions__get_subpixel_order_args NULL
#endif

PHP_METHOD(CairoFontOptions, setAntialias);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoFontOptions__set_antialias_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
  ZEND_ARG_INFO(0, aa)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoFontOptions__set_antialias_args NULL
#endif

PHP_METHOD(CairoFontOptions, setHintMetrics);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoFontOptions__set_hint_metrics_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
  ZEND_ARG_INFO(0, hm)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoFontOptions__set_hint_metrics_args NULL
#endif

PHP_METHOD(CairoFontOptions, setHintStyle);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoFontOptions__set_hint_style_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
  ZEND_ARG_INFO(0, hs)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoFontOptions__set_hint_style_args NULL
#endif

PHP_METHOD(CairoFontOptions, setSubpixelOrder);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoFontOptions__set_subpixel_order_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
  ZEND_ARG_INFO(0, so)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoFontOptions__set_subpixel_order_args NULL
#endif

PHP_METHOD(CairoMatrix, __construct);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoMatrix____construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 5)
  ZEND_ARG_INFO(0, yx)
  ZEND_ARG_INFO(0, xy)
  ZEND_ARG_INFO(0, yy)
  ZEND_ARG_INFO(0, x0)
  ZEND_ARG_INFO(0, y0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoMatrix____construct_args NULL
#endif

PHP_METHOD(CairoMatrix, initRotate);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoMatrix__init_rotate_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, radians)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoMatrix__init_rotate_args NULL
#endif

PHP_METHOD(CairoMatrix, invert);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoMatrix__invert_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoMatrix__invert_args NULL
#endif

PHP_METHOD(CairoMatrix, multiply);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoMatrix__multiply_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_OBJ_INFO(0, o2, CairoMatrix, 1)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoMatrix__multiply_args NULL
#endif

PHP_METHOD(CairoMatrix, rotate);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoMatrix__rotate_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, radians)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoMatrix__rotate_args NULL
#endif

PHP_METHOD(CairoMatrix, scale);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoMatrix__scale_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, sx)
  ZEND_ARG_INFO(0, xy)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoMatrix__scale_args NULL
#endif

PHP_METHOD(CairoMatrix, transformDistance);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoMatrix__transform_distance_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, dx)
  ZEND_ARG_INFO(0, dy)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoMatrix__transform_distance_args NULL
#endif

PHP_METHOD(CairoMatrix, transformPoint);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoMatrix__transform_point_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, x)
  ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoMatrix__transform_point_args NULL
#endif

PHP_METHOD(CairoMatrix, translate);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoMatrix__translate_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, tx)
  ZEND_ARG_INFO(0, ty)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoMatrix__translate_args NULL
#endif

PHP_METHOD(CairoPath, __construct);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoPath____construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoPath____construct_args NULL
#endif

PHP_METHOD(CairoPath, toStr);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoPath__to_str_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoPath__to_str_args NULL
#endif

PHP_METHOD(CairoPattern, __construct);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoPattern____construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoPattern____construct_args NULL
#endif

PHP_METHOD(CairoPattern, getMatrix);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoPattern__get_matrix_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoPattern__get_matrix_args NULL
#endif

PHP_METHOD(CairoPattern, setMatrix);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoPattern__set_matrix_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_OBJ_INFO(0, m, CairoMatrix, 1)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoPattern__set_matrix_args NULL
#endif

PHP_METHOD(CairoGradient, __contruct);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoGradient____contruct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoGradient____contruct_args NULL
#endif

PHP_METHOD(CairoGradient, addColorStopRgb);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoGradient__add_color_stop_rgb_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 4)
  ZEND_ARG_INFO(0, offset)
  ZEND_ARG_INFO(0, red)
  ZEND_ARG_INFO(0, green)
  ZEND_ARG_INFO(0, blue)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoGradient__add_color_stop_rgb_args NULL
#endif

PHP_METHOD(CairoGradient, addColorStopRgba);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoGradient__add_color_stop_rgba_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 5)
  ZEND_ARG_INFO(0, offset)
  ZEND_ARG_INFO(0, red)
  ZEND_ARG_INFO(0, green)
  ZEND_ARG_INFO(0, blue)
  ZEND_ARG_INFO(0, alpha)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoGradient__add_color_stop_rgba_args NULL
#endif

PHP_METHOD(CairoLinearGradient, __construct);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoLinearGradient____construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 3)
  ZEND_ARG_INFO(0, y0)
  ZEND_ARG_INFO(0, x1)
  ZEND_ARG_INFO(0, y1)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoLinearGradient____construct_args NULL
#endif

PHP_METHOD(CairoLinearGradient, getLinearPoints);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoLinearGradient__get_linear_points_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoLinearGradient__get_linear_points_args NULL
#endif

PHP_METHOD(CairoRadialGradient, __constuct);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoRadialGradient____constuct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 6)
  ZEND_ARG_INFO(0, cx0)
  ZEND_ARG_INFO(0, cy0)
  ZEND_ARG_INFO(0, radius0)
  ZEND_ARG_INFO(0, cx1)
  ZEND_ARG_INFO(0, cy1)
  ZEND_ARG_INFO(0, radius1)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoRadialGradient____constuct_args NULL
#endif

PHP_METHOD(CairoRadialGradient, getRadialCircles);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoRadialGradient__get_radial_circles_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoRadialGradient__get_radial_circles_args NULL
#endif

PHP_METHOD(CairoSolidPattern, __construct);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoSolidPattern____construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, g)
  ZEND_ARG_INFO(0, b)
  ZEND_ARG_INFO(0, a)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoSolidPattern____construct_args NULL
#endif

PHP_METHOD(CairoSolidPattern, getRgba);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoSolidPattern__get_rgba_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoSolidPattern__get_rgba_args NULL
#endif

PHP_METHOD(CairoSurfacePattern, __construct);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoSurfacePattern____construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoSurfacePattern____construct_args NULL
#endif

PHP_METHOD(CairoPattern, getExtend);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoPattern__get_extend_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoPattern__get_extend_args NULL
#endif

PHP_METHOD(CairoSurfacePattern, getFilter);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoSurfacePattern__get_filter_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoSurfacePattern__get_filter_args NULL
#endif

PHP_METHOD(CairoSurfacePattern, getSurface);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoSurfacePattern__get_surface_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoSurfacePattern__get_surface_args NULL
#endif

PHP_METHOD(CairoPattern, setExtend);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoPattern__set_extend_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, extend)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoPattern__set_extend_args NULL
#endif

PHP_METHOD(CairoSurfacePattern, setFilter);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoSurfacePattern__set_filter_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, filter)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoSurfacePattern__set_filter_args NULL
#endif

PHP_METHOD(CairoScaledFont, __construct);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoScaledFont____construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 3)
  ZEND_ARG_OBJ_INFO(0, mx1, CairoMatrix, 1)
  ZEND_ARG_OBJ_INFO(0, mx2, CairoMatrix, 1)
  ZEND_ARG_OBJ_INFO(0, fo, CairoFontOptions, 1)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoScaledFont____construct_args NULL
#endif

PHP_METHOD(CairoScaledFont, extents);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoScaledFont__extents_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoScaledFont__extents_args NULL
#endif

PHP_METHOD(CairoScaledFont, getFontFace);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoScaledFont__get_font_face_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoScaledFont__get_font_face_args NULL
#endif

PHP_METHOD(CairoScaledFont, textExtents);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoScaledFont__text_extents_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, str)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoScaledFont__text_extents_args NULL
#endif

PHP_METHOD(CairoSurface, __construct);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoSurface____construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoSurface____construct_args NULL
#endif

PHP_METHOD(CairoSurface, createSimilar);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoSurface__create_similar_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 3)
  ZEND_ARG_INFO(0, content)
  ZEND_ARG_INFO(0, width)
  ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoSurface__create_similar_args NULL
#endif

PHP_METHOD(CairoSurface, finish);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoSurface__finish_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoSurface__finish_args NULL
#endif

PHP_METHOD(CairoSurface, flush);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoSurface__flush_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoSurface__flush_args NULL
#endif

PHP_METHOD(CairoSurface, getContent);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoSurface__get_content_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoSurface__get_content_args NULL
#endif

PHP_METHOD(CairoSurface, getDeviceOffset);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoSurface__get_device_offset_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoSurface__get_device_offset_args NULL
#endif

PHP_METHOD(CairoSurface, getFontOptions);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoSurface__get_font_options_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoSurface__get_font_options_args NULL
#endif

PHP_METHOD(CairoSurface, markDirtyRectangle);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoSurface__mark_dirty_rectangle_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
  ZEND_ARG_INFO(0, x)
  ZEND_ARG_INFO(0, y)
  ZEND_ARG_INFO(0, width)
  ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoSurface__mark_dirty_rectangle_args NULL
#endif

PHP_METHOD(CairoSurface, setDeviceOffset);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoSurface__set_device_offset_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, x_offset)
  ZEND_ARG_INFO(0, y_offset)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoSurface__set_device_offset_args NULL
#endif

PHP_METHOD(CairoSurface, setFallbackResolution);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoSurface__set_fallback_resolution_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, x_ppi)
  ZEND_ARG_INFO(0, y_ppi)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoSurface__set_fallback_resolution_args NULL
#endif

PHP_METHOD(CairoSurface, writeToPng);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoSurface__write_to_png_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, file)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoSurface__write_to_png_args NULL
#endif

PHP_METHOD(CairoSurface, writeToPngStream);
#if (PHP_MAJOR_VERSION >=5)
ZEND_BEGIN_ARG_INFO_EX(CairoSurface__write_to_png_stream_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, zstream)
ZEND_END_ARG_INFO()
#else
#define CairoSurface__write_to_png_stream_args NULL
#endif

PHP_METHOD(CairoImageSurface, __construct);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoImageSurface____construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, widthm)
  ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoImageSurface____construct_args NULL
#endif

PHP_METHOD(CairoImageSurface, createFromData);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoImageSurface__create_from_data_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 4)
  ZEND_ARG_INFO(0, obj)
  ZEND_ARG_INFO(0, format)
  ZEND_ARG_INFO(0, width)
  ZEND_ARG_INFO(0, height)
  ZEND_ARG_INFO(0, stride)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoImageSurface__create_from_data_args NULL
#endif

PHP_METHOD(CairoImageSurface, createFromPng);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoImageSurface__create_from_png_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, file)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoImageSurface__create_from_png_args NULL
#endif


PHP_METHOD(CairoImageSurface, createFromPngStream);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoImageSurface__create_from_png_stream_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
 ZEND_ARG_INFO(0, zstream)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoImageSurface__create_from_png_stream_args NULL
#endif
  
PHP_METHOD(CairoImageSurface, getData);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoImageSurface__get_data_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoImageSurface__get_data_args NULL
#endif

PHP_METHOD(CairoImageSurface, getFormat);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoImageSurface__get_format_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoImageSurface__get_format_args NULL
#endif

PHP_METHOD(CairoImageSurface, getHeight);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoImageSurface__get_height_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoImageSurface__get_height_args NULL
#endif

PHP_METHOD(CairoImageSurface, getStride);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoImageSurface__get_stride_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoImageSurface__get_stride_args NULL
#endif

PHP_METHOD(CairoImageSurface, getWidth);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoImageSurface__get_width_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoImageSurface__get_width_args NULL
#endif

PHP_METHOD(CairoPDFSurface, __construct);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoPDFSurface____construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, wpts)
  ZEND_ARG_INFO(0, hpts)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoPDFSurface____construct_args NULL
#endif

PHP_METHOD(CairoPDFSurface, setSize);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoPDFSurface__set_size_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, wpts)
  ZEND_ARG_INFO(0, hpts)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoPDFSurface__set_size_args NULL
#endif

PHP_METHOD(CairoPSSurface, __construct);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoPSSurface____construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, wpts)
  ZEND_ARG_INFO(0, hpts)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoPSSurface____construct_args NULL
#endif

PHP_METHOD(CairoPSSurface, dscBeginPageSetup);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoPSSurface__dsc_begin_page_setup_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoPSSurface__dsc_begin_page_setup_args NULL
#endif

PHP_METHOD(CairoPSSurface, dscBeginSetup);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoPSSurface__dsc_begin_setup_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoPSSurface__dsc_begin_setup_args NULL
#endif

PHP_METHOD(CairoPSSurface, dscComment);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoPSSurface__dsc_comment_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoPSSurface__dsc_comment_args NULL
#endif

PHP_METHOD(CairoPSSurface, getLevels);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoPSSurface__get_levels_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoPSSurface__get_levels_args NULL
#endif

PHP_METHOD(CairoPSSurface, getLevelString);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoPSSurface__get_level_string_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoPSSurface__get_level_string_args NULL
#endif

PHP_METHOD(CairoPSSurface, restrictToLevel);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoPSSurface__restrict_to_level_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, level)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoPSSurface__restrict_to_level_args NULL
#endif

PHP_METHOD(CairoPSSurface, setEps);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoPSSurface__set_eps_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoPSSurface__set_eps_args NULL
#endif

PHP_METHOD(CairoPSSurface, setSize);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoPSSurface__set_size_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, wpts)
  ZEND_ARG_INFO(0, hpts)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoPSSurface__set_size_args NULL
#endif

PHP_METHOD(CairoQuartzSurface, __construct);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoQuartzSurface____construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, hpixels)
  ZEND_ARG_INFO(0, format)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoQuartzSurface____construct_args NULL
#endif

PHP_METHOD(CairoSVGSurface, __construct);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoSVGSurface____construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, wpts)
  ZEND_ARG_INFO(0, hpts)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoSVGSurface____construct_args NULL
#endif

PHP_METHOD(CairoWin32Surface, __construct);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoWin32Surface____construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoWin32Surface____construct_args NULL
#endif

PHP_METHOD(CairoXlibSurface, __construct);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoXlibSurface____construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoXlibSurface____construct_args NULL
#endif

PHP_METHOD(CairoXlibSurface, getDepth);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoXlibSurface__get_depth_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoXlibSurface__get_depth_args NULL
#endif

PHP_METHOD(CairoXlibSurface, getHeight);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoXlibSurface__get_height_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoXlibSurface__get_height_args NULL
#endif

PHP_METHOD(CairoXlibSurface, getWidth);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(CairoXlibSurface__get_width_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define CairoXlibSurface__get_width_args NULL
#endif

#ifdef  __cplusplus
} // extern "C" 
#endif

#endif /* PHP_HAVE_CAIRO */

#endif /* PHP_CAIRO_H */

/* {{{ Proto's */

//zend_class_entry* get_CairoSurface_ce_ptr(cairo_surface_t *);
//zend_class_entry* get_CairoPattern_ce_ptr(cairo_pattern_t *);

/* }}} */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
