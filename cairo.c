/*
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,	   |
   | that is bundled with this package in the file LICENSE, and is		  |
   | available through the world-wide-web at the following url:			  |
   | http://www.php.net/license/3_01.txt.								   |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to		  |
   | license@php.net so we can mail you a copy immediately.				  |
   +----------------------------------------------------------------------+
   | Authors: Akshat Gupta <g.akshat@gmail.com>							  |
   +----------------------------------------------------------------------+
*/

/* $ Id: 1.0.1$ */ 

#include "php_cairo_api.h"
#include "php_cairo.h"
#include "CairoExceptionMacro.h"
#include "php_cairo_ce_ptr.h"

#if HAVE_CAIRO

/* {{{ Class definitions */
/* }}} Class definitions*/

/* {{{ cairo_functions[] */
function_entry cairo_functions[] = {
	PHP_FE(cairo_version	   , cairo_version_arg_info)
	PHP_FE(cairo_version_string, cairo_version_string_arg_info)
	PHP_FE(cairo_available_surfaces, cairo_available_surfaces_arg_info)
	{ NULL, NULL, NULL }
};
/* }}} */


/* {{{ cairo_module_entry
 */
zend_module_entry cairo_module_entry = {
	STANDARD_MODULE_HEADER,
	"cairo",
	cairo_functions,
	PHP_MINIT(cairo),	  /* Replace with NULL if there is nothing to do at php startup   */ 
	NULL, /* Replace with NULL if there is nothing to do at php shutdown  */
	NULL,	  /* Replace with NULL if there is nothing to do at request start */
	NULL, /* Replace with NULL if there is nothing to do at request end   */
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
	class_init_Cairo();
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
#ifdef CAIRO_HAS_PDF_SURFACE
	class_init_CairoPDFSurface();
#endif
#ifdef CAIRO_HAS_PS_SURFACE
	class_init_CairoPSSurface();
#endif
#ifdef CAIRO_HAS_QUARTZ_SURFACE
	class_init_CairoQuartzSurface();
#endif
#ifdef CAIRO_HAS_SVG_SURFACE
	class_init_CairoSVGSurface();
#endif
#ifdef CAIRO_HAS_WIN32_SURFACE
	class_init_CairoWin32Surface();
#endif
#ifdef CAIRO_HAS_XLIB_SURFACE
	class_init_CairoXlibSurface();
#endif
	class_init_CairoException();

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
	if (ZEND_NUM_ARGS()>0)	{
		WRONG_PARAM_COUNT;
	}

	
	RETURN_LONG(cairo_version());
}
/* }}} cairo_version */


/* {{{ proto string cairo_version_string()
   */
PHP_FUNCTION(cairo_version_string)
{

	if (ZEND_NUM_ARGS()>0)	{
		WRONG_PARAM_COUNT;
	}

	RETURN_STRING(cairo_version_string(), 1);
}
/* }}} cairo_version_string */


/* {{{ proto string cairo_available_surfaces()
 *    */
PHP_FUNCTION(cairo_available_surfaces)
{

    if (ZEND_NUM_ARGS()>0)  {
	        WRONG_PARAM_COUNT;
    }

    array_init(return_value);

#ifdef CAIRO_HAS_PNG_FUNCTIONS
	add_next_index_string(return_value,"PNG SUPPORT",1);
#endif

#ifdef CAIRO_HAS_PDF_SURFACE
    add_next_index_string(return_value,"PDF SUPPORT",1);
#endif
#ifdef CAIRO_HAS_PS_SURFACE
   	add_next_index_string(return_value,"PS SUPPORT",1);
#endif
#ifdef CAIRO_HAS_SVG_SURFACE
    add_next_index_string(return_value,"SVG SUPPORT",1);
#endif
#ifdef CAIRO_HAS_XLIB_SURFACE
    add_next_index_string(return_value,"XLIB SUPPORT",1);
#endif
#ifdef CAIRO_HAS_QUARTZ_SURFACE
    add_next_index_string(return_value,"QUARTZ SUPPORT",1);
#endif
#ifdef CAIRO_HAS_WIN32_SURFACE
    add_next_index_string(return_value,"WIN32 SUPPORT",1);
#endif

}
					/* }}} cairo_version_string */


#endif /* HAVE_CAIRO */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw = 4 ts = 4 fdm = marker
 * vim<600: noet sw = 4 ts = 4
 */
