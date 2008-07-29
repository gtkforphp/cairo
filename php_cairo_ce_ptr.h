/*This file contains the class entries and also the link for various class declaration
 */ 

static zend_class_entry * CairoContext_ce_ptr = NULL;
static zend_class_entry * CairoFontOptions_ce_ptr = NULL;
static zend_class_entry * CairoScaledFont_ce_ptr = NULL;
//static zend_class_entry * CairoPath_ce_ptr = NULL;
static zend_class_entry * CairoPattern_ce_ptr = NULL;
static zend_class_entry * CairoGradient_ce_ptr = NULL;
static zend_class_entry * CairoLinearGradient_ce_ptr = NULL;
static zend_class_entry * CairoRadialGradient_ce_ptr = NULL;
static zend_class_entry * CairoSolidPattern_ce_ptr = NULL;
static zend_class_entry * CairoSurfacePattern_ce_ptr = NULL;
/* The classes dervied from CairoSurface have there ce_ptr in the class file itself ....
 * They are not called directly and get_CairoSurface_ce_ptr() has to be used.
 */

static zend_class_entry * CairoFontFace_ce_ptr = NULL;
//static zend_class_entry * CairoMatrix_ce_ptr = NULL;
static zend_class_entry * CairoException_ce_ptr = NULL;

extern void class_init_Cairo();
extern void class_init_CairoContext();
extern void class_init_CairoFontFace();
extern void class_init_CairoFontOptions();
extern void class_init_CairoMatrix();
extern void class_init_CairoPath();
extern void class_init_CairoPattern();
extern void class_init_CairoGradient();
extern void class_init_CairoLinearGradient();
extern void class_init_CairoRadialGradient();
extern void class_init_CairoSolidPattern();
extern void class_init_CairoSurfacePattern();
extern void class_init_CairoScaledFont();
extern void class_init_CairoSurface();
extern void class_init_CairoImageSurface();
#ifdef CAIRO_HAS_PDF_SURFACE
extern   void  class_init_CairoPDFSurface();
#endif
#ifdef CAIRO_HAS_PS_SURFACE
extern   void  class_init_CairoPSSurface();
#endif
#ifdef CAIRO_HAS_QUARTZ_SURFACE
extern   void  class_init_CairoQuartzSurface();
#endif
#ifdef CAIRO_HAS_SVG_SURFACE
extern   void  class_init_CairoSVGSurface();
#endif
#ifdef CAIRO_HAS_WIN32_SURFACE
extern   void  class_init_CairoWin32Surface();
#endif
#ifdef CAIRO_HAS_XLIB_SURFACE
extern   void  class_init_CairoXlibSurface();
#endif
extern   void  class_init_CairoException();
