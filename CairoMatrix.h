PHP_METHOD(CairoMatrix, __construct);
ZEND_BEGIN_ARG_INFO_EX(CairoMatrix____construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 5)
  ZEND_ARG_INFO(0, yx)
  ZEND_ARG_INFO(0, xy)
  ZEND_ARG_INFO(0, yy)
  ZEND_ARG_INFO(0, x0)
  ZEND_ARG_INFO(0, y0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoMatrix, initRotate);
ZEND_BEGIN_ARG_INFO_EX(CairoMatrix__init_rotate_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, radians)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoMatrix, invert);
ZEND_BEGIN_ARG_INFO_EX(CairoMatrix__invert_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoMatrix, multiply);
ZEND_BEGIN_ARG_INFO_EX(CairoMatrix__multiply_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_OBJ_INFO(0, o2, CairoMatrix, 1)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoMatrix, rotate);
ZEND_BEGIN_ARG_INFO_EX(CairoMatrix__rotate_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, radians)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoMatrix, scale);
ZEND_BEGIN_ARG_INFO_EX(CairoMatrix__scale_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, sx)
  ZEND_ARG_INFO(0, xy)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoMatrix, transformDistance);
ZEND_BEGIN_ARG_INFO_EX(CairoMatrix__transform_distance_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, dx)
  ZEND_ARG_INFO(0, dy)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoMatrix, transformPoint);
ZEND_BEGIN_ARG_INFO_EX(CairoMatrix__transform_point_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, x)
  ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoMatrix, translate);
ZEND_BEGIN_ARG_INFO_EX(CairoMatrix__translate_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, tx)
  ZEND_ARG_INFO(0, ty)
ZEND_END_ARG_INFO()
