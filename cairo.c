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

#include "php_cairo.h"

#if HAVE_CAIRO

static cairo_status_t _cairo_write(void *closure, const unsigned char *data, unsigned int length) {
  PHPWRITE((const char *)data, length);
  return CAIRO_STATUS_SUCCESS;
}

static cairo_status_t _cairo_write_stream(void *stream, const unsigned char *data, unsigned int length) {
  if (length != php_stream_write((php_stream *)stream, (const char *)data, length)) {
	return CAIRO_STATUS_WRITE_ERROR;
  }

  return CAIRO_STATUS_SUCCESS;
}

static cairo_status_t _cairo_read_stream(void *stream, unsigned char *data, unsigned int length) {
  if (length != php_stream_read((php_stream *)stream, (char *)data, length)) {
	return CAIRO_STATUS_READ_ERROR;
  }

  return CAIRO_STATUS_SUCCESS;
}
void _cairo_close_stream(void *data)
{
  php_stream_close((php_stream *)data);
}
/* {{{ Resource destructors */
int le_cairo_surface;
void cairo_surface_dtor(zend_rsrc_list_entry *rsrc TSRMLS_DC)
{
	cairo_surface_t * resource = (cairo_surface_t *)(rsrc->ptr);

	do {
		cairo_surface_destroy(resource);   
	} while (0);
}

int le_cairo_context;
void cairo_context_dtor(zend_rsrc_list_entry *rsrc TSRMLS_DC)
{
	cairo_t * resource = (cairo_t *)(rsrc->ptr);

	do {
		cairo_destroy(resource);   
	} while (0);
}

int le_cairo_pattern;
void cairo_pattern_dtor(zend_rsrc_list_entry *rsrc TSRMLS_DC)
{
	cairo_pattern_t * resource = (cairo_pattern_t *)(rsrc->ptr);

	do {
		cairo_pattern_destroy(resource);   
	} while (0);
}

int le_cairo_path;
void cairo_path_dtor(zend_rsrc_list_entry *rsrc TSRMLS_DC)
{
	cairo_path_t * resource = (cairo_path_t *)(rsrc->ptr);

	do {
		cairo_path_destroy(resource);   
	} while (0);
}

int le_cairo_font_face;
void cairo_font_face_dtor(zend_rsrc_list_entry *rsrc TSRMLS_DC)
{
	cairo_font_face_t * resource = (cairo_font_face_t *)(rsrc->ptr);

	do {
		cairo_font_face_destroy(resource);   
	} while (0);
}

int le_cairo_scaled_font;
void cairo_scaled_font_dtor(zend_rsrc_list_entry *rsrc TSRMLS_DC)
{
	cairo_scaled_font_t * resource = (cairo_scaled_font_t *)(rsrc->ptr);

	do {
		cairo_scaled_font_destroy(resource);   
	} while (0);
}

int le_cairo_font_options;
void cairo_font_options_dtor(zend_rsrc_list_entry *rsrc TSRMLS_DC)
{
	cairo_font_options_t * resource = (cairo_font_options_t *)(rsrc->ptr);

	do {
		cairo_font_options_destroy(resource);   
	} while (0);
}

int le_cairo_matrix;
void cairo_matrix_dtor(zend_rsrc_list_entry *rsrc TSRMLS_DC)
{
	cairo_matrix_t * resource = (cairo_matrix_t *)(rsrc->ptr);

	do {
	} while (0);

	efree(resource);
}

/* }}} *

/* {{{ cairo_functions[] */
function_entry cairo_functions[] = {
	PHP_FE(cairo_image_surface_create, cairo_image_surface_create_arg_info)
	PHP_FE(cairo_surface_destroy, cairo_surface_destroy_arg_info)
	PHP_FE(cairo_create        , cairo_create_arg_info)
	PHP_FE(cairo_destroy       , cairo_destroy_arg_info)
	PHP_FE(cairo_pattern_create_linear, cairo_pattern_create_linear_arg_info)
	PHP_FE(cairo_pattern_create_radial, cairo_pattern_create_radial_arg_info)
	PHP_FE(cairo_pattern_create_for_surface, cairo_pattern_create_for_surface_arg_info)
	PHP_FE(cairo_pattern_create_rgb, cairo_pattern_create_rgb_arg_info)
	PHP_FE(cairo_pattern_create_rgba, cairo_pattern_create_rgba_arg_info)
	PHP_FE(cairo_pattern_destroy, cairo_pattern_destroy_arg_info)
	PHP_FE(cairo_path_destroy  , cairo_path_destroy_arg_info)
	PHP_FE(cairo_select_font_face, cairo_select_font_face_arg_info)
	PHP_FE(cairo_set_font_size , cairo_set_font_size_arg_info)
	PHP_FE(cairo_set_source_rgb, cairo_set_source_rgb_arg_info)
	PHP_FE(cairo_set_source_rgba, cairo_set_source_rgba_arg_info)
	PHP_FE(cairo_move_to       , cairo_move_to_arg_info)
	PHP_FE(cairo_rel_move_to   , cairo_rel_move_to_arg_info)
	PHP_FE(cairo_show_text     , cairo_show_text_arg_info)
#if CAIRO_HAS_PNG_FUNCTIONS
	PHP_FE(cairo_surface_show_png, cairo_surface_show_png_arg_info)
#endif /* CAIRO_HAS_PNG_FUNCTIONS */
#if CAIRO_HAS_PNG_FUNCTIONS
	PHP_FE(cairo_surface_write_to_png, cairo_surface_write_to_png_arg_info)
#endif /* CAIRO_HAS_PNG_FUNCTIONS */
#if CAIRO_HAS_PNG_FUNCTIONS
	PHP_FE(cairo_image_surface_create_from_png, cairo_image_surface_create_from_png_arg_info)
#endif /* CAIRO_HAS_PNG_FUNCTIONS */
#if CAIRO_HAS_PDF_SURFACE
	PHP_FE(cairo_pdf_surface_create, cairo_pdf_surface_create_arg_info)
#endif /* CAIRO_HAS_PDF_SURFACE */
#if CAIRO_HAS_PDF_SURFACE
	PHP_FE(cairo_pdf_surface_set_size, cairo_pdf_surface_set_size_arg_info)
#endif /* CAIRO_HAS_PDF_SURFACE */
#if CAIRO_HAS_PS_SURFACE
	PHP_FE(cairo_ps_surface_create, cairo_ps_surface_create_arg_info)
#endif /* CAIRO_HAS_PS_SURFACE */
#if CAIRO_HAS_PS_SURFACE
	PHP_FE(cairo_ps_surface_set_size, cairo_ps_surface_set_size_arg_info)
#endif /* CAIRO_HAS_PS_SURFACE */
#if CAIRO_HAS_PS_SURFACE
	PHP_FE(cairo_ps_surface_dsc_begin_setup, cairo_ps_surface_dsc_begin_setup_arg_info)
#endif /* CAIRO_HAS_PS_SURFACE */
#if CAIRO_HAS_PS_SURFACE
	PHP_FE(cairo_ps_surface_dsc_begin_page_setup, cairo_ps_surface_dsc_begin_page_setup_arg_info)
#endif /* CAIRO_HAS_PS_SURFACE */
#if CAIRO_HAS_PS_SURFACE
	PHP_FE(cairo_ps_surface_dsc_comment, cairo_ps_surface_dsc_comment_arg_info)
#endif /* CAIRO_HAS_PS_SURFACE */
	PHP_FE(cairo_stroke        , cairo_stroke_arg_info)
	PHP_FE(cairo_stroke_preserve, cairo_stroke_preserve_arg_info)
	PHP_FE(cairo_arc           , cairo_arc_arg_info)
	PHP_FE(cairo_arc_negative  , cairo_arc_negative_arg_info)
	PHP_FE(cairo_fill          , cairo_fill_arg_info)
	PHP_FE(cairo_fill_preserve , cairo_fill_preserve_arg_info)
	PHP_FE(cairo_set_line_width, cairo_set_line_width_arg_info)
	PHP_FE(cairo_get_line_width, cairo_get_line_width_arg_info)
	PHP_FE(cairo_line_to       , cairo_line_to_arg_info)
	PHP_FE(cairo_rel_line_to   , cairo_rel_line_to_arg_info)
	PHP_FE(cairo_pattern_add_color_stop_rgb, cairo_pattern_add_color_stop_rgb_arg_info)
	PHP_FE(cairo_pattern_add_color_stop_rgba, cairo_pattern_add_color_stop_rgba_arg_info)
	PHP_FE(cairo_rectangle     , cairo_rectangle_arg_info)
	PHP_FE(cairo_set_source    , cairo_set_source_arg_info)
	PHP_FE(cairo_scale         , cairo_scale_arg_info)
	PHP_FE(cairo_version       , cairo_version_arg_info)
	PHP_FE(cairo_version_string, cairo_version_string_arg_info)
	PHP_FE(cairo_save          , cairo_save_arg_info)
	PHP_FE(cairo_restore       , cairo_restore_arg_info)
	PHP_FE(cairo_status        , cairo_status_arg_info)
	PHP_FE(cairo_pattern_status, cairo_pattern_status_arg_info)
	PHP_FE(cairo_status_to_string, cairo_status_to_string_arg_info)
	PHP_FE(cairo_push_group    , cairo_push_group_arg_info)
	PHP_FE(cairo_pop_group     , cairo_pop_group_arg_info)
	PHP_FE(cairo_pop_group_to_source, cairo_pop_group_to_source_arg_info)
	PHP_FE(cairo_rotate        , cairo_rotate_arg_info)
	PHP_FE(cairo_translate     , cairo_translate_arg_info)
	PHP_FE(cairo_curve_to      , cairo_curve_to_arg_info)
	PHP_FE(cairo_rel_curve_to  , cairo_rel_curve_to_arg_info)
	PHP_FE(cairo_close_path    , cairo_close_path_arg_info)
	PHP_FE(cairo_set_antialias , cairo_set_antialias_arg_info)
	PHP_FE(cairo_get_antialias , cairo_get_antialias_arg_info)
	PHP_FE(cairo_set_fill_rule , cairo_set_fill_rule_arg_info)
	PHP_FE(cairo_get_fill_rule , cairo_get_fill_rule_arg_info)
	PHP_FE(cairo_set_line_cap  , cairo_set_line_cap_arg_info)
	PHP_FE(cairo_get_line_cap  , cairo_get_line_cap_arg_info)
	PHP_FE(cairo_set_line_join , cairo_set_line_join_arg_info)
	PHP_FE(cairo_get_line_join , cairo_get_line_join_arg_info)
	PHP_FE(cairo_set_tolerance , cairo_set_tolerance_arg_info)
	PHP_FE(cairo_get_tolerance , cairo_get_tolerance_arg_info)
	PHP_FE(cairo_set_miter_limit, cairo_set_miter_limit_arg_info)
	PHP_FE(cairo_get_miter_limit, cairo_get_miter_limit_arg_info)
	PHP_FE(cairo_set_operator  , cairo_set_operator_arg_info)
	PHP_FE(cairo_get_operator  , cairo_get_operator_arg_info)
	PHP_FE(cairo_paint         , cairo_paint_arg_info)
	PHP_FE(cairo_paint_with_alpha, cairo_paint_with_alpha_arg_info)
	PHP_FE(cairo_surface_flush , cairo_surface_flush_arg_info)
	PHP_FE(cairo_clip          , cairo_clip_arg_info)
	PHP_FE(cairo_clip_preserve , cairo_clip_preserve_arg_info)
	PHP_FE(cairo_reset_clip    , cairo_reset_clip_arg_info)
	PHP_FE(cairo_image_surface_get_height, cairo_image_surface_get_height_arg_info)
	PHP_FE(cairo_image_surface_get_width, cairo_image_surface_get_width_arg_info)
	PHP_FE(cairo_surface_status, cairo_surface_status_arg_info)
	PHP_FE(cairo_in_fill       , cairo_in_fill_arg_info)
	PHP_FE(cairo_in_stroke     , cairo_in_stroke_arg_info)
	PHP_FE(cairo_new_path      , cairo_new_path_arg_info)
	PHP_FE(cairo_new_sub_path  , cairo_new_sub_path_arg_info)
	PHP_FE(cairo_image_surface_get_type, cairo_image_surface_get_type_arg_info)
	PHP_FE(cairo_image_surface_get_format, cairo_image_surface_get_format_arg_info)
	PHP_FE(cairo_pattern_set_extend, cairo_pattern_set_extend_arg_info)
	PHP_FE(cairo_copy_page     , cairo_copy_page_arg_info)
	PHP_FE(cairo_show_page     , cairo_show_page_arg_info)
	PHP_FE(cairo_copy_path     , cairo_copy_path_arg_info)
	PHP_FE(cairo_copy_path_flat, cairo_copy_path_flat_arg_info)
	PHP_FE(cairo_append_path   , cairo_append_path_arg_info)
	PHP_FE(cairo_get_source    , cairo_get_source_arg_info)
	PHP_FE(cairo_mask          , cairo_mask_arg_info)
	PHP_FE(cairo_mask_surface  , cairo_mask_surface_arg_info)
	PHP_FE(cairo_pattern_get_extend, cairo_pattern_get_extend_arg_info)
	PHP_FE(cairo_pattern_get_filter, cairo_pattern_get_filter_arg_info)
	PHP_FE(cairo_pattern_get_pattern_type, cairo_pattern_get_pattern_type_arg_info)
	PHP_FE(cairo_surface_mark_dirty, cairo_surface_mark_dirty_arg_info)
	PHP_FE(cairo_surface_mark_dirty_rectangle, cairo_surface_mark_dirty_rectangle_arg_info)
	PHP_FE(cairo_surface_set_fallback_resolution, cairo_surface_set_fallback_resolution_arg_info)
	PHP_FE(cairo_surface_set_device_offset, cairo_surface_set_device_offset_arg_info)
	PHP_FE(cairo_set_source_surface, cairo_set_source_surface_arg_info)
#if CAIRO_HAS_SVG_SURFACE
	PHP_FE(cairo_svg_surface_create, cairo_svg_surface_create_arg_info)
#endif /* CAIRO_HAS_SVG_SURFACE */
#if CAIRO_HAS_SVG_SURFACE
	PHP_FE(cairo_svg_surface_restrict_to_version, cairo_svg_surface_restrict_to_version_arg_info)
#endif /* CAIRO_HAS_SVG_SURFACE */
#if CAIRO_HAS_SVG_SURFACE
	PHP_FE(cairo_svg_version_to_string, cairo_svg_version_to_string_arg_info)
#endif /* CAIRO_HAS_SVG_SURFACE */
	PHP_FE(cairo_text_path     , cairo_text_path_arg_info)
	PHP_FE(cairo_get_font_face , cairo_get_font_face_arg_info)
	PHP_FE(cairo_font_face_destroy, cairo_font_face_destroy_arg_info)
	PHP_FE(cairo_font_face_get_type, cairo_font_face_get_type_arg_info)
	PHP_FE(cairo_font_face_status, cairo_font_face_status_arg_info)
	PHP_FE(cairo_set_font_face , cairo_set_font_face_arg_info)
	PHP_FE(cairo_font_options_create, cairo_font_options_create_arg_info)
	PHP_FE(cairo_font_options_copy, cairo_font_options_copy_arg_info)
	PHP_FE(cairo_font_options_destroy, cairo_font_options_destroy_arg_info)
	PHP_FE(cairo_set_font_options, cairo_set_font_options_arg_info)
	PHP_FE(cairo_font_options_set_antialias, cairo_font_options_set_antialias_arg_info)
	PHP_FE(cairo_font_options_set_hint_metrics, cairo_font_options_set_hint_metrics_arg_info)
	PHP_FE(cairo_font_options_set_hint_style, cairo_font_options_set_hint_style_arg_info)
	PHP_FE(cairo_font_options_set_subpixel_order, cairo_font_options_set_subpixel_order_arg_info)
	PHP_FE(cairo_font_options_get_antialias, cairo_font_options_get_antialias_arg_info)
	PHP_FE(cairo_font_options_get_hint_metrics, cairo_font_options_get_hint_metrics_arg_info)
	PHP_FE(cairo_font_options_get_hint_style, cairo_font_options_get_hint_style_arg_info)
	PHP_FE(cairo_font_options_get_subpixel_order, cairo_font_options_get_subpixel_order_arg_info)
	PHP_FE(cairo_font_options_equal, cairo_font_options_equal_arg_info)
	PHP_FE(cairo_font_options_merge, cairo_font_options_merge_arg_info)
	PHP_FE(cairo_font_options_status, cairo_font_options_status_arg_info)
	PHP_FE(cairo_get_font_options, cairo_get_font_options_arg_info)
	PHP_FE(cairo_surface_get_font_options, cairo_surface_get_font_options_arg_info)
	PHP_FE(cairo_path_to_array , cairo_path_to_array_arg_info)
	PHP_FE(cairo_marix_destroy , cairo_marix_destroy_arg_info)
	PHP_FE(cairo_get_matrix    , cairo_get_matrix_arg_info)
	PHP_FE(cairo_set_matrix    , cairo_set_matrix_arg_info)
	PHP_FE(cairo_identity_matrix, cairo_identity_matrix_arg_info)
	PHP_FE(cairo_matrix_invert , cairo_matrix_invert_arg_info)
	PHP_FE(cairo_matrix_create , cairo_matrix_create_arg_info)
	PHP_FE(cairo_matrix_create_identity, cairo_matrix_create_identity_arg_info)
	PHP_FE(cairo_matrix_create_rotate, cairo_matrix_create_rotate_arg_info)
	PHP_FE(cairo_matrix_create_translate, cairo_matrix_create_translate_arg_info)
	PHP_FE(cairo_matrix_create_scale, cairo_matrix_create_scale_arg_info)
	PHP_FE(cairo_matrix_multiply, cairo_matrix_multiply_arg_info)
	PHP_FE(cairo_matrix_rotate , cairo_matrix_rotate_arg_info)
	PHP_FE(cairo_matrix_translate, cairo_matrix_translate_arg_info)
	PHP_FE(cairo_matrix_scale  , cairo_matrix_scale_arg_info)
	PHP_FE(cairo_transform     , cairo_transform_arg_info)
	PHP_FE(cairo_pattern_get_matrix, cairo_pattern_get_matrix_arg_info)
	PHP_FE(cairo_pattern_set_matrix, cairo_pattern_set_matrix_arg_info)
	PHP_FE(cairo_get_font_matrix, cairo_get_font_matrix_arg_info)
	PHP_FE(cairo_set_font_matrix, cairo_set_font_matrix_arg_info)
	PHP_FE(cairo_scaled_font_destroy, cairo_scaled_font_destroy_arg_info)
	PHP_FE(cairo_scaled_font_create, cairo_scaled_font_create_arg_info)
	PHP_FE(cairo_scaled_font_get_type, cairo_scaled_font_get_type_arg_info)
	PHP_FE(cairo_scaled_font_status, cairo_scaled_font_status_arg_info)
	PHP_FE(cairo_scaled_font_get_font_matrix, cairo_scaled_font_get_font_matrix_arg_info)
	PHP_FE(cairo_scaled_font_get_ctm, cairo_scaled_font_get_ctm_arg_info)
	PHP_FE(cairo_scaled_font_get_font_options, cairo_scaled_font_get_font_options_arg_info)
	PHP_FE(cairo_scaled_font_get_font_face, cairo_scaled_font_get_font_face_arg_info)
	PHP_FE(cairo_set_scaled_font, cairo_set_scaled_font_arg_info)
	PHP_FE(cairo_surface_get_scaled_font_options, cairo_surface_get_scaled_font_options_arg_info)
	PHP_FE(cairo_svg_get_versions, cairo_svg_get_versions_arg_info)
	PHP_FE(cairo_get_current_point, cairo_get_current_point_arg_info)
	PHP_FE(cairo_matrix_transform_point, cairo_matrix_transform_point_arg_info)
	PHP_FE(cairo_matrix_transform_distance, cairo_matrix_transform_distance_arg_info)
	PHP_FE(cairo_device_to_user, cairo_device_to_user_arg_info)
	PHP_FE(cairo_device_to_user_distance, cairo_device_to_user_distance_arg_info)
	PHP_FE(cairo_user_to_device, cairo_user_to_device_arg_info)
	PHP_FE(cairo_user_to_device_distance, cairo_user_to_device_distance_arg_info)
	PHP_FE(cairo_surface_get_device_offset, cairo_surface_get_device_offset_arg_info)
	PHP_FE(cairo_fill_extents  , cairo_fill_extents_arg_info)
	PHP_FE(cairo_stroke_extents, cairo_stroke_extents_arg_info)
	PHP_FE(cairo_text_extends  , cairo_text_extends_arg_info)
	PHP_FE(cairo_surface_get_content, cairo_surface_get_content_arg_info)
	PHP_FE(cairo_pattern_set_filter, cairo_pattern_set_filter_arg_info)
	PHP_FE(cairo_push_group_with_content, cairo_push_group_with_content_arg_info)
	PHP_FE(cairo_surface_create_similar, cairo_surface_create_similar_arg_info)
	PHP_FE(cairo_set_dash      , cairo_set_dash_arg_info)
	PHP_FE(cairo_font_extents  , cairo_font_extents_arg_info)
	PHP_FE(cairo_scaled_font_extents, cairo_scaled_font_extents_arg_info)
	PHP_FE(cairo_scaled_font_text_extends, cairo_scaled_font_text_extends_arg_info)
	{ NULL, NULL, NULL }
};
/* }}} */


/* {{{ cairo_module_entry
 */
zend_module_entry cairo_module_entry = {
	STANDARD_MODULE_HEADER,
	"cairo",
	cairo_functions,
	PHP_MINIT(cairo),     /* Replace with NULL if there is nothing to do at php startup   */ 
	PHP_MSHUTDOWN(cairo), /* Replace with NULL if there is nothing to do at php shutdown  */
	PHP_RINIT(cairo),     /* Replace with NULL if there is nothing to do at request start */
	PHP_RSHUTDOWN(cairo), /* Replace with NULL if there is nothing to do at request end   */
	PHP_MINFO(cairo),
	"0.2.2", 
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_CAIRO
ZEND_GET_MODULE(cairo)
#endif


/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(cairo)
{
	REGISTER_LONG_CONSTANT("CAIRO_STATUS_SUCCESS", CAIRO_STATUS_SUCCESS, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_STATUS_NO_MEMORY", CAIRO_STATUS_NO_MEMORY, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_STATUS_INVALID_RESTORE", CAIRO_STATUS_INVALID_RESTORE, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_STATUS_INVALID_POP_GROUP", CAIRO_STATUS_INVALID_POP_GROUP, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_STATUS_NO_CURRENT_POINT", CAIRO_STATUS_NO_CURRENT_POINT, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_STATUS_INVALID_MATRIX", CAIRO_STATUS_INVALID_MATRIX, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_STATUS_INVALID_STATUS", CAIRO_STATUS_INVALID_STATUS, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_STATUS_NULL_POINTER", CAIRO_STATUS_NULL_POINTER, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_STATUS_INVALID_STRING", CAIRO_STATUS_INVALID_STRING, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_STATUS_INVALID_PATH_DATA", CAIRO_STATUS_INVALID_PATH_DATA, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_STATUS_READ_ERROR", CAIRO_STATUS_READ_ERROR, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_STATUS_WRITE_ERROR", CAIRO_STATUS_WRITE_ERROR, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_STATUS_SURFACE_FINISHED", CAIRO_STATUS_SURFACE_FINISHED, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_STATUS_SURFACE_TYPE_MISMATCH", CAIRO_STATUS_SURFACE_TYPE_MISMATCH, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_STATUS_PATTERN_TYPE_MISMATCH", CAIRO_STATUS_PATTERN_TYPE_MISMATCH, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_STATUS_INVALID_CONTENT", CAIRO_STATUS_INVALID_CONTENT, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_STATUS_INVALID_FORMAT", CAIRO_STATUS_INVALID_FORMAT, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_STATUS_INVALID_VISUAL", CAIRO_STATUS_INVALID_VISUAL, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_STATUS_FILE_NOT_FOUND", CAIRO_STATUS_FILE_NOT_FOUND, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_STATUS_INVALID_DASH", CAIRO_STATUS_INVALID_DASH, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_STATUS_INVALID_DSC_COMMENT", CAIRO_STATUS_INVALID_DSC_COMMENT, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_CONTENT_COLOR", CAIRO_CONTENT_COLOR, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_CONTENT_ALPHA", CAIRO_CONTENT_ALPHA, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_CONTENT_COLOR_ALPHA", CAIRO_CONTENT_COLOR_ALPHA, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_OPERATOR_CLEAR", CAIRO_OPERATOR_CLEAR, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_OPERATOR_SOURCE", CAIRO_OPERATOR_SOURCE, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_OPERATOR_OVER", CAIRO_OPERATOR_OVER, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_OPERATOR_IN", CAIRO_OPERATOR_IN, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_OPERATOR_OUT", CAIRO_OPERATOR_OUT, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_OPERATOR_ATOP", CAIRO_OPERATOR_ATOP, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_OPERATOR_DEST", CAIRO_OPERATOR_DEST, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_OPERATOR_DEST_OVER", CAIRO_OPERATOR_DEST_OVER, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_OPERATOR_DEST_IN", CAIRO_OPERATOR_DEST_IN, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_OPERATOR_DEST_OUT", CAIRO_OPERATOR_DEST_OUT, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_OPERATOR_DEST_ATOP", CAIRO_OPERATOR_DEST_ATOP, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_OPERATOR_XOR", CAIRO_OPERATOR_XOR, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_OPERATOR_ADD", CAIRO_OPERATOR_ADD, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_OPERATOR_SATURATE", CAIRO_OPERATOR_SATURATE, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_ANTIALIAS_DEFAULT", CAIRO_ANTIALIAS_DEFAULT, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_ANTIALIAS_NONE", CAIRO_ANTIALIAS_NONE, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_ANTIALIAS_GRAY", CAIRO_ANTIALIAS_GRAY, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_ANTIALIAS_SUBPIXEL", CAIRO_ANTIALIAS_SUBPIXEL, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_FILL_RULE_WINDING", CAIRO_FILL_RULE_WINDING, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_FILL_RULE_EVEN_ODD", CAIRO_FILL_RULE_EVEN_ODD, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_LINE_CAP_BUTT", CAIRO_LINE_CAP_BUTT, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_LINE_CAP_ROUND", CAIRO_LINE_CAP_ROUND, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_LINE_CAP_SQUARE", CAIRO_LINE_CAP_SQUARE, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_LINE_JOIN_MITER", CAIRO_LINE_JOIN_MITER, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_LINE_JOIN_ROUND", CAIRO_LINE_JOIN_ROUND, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_LINE_JOIN_BEVEL", CAIRO_LINE_JOIN_BEVEL, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_FONT_SLANT_NORMAL", CAIRO_FONT_SLANT_NORMAL, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_FONT_SLANT_ITALIC", CAIRO_FONT_SLANT_ITALIC, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_FONT_SLANT_OBLIQUE", CAIRO_FONT_SLANT_OBLIQUE, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_FONT_WEIGHT_NORMAL", CAIRO_FONT_WEIGHT_NORMAL, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_FONT_WEIGHT_BOLD", CAIRO_FONT_WEIGHT_BOLD, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_SUBPIXEL_ORDER_DEFAULT", CAIRO_SUBPIXEL_ORDER_DEFAULT, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_SUBPIXEL_ORDER_RGB", CAIRO_SUBPIXEL_ORDER_RGB, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_SUBPIXEL_ORDER_BGR", CAIRO_SUBPIXEL_ORDER_BGR, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_SUBPIXEL_ORDER_VRGB", CAIRO_SUBPIXEL_ORDER_VRGB, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_SUBPIXEL_ORDER_VBGR", CAIRO_SUBPIXEL_ORDER_VBGR, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_HINT_STYLE_DEFAULT", CAIRO_HINT_STYLE_DEFAULT, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_HINT_STYLE_NONE", CAIRO_HINT_STYLE_NONE, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_HINT_STYLE_SLIGHT", CAIRO_HINT_STYLE_SLIGHT, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_HINT_STYLE_MEDIUM", CAIRO_HINT_STYLE_MEDIUM, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_HINT_STYLE_FULL", CAIRO_HINT_STYLE_FULL, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_HINT_METRICS_DEFAULT", CAIRO_HINT_METRICS_DEFAULT, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_HINT_METRICS_OFF", CAIRO_HINT_METRICS_OFF, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_HINT_METRICS_ON", CAIRO_HINT_METRICS_ON, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_FONT_TYPE_TOY", CAIRO_FONT_TYPE_TOY, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_FONT_TYPE_FT", CAIRO_FONT_TYPE_FT, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_FONT_TYPE_WIN32", CAIRO_FONT_TYPE_WIN32, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_FONT_TYPE_ATSUI", CAIRO_FONT_TYPE_ATSUI, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_PATH_MOVE_TO", CAIRO_PATH_MOVE_TO, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_PATH_LINE_TO", CAIRO_PATH_LINE_TO, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_PATH_CURVE_TO", CAIRO_PATH_CURVE_TO, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_PATH_CLOSE_PATH", CAIRO_PATH_CLOSE_PATH, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_SURFACE_TYPE_IMAGE", CAIRO_SURFACE_TYPE_IMAGE, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_SURFACE_TYPE_PDF", CAIRO_SURFACE_TYPE_PDF, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_SURFACE_TYPE_PS", CAIRO_SURFACE_TYPE_PS, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_SURFACE_TYPE_XLIB", CAIRO_SURFACE_TYPE_XLIB, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_SURFACE_TYPE_XCB", CAIRO_SURFACE_TYPE_XCB, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_SURFACE_TYPE_GLITZ", CAIRO_SURFACE_TYPE_GLITZ, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_SURFACE_TYPE_QUARTZ", CAIRO_SURFACE_TYPE_QUARTZ, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_SURFACE_TYPE_WIN32", CAIRO_SURFACE_TYPE_WIN32, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_SURFACE_TYPE_BEOS", CAIRO_SURFACE_TYPE_BEOS, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_SURFACE_TYPE_DIRECTFB", CAIRO_SURFACE_TYPE_DIRECTFB, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_SURFACE_TYPE_SVG", CAIRO_SURFACE_TYPE_SVG, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_FORMAT_ARGB32", CAIRO_FORMAT_ARGB32, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_FORMAT_RGB24", CAIRO_FORMAT_RGB24, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_FORMAT_A8", CAIRO_FORMAT_A8, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_FORMAT_A1", CAIRO_FORMAT_A1, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_FORMAT_RGB16_565", CAIRO_FORMAT_RGB16_565, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_PATTERN_TYPE_SOLID", CAIRO_PATTERN_TYPE_SOLID, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_PATTERN_TYPE_SURFACE", CAIRO_PATTERN_TYPE_SURFACE, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_PATTERN_TYPE_LINEAR", CAIRO_PATTERN_TYPE_LINEAR, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_PATTERN_TYPE_RADIAL", CAIRO_PATTERN_TYPE_RADIAL, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_EXTEND_NONE", CAIRO_EXTEND_NONE, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_EXTEND_REPEAT", CAIRO_EXTEND_REPEAT, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_EXTEND_REFLECT", CAIRO_EXTEND_REFLECT, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_EXTEND_PAD", CAIRO_EXTEND_PAD, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_FILTER_FAST", CAIRO_FILTER_FAST, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_FILTER_GOOD", CAIRO_FILTER_GOOD, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_FILTER_BEST", CAIRO_FILTER_BEST, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_FILTER_NEAREST", CAIRO_FILTER_NEAREST, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_FILTER_BILINEAR", CAIRO_FILTER_BILINEAR, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_FILTER_GAUSSIAN", CAIRO_FILTER_GAUSSIAN, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_SVG_VERSION_1_1", CAIRO_SVG_VERSION_1_1, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("CAIRO_SVG_VERSION_1_2", CAIRO_SVG_VERSION_1_2, CONST_PERSISTENT | CONST_CS);
	le_cairo_surface = zend_register_list_destructors_ex(cairo_surface_dtor, 
						   NULL, "cairo_surface", module_number);
	le_cairo_context = zend_register_list_destructors_ex(cairo_context_dtor, 
						   NULL, "cairo_context", module_number);
	le_cairo_pattern = zend_register_list_destructors_ex(cairo_pattern_dtor, 
						   NULL, "cairo_pattern", module_number);
	le_cairo_path = zend_register_list_destructors_ex(cairo_path_dtor, 
						   NULL, "cairo_path", module_number);
	le_cairo_font_face = zend_register_list_destructors_ex(cairo_font_face_dtor, 
						   NULL, "cairo_font_face", module_number);
	le_cairo_scaled_font = zend_register_list_destructors_ex(cairo_scaled_font_dtor, 
						   NULL, "cairo_scaled_font", module_number);
	le_cairo_font_options = zend_register_list_destructors_ex(cairo_font_options_dtor, 
						   NULL, "cairo_font_options", module_number);
	le_cairo_matrix = zend_register_list_destructors_ex(cairo_matrix_dtor, 
						   NULL, "cairo_matrix", module_number);

	/* add your stuff here */

	return SUCCESS;
}
/* }}} */


/* {{{ PHP_MSHUTDOWN_FUNCTION */
PHP_MSHUTDOWN_FUNCTION(cairo)
{

	/* add your stuff here */

	return SUCCESS;
}
/* }}} */


/* {{{ PHP_RINIT_FUNCTION */
PHP_RINIT_FUNCTION(cairo)
{
	/* add your stuff here */

	return SUCCESS;
}
/* }}} */


/* {{{ PHP_RSHUTDOWN_FUNCTION */
PHP_RSHUTDOWN_FUNCTION(cairo)
{
	/* add your stuff here */

	return SUCCESS;
}
/* }}} */


/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(cairo)
{
	php_info_print_box_start(0);
	php_printf("<p>Cairo Wrapper Extension</p>\n");
	php_printf("<p>Version 0.2.2beta (2006-09-27)</p>\n");
	php_printf("<p><b>Authors:</b></p>\n");
	php_printf("<p>Hartmut Holzgraefe &lt;hartmut@php.net&gt; (lead)</p>\n");
	php_info_print_box_end();
	do {
		php_info_print_table_start();
		php_info_print_table_header(2, "Cairo Wrapper", "enabled");
		php_info_print_table_row(2, "Cairo Version", CAIRO_VERSION_STRING);
#if CAIRO_HAS_PNG_FUNCTIONS
		php_info_print_table_row(2, "PNG backend", "yes");
#else 
		php_info_print_table_row(2, "PNG backend", "no");
#endif
#if CAIRO_HAS_SVG_SURFACE
		php_info_print_table_row(2, "SVG backend", "yes");
#else 
		php_info_print_table_row(2, "SVG backend", "no");
#endif
#if CAIRO_HAS_QUARTZ_SURFACE
		php_info_print_table_row(2, "Quartz backend", "yes");
#else 
		php_info_print_table_row(2, "Quartz backend", "no");
#endif
#if CAIRO_HAS_XCB_SURFACE
		php_info_print_table_row(2, "XCB backend", "yes");
#else 
		php_info_print_table_row(2, "XCB backend", "no");
#endif
#if CAIRO_HAS_WIN32_SURFACE
		php_info_print_table_row(2, "Win32 backend", "yes");
#else 
		php_info_print_table_row(2, "Win32 backend", "no");
#endif
#if CAIRO_HAS_PDF_SURFACE
		php_info_print_table_row(2, "PDF backend", "yes");
#else 
		php_info_print_table_row(2, "PDF backend", "no");
#endif
#if CAIRO_HAS_PS_SURFACE
		php_info_print_table_row(2, "PS backend", "yes");
#else 
		php_info_print_table_row(2, "PS backend", "no");
#endif
#if CAIRO_HAS_XLIB_SURFACE
		php_info_print_table_row(2, "Xlib backend", "yes");
#else 
		php_info_print_table_row(2, "Xlib backend", "no");
#endif
#if CAIRO_HAS_XLIB_RENDER_SURFACE
		php_info_print_table_row(2, "Xlib render backend", "yes");
#else 
		php_info_print_table_row(2, "Xlib render backend", "no");
#endif
#if CAIRO_HAS_BEOS_SURFACE
		php_info_print_table_row(2, "BeOS backend", "yes");
#else 
		php_info_print_table_row(2, "BeOS backend", "no");
#endif
#if CAIRO_HAS_GLITZ_SURFACE
		php_info_print_table_row(2, "Glitz backend", "yes");
#else 
		php_info_print_table_row(2, "Glitz backend", "no");
#endif
#if CAIRO_HAS_DIRECTFB_SURFACE
		php_info_print_table_row(2, "FrameBuffer backend", "yes");
#else 
		php_info_print_table_row(2, "FrameBuffer backend", "no");
#endif
#if CAIRO_HAS_FT_FONT
		php_info_print_table_row(2, "freetype font support", "yes");
#else 
		php_info_print_table_row(2, "freetype font support", "no");
#endif
#if CAIRO_HAS_WIN32_FONT
		php_info_print_table_row(2, "Win32 font support", "yes");
#else 
		php_info_print_table_row(2, "Win32 font support", "no");
#endif
#if CAIRO_HAS_ATSUI_FONT
		php_info_print_table_row(2, "ATSUI font support", "yes");
#else 
		php_info_print_table_row(2, "ATSUI font support", "no");
#endif

		php_info_print_table_end();
	} while (0);

}
/* }}} */


/* {{{ proto resource cairo_surface cairo_image_surface_create(int format, int x, int y)
  Create new bitmap surface resource */
PHP_FUNCTION(cairo_image_surface_create)
{
	cairo_surface_t * return_res;
	long return_res_id = -1;
	long format = 0;
	long x = 0;
	long y = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lll", &format, &x, &y) == FAILURE) {
		return;
	}
	do {
		return_res = cairo_image_surface_create(format, x, y);
	} while (0);
	return_res_id = ZEND_REGISTER_RESOURCE(return_value, return_res, le_cairo_surface);
}
/* }}} cairo_image_surface_create */


/* {{{ proto void cairo_surface_destroy(resource cairo_surface surface)
  Destroy surface resource */
PHP_FUNCTION(cairo_surface_destroy)
{
	zval * surface_res = NULL;
	int surface_resid = -1;
	cairo_surface_t * surface;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &surface_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(surface, cairo_surface_t *, &surface_res, surface_resid, "cairo_surface", le_cairo_surface);


	do {
		FREE_RESOURCE(surface_res);
	} while (0);
}
/* }}} cairo_surface_destroy */


/* {{{ proto resource cairo_context cairo_create(resource cairo_surface surface)
  Create new drawing context resource */
PHP_FUNCTION(cairo_create)
{
	cairo_t * return_res;
	long return_res_id = -1;
	zval * surface_res = NULL;
	int surface_resid = -1;
	cairo_surface_t * surface;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &surface_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(surface, cairo_surface_t *, &surface_res, surface_resid, "cairo_surface", le_cairo_surface);


	do {
		return_res = cairo_create(surface);
	} while (0);
	return_res_id = ZEND_REGISTER_RESOURCE(return_value, return_res, le_cairo_context);
}
/* }}} cairo_create */


/* {{{ proto void cairo_destroy(resource cairo_context cr)
  Destroy drawing context resource */
PHP_FUNCTION(cairo_destroy)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &cr_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		FREE_RESOURCE(cr_res);
	} while (0);
}
/* }}} cairo_destroy */


/* {{{ proto resource cairo_pattern cairo_pattern_create_linear(float x0, float y0, float x1, float y1)
  Create a linear fill pattern */
PHP_FUNCTION(cairo_pattern_create_linear)
{
	cairo_pattern_t * return_res;
	long return_res_id = -1;
	double x0 = 0.0;
	double y0 = 0.0;
	double x1 = 0.0;
	double y1 = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dddd", &x0, &y0, &x1, &y1) == FAILURE) {
		return;
	}
	do {
		return_res = cairo_pattern_create_linear(x0, y0, x1, y1);
	} while (0);
	return_res_id = ZEND_REGISTER_RESOURCE(return_value, return_res, le_cairo_pattern);
}
/* }}} cairo_pattern_create_linear */


/* {{{ proto resource cairo_pattern cairo_pattern_create_radial(float cx0, float cy0, float radius0, float cx1, float cy1, float radius1)
  Create a radial fill pattern */
PHP_FUNCTION(cairo_pattern_create_radial)
{
	cairo_pattern_t * return_res;
	long return_res_id = -1;
	double cx0 = 0.0;
	double cy0 = 0.0;
	double radius0 = 0.0;
	double cx1 = 0.0;
	double cy1 = 0.0;
	double radius1 = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dddddd", &cx0, &cy0, &radius0, &cx1, &cy1, &radius1) == FAILURE) {
		return;
	}
	do {
		return_res = cairo_pattern_create_radial(cx0,  cy0,  radius0,  cx1,  cy1,  radius1);
	} while (0);
	return_res_id = ZEND_REGISTER_RESOURCE(return_value, return_res, le_cairo_pattern);
}
/* }}} cairo_pattern_create_radial */


/* {{{ proto resource cairo_pattern cairo_pattern_create_for_surface(resource cairo_surface surface)
  Create a fill pattern from an existing surface resource */
PHP_FUNCTION(cairo_pattern_create_for_surface)
{
	cairo_pattern_t * return_res;
	long return_res_id = -1;
	zval * surface_res = NULL;
	int surface_resid = -1;
	cairo_surface_t * surface;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &surface_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(surface, cairo_surface_t *, &surface_res, surface_resid, "cairo_surface", le_cairo_surface);


	do {
		return_res = cairo_pattern_create_for_surface(surface);
	} while (0);
	return_res_id = ZEND_REGISTER_RESOURCE(return_value, return_res, le_cairo_pattern);
}
/* }}} cairo_pattern_create_for_surface */


/* {{{ proto resource cairo_pattern cairo_pattern_create_rgb(float red, float green, float blue)
  Create a solid color fill pattern */
PHP_FUNCTION(cairo_pattern_create_rgb)
{
	cairo_pattern_t * return_res;
	long return_res_id = -1;
	double red = 0.0;
	double green = 0.0;
	double blue = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ddd", &red, &green, &blue) == FAILURE) {
		return;
	}
	do {
		return_res = cairo_pattern_create_rgb(red, green, blue);
	} while (0);
	return_res_id = ZEND_REGISTER_RESOURCE(return_value, return_res, le_cairo_pattern);
}
/* }}} cairo_pattern_create_rgb */


/* {{{ proto resource cairo_pattern cairo_pattern_create_rgba(float red, float green, float blue, float alpha)
  Create a transparent colored fill pattern */
PHP_FUNCTION(cairo_pattern_create_rgba)
{
	cairo_pattern_t * return_res;
	long return_res_id = -1;
	double red = 0.0;
	double green = 0.0;
	double blue = 0.0;
	double alpha = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dddd", &red, &green, &blue, &alpha) == FAILURE) {
		return;
	}
	do {
		return_res = cairo_pattern_create_rgba(red, green, blue, alpha);
	} while (0);
	return_res_id = ZEND_REGISTER_RESOURCE(return_value, return_res, le_cairo_pattern);
}
/* }}} cairo_pattern_create_rgba */


/* {{{ proto void cairo_pattern_destroy(resource cairo_pattern cr)
  Destroy a fill pattern resource */
PHP_FUNCTION(cairo_pattern_destroy)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_pattern_t * cr;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &cr_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_pattern_t *, &cr_res, cr_resid, "cairo_pattern", le_cairo_pattern);


	do {
		FREE_RESOURCE(cr_res);
	} while (0);
}
/* }}} cairo_pattern_destroy */


/* {{{ proto void cairo_path_destroy(resource cairo_path cr)
  Destroy a drawing path resource */
PHP_FUNCTION(cairo_path_destroy)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_path_t * cr;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &cr_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_path_t *, &cr_res, cr_resid, "cairo_path", le_cairo_path);


	do {
		FREE_RESOURCE(cr_res);
	} while (0);
}
/* }}} cairo_path_destroy */


/* {{{ proto void cairo_select_font_face(resource cairo_context cr, string fontname, int slant, int weight)
  Set current font for a drawing context */
PHP_FUNCTION(cairo_select_font_face)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;
	const char * fontname = NULL;
	int fontname_len = 0;
	long slant = 0;
	long weight = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rsll", &cr_res, &fontname, &fontname_len, &slant, &weight) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		cairo_select_font_face(cr, fontname, slant, weight);
	} while (0);
}
/* }}} cairo_select_font_face */


/* {{{ proto void cairo_set_font_size(resource cairo_context cr, float size)
  Set current font size for a drawing context */
PHP_FUNCTION(cairo_set_font_size)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;
	double size = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rd", &cr_res, &size) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		cairo_set_font_size(cr, size);
	} while (0);
}
/* }}} cairo_set_font_size */


/* {{{ proto void cairo_set_source_rgb(resource cairo_context cr, float red, float green, float blue)
  Set opaque drawing color for a drawing context */
PHP_FUNCTION(cairo_set_source_rgb)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;
	double red = 0.0;
	double green = 0.0;
	double blue = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rddd", &cr_res, &red, &green, &blue) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		cairo_set_source_rgb(cr, red, green, blue);
	} while (0);
}
/* }}} cairo_set_source_rgb */


/* {{{ proto void cairo_set_source_rgba(resource cairo_context cr, float red, float green, float blue, float alpha)
  Set transparent drawing color for a drawing context */
PHP_FUNCTION(cairo_set_source_rgba)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;
	double red = 0.0;
	double green = 0.0;
	double blue = 0.0;
	double alpha = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rdddd", &cr_res, &red, &green, &blue, &alpha) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		cairo_set_source_rgba(cr, red, green, blue, alpha);
	} while (0);
}
/* }}} cairo_set_source_rgba */


/* {{{ proto void cairo_move_to(resource cairo_context cr, float x, float y)
  Set current drawing position to a new starting point */
PHP_FUNCTION(cairo_move_to)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;
	double x = 0.0;
	double y = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rdd", &cr_res, &x, &y) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		cairo_move_to(cr, x, y);
	} while (0);
}
/* }}} cairo_move_to */


/* {{{ proto void cairo_rel_move_to(resource cairo_context cr, float dx, float dy)
  Move current drawing position relative to current position */
PHP_FUNCTION(cairo_rel_move_to)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;
	double dx = 0.0;
	double dy = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rdd", &cr_res, &dx, &dy) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		cairo_rel_move_to(cr, dx, dy);
	} while (0);
}
/* }}} cairo_rel_move_to */


/* {{{ proto void cairo_show_text(resource cairo_context cr, string text)
  Show text at current position using current font */
PHP_FUNCTION(cairo_show_text)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;
	const char * text = NULL;
	int text_len = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rs", &cr_res, &text, &text_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		cairo_show_text(cr, text);
	} while (0);
}
/* }}} cairo_show_text */


#if CAIRO_HAS_PNG_FUNCTIONS
/* {{{ proto void cairo_surface_show_png(resource cairo_surface surface)
  Create immediate PNG image output */
PHP_FUNCTION(cairo_surface_show_png)
{
	zval * surface_res = NULL;
	int surface_resid = -1;
	cairo_surface_t * surface;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &surface_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(surface, cairo_surface_t *, &surface_res, surface_resid, "cairo_surface", le_cairo_surface);


	do {
		cairo_surface_write_to_png_stream(surface, _cairo_write, NULL);
	} while (0);
}
/* }}} cairo_surface_show_png */

#endif /* CAIRO_HAS_PNG_FUNCTIONS */

#if CAIRO_HAS_PNG_FUNCTIONS
/* {{{ proto void cairo_surface_write_to_png(resource cairo_surface surface, string path)
  Save surface contents to a PNG file */
PHP_FUNCTION(cairo_surface_write_to_png)
{
	zval * surface_res = NULL;
	int surface_resid = -1;
	cairo_surface_t * surface;
	const char * path = NULL;
	int path_len = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rs", &surface_res, &path, &path_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(surface, cairo_surface_t *, &surface_res, surface_resid, "cairo_surface", le_cairo_surface);


	do {
		php_stream *stream;
		stream = php_stream_open_wrapper((char *)path, "wb", ENFORCE_SAFE_MODE | REPORT_ERRORS, NULL);

		if (stream) {
		  cairo_surface_write_to_png_stream(surface, _cairo_write_stream, stream);
		  php_stream_close(stream);
		}
	} while (0);
}
/* }}} cairo_surface_write_to_png */

#endif /* CAIRO_HAS_PNG_FUNCTIONS */

#if CAIRO_HAS_PNG_FUNCTIONS
/* {{{ proto resource cairo_surface cairo_image_surface_create_from_png(string path)
  Create new drawing surface from a PNG file */
PHP_FUNCTION(cairo_image_surface_create_from_png)
{
	cairo_surface_t * return_res;
	long return_res_id = -1;
	const char * path = NULL;
	int path_len = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &path, &path_len) == FAILURE) {
		return;
	}
	do {
		php_stream *stream;
		stream = php_stream_open_wrapper((char *)path, "rb", ENFORCE_SAFE_MODE | REPORT_ERRORS, NULL);

		if (!stream) {
		  RETURN_FALSE;
		}
 
		return_res = cairo_image_surface_create_from_png_stream(_cairo_read_stream, stream);
		php_stream_close(stream);
	} while (0);
	return_res_id = ZEND_REGISTER_RESOURCE(return_value, return_res, le_cairo_surface);
}
/* }}} cairo_image_surface_create_from_png */

#endif /* CAIRO_HAS_PNG_FUNCTIONS */

#if CAIRO_HAS_PDF_SURFACE
/* {{{ proto resource cairo_surface cairo_pdf_surface_create(string path, float width_in_points, float height_in_points)
  Create a new surface for PDF output */
PHP_FUNCTION(cairo_pdf_surface_create)
{
	cairo_surface_t * return_res;
	long return_res_id = -1;
	const char * path = NULL;
	int path_len = 0;
	double width_in_points = 0.0;
	double height_in_points = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sdd", &path, &path_len, &width_in_points, &height_in_points) == FAILURE) {
		return;
	}
	do {
		cairo_status_t status;
		php_stream *stream = php_stream_open_wrapper((char *)path, "wb", ENFORCE_SAFE_MODE | REPORT_ERRORS, NULL);

		if (!stream) {
		  RETURN_FALSE;
		}
 
		return_res = cairo_pdf_surface_create_for_stream(_cairo_write_stream, stream, width_in_points, height_in_points);
		status = cairo_surface_set_user_data(return_res, (cairo_user_data_key_t *)cairo_pdf_surface_create, stream, _cairo_close_stream);
	} while (0);
	return_res_id = ZEND_REGISTER_RESOURCE(return_value, return_res, le_cairo_surface);
}
/* }}} cairo_pdf_surface_create */

#endif /* CAIRO_HAS_PDF_SURFACE */

#if CAIRO_HAS_PDF_SURFACE
/* {{{ proto void cairo_pdf_surface_set_size(resource cairo_surface surface, float width_in_points, float height_in_points)
  Set size for current PDF page */
PHP_FUNCTION(cairo_pdf_surface_set_size)
{
	zval * surface_res = NULL;
	int surface_resid = -1;
	cairo_surface_t * surface;
	double width_in_points = 0.0;
	double height_in_points = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rdd", &surface_res, &width_in_points, &height_in_points) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(surface, cairo_surface_t *, &surface_res, surface_resid, "cairo_surface", le_cairo_surface);


	do {
		cairo_pdf_surface_set_size(surface, width_in_points, height_in_points);
	} while (0);
}
/* }}} cairo_pdf_surface_set_size */

#endif /* CAIRO_HAS_PDF_SURFACE */

#if CAIRO_HAS_PS_SURFACE
/* {{{ proto resource cairo_surface cairo_ps_surface_create(string path, float width_in_points, float height_in_points)
  Create a new surface for Postscript output */
PHP_FUNCTION(cairo_ps_surface_create)
{
	cairo_surface_t * return_res;
	long return_res_id = -1;
	const char * path = NULL;
	int path_len = 0;
	double width_in_points = 0.0;
	double height_in_points = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sdd", &path, &path_len, &width_in_points, &height_in_points) == FAILURE) {
		return;
	}
	do {
		cairo_status_t status;
		php_stream *stream = php_stream_open_wrapper((char *)path, "wb", ENFORCE_SAFE_MODE | REPORT_ERRORS, NULL);

		if (!stream) {
		  RETURN_FALSE;
		}
 
		return_res = cairo_ps_surface_create_for_stream(_cairo_write_stream, stream, width_in_points, height_in_points);
		status = cairo_surface_set_user_data(return_res, (cairo_user_data_key_t *)cairo_ps_surface_create, stream, _cairo_close_stream);
	} while (0);
	return_res_id = ZEND_REGISTER_RESOURCE(return_value, return_res, le_cairo_surface);
}
/* }}} cairo_ps_surface_create */

#endif /* CAIRO_HAS_PS_SURFACE */

#if CAIRO_HAS_PS_SURFACE
/* {{{ proto void cairo_ps_surface_set_size(resource cairo_surface surface, float width_in_points, float height_in_points)
  Set size for current Postscript page */
PHP_FUNCTION(cairo_ps_surface_set_size)
{
	zval * surface_res = NULL;
	int surface_resid = -1;
	cairo_surface_t * surface;
	double width_in_points = 0.0;
	double height_in_points = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rdd", &surface_res, &width_in_points, &height_in_points) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(surface, cairo_surface_t *, &surface_res, surface_resid, "cairo_surface", le_cairo_surface);


	do {
		cairo_ps_surface_set_size(surface, width_in_points, height_in_points);
	} while (0);
}
/* }}} cairo_ps_surface_set_size */

#endif /* CAIRO_HAS_PS_SURFACE */

#if CAIRO_HAS_PS_SURFACE
/* {{{ proto void cairo_ps_surface_dsc_begin_setup(resource cairo_surface surface)
  Direct following comments to the general setup section */
PHP_FUNCTION(cairo_ps_surface_dsc_begin_setup)
{
	zval * surface_res = NULL;
	int surface_resid = -1;
	cairo_surface_t * surface;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &surface_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(surface, cairo_surface_t *, &surface_res, surface_resid, "cairo_surface", le_cairo_surface);


	do {
		cairo_ps_surface_dsc_begin_setup(surface);
	} while (0);
}
/* }}} cairo_ps_surface_dsc_begin_setup */

#endif /* CAIRO_HAS_PS_SURFACE */

#if CAIRO_HAS_PS_SURFACE
/* {{{ proto void cairo_ps_surface_dsc_begin_page_setup(resource cairo_surface surface)
  Direct following comments to the page setup section */
PHP_FUNCTION(cairo_ps_surface_dsc_begin_page_setup)
{
	zval * surface_res = NULL;
	int surface_resid = -1;
	cairo_surface_t * surface;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &surface_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(surface, cairo_surface_t *, &surface_res, surface_resid, "cairo_surface", le_cairo_surface);


	do {
		cairo_ps_surface_dsc_begin_page_setup(surface);
	} while (0);
}
/* }}} cairo_ps_surface_dsc_begin_page_setup */

#endif /* CAIRO_HAS_PS_SURFACE */

#if CAIRO_HAS_PS_SURFACE
/* {{{ proto void cairo_ps_surface_dsc_comment(resource cairo_surface surface, string comment)
  Emmit a comment into the preselected setup section */
PHP_FUNCTION(cairo_ps_surface_dsc_comment)
{
	zval * surface_res = NULL;
	int surface_resid = -1;
	cairo_surface_t * surface;
	const char * comment = NULL;
	int comment_len = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rs", &surface_res, &comment, &comment_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(surface, cairo_surface_t *, &surface_res, surface_resid, "cairo_surface", le_cairo_surface);


	do {
		cairo_ps_surface_dsc_comment(surface, comment);
	} while (0);
}
/* }}} cairo_ps_surface_dsc_comment */

#endif /* CAIRO_HAS_PS_SURFACE */

/* {{{ proto void cairo_stroke(resource cairo_context cr)
  Draw current path to surface */
PHP_FUNCTION(cairo_stroke)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &cr_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		cairo_stroke(cr);
	} while (0);
}
/* }}} cairo_stroke */


/* {{{ proto void cairo_stroke_preserve(resource cairo_context cr)
  Draw current path to surface and keep it for further operations */
PHP_FUNCTION(cairo_stroke_preserve)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &cr_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		cairo_stroke_preserve(cr);
	} while (0);
}
/* }}} cairo_stroke_preserve */


/* {{{ proto void cairo_arc(resource cairo_context cr, float xc, float yc, float radius, float angle1, float angle2);
  Draw an arc clockwise */
PHP_FUNCTION(cairo_arc)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;
	double xc = 0.0;
	double yc = 0.0;
	double radius = 0.0;
	double angle1 = 0.0;
	double angle2 = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rddddd", &cr_res, &xc, &yc, &radius, &angle1, &angle2) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		cairo_arc(cr, xc, yc, radius, angle1, angle2);
	} while (0);
}
/* }}} cairo_arc */


/* {{{ proto void cairo_arc_negative(resource cairo_context cr, float xc, float yc, float radius, float angle1, float angle2);
  Draw an arc counter-clockwise */
PHP_FUNCTION(cairo_arc_negative)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;
	double xc = 0.0;
	double yc = 0.0;
	double radius = 0.0;
	double angle1 = 0.0;
	double angle2 = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rddddd", &cr_res, &xc, &yc, &radius, &angle1, &angle2) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		cairo_arc_negative(cr, xc, yc, radius, angle1, angle2);
	} while (0);
}
/* }}} cairo_arc_negative */


/* {{{ proto void cairo_fill(resource cairo_context cr)
  Fill the current path */
PHP_FUNCTION(cairo_fill)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &cr_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		cairo_fill(cr);
	} while (0);
}
/* }}} cairo_fill */


/* {{{ proto void cairo_fill_preserve(resource cairo_context cr)
  Fill the current path and keep it for further operations */
PHP_FUNCTION(cairo_fill_preserve)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &cr_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		cairo_fill_preserve(cr);
	} while (0);
}
/* }}} cairo_fill_preserve */


/* {{{ proto void cairo_set_line_width(resource cairo_context cr, float width)
  Set line width for the next stroke operation */
PHP_FUNCTION(cairo_set_line_width)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;
	double width = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rd", &cr_res, &width) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		cairo_set_line_width(cr, width);
	} while (0);
}
/* }}} cairo_set_line_width */


/* {{{ proto float cairo_get_line_width(resource cairo_context cr, float width)
  Get current line width */
PHP_FUNCTION(cairo_get_line_width)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;
	double width = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rd", &cr_res, &width) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		RETURN_DOUBLE(cairo_get_line_width(cr));
	} while (0);
}
/* }}} cairo_get_line_width */


/* {{{ proto void cairo_line_to(resource cairo_context cr, float xc, float yc)
  Draw a line starting at the current drawing position */
PHP_FUNCTION(cairo_line_to)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;
	double xc = 0.0;
	double yc = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rdd", &cr_res, &xc, &yc) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		cairo_line_to(cr, xc, yc);
	} while (0);
}
/* }}} cairo_line_to */


/* {{{ proto void cairo_rel_line_to(resource cairo_context cr, float dx, float dy)
  Draw a line from the current drawing position using relative offsets */
PHP_FUNCTION(cairo_rel_line_to)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;
	double dx = 0.0;
	double dy = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rdd", &cr_res, &dx, &dy) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		cairo_line_to(cr, dx, dy);
	} while (0);
}
/* }}} cairo_rel_line_to */


/* {{{ proto void cairo_pattern_add_color_stop_rgb(resource cairo_pattern pattern, float offset, float red, float green, float blue)
  Set opaque target color for a given fill pattern gradient control vector offset */
PHP_FUNCTION(cairo_pattern_add_color_stop_rgb)
{
	zval * pattern_res = NULL;
	int pattern_resid = -1;
	cairo_pattern_t * pattern;
	double offset = 0.0;
	double red = 0.0;
	double green = 0.0;
	double blue = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rdddd", &pattern_res, &offset, &red, &green, &blue) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(pattern, cairo_pattern_t *, &pattern_res, pattern_resid, "cairo_pattern", le_cairo_pattern);


	do {
		cairo_pattern_add_color_stop_rgb(pattern, offset, red, green, blue);
	} while (0);
}
/* }}} cairo_pattern_add_color_stop_rgb */


/* {{{ proto void cairo_pattern_add_color_stop_rgba(resource cairo_pattern pattern, float offset, float red, float green, float blue, float alpha)
  Set translucent target color for a given fill pattern gradient control vector offset */
PHP_FUNCTION(cairo_pattern_add_color_stop_rgba)
{
	zval * pattern_res = NULL;
	int pattern_resid = -1;
	cairo_pattern_t * pattern;
	double offset = 0.0;
	double red = 0.0;
	double green = 0.0;
	double blue = 0.0;
	double alpha = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rddddd", &pattern_res, &offset, &red, &green, &blue, &alpha) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(pattern, cairo_pattern_t *, &pattern_res, pattern_resid, "cairo_pattern", le_cairo_pattern);


	do {
		cairo_pattern_add_color_stop_rgba(pattern, offset, red, green, blue, alpha);
	} while (0);
}
/* }}} cairo_pattern_add_color_stop_rgba */


/* {{{ proto void cairo_rectangle(resource cairo_context cr, float x, float y, float width, float height)
  Draw a rectangle */
PHP_FUNCTION(cairo_rectangle)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;
	double x = 0.0;
	double y = 0.0;
	double width = 0.0;
	double height = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rdddd", &cr_res, &x, &y, &width, &height) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		cairo_rectangle(cr, x, y, width, height);
	} while (0);
}
/* }}} cairo_rectangle */


/* {{{ proto void cairo_set_source (resource cairo_context cr, resource cairo_pattern pattern)
  Set source fill pattern for drawing context */
PHP_FUNCTION(cairo_set_source)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;
	zval * pattern_res = NULL;
	int pattern_resid = -1;
	cairo_pattern_t * pattern;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rr", &cr_res, &pattern_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);
	ZEND_FETCH_RESOURCE(pattern, cairo_pattern_t *, &pattern_res, pattern_resid, "cairo_pattern", le_cairo_pattern);


	do {
		cairo_set_source(cr, pattern);
	} while (0);
}
/* }}} cairo_set_source */


/* {{{ proto void cairo_scale (resource cairo_context cr, int width, int height)
  Change scaling of current drawing context */
PHP_FUNCTION(cairo_scale)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;
	long width = 0;
	long height = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rll", &cr_res, &width, &height) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		cairo_scale(cr, width, height);
	} while (0);
}
/* }}} cairo_scale */


/* {{{ proto int cairo_version(void)
  Return cairo library version */
PHP_FUNCTION(cairo_version)
{
	if (ZEND_NUM_ARGS()>0)  {
		WRONG_PARAM_COUNT;
	}

	do {
		RETURN_LONG(cairo_version());
	} while (0);
}
/* }}} cairo_version */


/* {{{ proto string cairo_version_string(void)
  Return cairo library version string */
PHP_FUNCTION(cairo_version_string)
{
	if (ZEND_NUM_ARGS()>0)  {
		WRONG_PARAM_COUNT;
	}

	do {
		RETURN_STRING((char*)cairo_version_string(), 1);
	} while (0);
}
/* }}} cairo_version_string */


/* {{{ proto void cairo_save(resource cairo_context cr)
  Save current drawing context settings */
PHP_FUNCTION(cairo_save)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &cr_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		cairo_save(cr);
	} while (0);
}
/* }}} cairo_save */


/* {{{ proto void cairo_restore(resource cairo_context cr)
  Restore drawing context settings peviously saved */
PHP_FUNCTION(cairo_restore)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &cr_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		cairo_restore(cr);
	} while (0);
}
/* }}} cairo_restore */


/* {{{ proto int cairo_status(resource cairo_context cr)
  Get current drawing context status */
PHP_FUNCTION(cairo_status)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &cr_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		RETURN_LONG(cairo_status(cr));
	} while (0);
}
/* }}} cairo_status */


/* {{{ proto int cairo_pattern_status(resource cairo_pattern pattern)
  Get current fill pattern status */
PHP_FUNCTION(cairo_pattern_status)
{
	zval * pattern_res = NULL;
	int pattern_resid = -1;
	cairo_pattern_t * pattern;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &pattern_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(pattern, cairo_pattern_t *, &pattern_res, pattern_resid, "cairo_pattern", le_cairo_pattern);


	do {
		RETURN_LONG(cairo_pattern_status(pattern));
	} while (0);
}
/* }}} cairo_pattern_status */


/* {{{ proto string cairo_status_to_string(int status)
  Get descriptive message for status code */
PHP_FUNCTION(cairo_status_to_string)
{
	long status = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &status) == FAILURE) {
		return;
	}
	do {
		RETURN_STRING((char*)cairo_status_to_string(status), 1);
	} while (0);
}
/* }}} cairo_status_to_string */


/* {{{ proto void cairo_push_group(resource cairo_context cr)
  Redirect drawing to an intermediate surface */
PHP_FUNCTION(cairo_push_group)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &cr_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		cairo_push_group(cr);
	} while (0);
}
/* }}} cairo_push_group */


/* {{{ proto resource cairo_pattern cairo_pop_group(resource cairo_context cr)
  Create pattern from intermediate surface */
PHP_FUNCTION(cairo_pop_group)
{
	cairo_pattern_t * return_res;
	long return_res_id = -1;
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &cr_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		return_res = cairo_pop_group(cr);
	} while (0);
	return_res_id = ZEND_REGISTER_RESOURCE(return_value, return_res, le_cairo_pattern);
}
/* }}} cairo_pop_group */


/* {{{ proto void cairo_pop_group_to_source(resource cairo_context cr)
  Set source fill pattern from intermediate surface */
PHP_FUNCTION(cairo_pop_group_to_source)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &cr_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		cairo_pop_group_to_source(cr);
	} while (0);
}
/* }}} cairo_pop_group_to_source */


/* {{{ proto void cairo_rotate(resource cairo_context cr, float angle)
  Rotate current drawing context */
PHP_FUNCTION(cairo_rotate)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;
	double angle = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rd", &cr_res, &angle) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		cairo_rotate(cr, angle);
	} while (0);
}
/* }}} cairo_rotate */


/* {{{ proto void cairo_translate(resource cairo_context cr, float tx, float ty)
  Move origin of current drawing context */
PHP_FUNCTION(cairo_translate)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;
	double tx = 0.0;
	double ty = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rdd", &cr_res, &tx, &ty) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		cairo_translate(cr, tx, ty);
	} while (0);
}
/* }}} cairo_translate */


/* {{{ proto void cairo_curve_to(resource cairo_context cr, float x1, float y1, float x2, float y2, float x3, float y3)
  Draw cubic spline given absolute control points */
PHP_FUNCTION(cairo_curve_to)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;
	double x1 = 0.0;
	double y1 = 0.0;
	double x2 = 0.0;
	double y2 = 0.0;
	double x3 = 0.0;
	double y3 = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rdddddd", &cr_res, &x1, &y1, &x2, &y2, &x3, &y3) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		cairo_curve_to(cr, x1, y1, x2, y2, x3, y3);
	} while (0);
}
/* }}} cairo_curve_to */


/* {{{ proto void cairo_rel_curve_to(resource cairo_context cr, float dx1, float dy1, float dx2, float dy2, float dx3, float dy3)
  Draw cubic spline with control points relative to the current position */
PHP_FUNCTION(cairo_rel_curve_to)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;
	double dx1 = 0.0;
	double dy1 = 0.0;
	double dx2 = 0.0;
	double dy2 = 0.0;
	double dx3 = 0.0;
	double dy3 = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rdddddd", &cr_res, &dx1, &dy1, &dx2, &dy2, &dx3, &dy3) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		cairo_rel_curve_to(cr, dx1, dy1, dx2, dy2, dx3, dy3);
	} while (0);
}
/* }}} cairo_rel_curve_to */


/* {{{ proto void cairo_close_path(resource cairo_context cr)
  Close current drawing path with a line to the path starting point */
PHP_FUNCTION(cairo_close_path)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &cr_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		cairo_close_path(cr);
	} while (0);
}
/* }}} cairo_close_path */


/* {{{ proto void cairo_set_antialias(resource cairo_context cr, int antialias)
  Set antialias mode */
PHP_FUNCTION(cairo_set_antialias)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;
	long antialias = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &cr_res, &antialias) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		cairo_set_antialias(cr, antialias);
	} while (0);
}
/* }}} cairo_set_antialias */


/* {{{ proto int cairo_get_antialias(resource cairo_context cr)
  Get current antialias mode */
PHP_FUNCTION(cairo_get_antialias)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &cr_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		RETURN_LONG(cairo_get_antialias(cr));
	} while (0);
}
/* }}} cairo_get_antialias */


/* {{{ proto void cairo_set_fill_rule(resource cairo_context cr, int fill_rule)
  Set fill rule */
PHP_FUNCTION(cairo_set_fill_rule)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;
	long fill_rule = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &cr_res, &fill_rule) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		cairo_set_fill_rule(cr, fill_rule);
	} while (0);
}
/* }}} cairo_set_fill_rule */


/* {{{ proto int cairo_get_fill_rule(resource cairo_context cr)
  Get current fill rule */
PHP_FUNCTION(cairo_get_fill_rule)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &cr_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		RETURN_LONG(cairo_get_fill_rule(cr));
	} while (0);
}
/* }}} cairo_get_fill_rule */


/* {{{ proto void cairo_set_line_cap(resource cairo_context cr, int line_cap)
  Set line caps mode */
PHP_FUNCTION(cairo_set_line_cap)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;
	long line_cap = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &cr_res, &line_cap) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		cairo_set_line_cap(cr, line_cap);
	} while (0);
}
/* }}} cairo_set_line_cap */


/* {{{ proto int cairo_get_line_cap(resource cairo_context cr)
  Get current line caps mode */
PHP_FUNCTION(cairo_get_line_cap)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &cr_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		RETURN_LONG(cairo_get_line_cap(cr));
	} while (0);
}
/* }}} cairo_get_line_cap */


/* {{{ proto void cairo_set_line_join(resource cairo_context cr, int line_join)
  Set line join style */
PHP_FUNCTION(cairo_set_line_join)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;
	long line_join = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &cr_res, &line_join) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		cairo_set_line_join(cr, line_join);
	} while (0);
}
/* }}} cairo_set_line_join */


/* {{{ proto int cairo_get_line_join(resource cairo_context cr)
  Get current line join style */
PHP_FUNCTION(cairo_get_line_join)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &cr_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		RETURN_LONG(cairo_get_line_join(cr));
	} while (0);
}
/* }}} cairo_get_line_join */


/* {{{ proto void cairo_set_tolerance(resource cairo_context cr, float tolerance)
  Set curve conversion tolerance */
PHP_FUNCTION(cairo_set_tolerance)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;
	double tolerance = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rd", &cr_res, &tolerance) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		cairo_set_tolerance(cr, tolerance);
	} while (0);
}
/* }}} cairo_set_tolerance */


/* {{{ proto float cairo_get_tolerance(resource cairo_context cr)
  Get current curve conversion tolerance */
PHP_FUNCTION(cairo_get_tolerance)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &cr_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		RETURN_DOUBLE(cairo_get_tolerance(cr));
	} while (0);
}
/* }}} cairo_get_tolerance */


/* {{{ proto void cairo_set_miter_limit(resource cairo_context cr, float miter_limit)
  Set miter limit */
PHP_FUNCTION(cairo_set_miter_limit)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;
	double miter_limit = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rd", &cr_res, &miter_limit) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		cairo_set_miter_limit(cr, miter_limit);
	} while (0);
}
/* }}} cairo_set_miter_limit */


/* {{{ proto float cairo_get_miter_limit(resource cairo_context cr)
  Get current miter limit */
PHP_FUNCTION(cairo_get_miter_limit)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &cr_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		RETURN_DOUBLE(cairo_get_miter_limit(cr));
	} while (0);
}
/* }}} cairo_get_miter_limit */


/* {{{ proto void cairo_set_operator(resource cairo_context cr, int operator)
  Set compositing operator */
PHP_FUNCTION(cairo_set_operator)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;
	long operator = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &cr_res, &operator) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		cairo_set_operator(cr, operator);
	} while (0);
}
/* }}} cairo_set_operator */


/* {{{ proto int cairo_get_operator(resource cairo_context cr)
  Get current compositing operator */
PHP_FUNCTION(cairo_get_operator)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &cr_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		RETURN_LONG(cairo_get_operator(cr));
	} while (0);
}
/* }}} cairo_get_operator */


/* {{{ proto void cairo_paint(resource cairo_context cr)
  Paint current source fill pattern in complete clip region */
PHP_FUNCTION(cairo_paint)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &cr_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		cairo_paint(cr);
	} while (0);
}
/* }}} cairo_paint */


/* {{{ proto void cairo_paint_with_alpha(resource cairo_context cr, float alpha)
  Paint current source fill pattern transparently in complete clip region */
PHP_FUNCTION(cairo_paint_with_alpha)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;
	double alpha = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rd", &cr_res, &alpha) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		cairo_paint_with_alpha(cr, alpha);
	} while (0);
}
/* }}} cairo_paint_with_alpha */


/* {{{ proto void cairo_surface_flush(resource cairo_surface surface)
  Flush pending operations to device */
PHP_FUNCTION(cairo_surface_flush)
{
	zval * surface_res = NULL;
	int surface_resid = -1;
	cairo_surface_t * surface;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &surface_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(surface, cairo_surface_t *, &surface_res, surface_resid, "cairo_surface", le_cairo_surface);


	do {
		cairo_surface_flush(surface);
	} while (0);
}
/* }}} cairo_surface_flush */


/* {{{ proto void cairo_clip(resource cairo_context cr)
  Create new clip region from current clip region and path */
PHP_FUNCTION(cairo_clip)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &cr_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		cairo_clip(cr);
	} while (0);
}
/* }}} cairo_clip */


/* {{{ proto void cairo_clip_preserve(resource cairo_context cr)
  Create new clip region from current clip region and path, keep path for further operations */
PHP_FUNCTION(cairo_clip_preserve)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &cr_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		cairo_clip_preserve(cr);
	} while (0);
}
/* }}} cairo_clip_preserve */


/* {{{ proto void cairo_reset_clip(resource cairo_context cr)
  Reset clipping region */
PHP_FUNCTION(cairo_reset_clip)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &cr_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		cairo_reset_clip(cr);
	} while (0);
}
/* }}} cairo_reset_clip */


/* {{{ proto int cairo_image_surface_get_height(resource cairo_surface surface)
  Get height of a bitmap image surface in pixels */
PHP_FUNCTION(cairo_image_surface_get_height)
{
	zval * surface_res = NULL;
	int surface_resid = -1;
	cairo_surface_t * surface;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &surface_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(surface, cairo_surface_t *, &surface_res, surface_resid, "cairo_surface", le_cairo_surface);


	do {
		RETURN_LONG(cairo_image_surface_get_height(surface));
	} while (0);
}
/* }}} cairo_image_surface_get_height */


/* {{{ proto int cairo_image_surface_get_width(resource cairo_surface surface)
  Get width of a bitmap image surface in pixels */
PHP_FUNCTION(cairo_image_surface_get_width)
{
	zval * surface_res = NULL;
	int surface_resid = -1;
	cairo_surface_t * surface;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &surface_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(surface, cairo_surface_t *, &surface_res, surface_resid, "cairo_surface", le_cairo_surface);


	do {
		RETURN_LONG(cairo_image_surface_get_width(surface));
	} while (0);
}
/* }}} cairo_image_surface_get_width */


/* {{{ proto void cairo_surface_status(resource cairo_surface surface)
  Get current surface status */
PHP_FUNCTION(cairo_surface_status)
{
	zval * surface_res = NULL;
	int surface_resid = -1;
	cairo_surface_t * surface;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &surface_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(surface, cairo_surface_t *, &surface_res, surface_resid, "cairo_surface", le_cairo_surface);


	do {
		cairo_surface_status(surface);
	} while (0);
}
/* }}} cairo_surface_status */


/* {{{ proto bool cairo_in_fill(resource cairo_context cr, float x, float y)
  Check whether the given point would be modified by the next fill operation */
PHP_FUNCTION(cairo_in_fill)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;
	double x = 0.0;
	double y = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rdd", &cr_res, &x, &y) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		RETURN_BOOL(cairo_in_fill(cr, x, y));
	} while (0);
}
/* }}} cairo_in_fill */


/* {{{ proto bool cairo_in_stroke(resource cairo_context cr, float x, float y)
  Check whether the given point would be modified by the next stroke operation */
PHP_FUNCTION(cairo_in_stroke)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;
	double x = 0.0;
	double y = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rdd", &cr_res, &x, &y) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		RETURN_BOOL(cairo_in_stroke(cr, x, y));
	} while (0);
}
/* }}} cairo_in_stroke */


/* {{{ proto void cairo_new_path(resource cairo_context cr)
  Start fresh drawing path, purge any previous path information */
PHP_FUNCTION(cairo_new_path)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &cr_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		cairo_new_path(cr);
	} while (0);
}
/* }}} cairo_new_path */


/* {{{ proto void cairo_new_sub_path(resource cairo_context cr)
  Start a new sub path */
PHP_FUNCTION(cairo_new_sub_path)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &cr_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		cairo_new_sub_path(cr);
	} while (0);
}
/* }}} cairo_new_sub_path */


/* {{{ proto int cairo_image_surface_get_type(resource cairo_surface surface)
  Get type of bitmap image surface */
PHP_FUNCTION(cairo_image_surface_get_type)
{
	zval * surface_res = NULL;
	int surface_resid = -1;
	cairo_surface_t * surface;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &surface_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(surface, cairo_surface_t *, &surface_res, surface_resid, "cairo_surface", le_cairo_surface);


	do {
		RETURN_LONG(cairo_image_surface_get_type(surface));
	} while (0);
}
/* }}} cairo_image_surface_get_type */


/* {{{ proto int cairo_image_surface_get_format(resource cairo_surface surface)
  Get format of bitmap image surface */
PHP_FUNCTION(cairo_image_surface_get_format)
{
	zval * surface_res = NULL;
	int surface_resid = -1;
	cairo_surface_t * surface;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &surface_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(surface, cairo_surface_t *, &surface_res, surface_resid, "cairo_surface", le_cairo_surface);


	do {
		RETURN_LONG(cairo_image_surface_get_format(surface));
	} while (0);
}
/* }}} cairo_image_surface_get_format */


/* {{{ proto void cairo_pattern_set_extend(resource cairo_pattern pattern, int extend)
  Set fill pattern extend mode */
PHP_FUNCTION(cairo_pattern_set_extend)
{
	zval * pattern_res = NULL;
	int pattern_resid = -1;
	cairo_pattern_t * pattern;
	long extend = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &pattern_res, &extend) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(pattern, cairo_pattern_t *, &pattern_res, pattern_resid, "cairo_pattern", le_cairo_pattern);


	do {
		cairo_pattern_set_extend(pattern, extend);
	} while (0);
}
/* }}} cairo_pattern_set_extend */


/* {{{ proto void cairo_copy_page(resource cairo_context cr)
  Finish current page and start a new one preserving the surface contents */
PHP_FUNCTION(cairo_copy_page)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &cr_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		cairo_copy_page(cr);
	} while (0);
}
/* }}} cairo_copy_page */


/* {{{ proto void cairo_show_page(resource cairo_context cr)
  Finish current page and start a new empty one */
PHP_FUNCTION(cairo_show_page)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &cr_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		cairo_show_page(cr);
	} while (0);
}
/* }}} cairo_show_page */


/* {{{ proto resource cairo_path cairo_copy_path(resource cairo_context cr)
  Get current path from drawing context */
PHP_FUNCTION(cairo_copy_path)
{
	cairo_path_t * return_res;
	long return_res_id = -1;
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &cr_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		return_res = cairo_copy_path(cr);
	} while (0);
	return_res_id = ZEND_REGISTER_RESOURCE(return_value, return_res, le_cairo_path);
}
/* }}} cairo_copy_path */


/* {{{ proto resource cairo_path cairo_copy_path_flat(resource cairo_context cr)
  Get current path from drawing context, convert all curves to straight line segments */
PHP_FUNCTION(cairo_copy_path_flat)
{
	cairo_path_t * return_res;
	long return_res_id = -1;
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &cr_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		return_res = cairo_copy_path_flat(cr);
	} while (0);
	return_res_id = ZEND_REGISTER_RESOURCE(return_value, return_res, le_cairo_path);
}
/* }}} cairo_copy_path_flat */


/* {{{ proto void cairo_append_path(resource cairo_context cr, resource cairo_path path)
  Append a given path to the current drawing context path */
PHP_FUNCTION(cairo_append_path)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;
	zval * path_res = NULL;
	int path_resid = -1;
	cairo_path_t * path;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rr", &cr_res, &path_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);
	ZEND_FETCH_RESOURCE(path, cairo_path_t *, &path_res, path_resid, "cairo_path", le_cairo_path);


	do {
		cairo_append_path(cr, path);
	} while (0);
}
/* }}} cairo_append_path */


/* {{{ proto resource cairo_pattern cairo_get_source(resource cairo_context cr)
  Get current source fill pattern from drawing context */
PHP_FUNCTION(cairo_get_source)
{
	cairo_pattern_t * return_res;
	long return_res_id = -1;
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &cr_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		return_res = cairo_get_source(cr);
	} while (0);
	return_res_id = ZEND_REGISTER_RESOURCE(return_value, return_res, le_cairo_pattern);
}
/* }}} cairo_get_source */


/* {{{ proto void cairo_mask(resource cairo_context cr, resource cairo_pattern pattern)
  Paint current source fill pattern using alpha channel mask pattern */
PHP_FUNCTION(cairo_mask)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;
	zval * pattern_res = NULL;
	int pattern_resid = -1;
	cairo_pattern_t * pattern;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rr", &cr_res, &pattern_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);
	ZEND_FETCH_RESOURCE(pattern, cairo_pattern_t *, &pattern_res, pattern_resid, "cairo_pattern", le_cairo_pattern);


	do {
		cairo_mask(cr, pattern);
	} while (0);
}
/* }}} cairo_mask */


/* {{{ proto void cairo_mask_surface(resource cairo_context cr, resource cairo_surface  surface, float surface_x, float surface_y)
  Paint current source fill pattern using a surface as alpha channel mask */
PHP_FUNCTION(cairo_mask_surface)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;
	zval * surface_res = NULL;
	int surface_resid = -1;
	cairo_surface_t * surface;
	double surface_x = 0.0;
	double surface_y = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rrdd", &cr_res, &surface_res, &surface_x, &surface_y) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);
	ZEND_FETCH_RESOURCE(surface, cairo_surface_t *, &surface_res, surface_resid, "cairo_surface", le_cairo_surface);


	do {
		cairo_mask_surface(cr, surface, surface_x, surface_y);
	} while (0);
}
/* }}} cairo_mask_surface */


/* {{{ proto int cairo_pattern_get_extend(resource cairo_pattern pattern)
  Get fill pattern extend mode */
PHP_FUNCTION(cairo_pattern_get_extend)
{
	zval * pattern_res = NULL;
	int pattern_resid = -1;
	cairo_pattern_t * pattern;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &pattern_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(pattern, cairo_pattern_t *, &pattern_res, pattern_resid, "cairo_pattern", le_cairo_pattern);


	do {
		RETURN_LONG(cairo_pattern_get_extend(pattern));
	} while (0);
}
/* }}} cairo_pattern_get_extend */


/* {{{ proto int cairo_pattern_get_filter(resource cairo_pattern pattern)
  Get fill pattern filter setting */
PHP_FUNCTION(cairo_pattern_get_filter)
{
	zval * pattern_res = NULL;
	int pattern_resid = -1;
	cairo_pattern_t * pattern;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &pattern_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(pattern, cairo_pattern_t *, &pattern_res, pattern_resid, "cairo_pattern", le_cairo_pattern);


	do {
		RETURN_LONG(cairo_pattern_get_filter(pattern));
	} while (0);
}
/* }}} cairo_pattern_get_filter */


/* {{{ proto int cairo_pattern_get_pattern_tpye(resource cairo_pattern pattern)
  Get fill pattern type */
PHP_FUNCTION(cairo_pattern_get_pattern_type)
{
	zval * pattern_res = NULL;
	int pattern_resid = -1;
	cairo_pattern_t * pattern;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &pattern_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(pattern, cairo_pattern_t *, &pattern_res, pattern_resid, "cairo_pattern", le_cairo_pattern);


	do {
		RETURN_LONG(cairo_pattern_get_pattern_type(pattern));
	} while (0);
}
/* }}} cairo_pattern_get_pattern_type */


/* {{{ proto void cairo_surface_mark_dirty(resource cairo_surface surface)
  Mark surface as dirty due to non-cairo drawing operations */
PHP_FUNCTION(cairo_surface_mark_dirty)
{
	zval * surface_res = NULL;
	int surface_resid = -1;
	cairo_surface_t * surface;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &surface_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(surface, cairo_surface_t *, &surface_res, surface_resid, "cairo_surface", le_cairo_surface);


	do {
		cairo_surface_mark_dirty(surface);
	} while (0);
}
/* }}} cairo_surface_mark_dirty */


/* {{{ proto void cairo_surface_make_dirty_rectangle(resource cairo_surface surface, int x, int y, int width, int height)
  Mark part of the surface as dirty due to non-cairo drawing operations */
PHP_FUNCTION(cairo_surface_mark_dirty_rectangle)
{
	zval * surface_res = NULL;
	int surface_resid = -1;
	cairo_surface_t * surface;
	long x = 0;
	long y = 0;
	long width = 0;
	long height = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rllll", &surface_res, &x, &y, &width, &height) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(surface, cairo_surface_t *, &surface_res, surface_resid, "cairo_surface", le_cairo_surface);


	do {
		cairo_surface_mark_dirty_rectangle(surface, x, y, width, height);
	} while (0);
}
/* }}} cairo_surface_mark_dirty_rectangle */


/* {{{ proto void cairo_surface_set_fallback_resolution(resource cairo_surface surface, float x_pixels_per_inch, float y_pixels_per_inch)
  Set resolution for fallback operations on images not supported by the current surface */
PHP_FUNCTION(cairo_surface_set_fallback_resolution)
{
	zval * surface_res = NULL;
	int surface_resid = -1;
	cairo_surface_t * surface;
	double x_pixels_per_inch = 0.0;
	double y_pixels_per_inch = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rdd", &surface_res, &x_pixels_per_inch, &y_pixels_per_inch) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(surface, cairo_surface_t *, &surface_res, surface_resid, "cairo_surface", le_cairo_surface);


	do {
		cairo_surface_set_fallback_resolution(surface, x_pixels_per_inch, y_pixels_per_inch);
	} while (0);
}
/* }}} cairo_surface_set_fallback_resolution */


/* {{{ proto void cairo_surface_set_device_offset(resource cairo_surface surface, float x_offset, float y_offset)
  Set device drawing offset */
PHP_FUNCTION(cairo_surface_set_device_offset)
{
	zval * surface_res = NULL;
	int surface_resid = -1;
	cairo_surface_t * surface;
	double x_offset = 0.0;
	double y_offset = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rdd", &surface_res, &x_offset, &y_offset) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(surface, cairo_surface_t *, &surface_res, surface_resid, "cairo_surface", le_cairo_surface);


	do {
		cairo_surface_set_devide_offset(surface, x_offset, y_offset);
	} while (0);
}
/* }}} cairo_surface_set_device_offset */


/* {{{ proto void cairo_set_source_surface(resource cairo_context cr, resource cairo_surface  surface, float x, float y)
  Create drawing context source fill pattern from surface */
PHP_FUNCTION(cairo_set_source_surface)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;
	zval * surface_res = NULL;
	int surface_resid = -1;
	cairo_surface_t * surface;
	double x = 0.0;
	double y = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rrdd", &cr_res, &surface_res, &x, &y) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);
	ZEND_FETCH_RESOURCE(surface, cairo_surface_t *, &surface_res, surface_resid, "cairo_surface", le_cairo_surface);


	do {
		cairo_set_source_surface(cr, surface, x, y);
	} while (0);
}
/* }}} cairo_set_source_surface */


#if CAIRO_HAS_SVG_SURFACE
/* {{{ proto resource cairo_surface cairo_svg_surface_create(string path, float width_in_points, float height_in_points)
  Create a Scalabel Vector Graphics surface */
PHP_FUNCTION(cairo_svg_surface_create)
{
	cairo_surface_t * return_res;
	long return_res_id = -1;
	const char * path = NULL;
	int path_len = 0;
	double width_in_points = 0.0;
	double height_in_points = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sdd", &path, &path_len, &width_in_points, &height_in_points) == FAILURE) {
		return;
	}
	do {
		cairo_status_t status;
		php_stream *stream = php_stream_open_wrapper((char *)path, "wb", ENFORCE_SAFE_MODE | REPORT_ERRORS, NULL);

		if (!stream) {
		  RETURN_FALSE;
		}
 
		return_res = cairo_svg_surface_create_for_stream(_cairo_write_stream, stream, width_in_points, height_in_points);
		status = cairo_surface_set_user_data(return_res, (cairo_user_data_key_t *)cairo_svg_surface_create, stream, _cairo_close_stream);
	} while (0);
	return_res_id = ZEND_REGISTER_RESOURCE(return_value, return_res, le_cairo_surface);
}
/* }}} cairo_svg_surface_create */

#endif /* CAIRO_HAS_SVG_SURFACE */

#if CAIRO_HAS_SVG_SURFACE
/* {{{ proto void cairo_svg_surface_restrict_to_version(resource cairo_surface surface, int version)
  Set SVG version to produce output for */
PHP_FUNCTION(cairo_svg_surface_restrict_to_version)
{
	zval * surface_res = NULL;
	int surface_resid = -1;
	cairo_surface_t * surface;
	long version = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &surface_res, &version) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(surface, cairo_surface_t *, &surface_res, surface_resid, "cairo_surface", le_cairo_surface);


	do {
		cairo_svg_surface_restrict_to_version(surface, version);
	} while (0);
}
/* }}} cairo_svg_surface_restrict_to_version */

#endif /* CAIRO_HAS_SVG_SURFACE */

#if CAIRO_HAS_SVG_SURFACE
/* {{{ proto string cairo_svg_version_to_string(int version)
  Get descriptive SVG version info */
PHP_FUNCTION(cairo_svg_version_to_string)
{
	long version = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &version) == FAILURE) {
		return;
	}
	do {
		RETURN_STRING((char *)cairo_svg_version_to_string(version), 1);
	} while (0);
}
/* }}} cairo_svg_version_to_string */

#endif /* CAIRO_HAS_SVG_SURFACE */

/* {{{ proto void cairo_text_path(resource cairo_context cr, string text)
  Create drawing path from text */
PHP_FUNCTION(cairo_text_path)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;
	const char * text = NULL;
	int text_len = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rs", &cr_res, &text, &text_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		cairo_text_path(cr, text);
	} while (0);
}
/* }}} cairo_text_path */


/* {{{ proto resource cairo_font_face cairo_get_font_face(resource cairo_context cr)
  Get current font face */
PHP_FUNCTION(cairo_get_font_face)
{
	cairo_font_face_t * return_res;
	long return_res_id = -1;
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &cr_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		if (!(return_res = cairo_get_font_face(cr))) {
		  RETURN_FALSE;
		}
	} while (0);
	return_res_id = ZEND_REGISTER_RESOURCE(return_value, return_res, le_cairo_font_face);
}
/* }}} cairo_get_font_face */


/* {{{ proto void cairo_font_destroy(resource cairo_font_face font_face)
  Destry font face resource */
PHP_FUNCTION(cairo_font_face_destroy)
{
	zval * font_face_res = NULL;
	int font_face_resid = -1;
	cairo_font_face_t * font_face;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &font_face_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(font_face, cairo_font_face_t *, &font_face_res, font_face_resid, "cairo_font_face", le_cairo_font_face);


	do {
		FREE_RESOURCE(font_face_res);
	} while (0);
}
/* }}} cairo_font_face_destroy */


/* {{{ proto int cairo_font_face_get_type(resource cairo_font_face font_face)
  Get font face type */
PHP_FUNCTION(cairo_font_face_get_type)
{
	zval * font_face_res = NULL;
	int font_face_resid = -1;
	cairo_font_face_t * font_face;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &font_face_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(font_face, cairo_font_face_t *, &font_face_res, font_face_resid, "cairo_font_face", le_cairo_font_face);


	do {
		RETURN_LONG(cairo_font_face_get_type(font_face));
	} while (0);
}
/* }}} cairo_font_face_get_type */


/* {{{ proto int cairo_font_face_status(resource cairo_font_face font_face)
  Get font face status */
PHP_FUNCTION(cairo_font_face_status)
{
	zval * font_face_res = NULL;
	int font_face_resid = -1;
	cairo_font_face_t * font_face;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &font_face_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(font_face, cairo_font_face_t *, &font_face_res, font_face_resid, "cairo_font_face", le_cairo_font_face);


	do {
		RETURN_LONG(cairo_font_face_status(font_face));
	} while (0);
}
/* }}} cairo_font_face_status */


/* {{{ proto void cairo_set_font_face(resource cairo_context cr, resource cairo_font_face font_face)
  Set new font face for drawing context */
PHP_FUNCTION(cairo_set_font_face)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;
	zval * font_face_res = NULL;
	int font_face_resid = -1;
	cairo_font_face_t * font_face;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rr", &cr_res, &font_face_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);
	ZEND_FETCH_RESOURCE(font_face, cairo_font_face_t *, &font_face_res, font_face_resid, "cairo_font_face", le_cairo_font_face);


	do {
		cairo_set_font_face(cr, font_face);
	} while (0);
}
/* }}} cairo_set_font_face */


/* {{{ proto resource cairo_font_options cairo_font_options_create(void)
  Create font options resource */
PHP_FUNCTION(cairo_font_options_create)
{
	cairo_font_options_t * return_res;
	long return_res_id = -1;
	if (ZEND_NUM_ARGS()>0)  {
		WRONG_PARAM_COUNT;
	}

	do {
		return_res = cairo_font_options_create();
	} while (0);
	return_res_id = ZEND_REGISTER_RESOURCE(return_value, return_res, le_cairo_font_options);
}
/* }}} cairo_font_options_create */


/* {{{ proto resource cairo_font_options cairo_font_options_copy(resource cairo_font_options font_options)
  Create a copy of an existing font options resource */
PHP_FUNCTION(cairo_font_options_copy)
{
	cairo_font_options_t * return_res;
	long return_res_id = -1;
	zval * font_options_res = NULL;
	int font_options_resid = -1;
	cairo_font_options_t * font_options;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &font_options_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(font_options, cairo_font_options_t *, &font_options_res, font_options_resid, "cairo_font_options", le_cairo_font_options);


	do {
		return_res = cairo_font_options_copy(font_options);
	} while (0);
	return_res_id = ZEND_REGISTER_RESOURCE(return_value, return_res, le_cairo_font_options);
}
/* }}} cairo_font_options_copy */


/* {{{ proto void cairo_font_options_destroy(resource cairo_font_options font_options)
  Destroy a font options resource */
PHP_FUNCTION(cairo_font_options_destroy)
{
	zval * font_options_res = NULL;
	int font_options_resid = -1;
	cairo_font_options_t * font_options;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &font_options_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(font_options, cairo_font_options_t *, &font_options_res, font_options_resid, "cairo_font_options", le_cairo_font_options);


	do {
		FREE_RESOURCE(font_options_res);
	} while (0);
}
/* }}} cairo_font_options_destroy */


/* {{{ proto void cairo_set_font_options(resource cairo_context cr, resource cairo_font_options font_options)
  Set font options for current drawing font */
PHP_FUNCTION(cairo_set_font_options)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;
	zval * font_options_res = NULL;
	int font_options_resid = -1;
	cairo_font_options_t * font_options;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rr", &cr_res, &font_options_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);
	ZEND_FETCH_RESOURCE(font_options, cairo_font_options_t *, &font_options_res, font_options_resid, "cairo_font_options", le_cairo_font_options);


	do {
		cairo_set_font_options(cr, font_options);
	} while (0);
}
/* }}} cairo_set_font_options */


/* {{{ proto void cairo_font_options_set_antialias(resource cairo_font_options font_options, int antialias)
  Set antialias font option */
PHP_FUNCTION(cairo_font_options_set_antialias)
{
	zval * font_options_res = NULL;
	int font_options_resid = -1;
	cairo_font_options_t * font_options;
	long antialias = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &font_options_res, &antialias) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(font_options, cairo_font_options_t *, &font_options_res, font_options_resid, "cairo_font_options", le_cairo_font_options);


	do {
		cairo_font_options_set_antialias(font_options, antialias);
	} while (0);
}
/* }}} cairo_font_options_set_antialias */


/* {{{ proto void cairo_font_options_set_hint_metrics(resource cairo_font_options font_options, int hint_metrics)
  Set hint metrics font option */
PHP_FUNCTION(cairo_font_options_set_hint_metrics)
{
	zval * font_options_res = NULL;
	int font_options_resid = -1;
	cairo_font_options_t * font_options;
	long hint_metrics = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &font_options_res, &hint_metrics) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(font_options, cairo_font_options_t *, &font_options_res, font_options_resid, "cairo_font_options", le_cairo_font_options);


	do {
		cairo_font_options_set_hint_metrics(font_options, hint_metrics);
	} while (0);
}
/* }}} cairo_font_options_set_hint_metrics */


/* {{{ proto void cairo_font_options_set_hint_style(resource cairo_font_options font_options, int hint_style)
  Set hint style font option */
PHP_FUNCTION(cairo_font_options_set_hint_style)
{
	zval * font_options_res = NULL;
	int font_options_resid = -1;
	cairo_font_options_t * font_options;
	long hint_style = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &font_options_res, &hint_style) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(font_options, cairo_font_options_t *, &font_options_res, font_options_resid, "cairo_font_options", le_cairo_font_options);


	do {
		cairo_font_options_set_hint_style(font_options, hint_style);
	} while (0);
}
/* }}} cairo_font_options_set_hint_style */


/* {{{ proto void cairo_font_options_set_subpixel_order(resource cairo_font_options font_options, int subpixel_order)
  Set subpixel order font option */
PHP_FUNCTION(cairo_font_options_set_subpixel_order)
{
	zval * font_options_res = NULL;
	int font_options_resid = -1;
	cairo_font_options_t * font_options;
	long subpixel_order = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &font_options_res, &subpixel_order) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(font_options, cairo_font_options_t *, &font_options_res, font_options_resid, "cairo_font_options", le_cairo_font_options);


	do {
		cairo_font_options_set_subpixel_order(font_options, subpixel_order);
	} while (0);
}
/* }}} cairo_font_options_set_subpixel_order */


/* {{{ proto int cairo_font_options_get_antialias(resource cairo_font_options font_options)
  Get antialias setting from font option */
PHP_FUNCTION(cairo_font_options_get_antialias)
{
	zval * font_options_res = NULL;
	int font_options_resid = -1;
	cairo_font_options_t * font_options;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &font_options_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(font_options, cairo_font_options_t *, &font_options_res, font_options_resid, "cairo_font_options", le_cairo_font_options);


	do {
		RETURN_LONG(cairo_font_options_get_antialias(font_options));
	} while (0);
}
/* }}} cairo_font_options_get_antialias */


/* {{{ proto int cairo_font_options_get_hint_metrics(resource cairo_font_options font_options)
  Get hint metrics setting from font option */
PHP_FUNCTION(cairo_font_options_get_hint_metrics)
{
	zval * font_options_res = NULL;
	int font_options_resid = -1;
	cairo_font_options_t * font_options;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &font_options_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(font_options, cairo_font_options_t *, &font_options_res, font_options_resid, "cairo_font_options", le_cairo_font_options);


	do {
		RETURN_LONG(cairo_font_options_get_hint_metrics(font_options));
	} while (0);
}
/* }}} cairo_font_options_get_hint_metrics */


/* {{{ proto int cairo_font_options_get_hint_style(resource cairo_font_options font_options)
  Get hint style setting from font option */
PHP_FUNCTION(cairo_font_options_get_hint_style)
{
	zval * font_options_res = NULL;
	int font_options_resid = -1;
	cairo_font_options_t * font_options;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &font_options_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(font_options, cairo_font_options_t *, &font_options_res, font_options_resid, "cairo_font_options", le_cairo_font_options);


	do {
		RETURN_LONG(cairo_font_options_get_hint_style(font_options));
	} while (0);
}
/* }}} cairo_font_options_get_hint_style */


/* {{{ proto int cairo_font_options_get_subpixel_order(resource cairo_font_options font_options)
  Get subpixel order setting from fong option */
PHP_FUNCTION(cairo_font_options_get_subpixel_order)
{
	zval * font_options_res = NULL;
	int font_options_resid = -1;
	cairo_font_options_t * font_options;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &font_options_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(font_options, cairo_font_options_t *, &font_options_res, font_options_resid, "cairo_font_options", le_cairo_font_options);


	do {
		RETURN_LONG(cairo_font_options_get_subpixel_order(font_options));
	} while (0);
}
/* }}} cairo_font_options_get_subpixel_order */


/* {{{ proto bool cairo_font_options_equal(resource cairo_font_options options, resource cairo_font_options other)
  Compare two font options */
PHP_FUNCTION(cairo_font_options_equal)
{
	zval * options_res = NULL;
	int options_resid = -1;
	cairo_font_options_t * options;
	zval * other_res = NULL;
	int other_resid = -1;
	cairo_font_options_t * other;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rr", &options_res, &other_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(options, cairo_font_options_t *, &options_res, options_resid, "cairo_font_options", le_cairo_font_options);
	ZEND_FETCH_RESOURCE(other, cairo_font_options_t *, &other_res, other_resid, "cairo_font_options", le_cairo_font_options);


	do {
		RETURN_BOOL(cairo_font_options_equal(options, other));
	} while (0);
}
/* }}} cairo_font_options_equal */


/* {{{ proto void cairo_font_options_merge(resource cairo_font_options options, resource cairo_font_options other)
  Merge font options */
PHP_FUNCTION(cairo_font_options_merge)
{
	zval * options_res = NULL;
	int options_resid = -1;
	cairo_font_options_t * options;
	zval * other_res = NULL;
	int other_resid = -1;
	cairo_font_options_t * other;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rr", &options_res, &other_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(options, cairo_font_options_t *, &options_res, options_resid, "cairo_font_options", le_cairo_font_options);
	ZEND_FETCH_RESOURCE(other, cairo_font_options_t *, &other_res, other_resid, "cairo_font_options", le_cairo_font_options);


	do {
		cairo_font_options_merge(options, other);
	} while (0);
}
/* }}} cairo_font_options_merge */


/* {{{ proto int cairo_font_options_status(resource cairo_font_options options)
  Get font options status */
PHP_FUNCTION(cairo_font_options_status)
{
	zval * options_res = NULL;
	int options_resid = -1;
	cairo_font_options_t * options;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &options_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(options, cairo_font_options_t *, &options_res, options_resid, "cairo_font_options", le_cairo_font_options);


	do {
		RETURN_LONG(cairo_font_options_status(options));
	} while (0);
}
/* }}} cairo_font_options_status */


/* {{{ proto void cairo_get_font_options(resource cairo_context cr, resource cairo_font_options options)
  Get current font options from drawing context */
PHP_FUNCTION(cairo_get_font_options)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;
	zval * options_res = NULL;
	int options_resid = -1;
	cairo_font_options_t * options;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rr", &cr_res, &options_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);
	ZEND_FETCH_RESOURCE(options, cairo_font_options_t *, &options_res, options_resid, "cairo_font_options", le_cairo_font_options);


	do {
		cairo_get_font_options(cr, options);
	} while (0);
}
/* }}} cairo_get_font_options */


/* {{{ proto void cairo_surface_get_font_options(resource cairo_surface surface, resource cairo_font_options options)
  Get current font options from surface */
PHP_FUNCTION(cairo_surface_get_font_options)
{
	zval * surface_res = NULL;
	int surface_resid = -1;
	cairo_surface_t * surface;
	zval * options_res = NULL;
	int options_resid = -1;
	cairo_font_options_t * options;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rr", &surface_res, &options_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(surface, cairo_surface_t *, &surface_res, surface_resid, "cairo_surface", le_cairo_surface);
	ZEND_FETCH_RESOURCE(options, cairo_font_options_t *, &options_res, options_resid, "cairo_font_options", le_cairo_font_options);


	do {
		cairo_surface_get_font_options(surface, options);
	} while (0);
}
/* }}} cairo_surface_get_font_options */


/* {{{ proto array cairo_path_to_array(resource cairo_path path)
  Extract drawing operations from path */
PHP_FUNCTION(cairo_path_to_array)
{
	zval * path_res = NULL;
	int path_resid = -1;
	cairo_path_t * path;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &path_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(path, cairo_path_t *, &path_res, path_resid, "cairo_path", le_cairo_path);


	array_init(return_value);

	do {
		int i, j, num_points;
		zval *data, *points, *point;  
		cairo_path_data_t *path_data = path->data;

		for (i = 0; i < path->num_data; i++) {
		  MAKE_STD_ZVAL(data);
		  array_init(data);

		  MAKE_STD_ZVAL(points);
		  array_init(points);

		  num_points = path_data->header.length - 1;

		  add_assoc_long(data, "type",   path_data->header.type);
		  add_assoc_long(data, "length", num_points);

		  for (j = 0; j < num_points; j++) {
			i++;

			path_data++;

			MAKE_STD_ZVAL(point);
			array_init(point);
			add_index_double(point, 0, path_data->point.x);
			add_index_double(point, 1, path_data->point.y);
			
			add_index_zval(points, j, point);
		  }

		  add_assoc_zval(data, "points", points);

		  add_next_index_zval(return_value, data);
		
		  path_data++;
		}
	} while (0);
}
/* }}} cairo_path_to_array */


/* {{{ proto void cairo_matrix_destroy(resource cairo_context cr)
  Destroy transformation matrix */
PHP_FUNCTION(cairo_marix_destroy)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &cr_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		FREE_RESOURCE(cr_res);
	} while (0);
}
/* }}} cairo_marix_destroy */


/* {{{ proto resource cairo_matrix cairo_get_matrix(resource cairo_context cr)
  Get current transformation matrix from drawing context */
PHP_FUNCTION(cairo_get_matrix)
{
	cairo_matrix_t * return_res = (cairo_matrix_t *)ecalloc(1, sizeof(cairo_matrix_t));
	long return_res_id = -1;
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &cr_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		cairo_get_matrix(cr, return_res);
	} while (0);
	return_res_id = ZEND_REGISTER_RESOURCE(return_value, return_res, le_cairo_matrix);
}
/* }}} cairo_get_matrix */


/* {{{ proto void cairo_set_matrix(resource cairo_context cr, resource cairo_matrix matrix)
  Set transformation matrix for drawing context */
PHP_FUNCTION(cairo_set_matrix)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;
	zval * matrix_res = NULL;
	int matrix_resid = -1;
	cairo_matrix_t * matrix;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rr", &cr_res, &matrix_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);
	ZEND_FETCH_RESOURCE(matrix, cairo_matrix_t *, &matrix_res, matrix_resid, "cairo_matrix", le_cairo_matrix);


	do {
		cairo_set_matrix(cr, matrix);
	} while (0);
}
/* }}} cairo_set_matrix */


/* {{{ proto void cairo_identity_matrix(resource cairo_context cr)
  Reset drawing context transformation matrix */
PHP_FUNCTION(cairo_identity_matrix)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &cr_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		cairo_identity_matrix(cr);
	} while (0);
}
/* }}} cairo_identity_matrix */


/* {{{ proto void cairo_matrix_invert(resource cairo_matrix matrix)
  Invert the given matrix */
PHP_FUNCTION(cairo_matrix_invert)
{
	zval * matrix_res = NULL;
	int matrix_resid = -1;
	cairo_matrix_t * matrix;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &matrix_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(matrix, cairo_matrix_t *, &matrix_res, matrix_resid, "cairo_matrix", le_cairo_matrix);


	do {
		cairo_matrix_invert(matrix);
	} while (0);
}
/* }}} cairo_matrix_invert */


/* {{{ proto resource cairo_matrix cairo_matrix_create(float xx, float yx, float xy, float yy, float x0, float y0)
  Create a new matrix from parameters */
PHP_FUNCTION(cairo_matrix_create)
{
	cairo_matrix_t * return_res = (cairo_matrix_t *)ecalloc(1, sizeof(cairo_matrix_t));
	long return_res_id = -1;
	double xx = 0.0;
	double yx = 0.0;
	double xy = 0.0;
	double yy = 0.0;
	double x0 = 0.0;
	double y0 = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dddddd", &xx, &yx, &xy, &yy, &x0, &y0) == FAILURE) {
		return;
	}
	do {
		cairo_matrix_init(return_res, xx, yx, xy, yy, x0, y0);
	} while (0);
	return_res_id = ZEND_REGISTER_RESOURCE(return_value, return_res, le_cairo_matrix);
}
/* }}} cairo_matrix_create */


/* {{{ proto resource cairo_matrix cairo_matrix_create_identity(void)
  Create a new identity matrix */
PHP_FUNCTION(cairo_matrix_create_identity)
{
	cairo_matrix_t * return_res = (cairo_matrix_t *)ecalloc(1, sizeof(cairo_matrix_t));
	long return_res_id = -1;
	if (ZEND_NUM_ARGS()>0)  {
		WRONG_PARAM_COUNT;
	}

	do {
		cairo_matrix_init_identity(return_res);
	} while (0);
	return_res_id = ZEND_REGISTER_RESOURCE(return_value, return_res, le_cairo_matrix);
}
/* }}} cairo_matrix_create_identity */


/* {{{ proto resource cairo_matrix cairo_matrix_create_rotate(float radians)
  Create a new rotation matrix */
PHP_FUNCTION(cairo_matrix_create_rotate)
{
	cairo_matrix_t * return_res = (cairo_matrix_t *)ecalloc(1, sizeof(cairo_matrix_t));
	long return_res_id = -1;
	double radians = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "d", &radians) == FAILURE) {
		return;
	}
	do {
		cairo_matrix_init_rotate(return_res, radians);
	} while (0);
	return_res_id = ZEND_REGISTER_RESOURCE(return_value, return_res, le_cairo_matrix);
}
/* }}} cairo_matrix_create_rotate */


/* {{{ proto resource cairo_matrix cairo_matrix_create_translate(float dx, float dy)
  Create a new translation matrix */
PHP_FUNCTION(cairo_matrix_create_translate)
{
	cairo_matrix_t * return_res = (cairo_matrix_t *)ecalloc(1, sizeof(cairo_matrix_t));
	long return_res_id = -1;
	double dx = 0.0;
	double dy = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dd", &dx, &dy) == FAILURE) {
		return;
	}
	do {
		cairo_matrix_init_translate(return_res, dx, dy);
	} while (0);
	return_res_id = ZEND_REGISTER_RESOURCE(return_value, return_res, le_cairo_matrix);
}
/* }}} cairo_matrix_create_translate */


/* {{{ proto resource cairo_matrix cairo_matrix_create_scale(float sx, float sy)
  Create a new scaling matrix */
PHP_FUNCTION(cairo_matrix_create_scale)
{
	cairo_matrix_t * return_res = (cairo_matrix_t *)ecalloc(1, sizeof(cairo_matrix_t));
	long return_res_id = -1;
	double sx = 0.0;
	double sy = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dd", &sx, &sy) == FAILURE) {
		return;
	}
	do {
		cairo_matrix_init_scale(return_res, sx, sy);
	} while (0);
	return_res_id = ZEND_REGISTER_RESOURCE(return_value, return_res, le_cairo_matrix);
}
/* }}} cairo_matrix_create_scale */


/* {{{ proto resource cairo_matrix_multiply(resource cairo_matrix m1, resource cairo_matrix m2)
  Multiply two transformation matrixes */
PHP_FUNCTION(cairo_matrix_multiply)
{
	void * return_res;
	long return_res_id = -1;
	zval * m1_res = NULL;
	int m1_resid = -1;
	cairo_matrix_t * m1;
	zval * m2_res = NULL;
	int m2_resid = -1;
	cairo_matrix_t * m2;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rr", &m1_res, &m2_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(m1, cairo_matrix_t *, &m1_res, m1_resid, "cairo_matrix", le_cairo_matrix);
	ZEND_FETCH_RESOURCE(m2, cairo_matrix_t *, &m2_res, m2_resid, "cairo_matrix", le_cairo_matrix);


	do {
		cairo_matrix_multiply(return_res, m1, m2);
	} while (0);
}
/* }}} cairo_matrix_multiply */


/* {{{ proto void cairo_matrix_rotate(resource cairo_matrix matrix, float radians)
  Rote a matrix */
PHP_FUNCTION(cairo_matrix_rotate)
{
	zval * matrix_res = NULL;
	int matrix_resid = -1;
	cairo_matrix_t * matrix;
	double radians = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rd", &matrix_res, &radians) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(matrix, cairo_matrix_t *, &matrix_res, matrix_resid, "cairo_matrix", le_cairo_matrix);


	do {
		cairo_matrix_rotate(matrix, radians);
	} while (0);
}
/* }}} cairo_matrix_rotate */


/* {{{ proto void cairo_matrix_translate(resource cairo_matrix matrix, float dx, float dy)
  Translate a matrix */
PHP_FUNCTION(cairo_matrix_translate)
{
	zval * matrix_res = NULL;
	int matrix_resid = -1;
	cairo_matrix_t * matrix;
	double dx = 0.0;
	double dy = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rdd", &matrix_res, &dx, &dy) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(matrix, cairo_matrix_t *, &matrix_res, matrix_resid, "cairo_matrix", le_cairo_matrix);


	do {
		cairo_matrix_translate(matrix, dx, dy);
	} while (0);
}
/* }}} cairo_matrix_translate */


/* {{{ proto void cairo_matrix_scale(resource cairo_matrix matrix, float sx, float sy)
  Scale a matrix */
PHP_FUNCTION(cairo_matrix_scale)
{
	zval * matrix_res = NULL;
	int matrix_resid = -1;
	cairo_matrix_t * matrix;
	double sx = 0.0;
	double sy = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rdd", &matrix_res, &sx, &sy) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(matrix, cairo_matrix_t *, &matrix_res, matrix_resid, "cairo_matrix", le_cairo_matrix);


	do {
		cairo_matrix_scale(matrix, sx, sy);
	} while (0);
}
/* }}} cairo_matrix_scale */


/* {{{ proto void cairo_transform(resource cairo_context cr, resource cairo_matrix matrix)
  Add transformation to a drawing context */
PHP_FUNCTION(cairo_transform)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;
	zval * matrix_res = NULL;
	int matrix_resid = -1;
	cairo_matrix_t * matrix;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rr", &cr_res, &matrix_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);
	ZEND_FETCH_RESOURCE(matrix, cairo_matrix_t *, &matrix_res, matrix_resid, "cairo_matrix", le_cairo_matrix);


	do {
		cairo_transform(cr, matrix);
	} while (0);
}
/* }}} cairo_transform */


/* {{{ proto resource cairo_matrix cairo_pattern_get_matrix(resource cairo_pattern pattern)
  Get fill pattern transformation matrix */
PHP_FUNCTION(cairo_pattern_get_matrix)
{
	cairo_matrix_t * return_res = (cairo_matrix_t *)ecalloc(1, sizeof(cairo_matrix_t));
	long return_res_id = -1;
	zval * pattern_res = NULL;
	int pattern_resid = -1;
	cairo_pattern_t * pattern;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &pattern_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(pattern, cairo_pattern_t *, &pattern_res, pattern_resid, "cairo_pattern", le_cairo_pattern);


	do {
		cairo_pattern_get_matrix(pattern, return_res);
	} while (0);
	return_res_id = ZEND_REGISTER_RESOURCE(return_value, return_res, le_cairo_matrix);
}
/* }}} cairo_pattern_get_matrix */


/* {{{ proto void cairo_pattern_set_matrix(resource cairo_pattern pattern, resource cairo_matrix matrix)
  Set fill pattern transformation matrix */
PHP_FUNCTION(cairo_pattern_set_matrix)
{
	zval * pattern_res = NULL;
	int pattern_resid = -1;
	cairo_pattern_t * pattern;
	zval * matrix_res = NULL;
	int matrix_resid = -1;
	cairo_matrix_t * matrix;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rr", &pattern_res, &matrix_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(pattern, cairo_pattern_t *, &pattern_res, pattern_resid, "cairo_pattern", le_cairo_pattern);
	ZEND_FETCH_RESOURCE(matrix, cairo_matrix_t *, &matrix_res, matrix_resid, "cairo_matrix", le_cairo_matrix);


	do {
		cairo_pattern_set_matrix(pattern, matrix);
	} while (0);
}
/* }}} cairo_pattern_set_matrix */


/* {{{ proto resource cairo_matrix cairo_get_font_matrix(resource cairo_context cr)
  Get current font transformation from drawing context */
PHP_FUNCTION(cairo_get_font_matrix)
{
	cairo_matrix_t * return_res = (cairo_matrix_t *)ecalloc(1, sizeof(cairo_matrix_t));
	long return_res_id = -1;
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &cr_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		cairo_get_font_matrix(cr, return_res);
	} while (0);
	return_res_id = ZEND_REGISTER_RESOURCE(return_value, return_res, le_cairo_matrix);
}
/* }}} cairo_get_font_matrix */


/* {{{ proto void cairo_set_matrix(resource cairo_context cr, resource cairo_matrix matrix)
  Set font transformation matrix for drawing context */
PHP_FUNCTION(cairo_set_font_matrix)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;
	zval * matrix_res = NULL;
	int matrix_resid = -1;
	cairo_matrix_t * matrix;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rr", &cr_res, &matrix_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);
	ZEND_FETCH_RESOURCE(matrix, cairo_matrix_t *, &matrix_res, matrix_resid, "cairo_matrix", le_cairo_matrix);


	do {
		cairo_set_font_matrix(cr, matrix);
	} while (0);
}
/* }}} cairo_set_font_matrix */


/* {{{ proto void cairo_scaled_font_destroy(resource cairo_scaled_font scaled_font)
  Destroy scaled font resource */
PHP_FUNCTION(cairo_scaled_font_destroy)
{
	zval * scaled_font_res = NULL;
	int scaled_font_resid = -1;
	cairo_scaled_font_t * scaled_font;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &scaled_font_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(scaled_font, cairo_scaled_font_t *, &scaled_font_res, scaled_font_resid, "cairo_scaled_font", le_cairo_scaled_font);


	do {
		FREE_RESOURCE(scaled_font_res);
	} while (0);
}
/* }}} cairo_scaled_font_destroy */


/* {{{ proto resource cairo_scaled_font cairo_scaled_font_create(resource cairo_font_face font_face,  resource cairo_matrix font_matrix,  resource cairo_matrix ctm,  resource cairo_font_options options)
  Create a scaled font resource */
PHP_FUNCTION(cairo_scaled_font_create)
{
	cairo_scaled_font_t * return_res;
	long return_res_id = -1;
	zval * font_face_res = NULL;
	int font_face_resid = -1;
	cairo_font_face_t * font_face;
	zval * font_matrix_res = NULL;
	int font_matrix_resid = -1;
	cairo_matrix_t * font_matrix;
	zval * ctm_res = NULL;
	int ctm_resid = -1;
	cairo_matrix_t * ctm;
	zval * options_res = NULL;
	int options_resid = -1;
	cairo_font_options_t * options;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rrrr", &font_face_res, &font_matrix_res, &ctm_res, &options_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(font_face, cairo_font_face_t *, &font_face_res, font_face_resid, "cairo_font_face", le_cairo_font_face);
	ZEND_FETCH_RESOURCE(font_matrix, cairo_matrix_t *, &font_matrix_res, font_matrix_resid, "cairo_matrix", le_cairo_matrix);
	ZEND_FETCH_RESOURCE(ctm, cairo_matrix_t *, &ctm_res, ctm_resid, "cairo_matrix", le_cairo_matrix);
	ZEND_FETCH_RESOURCE(options, cairo_font_options_t *, &options_res, options_resid, "cairo_font_options", le_cairo_font_options);


	do {
		return_res = cairo_scaled_font_create(font_face,  font_matrix,  ctm, options);
	} while (0);
	return_res_id = ZEND_REGISTER_RESOURCE(return_value, return_res, le_cairo_scaled_font);
}
/* }}} cairo_scaled_font_create */


/* {{{ proto int cairo_scaled_font_get_type(resource cairo_scaled_font scaled_font)
  Get scaled font type */
PHP_FUNCTION(cairo_scaled_font_get_type)
{
	zval * scaled_font_res = NULL;
	int scaled_font_resid = -1;
	cairo_scaled_font_t * scaled_font;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &scaled_font_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(scaled_font, cairo_scaled_font_t *, &scaled_font_res, scaled_font_resid, "cairo_scaled_font", le_cairo_scaled_font);


	do {
		RETURN_LONG(cairo_scaled_font_get_type(scaled_font));
	} while (0);
}
/* }}} cairo_scaled_font_get_type */


/* {{{ proto int cairo_scaled_font_status(resource cairo_scaled_font scaled_font)
  Get scaled font status */
PHP_FUNCTION(cairo_scaled_font_status)
{
	zval * scaled_font_res = NULL;
	int scaled_font_resid = -1;
	cairo_scaled_font_t * scaled_font;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &scaled_font_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(scaled_font, cairo_scaled_font_t *, &scaled_font_res, scaled_font_resid, "cairo_scaled_font", le_cairo_scaled_font);


	do {
		RETURN_LONG(cairo_scaled_font_status(scaled_font));
	} while (0);
}
/* }}} cairo_scaled_font_status */


/* {{{ proto resource cairo_matrix cairo_scaled_font_get_font_matrix(resource cairo_scaled_font scaled_font)
  Get scaled font user space transformation matrix */
PHP_FUNCTION(cairo_scaled_font_get_font_matrix)
{
	cairo_matrix_t * return_res = (cairo_matrix_t *)ecalloc(1, sizeof(cairo_matrix_t));
	long return_res_id = -1;
	zval * scaled_font_res = NULL;
	int scaled_font_resid = -1;
	cairo_scaled_font_t * scaled_font;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &scaled_font_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(scaled_font, cairo_scaled_font_t *, &scaled_font_res, scaled_font_resid, "cairo_scaled_font", le_cairo_scaled_font);


	do {
		cairo_scaled_font_get_font_matrix(scaled_font, return_res);
	} while (0);
	return_res_id = ZEND_REGISTER_RESOURCE(return_value, return_res, le_cairo_matrix);
}
/* }}} cairo_scaled_font_get_font_matrix */


/* {{{ proto resource cairo_matrix cairo_scaled_font_get_font_ctm(resource cairo_scaled_font scaled_font)
  Get scaled font device space transformation matrix */
PHP_FUNCTION(cairo_scaled_font_get_ctm)
{
	cairo_matrix_t * return_res = (cairo_matrix_t *)ecalloc(1, sizeof(cairo_matrix_t));
	long return_res_id = -1;
	zval * scaled_font_res = NULL;
	int scaled_font_resid = -1;
	cairo_scaled_font_t * scaled_font;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &scaled_font_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(scaled_font, cairo_scaled_font_t *, &scaled_font_res, scaled_font_resid, "cairo_scaled_font", le_cairo_scaled_font);


	do {
		cairo_scaled_font_get_ctm(scaled_font, return_res);
	} while (0);
	return_res_id = ZEND_REGISTER_RESOURCE(return_value, return_res, le_cairo_matrix);
}
/* }}} cairo_scaled_font_get_ctm */


/* {{{ proto resource cairo_font_options cairo_scaled_font_get_font_options(resource cairo_scaled_font scaled_font)
  Get scaled fonts font options */
PHP_FUNCTION(cairo_scaled_font_get_font_options)
{
	cairo_font_options_t * return_res;
	long return_res_id = -1;
	zval * scaled_font_res = NULL;
	int scaled_font_resid = -1;
	cairo_scaled_font_t * scaled_font;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &scaled_font_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(scaled_font, cairo_scaled_font_t *, &scaled_font_res, scaled_font_resid, "cairo_scaled_font", le_cairo_scaled_font);


	do {
		cairo_scaled_font_get_font_options(scaled_font, return_res);
	} while (0);
	return_res_id = ZEND_REGISTER_RESOURCE(return_value, return_res, le_cairo_font_options);
}
/* }}} cairo_scaled_font_get_font_options */


/* {{{ proto resource cairo_font_face cairo_scaled_font_get_font_face(resource cairo_scaled_font scaled_font)
  Get scaled fonts face */
PHP_FUNCTION(cairo_scaled_font_get_font_face)
{
	cairo_font_face_t * return_res;
	long return_res_id = -1;
	zval * scaled_font_res = NULL;
	int scaled_font_resid = -1;
	cairo_scaled_font_t * scaled_font;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &scaled_font_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(scaled_font, cairo_scaled_font_t *, &scaled_font_res, scaled_font_resid, "cairo_scaled_font", le_cairo_scaled_font);


	do {
		return_res = cairo_scaled_font_get_font_face(scaled_font);
	} while (0);
	return_res_id = ZEND_REGISTER_RESOURCE(return_value, return_res, le_cairo_font_face);
}
/* }}} cairo_scaled_font_get_font_face */


/* {{{ proto void cairo_set_scaled_font(resource cairo_context cr, resource cairo_scaled_font scaled_font)
  Set scaled font for drawing context */
PHP_FUNCTION(cairo_set_scaled_font)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;
	zval * scaled_font_res = NULL;
	int scaled_font_resid = -1;
	cairo_scaled_font_t * scaled_font;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rr", &cr_res, &scaled_font_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);
	ZEND_FETCH_RESOURCE(scaled_font, cairo_scaled_font_t *, &scaled_font_res, scaled_font_resid, "cairo_scaled_font", le_cairo_scaled_font);


	do {
		cairo_set_scaled_font(cr, scaled_font);
	} while (0);
}
/* }}} cairo_set_scaled_font */


/* {{{ proto resource cairo_font_options cairo_surface_get_scaled_font_options(resource cairo_surface surface)
  Get scaled font options form surface */
PHP_FUNCTION(cairo_surface_get_scaled_font_options)
{
	cairo_font_options_t * return_res;
	long return_res_id = -1;
	zval * surface_res = NULL;
	int surface_resid = -1;
	cairo_surface_t * surface;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &surface_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(surface, cairo_surface_t *, &surface_res, surface_resid, "cairo_surface", le_cairo_surface);


	do {
		cairo_surface_get_scaled_font_options(surface, return_res);
	} while (0);
	return_res_id = ZEND_REGISTER_RESOURCE(return_value, return_res, le_cairo_font_options);
}
/* }}} cairo_surface_get_scaled_font_options */


/* {{{ proto array cairo_svg_get_versions(void)
  Get available SVG versions */
PHP_FUNCTION(cairo_svg_get_versions)
{
	if (ZEND_NUM_ARGS()>0)  {
		WRONG_PARAM_COUNT;
	}

	array_init(return_value);

	do {
		const cairo_svg_version_t *versions;
		int num_versions, i;

		cairo_svg_get_versions(&versions, &num_versions);

		for (i = 0; i < num_versions; i++) {
		  add_next_index_long(return_value, versions[i]);
		}
	} while (0);
}
/* }}} cairo_svg_get_versions */


/* {{{ proto array cairo_get_current_point(resource cairo_context cr)
  Get current drawing position from drawing context */
PHP_FUNCTION(cairo_get_current_point)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &cr_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	array_init(return_value);

	do {
		double x, y;

		cairo_get_current_point(cr, &x, &y);

		add_next_index_double(return_value, x);
		add_next_index_double(return_value, y);
	} while (0);
}
/* }}} cairo_get_current_point */


/* {{{ proto array cairo_matrix_transform_point(resource cairo_matrix matrix, float x, float y)
  Transform absolute point using transformation matrix */
PHP_FUNCTION(cairo_matrix_transform_point)
{
	zval * matrix_res = NULL;
	int matrix_resid = -1;
	cairo_matrix_t * matrix;
	double x = 0.0;
	double y = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rdd", &matrix_res, &x, &y) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(matrix, cairo_matrix_t *, &matrix_res, matrix_resid, "cairo_matrix", le_cairo_matrix);


	array_init(return_value);

	do {
		cairo_matrix_transform_point(matrix, &x, &y);

		add_next_index_double(return_value, x);
		add_next_index_double(return_value, y);
	} while (0);
}
/* }}} cairo_matrix_transform_point */


/* {{{ proto array cairo_matrix_transform_distance(resource cairo_matrix matrix, float dx, float dy)
  Transform relative distance using transformation matrix */
PHP_FUNCTION(cairo_matrix_transform_distance)
{
	zval * matrix_res = NULL;
	int matrix_resid = -1;
	cairo_matrix_t * matrix;
	double dx = 0.0;
	double dy = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rdd", &matrix_res, &dx, &dy) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(matrix, cairo_matrix_t *, &matrix_res, matrix_resid, "cairo_matrix", le_cairo_matrix);


	array_init(return_value);

	do {
		cairo_matrix_transform_distance(matrix, &dx, &dy);

		add_next_index_double(return_value, dx);
		add_next_index_double(return_value, dy);
	} while (0);
}
/* }}} cairo_matrix_transform_distance */


/* {{{ proto array cairo_device_to_user(resource cairo_context cr, float x, float y)
  Convert device space coordinates to user space */
PHP_FUNCTION(cairo_device_to_user)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;
	double x = 0.0;
	double y = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rdd", &cr_res, &x, &y) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	array_init(return_value);

	do {
		cairo_device_to_user(cr, &x, &y);

		add_next_index_double(return_value, x);
		add_next_index_double(return_value, y);
	} while (0);
}
/* }}} cairo_device_to_user */


/* {{{ proto array cairo_device_to_user_distance(resource cairo_context cr, float dx, float dy)
  Convert device space relative position to user space */
PHP_FUNCTION(cairo_device_to_user_distance)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;
	double dx = 0.0;
	double dy = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rdd", &cr_res, &dx, &dy) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	array_init(return_value);

	do {
		cairo_device_to_user_distance(cr, &dx, &dy);

		add_next_index_double(return_value, dx);
		add_next_index_double(return_value, dy);
	} while (0);
}
/* }}} cairo_device_to_user_distance */


/* {{{ proto array cairo_user_to_device(resource cairo_context cr, float x, float y)
  Convert user space coordinates to device space */
PHP_FUNCTION(cairo_user_to_device)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;
	double x = 0.0;
	double y = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rdd", &cr_res, &x, &y) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	array_init(return_value);

	do {
		cairo_user_to_device(cr, &x, &y);

		add_next_index_double(return_value, x);
		add_next_index_double(return_value, y);
	} while (0);
}
/* }}} cairo_user_to_device */


/* {{{ proto array cairo_user_to_device_distance(resource cairo_context cr, float dx, float dy)
  Convert user space relative position to device space */
PHP_FUNCTION(cairo_user_to_device_distance)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;
	double dx = 0.0;
	double dy = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rdd", &cr_res, &dx, &dy) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	array_init(return_value);

	do {
		cairo_user_to_device_distance(cr, &dx, &dy);

		add_next_index_double(return_value, dx);
		add_next_index_double(return_value, dy);
	} while (0);
}
/* }}} cairo_user_to_device_distance */


/* {{{ proto array cairo_surface_get_device_offset(resource cairo_surface surface)
  Get surface to device translation offset */
PHP_FUNCTION(cairo_surface_get_device_offset)
{
	zval * surface_res = NULL;
	int surface_resid = -1;
	cairo_surface_t * surface;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &surface_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(surface, cairo_surface_t *, &surface_res, surface_resid, "cairo_surface", le_cairo_surface);


	array_init(return_value);

	do {
		double x_offset, y_offset;

		cairo_surface_get_device_offset(surface, &x_offset, &y_offset);

		add_next_index_double(return_value, x_offset);
		add_next_index_double(return_value, y_offset);
	} while (0);
}
/* }}} cairo_surface_get_device_offset */


/* {{{ proto array cairo_fill_extends(resource cairo_context cr)
  Get current fill extends from drawing context */
PHP_FUNCTION(cairo_fill_extents)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &cr_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	array_init(return_value);

	do {
		double x1, y1, x2, y2;

		cairo_fill_extends(cr, &x1, &y1, &x2, &y2);
		add_next_index_double(return_value, x1);
		add_next_index_double(return_value, y1);
		add_next_index_double(return_value, x2);
		add_next_index_double(return_value, y2);
	} while (0);
}
/* }}} cairo_fill_extents */


/* {{{ proto array cairo_stroke_extends(resource cairo_context cr)
  Get current stroke extends from drawing context */
PHP_FUNCTION(cairo_stroke_extents)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &cr_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	array_init(return_value);

	do {
		double x1, y1, x2, y2;

		cairo_stroke_extends(cr, &x1, &y1, &x2, &y2);
		add_next_index_double(return_value, x1);
		add_next_index_double(return_value, y1);
		add_next_index_double(return_value, x2);
		add_next_index_double(return_value, y2);
	} while (0);
}
/* }}} cairo_stroke_extents */


/* {{{ proto array cairo_text_extends(resource cairo_context cr, string text)
  Get text extends for given string */
PHP_FUNCTION(cairo_text_extends)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;
	const char * text = NULL;
	int text_len = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rs", &cr_res, &text, &text_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	array_init(return_value);

	do {
		cairo_text_extents_t ext;

		cairo_text_extents(cr, text, &ext);

		add_assoc_double(return_value, "x_bearing", ext.x_bearing);
		add_assoc_double(return_value, "y_bearing", ext.y_bearing);
		add_assoc_double(return_value, "width",     ext.width);
		add_assoc_double(return_value, "height",    ext.height);
		add_assoc_double(return_value, "x_advance", ext.x_advance);
		add_assoc_double(return_value, "y_advance", ext.y_advance);
	} while (0);
}
/* }}} cairo_text_extends */


/* {{{ proto int cairo_surface_get_content(resource cairo_surface surface)
  Get surface content type */
PHP_FUNCTION(cairo_surface_get_content)
{
	zval * surface_res = NULL;
	int surface_resid = -1;
	cairo_surface_t * surface;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &surface_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(surface, cairo_surface_t *, &surface_res, surface_resid, "cairo_surface", le_cairo_surface);


	do {
		RETURN_LONG(cairo_surface_get_content(surface));
	} while (0);
}
/* }}} cairo_surface_get_content */


/* {{{ proto void cairo_pattern_set_filter(resource cairo_pattern pattern, int filter)
  Set fill pattern filter type */
PHP_FUNCTION(cairo_pattern_set_filter)
{
	zval * pattern_res = NULL;
	int pattern_resid = -1;
	cairo_pattern_t * pattern;
	long filter = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &pattern_res, &filter) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(pattern, cairo_pattern_t *, &pattern_res, pattern_resid, "cairo_pattern", le_cairo_pattern);


	do {
		cairo_pattern_set_filter(pattern, filter);
	} while (0);
}
/* }}} cairo_pattern_set_filter */


/* {{{ proto void cairo_push_group_with_content(resource cairo_context cr, int content)
  Redirect drawing to an intermediate surface of given content type */
PHP_FUNCTION(cairo_push_group_with_content)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;
	long content = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &cr_res, &content) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	do {
		cairo_push_group_with_content(cr, content);
	} while (0);
}
/* }}} cairo_push_group_with_content */


/* {{{ proto resource cairo_surface cairo_surface_create_similar(resource cairo_surface surface, int content, int width, int height)
  Create a new surface similar to an existing one */
PHP_FUNCTION(cairo_surface_create_similar)
{
	cairo_surface_t * return_res;
	long return_res_id = -1;
	zval * surface_res = NULL;
	int surface_resid = -1;
	cairo_surface_t * surface;
	long content = 0;
	long width = 0;
	long height = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rlll", &surface_res, &content, &width, &height) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(surface, cairo_surface_t *, &surface_res, surface_resid, "cairo_surface", le_cairo_surface);


	do {
		return_res = cairo_surface_create_similar(surface, content, width, height);
	} while (0);
	return_res_id = ZEND_REGISTER_RESOURCE(return_value, return_res, le_cairo_surface);
}
/* }}} cairo_surface_create_similar */


/* {{{ proto void cairo_set_dash(resource cairo_context cr, array dashes, float offset)
  Set line dash style */
PHP_FUNCTION(cairo_set_dash)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;
	zval * dashes = NULL;
	HashTable * dashes_hash = NULL;
	double offset = 0.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ra/d", &cr_res, &dashes, &offset) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);
	dashes_hash = HASH_OF(dashes);


	do {
		int num_dashes, n;
		double *dash_values, *pd;
		zval **ppzval;
 
		num_dashes = zend_hash_num_elements(Z_ARRVAL_P(dashes));
		dash_values = (double *)calloc(sizeof(double), num_dashes);    

		zend_hash_internal_pointer_reset(Z_ARRVAL_P(dashes));
		
		pd = dash_values;
		for (n = 0; n < num_dashes; n++) {
		  zend_hash_get_current_data(Z_ARRVAL_P(dashes), (void**)&ppzval);
		  *pd++ = Z_DVAL_PP(ppzval);
		}

		cairo_set_dash(cr, dash_values, num_dashes, offset);
	} while (0);
}
/* }}} cairo_set_dash */


/* {{{ proto array cairo_font_extents(resource cairo_context cr)
  Get font extets for current font */
PHP_FUNCTION(cairo_font_extents)
{
	zval * cr_res = NULL;
	int cr_resid = -1;
	cairo_t * cr;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &cr_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(cr, cairo_t *, &cr_res, cr_resid, "cairo_context", le_cairo_context);


	array_init(return_value);

	do {
		cairo_font_extents_t ext;

		cairo_font_extents(cr, &ext);

		add_assoc_double(return_value, "ascent", ext.ascent);
		add_assoc_double(return_value, "descent", ext.descent);
		add_assoc_double(return_value, "height", ext.height);
		add_assoc_double(return_value, "max_x_advance", ext.max_x_advance);
		add_assoc_double(return_value, "max_y_advance", ext.max_y_advance);
	} while (0);
}
/* }}} cairo_font_extents */


/* {{{ proto array cairo_scaled_font_extents(resource cairo_scaled_font font)
  Get font extents for given scaled font */
PHP_FUNCTION(cairo_scaled_font_extents)
{
	zval * font_res = NULL;
	int font_resid = -1;
	cairo_scaled_font_t * font;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &font_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(font, cairo_scaled_font_t *, &font_res, font_resid, "cairo_scaled_font", le_cairo_scaled_font);


	array_init(return_value);

	do {
		cairo_font_extents_t ext;

		cairo_scaled_font_extents(font, &ext);

		add_assoc_double(return_value, "ascent", ext.ascent);
		add_assoc_double(return_value, "descent", ext.descent);
		add_assoc_double(return_value, "height", ext.height);
		add_assoc_double(return_value, "max_x_advance", ext.max_x_advance);
		add_assoc_double(return_value, "max_y_advance", ext.max_y_advance);
	} while (0);
}
/* }}} cairo_scaled_font_extents */


/* {{{ proto array cairo_scaled_font_text_extends(resource cairo_scaled_font font, string text)
  Get text extends for a string using the given scaled font */
PHP_FUNCTION(cairo_scaled_font_text_extends)
{
	zval * font_res = NULL;
	int font_resid = -1;
	cairo_scaled_font_t * font;
	const char * text = NULL;
	int text_len = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rs", &font_res, &text, &text_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(font, cairo_scaled_font_t *, &font_res, font_resid, "cairo_scaled_font", le_cairo_scaled_font);


	array_init(return_value);

	do {
		cairo_text_extents_t ext;

		cairo_scaled_font_text_extents(font, text, &ext);

		add_assoc_double(return_value, "x_bearing", ext.x_bearing);
		add_assoc_double(return_value, "y_bearing", ext.y_bearing);
		add_assoc_double(return_value, "width",     ext.width);
		add_assoc_double(return_value, "height",    ext.height);
		add_assoc_double(return_value, "x_advance", ext.x_advance);
		add_assoc_double(return_value, "y_advance", ext.y_advance);
	} while (0);
}
/* }}} cairo_scaled_font_text_extends */

#endif /* HAVE_CAIRO */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
