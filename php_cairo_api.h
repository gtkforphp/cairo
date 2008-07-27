#include<php.h>
#include <cairo.h>

typedef struct _context_object {
	zend_object std;
	cairo_t *context;
} context_object;

typedef struct _surface_object {
	zend_object std;
	cairo_surface_t *surface;
} surface_object;

typedef struct _path_object {
	zend_object std;
	cairo_path_t *path;
} path_object;

typedef struct _fontoptions_object {
	zend_object std;
	cairo_font_options_t *fontoptions;
} fontoptions_object;

typedef struct _fontface_object {
	zend_object std;
	cairo_font_face_t *fontface;
} fontface_object;

typedef struct _matrix_object {
	zend_object std;
	cairo_matrix_t matrix;
} matrix_object;

typedef struct _pattern_object {
	zend_object std;
	cairo_pattern_t *pattern;
} pattern_object;

typedef struct _scaledfont_object {
	zend_object std;
	cairo_scaled_font_t *scaledfont;
} scaledfont_object;


extern zend_class_entry* get_CairoSurface_ce_ptr(cairo_surface_t *);
extern zend_class_entry* get_CairoContext_ce_ptr();
extern zend_class_entry* get_CairoPattern_ce_ptr(cairo_pattern_t *);
extern void phpCairoCheckStatus(cairo_status_t);
