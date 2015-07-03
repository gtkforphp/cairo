/*
  +----------------------------------------------------------------------+
  | For PHP Version 7                                                    |
  +----------------------------------------------------------------------+
  | Copyright (c) 2015 Elizabeth M Smith                                 |
  +----------------------------------------------------------------------+
  | http://www.opensource.org/licenses/mit-license.php  MIT License      |
  | Also available in LICENSE                                            |
  +----------------------------------------------------------------------+
  | Author: Elizabeth M Smith <auroraeosrose@gmail.com>                  |
  +----------------------------------------------------------------------+
*/

#ifdef HAVE_CONFIG_H
#	include "config.h"
#endif

#include <php.h>
#include <cairo.h>

#include "php_cairo.h"
#include "php_cairo_internal.h"

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(cairo)
{
	PHP_MINIT(cairo_exception)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_MINIT(cairo_matrix)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_MINIT(cairo_pattern)(INIT_FUNC_ARGS_PASSTHRU);
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION */
PHP_MSHUTDOWN_FUNCTION(cairo)
{
#if defined(ZEND_DEBUG) && ZEND_DEBUG == 1
	cairo_debug_reset_static_data();
#endif

	return SUCCESS;
}

/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(cairo)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "Cairo Graphics Library Bindings", "enabled");
	php_info_print_table_colspan_header(2,
#ifdef COMPILE_DL_CAIRO
		"compiled as dynamic module"
#else
		"compiled as static module"
#endif
        );
	php_info_print_table_row(2, "Cairo Library Version", CAIRO_VERSION_STRING);
	php_info_print_table_row(2, "Extension Version", PHP_CAIRO_VERSION);
	php_info_print_table_colspan_header(2, "Surface Backends Available");
	php_info_print_table_row(2, "Image Surface", "enabled");
	php_info_print_table_row(2, "PNG Support",
#ifdef CAIRO_HAS_PNG_FUNCTIONS
		"enabled"
#else
		"disabled"
#endif
		);
	php_info_print_table_row(2, "PDF Surface",
#ifdef CAIRO_HAS_PDF_SURFACE
		"enabled"
#else
		"disabled"
#endif
		);
	php_info_print_table_row(2, "PS Surface",
#ifdef CAIRO_HAS_PS_SURFACE
		"enabled"
#else
		"disabled"
#endif
		);
	php_info_print_table_row(2, "Xlib (X11, X.org) Surface",
#ifdef CAIRO_HAS_XLIB_SURFACE
		"enabled"
#else
		"disabled"
#endif
		);
	php_info_print_table_row(2, "Quartz (MacOSX) Surface",
#ifdef CAIRO_HAS_QUARTZ_SURFACE
		"enabled"
#else
		"disabled"
#endif
		);
	php_info_print_table_row(2, "SVG Surface",
#ifdef CAIRO_HAS_SVG_SURFACE
		"enabled"
#else
		"disabled"
#endif
		);
	php_info_print_table_row(2, "Win32 Surface",
#ifdef CAIRO_HAS_WIN32_SURFACE
		"enabled"
#else
		"disabled"
#endif
		);
	php_info_print_table_row(2, "Recording Surface",
#ifdef CAIRO_HAS_RECORDING_SURFACE
		"enabled"
#else
		"disabled"
#endif
		);
	php_info_print_table_colspan_header(2, "Font Backends Available");
	php_info_print_table_row(2, "Freetype Fonts",
#if defined(CAIRO_HAS_FT_FONT) && defined(HAVE_FREETYPE)
		"enabled"
#else
		"disabled"
#endif
		);
	php_info_print_table_row(2, "Quartz Fonts",
#ifdef CAIRO_HAS_QUARTZ_FONT
		"enabled"
#else
		"disabled"
#endif
		);
	php_info_print_table_row(2, "Win32 Fonts",
#ifdef CAIRO_HAS_WIN32_FONT
		"enabled"
#else
		"disabled"
#endif
		);
	php_info_print_table_row(2, "User Fonts",
#ifdef CAIRO_HAS_USER_FONT
		"enabled"
#else
		"disabled"
#endif
		);
	php_info_print_table_end();
}
/* }}} */

/* {{{ cairo_module_deps */
static const zend_module_dep cairo_module_deps[] = {
	ZEND_MOD_REQUIRED("eos_datastructures")
	ZEND_MOD_END
};
/* }}} */

/* {{{ cairo_module_entry */
zend_module_entry cairo_module_entry = {
	STANDARD_MODULE_HEADER_EX,
	NULL,
	cairo_module_deps,
	"cairo",
	NULL,
	PHP_MINIT(cairo),
	PHP_MSHUTDOWN(cairo),
	NULL,
	NULL,
	PHP_MINFO(cairo),
	PHP_CAIRO_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_CAIRO
	ZEND_GET_MODULE(cairo)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */