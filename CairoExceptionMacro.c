#define PHP_CAIRO_ERROR(status) \
	if (status != CAIRO_STATUS_SUCCESS) { \
		phpCairoCheckStatus(status); \
		return; \
	}

#define PHP_CAIRO_CONTEXT_ERROR(context) \
	cairo_status_t status = cairo_status (context); \
	PHP_CAIRO_ERROR(status)

#define PHP_CAIRO_PATTERN_ERROR(pattern) \
	cairo_status_t status = cairo_pattern_status(pattern); \
	PHP_CAIRO_ERROR(status)
	
#define PHP_CAIRO_SURFACE_ERROR(surface) \
	cairo_status_t status = cairo_surface_status(surface); \
	PHP_CAIRO_ERROR(status)

#define PHP_CAIRO_SCALEDFONT_ERROR(sc_font) \
	cairo_status_t status = cairo_scaled_font_status(sc_font); \
	PHP_CAIRO_ERROR(status)

#define PHP_CAIRO_FONTOPTIONS_ERROR(font_opt) \
	cairo_status_t status = cairo_font_options_status(font_opt); \
	PHP_CAIRO_ERROR(status)


	


	
