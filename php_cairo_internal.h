/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2008 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Akshat Gupta <g.akshat@gmail.com>                            |
  |         Elizabeth Smith <auroraeosrose@php.net>                      |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

/* declarations for class ce */
static zend_class_entry * CairoContext_ce_ptr = NULL;
static zend_class_entry * CairoPattern_ce_ptr = NULL;
static zend_class_entry * CairoGradient_ce_ptr = NULL;
static zend_class_entry * CairoLinearGradient_ce_ptr = NULL;
static zend_class_entry * CairoRadialGradient_ce_ptr = NULL;
static zend_class_entry * CairoSolidPattern_ce_ptr = NULL;
static zend_class_entry * CairoSurfacePattern_ce_ptr = NULL;
static zend_class_entry * CairoSurface_ce_ptr = NULL;
/* The classes derived from CairoSurface have their ce_ptr in the class file itself ....
 * They are not called directly and get_CairoSurface_ce_ptr() has to be used.
 */
static zend_class_entry * CairoException_ce_ptr = NULL;

/* Declarations for minit stuff */
extern void class_init_Cairo(TSRMLS_D);
extern void class_init_CairoContext(TSRMLS_D);
extern void class_init_CairoFontFace(TSRMLS_D);
extern void class_init_CairoFontOptions(TSRMLS_D);
extern void class_init_CairoMatrix(TSRMLS_D);
extern void class_init_CairoPath(TSRMLS_D);
extern void class_init_CairoPattern(TSRMLS_D);
extern void class_init_CairoGradient(TSRMLS_D);
extern void class_init_CairoLinearGradient(TSRMLS_D);
extern void class_init_CairoRadialGradient(TSRMLS_D);
extern void class_init_CairoSolidPattern(TSRMLS_D);
extern void class_init_CairoSurfacePattern(TSRMLS_D);
extern void class_init_CairoScaledFont(TSRMLS_D);
extern void class_init_CairoSurface(TSRMLS_D);
extern void class_init_CairoImageSurface(TSRMLS_D);

#ifdef CAIRO_HAS_PDF_SURFACE
extern   void  class_init_CairoPDFSurface(TSRMLS_D);
extern zend_class_entry *  get_CairoPdfSurface_ce_ptr();
#endif
#ifdef CAIRO_HAS_PS_SURFACE
extern   void  class_init_CairoPSSurface(TSRMLS_D);
extern zend_class_entry *  get_CairoPsSurface_ce_ptr();
#endif
#ifdef CAIRO_HAS_QUARTZ_SURFACE
extern   void  class_init_CairoQuartzSurface(TSRMLS_D);
extern zend_class_entry *  get_CairoQuartzSurface_ce_ptr();
#endif
#ifdef CAIRO_HAS_SVG_SURFACE
extern   void  class_init_CairoSVGSurface(TSRMLS_D);
extern zend_class_entry *  get_CairoSvgSurface_ce_ptr();
#endif
#ifdef CAIRO_HAS_WIN32_SURFACE
extern   void  class_init_CairoWin32Surface(TSRMLS_D);
extern zend_class_entry *  get_CairoWin32Surface_ce_ptr();
#endif
#ifdef CAIRO_HAS_XLIB_SURFACE
extern   void  class_init_CairoXlibSurface(TSRMLS_D);
extern zend_class_entry *  get_CairoXlibSurface_ce_ptr();
#endif

extern   void  class_init_CairoException(TSRMLS_D);

extern cairo_status_t _write_func(void *closure, const unsigned char *data, unsigned int length);
extern cairo_status_t _read_func(void *closure, unsigned char *data, unsigned int length);
extern zend_object_value CairoSurface_object_new(zend_class_entry *ce TSRMLS_DC);
/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw = 4 ts = 4 fdm = marker
 * vim<600: noet sw = 4 ts = 4
 */