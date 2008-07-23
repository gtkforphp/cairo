
PHP_METHOD(CairoPattern, __construct);
ZEND_BEGIN_ARG_INFO_EX(CairoPattern____construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoPattern, getMatrix);
ZEND_BEGIN_ARG_INFO_EX(CairoPattern__get_matrix_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoPattern, setMatrix);
ZEND_BEGIN_ARG_INFO_EX(CairoPattern__set_matrix_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_OBJ_INFO(0, m, CairoMatrix, 1)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoGradient, __contruct);
ZEND_BEGIN_ARG_INFO_EX(CairoGradient____contruct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoGradient, addColorStopRgb);
ZEND_BEGIN_ARG_INFO_EX(CairoGradient__add_color_stop_rgb_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 4)
  ZEND_ARG_INFO(0, offset)
  ZEND_ARG_INFO(0, red)
  ZEND_ARG_INFO(0, green)
  ZEND_ARG_INFO(0, blue)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoGradient, addColorStopRgba);
ZEND_BEGIN_ARG_INFO_EX(CairoGradient__add_color_stop_rgba_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 5)
  ZEND_ARG_INFO(0, offset)
  ZEND_ARG_INFO(0, red)
  ZEND_ARG_INFO(0, green)
  ZEND_ARG_INFO(0, blue)
  ZEND_ARG_INFO(0, alpha)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoLinearGradient, __construct);
ZEND_BEGIN_ARG_INFO_EX(CairoLinearGradient____construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 3)
  ZEND_ARG_INFO(0, y0)
  ZEND_ARG_INFO(0, x1)
  ZEND_ARG_INFO(0, y1)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoLinearGradient, getLinearPoints);
ZEND_BEGIN_ARG_INFO_EX(CairoLinearGradient__get_linear_points_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoRadialGradient, __constuct);
ZEND_BEGIN_ARG_INFO_EX(CairoRadialGradient____constuct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 6)
  ZEND_ARG_INFO(0, cx0)
  ZEND_ARG_INFO(0, cy0)
  ZEND_ARG_INFO(0, radius0)
  ZEND_ARG_INFO(0, cx1)
  ZEND_ARG_INFO(0, cy1)
  ZEND_ARG_INFO(0, radius1)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoRadialGradient, getRadialCircles);
ZEND_BEGIN_ARG_INFO_EX(CairoRadialGradient__get_radial_circles_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoSolidPattern, __construct);
ZEND_BEGIN_ARG_INFO_EX(CairoSolidPattern____construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, g)
  ZEND_ARG_INFO(0, b)
  ZEND_ARG_INFO(0, a)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoSolidPattern, getRgba);
ZEND_BEGIN_ARG_INFO_EX(CairoSolidPattern__get_rgba_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoSurfacePattern, __construct);
ZEND_BEGIN_ARG_INFO_EX(CairoSurfacePattern____construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoPattern, getExtend);
ZEND_BEGIN_ARG_INFO_EX(CairoPattern__get_extend_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoSurfacePattern, getFilter);
ZEND_BEGIN_ARG_INFO_EX(CairoSurfacePattern__get_filter_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoSurfacePattern, getSurface);
ZEND_BEGIN_ARG_INFO_EX(CairoSurfacePattern__get_surface_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoPattern, setExtend);
ZEND_BEGIN_ARG_INFO_EX(CairoPattern__set_extend_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, extend)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoSurfacePattern, setFilter);
ZEND_BEGIN_ARG_INFO_EX(CairoSurfacePattern__set_filter_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, filter)
ZEND_END_ARG_INFO()
