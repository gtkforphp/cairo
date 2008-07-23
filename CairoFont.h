
PHP_METHOD(CairoFontFace, __construct);
ZEND_BEGIN_ARG_INFO_EX(CairoFontFace____construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoFontOptions, __construct);
ZEND_BEGIN_ARG_INFO_EX(CairoFontOptions____construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoFontOptions, getAntialias);
ZEND_BEGIN_ARG_INFO_EX(CairoFontOptions__get_antialias_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoFontOptions, getHintMetrics);
ZEND_BEGIN_ARG_INFO_EX(CairoFontOptions__get_hint_metrics_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoFontOptions, getHintStyle);
ZEND_BEGIN_ARG_INFO_EX(CairoFontOptions__get_hint_style_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoFontOptions, getSubpixelOrder);
ZEND_BEGIN_ARG_INFO_EX(CairoFontOptions__get_subpixel_order_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoFontOptions, setAntialias);
ZEND_BEGIN_ARG_INFO_EX(CairoFontOptions__set_antialias_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
  ZEND_ARG_INFO(0, aa)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoFontOptions, setHintMetrics);
ZEND_BEGIN_ARG_INFO_EX(CairoFontOptions__set_hint_metrics_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
  ZEND_ARG_INFO(0, hm)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoFontOptions, setHintStyle);
ZEND_BEGIN_ARG_INFO_EX(CairoFontOptions__set_hint_style_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
  ZEND_ARG_INFO(0, hs)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoFontOptions, setSubpixelOrder);
ZEND_BEGIN_ARG_INFO_EX(CairoFontOptions__set_subpixel_order_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
  ZEND_ARG_INFO(0, so)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoScaledFont, __construct);
ZEND_BEGIN_ARG_INFO_EX(CairoScaledFont____construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 3)
  ZEND_ARG_OBJ_INFO(0, mx1, CairoMatrix, 1)
  ZEND_ARG_OBJ_INFO(0, mx2, CairoMatrix, 1)
  ZEND_ARG_OBJ_INFO(0, fo, CairoFontOptions, 1)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoScaledFont, extents);
ZEND_BEGIN_ARG_INFO_EX(CairoScaledFont__extents_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoScaledFont, getFontFace);
ZEND_BEGIN_ARG_INFO_EX(CairoScaledFont__get_font_face_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoScaledFont, textExtents);
ZEND_BEGIN_ARG_INFO_EX(CairoScaledFont__text_extents_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, str)
ZEND_END_ARG_INFO()
