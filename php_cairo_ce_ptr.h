/*This file contains the class entries and also the link for various class declaration
 */ 

static zend_class_entry * CairoContext_ce_ptr = NULL;
static zend_class_entry * CairoFontOptions_ce_ptr = NULL;
static zend_class_entry * CairoScaledFont_ce_ptr = NULL;
static zend_class_entry * CairoPath_ce_ptr = NULL;
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
static zend_class_entry * CairoMatrix_ce_ptr = NULL;
static zend_class_entry * CairoException_ce_ptr = NULL;

extern void  class_init_CairoContext();
extern  void  class_init_CairoFontFace();
extern   void  class_init_CairoFontOptions();
extern   void  class_init_CairoMatrix();
extern   void  class_init_CairoPath();
extern   void  class_init_CairoPattern();
extern   void  class_init_CairoGradient();
extern   void  class_init_CairoLinearGradient();
extern   void  class_init_CairoRadialGradient();
extern   void  class_init_CairoSolidPattern();
extern   void  class_init_CairoSurfacePattern();
extern   void  class_init_CairoScaledFont();
extern   void  class_init_CairoSurface();
extern   void  class_init_CairoImageSurface();
extern   void  class_init_CairoPDFSurface();
extern   void  class_init_CairoPSSurface();
extern   void  class_init_CairoQuartzSurface();
extern   void  class_init_CairoSVGSurface();
extern   void  class_init_CairoWin32Surface();
extern   void  class_init_CairoXlibSurface();
extern   void  class_init_CairoException();
