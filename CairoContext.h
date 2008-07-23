
PHP_METHOD(CairoContext, __construct);
ZEND_BEGIN_ARG_INFO_EX(CairoContext____construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
	ZEND_ARG_OBJ_INFO(0, obj, CairoSurface, 1)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, appendPath);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__append_path_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_OBJ_INFO(0, p, CairoPath, 1)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, arc);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__arc_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 5)
  ZEND_ARG_INFO(0, xc)
  ZEND_ARG_INFO(0, yc)
  ZEND_ARG_INFO(0, radius)
  ZEND_ARG_INFO(0, angle1)
  ZEND_ARG_INFO(0, angle2)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, arcNegative);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__arc_negative_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 5)
  ZEND_ARG_INFO(0, xc)
  ZEND_ARG_INFO(0, yc)
  ZEND_ARG_INFO(0, radius)
  ZEND_ARG_INFO(0, angle1)
  ZEND_ARG_INFO(0, angle2)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, clip);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__clip_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, clipExtents);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__clip_extents_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, clipPreserve);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__clip_preserve_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, closePath);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__close_path_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, copyClipRectangleList);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__copy_clip_rectangle_list_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, copyPage);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__copy_page_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, copyPath);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__copy_path_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, copyPathFlat);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__copy_path_flat_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, curveTo);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__curve_to_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 6)
  ZEND_ARG_INFO(0, x1)
  ZEND_ARG_INFO(0, y1)
  ZEND_ARG_INFO(0, x2)
  ZEND_ARG_INFO(0, y2)
  ZEND_ARG_INFO(0, x3)
  ZEND_ARG_INFO(0, y3)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, deviceToUser);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__device_to_user_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, x)
  ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, deviceToUserDistance);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__device_to_user_distance_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, x)
  ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, fill);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__fill_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, fillExtents);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__fill_extents_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, fillPreserve);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__fill_preserve_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, fontExtents);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__font_extents_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, getAntialias);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__get_antialias_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, getCurrentPoint);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__get_current_point_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, getDash);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__get_dash_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, getDashCount);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__get_dash_count_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, getFillRule);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__get_fill_rule_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, getFontFace);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__get_font_face_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, getFontMatrix);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__get_font_matrix_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, getFontOptions);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__get_font_options_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, getGroupTarget);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__get_group_target_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, getLineCap);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__get_line_cap_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, getLineJoin);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__get_line_join_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, getLineWidth);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__get_line_width_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, getMatrix);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__get_matrix_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, getMiterLimit);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__get_miter_limit_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, getOperator);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__get_operator_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, getScaledFont);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__get_scaled_font_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, getSource);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__get_source_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, getTarget);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__get_target_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, getTolerance);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__get_tolerance_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, glyphExtents);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__glyph_extents_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
#if (PHP_MINOR_VERSION > 0)  
  ZEND_ARG_ARRAY_INFO(0, obj, 1)
#else
  ZEND_ARG_INFO(0, obj)
#endif
  ZEND_ARG_INFO(0, num)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, glyphPath);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__glyph_path_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
#if (PHP_MINOR_VERSION > 0)
  ZEND_ARG_ARRAY_INFO(0, obh, 1)
#else
  ZEND_ARG_INFO(0, obh);
#endif
  ZEND_ARG_INFO(0, num)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, hasCurrentPoint);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__has_current_point_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, identityMatrix);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__identity_matrix_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, inFill);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__in_fill_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, x)
  ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, inStroke);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__in_stroke_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, x)
  ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, lineTo);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__line_to_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, x)
  ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, mask);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__mask_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_OBJ_INFO(0, p, CairoPattern, 1)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, maskSurface);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__mask_surface_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_OBJ_INFO(0, s, CairoSurface, 1)
  ZEND_ARG_INFO(0, surface_x)
  ZEND_ARG_INFO(0, surface_y)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, moveTo);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__move_to_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, x)
  ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, newPath);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__new_path_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, newSubPath);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__new_sub_path_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, paint);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__paint_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, paintWithAlpha);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__paint_with_alpha_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, alpha)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, pathExtents);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__path_extents_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
  ZEND_ARG_OBJ_INFO(0, path, CairoPath, 1)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, popGroup);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__pop_group_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, popGroupToSource);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__pop_group_to_source_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, pushGroup);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__push_group_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, pushGroupWithContent);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__push_group_with_content_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, content)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, rectangle);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__rectangle_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 4)
  ZEND_ARG_INFO(0, x)
  ZEND_ARG_INFO(0, y)
  ZEND_ARG_INFO(0, width)
  ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, relCurveTo);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__rel_curve_to_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 6)
  ZEND_ARG_INFO(0, x1)
  ZEND_ARG_INFO(0, y1)
  ZEND_ARG_INFO(0, x2)
  ZEND_ARG_INFO(0, y2)
  ZEND_ARG_INFO(0, x3)
  ZEND_ARG_INFO(0, y3)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, relLineTo);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__rel_line_to_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, x)
  ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, relMoveTo);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__rel_move_to_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, x)
  ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, resetClip);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__reset_clip_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, restore);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__restore_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, rotate);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__rotate_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, angle)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, save);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__save_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, scale);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__scale_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, x)
  ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, selectFontFace);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__select_font_face_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, family)
  ZEND_ARG_INFO(0, slant)
  ZEND_ARG_INFO(0, weight)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, setAntialias);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__set_antialias_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
  ZEND_ARG_INFO(0, antialias)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, setDash);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__set_dash_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
#if (PHP_MINOR_VERSION > 0)
  ZEND_ARG_ARRAY_INFO(0, dashes, 1)
#else
  ZEND_ARG_INFO(0, dashes)
#endif
  ZEND_ARG_INFO(0, num_dashes)
  ZEND_ARG_INFO(0, offset)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, setFillRule);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__set_fill_rule_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, fill_rule)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, setFontFace);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__set_font_face_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
  ZEND_ARG_OBJ_INFO(0, obj, CairoFontFace, 1)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, setFontMatrix);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__set_font_matrix_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_OBJ_INFO(0, matrix, CairoMatrix, 1)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, setFontOptions);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__set_font_options_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_OBJ_INFO(0, options, CairoFontOptions, 1)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, setFontSize);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__set_font_size_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, size)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, setLineCap);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__set_line_cap_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, line_cap)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, setLineJoin);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__set_line_join_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, line_join)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, setLineWidth);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__set_line_width_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, width)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, setMatrix);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__set_matrix_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_OBJ_INFO(0, matix, CairoMatrix, 1)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, setMiterLimit);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__set_miter_limit_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, limit)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, setOperator);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__set_operator_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, op)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, setSource);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__set_source_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
  ZEND_ARG_OBJ_INFO(0, p, CairoPattern, 1)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, setSourceRgb);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__set_source_rgb_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 3)
  ZEND_ARG_INFO(0, red)
  ZEND_ARG_INFO(0, green)
  ZEND_ARG_INFO(0, blue)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, setSourceRgba);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__set_source_rgba_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 3)
  ZEND_ARG_INFO(0, red)
  ZEND_ARG_INFO(0, green)
  ZEND_ARG_INFO(0, blue)
  ZEND_ARG_INFO(0, alpha)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, setSourceSurface);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__set_source_surface_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_OBJ_INFO(0, surface, CairoSurface, 1)
  ZEND_ARG_INFO(0, x)
  ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, setTolerance);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__set_tolerance_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, tolerance)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, showGlyphs);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__show_glyphs_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
#if (PHP_MINOR_VERSION > 0)
  ZEND_ARG_ARRAY_INFO(0, obj, 1)
#else
  ZEND_ARG_INFO(0, obj)
#endif
  ZEND_ARG_INFO(0, num_glyphs)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, showPage);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__show_page_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, showText);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__show_text_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, obj)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, stroke);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__stroke_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, strokeExtents);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__stroke_extents_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, strokePreserve);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__stroke_preserve_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, textExtents);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__text_extents_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, str)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, textPath);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__text_path_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, obj)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, transform);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__transform_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_OBJ_INFO(0, matrix, CairoMatrix, 1)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, translate);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__translate_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, tx)
  ZEND_ARG_INFO(0, ty)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, userToDevice);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__user_to_device_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, x)
  ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoContext, userToDeviceDistance);
ZEND_BEGIN_ARG_INFO_EX(CairoContext__user_to_device_distance_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, dx)
  ZEND_ARG_INFO(0, dy)
ZEND_END_ARG_INFO()
