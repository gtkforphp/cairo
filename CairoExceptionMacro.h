#define PHP_CAIRO_ERROR(status) \
	if (status != CAIRO_STATUS_SUCCESS) { \
		phpCairoCheckStatus(status); \
		return; \
	}

#define PHP_CAIRO_CONTEXT_ERROR(context) \
	PHP_CAIRO_ERROR(cairo_status(context))

#define PHP_CAIRO_PATTERN_ERROR(pattern) \
	PHP_CAIRO_ERROR(cairo_pattern_status(pattern))
	
#define PHP_CAIRO_SURFACE_ERROR(surface) \
	PHP_CAIRO_ERROR(cairo_surface_status(surface))

#define PHP_CAIRO_SCALEDFONT_ERROR(sc_font) \
	PHP_CAIRO_ERROR(cairo_scaled_font_status(sc_font))

#define PHP_CAIRO_FONTOPTIONS_ERROR(font_opt) \
	PHP_CAIRO_ERROR(cairo_font_options_status(font_opt))


	


	
