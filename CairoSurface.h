PHP_METHOD(CairoSurface, __construct);
ZEND_BEGIN_ARG_INFO_EX(CairoSurface____construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoSurface, createSimilar);
ZEND_BEGIN_ARG_INFO_EX(CairoSurface__create_similar_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 3)
  ZEND_ARG_INFO(0, content)
  ZEND_ARG_INFO(0, width)
  ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoSurface, finish);
ZEND_BEGIN_ARG_INFO_EX(CairoSurface__finish_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoSurface, flush);
ZEND_BEGIN_ARG_INFO_EX(CairoSurface__flush_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoSurface, getContent);
ZEND_BEGIN_ARG_INFO_EX(CairoSurface__get_content_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoSurface, getDeviceOffset);
ZEND_BEGIN_ARG_INFO_EX(CairoSurface__get_device_offset_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoSurface, getFontOptions);
ZEND_BEGIN_ARG_INFO_EX(CairoSurface__get_font_options_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoSurface, markDirtyRectangle);
ZEND_BEGIN_ARG_INFO_EX(CairoSurface__mark_dirty_rectangle_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
  ZEND_ARG_INFO(0, x)
  ZEND_ARG_INFO(0, y)
  ZEND_ARG_INFO(0, width)
  ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoSurface, setDeviceOffset);
ZEND_BEGIN_ARG_INFO_EX(CairoSurface__set_device_offset_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, x_offset)
  ZEND_ARG_INFO(0, y_offset)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoSurface, setFallbackResolution);
ZEND_BEGIN_ARG_INFO_EX(CairoSurface__set_fallback_resolution_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, x_ppi)
  ZEND_ARG_INFO(0, y_ppi)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoSurface, writeToPng);
ZEND_BEGIN_ARG_INFO_EX(CairoSurface__write_to_png_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, file)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoSurface, writeToPngStream);
ZEND_BEGIN_ARG_INFO_EX(CairoSurface__write_to_png_stream_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, zstream)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoImageSurface, __construct);
ZEND_BEGIN_ARG_INFO_EX(CairoImageSurface____construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, widthm)
  ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoImageSurface, createFromData);
ZEND_BEGIN_ARG_INFO_EX(CairoImageSurface__create_from_data_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 4)
  ZEND_ARG_INFO(0, obj)
  ZEND_ARG_INFO(0, format)
  ZEND_ARG_INFO(0, width)
  ZEND_ARG_INFO(0, height)
  ZEND_ARG_INFO(0, stride)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoImageSurface, createFromPng);
ZEND_BEGIN_ARG_INFO_EX(CairoImageSurface__create_from_png_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, file)
ZEND_END_ARG_INFO()


PHP_METHOD(CairoImageSurface, createFromPngStream);
ZEND_BEGIN_ARG_INFO_EX(CairoImageSurface__create_from_png_stream_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
 ZEND_ARG_INFO(0, zstream)
ZEND_END_ARG_INFO()
  
PHP_METHOD(CairoImageSurface, getData);
ZEND_BEGIN_ARG_INFO_EX(CairoImageSurface__get_data_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoImageSurface, getFormat);
ZEND_BEGIN_ARG_INFO_EX(CairoImageSurface__get_format_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoImageSurface, getHeight);
ZEND_BEGIN_ARG_INFO_EX(CairoImageSurface__get_height_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoImageSurface, getStride);
ZEND_BEGIN_ARG_INFO_EX(CairoImageSurface__get_stride_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoImageSurface, getWidth);
ZEND_BEGIN_ARG_INFO_EX(CairoImageSurface__get_width_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

#ifdef CAIRO_HAS_PDF_SURFACE

PHP_METHOD(CairoPDFSurface, __construct);
ZEND_BEGIN_ARG_INFO_EX(CairoPDFSurface____construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, wpts)
  ZEND_ARG_INFO(0, hpts)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoPDFSurface, setSize);
ZEND_BEGIN_ARG_INFO_EX(CairoPDFSurface__set_size_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, wpts)
  ZEND_ARG_INFO(0, hpts)
ZEND_END_ARG_INFO()

#endif

#ifdef CAIRO_HAS_PS_SURFACE

PHP_METHOD(CairoPSSurface, __construct);
ZEND_BEGIN_ARG_INFO_EX(CairoPSSurface____construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, wpts)
  ZEND_ARG_INFO(0, hpts)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoPSSurface, dscBeginPageSetup);
ZEND_BEGIN_ARG_INFO_EX(CairoPSSurface__dsc_begin_page_setup_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoPSSurface, dscBeginSetup);
ZEND_BEGIN_ARG_INFO_EX(CairoPSSurface__dsc_begin_setup_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoPSSurface, dscComment);
ZEND_BEGIN_ARG_INFO_EX(CairoPSSurface__dsc_comment_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoPSSurface, getLevels);
ZEND_BEGIN_ARG_INFO_EX(CairoPSSurface__get_levels_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoPSSurface, getLevelString);
ZEND_BEGIN_ARG_INFO_EX(CairoPSSurface__get_level_string_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoPSSurface, restrictToLevel);
ZEND_BEGIN_ARG_INFO_EX(CairoPSSurface__restrict_to_level_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, level)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoPSSurface, setEps);
ZEND_BEGIN_ARG_INFO_EX(CairoPSSurface__set_eps_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoPSSurface, setSize);
ZEND_BEGIN_ARG_INFO_EX(CairoPSSurface__set_size_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, wpts)
  ZEND_ARG_INFO(0, hpts)
ZEND_END_ARG_INFO()

#endif

#ifdef CAIRO_HAS_QUARTZ_SURFACE

PHP_METHOD(CairoQuartzSurface, __construct);
ZEND_BEGIN_ARG_INFO_EX(CairoQuartzSurface____construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, hpixels)
  ZEND_ARG_INFO(0, format)
ZEND_END_ARG_INFO()

#endif

#ifdef CAIRO_HAS_SVG_SURFACE

PHP_METHOD(CairoSVGSurface, __construct);
ZEND_BEGIN_ARG_INFO_EX(CairoSVGSurface____construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, wpts)
  ZEND_ARG_INFO(0, hpts)
ZEND_END_ARG_INFO()

#endif

#ifdef CAIRO_HAS_WIN32_SURFACE

PHP_METHOD(CairoWin32Surface, __construct);
ZEND_BEGIN_ARG_INFO_EX(CairoWin32Surface____construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

#endif

#ifdef CAIRO_HAS_XLIB_SURFACE

PHP_METHOD(CairoXlibSurface, __construct);
ZEND_BEGIN_ARG_INFO_EX(CairoXlibSurface____construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoXlibSurface, getDepth);
ZEND_BEGIN_ARG_INFO_EX(CairoXlibSurface__get_depth_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoXlibSurface, getHeight);
ZEND_BEGIN_ARG_INFO_EX(CairoXlibSurface__get_height_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CairoXlibSurface, getWidth);
ZEND_BEGIN_ARG_INFO_EX(CairoXlibSurface__get_width_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

#endif
