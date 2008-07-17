/*
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,       |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt.                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Authors: Akshat Gupta <g.akshat@gmail.com>                           |
   +----------------------------------------------------------------------+
*/

/* $ Id: 1.0.1$ */ 

#include "php_cairo_api.h"
#include "php_cairo.h"
#include "CairoExceptionMacro.c"
#include "CairoException.c"
#include "CairoFont.c"
#include "CairoMatrix.c"
#include "CairoPath.c"
#include "CairoSurface.c"
#include "CairoPattern.c"
#include "CairoContext.c"
#if HAVE_CAIRO

/* {{{ Class definitions */
/* }}} Class definitions*/

/* {{{ cairo_functions[] */
function_entry cairo_functions[] = {
	PHP_FE(cairo_version       , cairo_version_arg_info)
	PHP_FE(cairo_version_string, cairo_version_string_arg_info)
	{ NULL, NULL, NULL }
};
/* }}} */


/* {{{ cairo_module_entry
 */
zend_module_entry cairo_module_entry = {
	STANDARD_MODULE_HEADER,
	"cairo",
	cairo_functions,
	PHP_MINIT(cairo),     /* Replace with NULL if there is nothing to do at php startup   */ 
	PHP_MSHUTDOWN(cairo), /* Replace with NULL if there is nothing to do at php shutdown  */
	PHP_RINIT(cairo),     /* Replace with NULL if there is nothing to do at request start */
	PHP_RSHUTDOWN(cairo), /* Replace with NULL if there is nothing to do at request end   */
	PHP_MINFO(cairo),
	PHP_CAIRO_VERSION, 
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_CAIRO
ZEND_GET_MODULE(cairo)
#endif


/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(cairo)
{
	class_init_CairoContext();
	class_init_CairoFontFace();
	class_init_CairoFontOptions();
	class_init_CairoMatrix();
	class_init_CairoPath();
	class_init_CairoPattern();
	class_init_CairoGradient();
	class_init_CairoLinearGradient();
	class_init_CairoRadialGradient();
	class_init_CairoSolidPattern();
	class_init_CairoSurfacePattern();
	class_init_CairoScaledFont();
	class_init_CairoSurface();
	class_init_CairoImageSurface();
	class_init_CairoPDFSurface();
	class_init_CairoPSSurface();
	class_init_CairoQuartzSurface();
	class_init_CairoSVGSurface();
	class_init_CairoWin32Surface();
	class_init_CairoXlibSurface();
	class_init_CairoException();

	/* add your stuff here */
    
	/* constants */
#if HAS_ATSUI_FONT
    REGISTER_LONG_CONSTANT( "HAS_ATSUI_FONT", 1,  CONST_CS | CONST_PERSISTENT);
#else
    REGISTER_LONG_CONSTANT( "HAS_ATSUI_FONT", 0,  CONST_CS | CONST_PERSISTENT);
#endif
#if HAS_FT_FONT
    REGISTER_LONG_CONSTANT( "HAS_FT_FONT", 1,  CONST_CS | CONST_PERSISTENT);
#else
    REGISTER_LONG_CONSTANT( "HAS_FT_FONT", 0,  CONST_CS | CONST_PERSISTENT);
#endif
#if HAS_GLITZ_SURFACE
    REGISTER_LONG_CONSTANT( "HAS_GLITZ_SURFACE", 1,  CONST_CS | CONST_PERSISTENT);
#else
    REGISTER_LONG_CONSTANT( "HAS_GLITZ_SURFACE", 0,  CONST_CS | CONST_PERSISTENT);
#endif
#if HAS_PDF_SURFACE
    REGISTER_LONG_CONSTANT( "HAS_PDF_SURFACE", 1,  CONST_CS | CONST_PERSISTENT);
#else
    REGISTER_LONG_CONSTANT( "HAS_PDF_SURFACE", 0,  CONST_CS | CONST_PERSISTENT);
#endif
#if HAS_PNG_FUNCTIONS
    REGISTER_LONG_CONSTANT( "HAS_PNG_FUNCTIONS", 1,  CONST_CS | CONST_PERSISTENT);
#else
    REGISTER_LONG_CONSTANT( "HAS_PNG_FUNCTIONS", 0,  CONST_CS | CONST_PERSISTENT);
#endif
#if HAS_PS_SURFACE
    REGISTER_LONG_CONSTANT( "HAS_PS_SURFACE", 1,  CONST_CS | CONST_PERSISTENT);
#else
    REGISTER_LONG_CONSTANT( "HAS_PS_SURFACE", 0,  CONST_CS | CONST_PERSISTENT);
#endif
#if HAS_SVG_SURFACE
    REGISTER_LONG_CONSTANT( "HAS_SVG_SURFACE", 1,  CONST_CS | CONST_PERSISTENT);
#else
    REGISTER_LONG_CONSTANT( "HAS_SVG_SURFACE", 0,  CONST_CS | CONST_PERSISTENT);
#endif
#if HAS_QUARTZ_SURFACE
    REGISTER_LONG_CONSTANT( "HAS_QUARTZ_SURFACE", 1,  CONST_CS | CONST_PERSISTENT);
#else
    REGISTER_LONG_CONSTANT( "HAS_QUARTZ_SURFACE", 0,  CONST_CS | CONST_PERSISTENT);
#endif
#if HAS_WIN32_FONT
    REGISTER_LONG_CONSTANT( "HAS_WIN32_FONT", 1,  CONST_CS | CONST_PERSISTENT);
#else
    REGISTER_LONG_CONSTANT( "HAS_WIN32_FONT", 0,  CONST_CS | CONST_PERSISTENT);
#endif
#if HAS_WIN32_SURFACE
    REGISTER_LONG_CONSTANT( "HAS_WIN32_SURFACE", 1,  CONST_CS | CONST_PERSISTENT);
#else
    REGISTER_LONG_CONSTANT( "HAS_WIN32_SURFACE", 0,  CONST_CS | CONST_PERSISTENT);
#endif
#if HAS_XCB_SURFACE
    REGISTER_LONG_CONSTANT( "HAS_XCB_SURFACE", 1,  CONST_CS | CONST_PERSISTENT);
#else
    REGISTER_LONG_CONSTANT( "HAS_XCB_SURFACE", 0,  CONST_CS | CONST_PERSISTENT);
#endif
#if HAS_XLIB_SURFACE
    REGISTER_LONG_CONSTANT( "HAS_XLIB_SURFACE", 1,  CONST_CS | CONST_PERSISTENT);
#else
    REGISTER_LONG_CONSTANT( "HAS_XLIB_SURFACE", 0,  CONST_CS | CONST_PERSISTENT);
#endif

#define CONSTANT(x) REGISTER_LONG_CONSTANT( #x, CAIRO_##x,  CONST_CS | CONST_PERSISTENT)
    CONSTANT(ANTIALIAS_DEFAULT);
    CONSTANT(ANTIALIAS_NONE);
    CONSTANT(ANTIALIAS_GRAY);
    CONSTANT(ANTIALIAS_SUBPIXEL);

    CONSTANT(CONTENT_COLOR);
    CONSTANT(CONTENT_ALPHA);
    CONSTANT(CONTENT_COLOR_ALPHA);

    CONSTANT(EXTEND_NONE);
    CONSTANT(EXTEND_REPEAT);
    CONSTANT(EXTEND_REFLECT);
	CONSTANT(EXTEND_PAD);

    CONSTANT(FILL_RULE_WINDING);
    CONSTANT(FILL_RULE_EVEN_ODD);

    CONSTANT(FILTER_FAST);
    CONSTANT(FILTER_GOOD);
    CONSTANT(FILTER_BEST);
    CONSTANT(FILTER_NEAREST);
    CONSTANT(FILTER_BILINEAR);
    CONSTANT(FILTER_GAUSSIAN);

    CONSTANT(FONT_WEIGHT_NORMAL);
    CONSTANT(FONT_WEIGHT_BOLD);

    CONSTANT(FONT_SLANT_NORMAL);
    CONSTANT(FONT_SLANT_ITALIC);
    CONSTANT(FONT_SLANT_OBLIQUE);

    CONSTANT(FORMAT_ARGB32);
    CONSTANT(FORMAT_RGB24);
    CONSTANT(FORMAT_A8);
    CONSTANT(FORMAT_A1);
    CONSTANT(FORMAT_RGB16_565);

    CONSTANT(HINT_METRICS_DEFAULT);
    CONSTANT(HINT_METRICS_OFF);
    CONSTANT(HINT_METRICS_ON);

    CONSTANT(HINT_STYLE_DEFAULT);
    CONSTANT(HINT_STYLE_NONE);
    CONSTANT(HINT_STYLE_SLIGHT);
    CONSTANT(HINT_STYLE_MEDIUM);
    CONSTANT(HINT_STYLE_FULL);

    CONSTANT(LINE_CAP_BUTT);
    CONSTANT(LINE_CAP_ROUND);
    CONSTANT(LINE_CAP_SQUARE);

    CONSTANT(LINE_JOIN_MITER);
    CONSTANT(LINE_JOIN_ROUND);
    CONSTANT(LINE_JOIN_BEVEL);

    CONSTANT(OPERATOR_CLEAR);

    CONSTANT(OPERATOR_SOURCE);
    CONSTANT(OPERATOR_OVER);
    CONSTANT(OPERATOR_IN);
    CONSTANT(OPERATOR_OUT);
    CONSTANT(OPERATOR_ATOP);

    CONSTANT(OPERATOR_DEST);
    CONSTANT(OPERATOR_DEST_OVER);
    CONSTANT(OPERATOR_DEST_IN);
    CONSTANT(OPERATOR_DEST_OUT);
    CONSTANT(OPERATOR_DEST_ATOP);

    CONSTANT(OPERATOR_XOR);
    CONSTANT(OPERATOR_ADD);
    CONSTANT(OPERATOR_SATURATE);

    CONSTANT(PATH_MOVE_TO);
    CONSTANT(PATH_LINE_TO);
    CONSTANT(PATH_CURVE_TO);
    CONSTANT(PATH_CLOSE_PATH);

    CONSTANT(SUBPIXEL_ORDER_DEFAULT);
    CONSTANT(SUBPIXEL_ORDER_RGB);
    CONSTANT(SUBPIXEL_ORDER_BGR);
    CONSTANT(SUBPIXEL_ORDER_VRGB);
    CONSTANT(SUBPIXEL_ORDER_VBGR);
#undef CONSTANT



	return SUCCESS;
}
/* }}} */


/* {{{ PHP_MSHUTDOWN_FUNCTION */
PHP_MSHUTDOWN_FUNCTION(cairo)
{

	/* add your stuff here */

	return SUCCESS;
}
/* }}} */


/* {{{ PHP_RINIT_FUNCTION */
PHP_RINIT_FUNCTION(cairo)
{
	/* add your stuff here */

	return SUCCESS;
}
/* }}} */


/* {{{ PHP_RSHUTDOWN_FUNCTION */
PHP_RSHUTDOWN_FUNCTION(cairo)
{
	/* add your stuff here */

	return SUCCESS;
}
/* }}} */


/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(cairo)
{
	php_info_print_box_start(0);
	php_printf("<p>PHP bindings for Cairo Graphic Library</p>\n");
	php_printf(PHP_CAIRO_VERSION);
	php_printf("<p><b>Authors:</b></p>\n");
	php_printf("<p>Akshat Gupta &lt;g.akshat@gmail.com&gt; (lead)</p>\n");
	php_info_print_box_end();
	/* add your stuff here */

}
/* }}} */


/* {{{ proto int cairo_version()
   */
PHP_FUNCTION(cairo_version)
{



	if (ZEND_NUM_ARGS()>0)  {
		WRONG_PARAM_COUNT;
	}

	
	RETURN_LONG(cairo_version());
}
/* }}} cairo_version */


/* {{{ proto string cairo_version_string()
   */
PHP_FUNCTION(cairo_version_string)
{

	char *a;

	if (ZEND_NUM_ARGS()>0)  {
		WRONG_PARAM_COUNT;
	}

	RETURN_STRING(cairo_version_string(), 1);
}
/* }}} cairo_version_string */

#endif /* HAVE_CAIRO */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
