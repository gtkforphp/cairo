#define phpCAIRO_ERROR(status) \
	if (status != CAIRO_STATUS_SUCCESS) { \
		phpCairoCheckStatus(status); \
		return; \
	}

#define phpCAIRO_CONTEXT_ERROR(context) \
	cairo_status_t status = cairo_status (context); \
	phpCAIRO_ERROR(status)

#define phpCAIRO_PATTERN_ERROR(pattern) \
	cairo_status_t status = cairo_pattern_status(pattern); \
	phpCAIRO_ERROR(status)
	
#define phpCAIRO_SURFACE_ERROR(surface) \
	cairo_status_t status = cairo_surface_status(surface); \
	phpCAIRO_ERROR(status)

#define phpCAIRO_SCALEDFONT_ERROR(sc_font) \
	cairo_status_t status = cairo_scaled_font_status(sc_font); \
	phpCAIRO_ERROR(status)

#define phpCAIRO_FONTOPTIONS_ERROR(font_opt) \
	cairo_status_t status = cairo_font_options_status(font_opt); \
	phpCAIRO_ERROR(status)


	


	
