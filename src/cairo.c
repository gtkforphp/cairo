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

/* ----------------------------------------------------------------
    Cairo Namespace
------------------------------------------------------------------ */

ZEND_BEGIN_ARG_INFO(Cairo_version_args, ZEND_SEND_BY_VAL)
ZEND_END_ARG_INFO()

#if defined(CAIRO_HAS_FT_FONT) && defined(HAVE_FREETYPE)

const char* php_cairo_get_ft_error(int error) {
	int i;
	php_cairo_ft_error *current_error = php_cairo_ft_errors;

	while (current_error->err_msg != NULL) {
		if (current_error->err_code == error) {
			return current_error->err_msg;
		}
		current_error++;
	}
	return NULL;
}

#endif

/* {{{ proto int Cairo\version(void) 
       Returns an integer version number of the cairo library being used */
PHP_FUNCTION(version)
{
	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	RETURN_LONG(cairo_version());
}
/* }}} */

ZEND_BEGIN_ARG_INFO(Cairo_version_string_args, ZEND_SEND_BY_VAL)
ZEND_END_ARG_INFO()

/* {{{ proto string cairo_version_string(void)
       Returns a string version of the cairo library being used */
PHP_FUNCTION(version_string)
{
	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	RETURN_STRING(cairo_version_string());
}
/* }}} */

/* {{{ cairo_functions[] */
static const zend_function_entry cairo_functions[] = {
	ZEND_NS_FE("Cairo", version, Cairo_version_args)
	ZEND_NS_FE("Cairo", version_string, Cairo_version_string_args)
	ZEND_FE_END
};
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(cairo)
{
	/* Namespaced version constants */
	REGISTER_NS_LONG_CONSTANT("Cairo", "VERSION",
		CAIRO_VERSION, CONST_PERSISTENT | CONST_CS | CONST_CT_SUBST);
	REGISTER_NS_STRING_CONSTANT("Cairo", "VERSION_STRING",
		CAIRO_VERSION_STRING, CONST_PERSISTENT | CONST_CS | CONST_CT_SUBST);

	PHP_MINIT(cairo_pattern)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_MINIT(cairo_rectangle)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_MINIT(cairo_matrix)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_MINIT(cairo_exception)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_MINIT(cairo_region)(INIT_FUNC_ARGS_PASSTHRU);
        PHP_MINIT(cairo_font_face)(INIT_FUNC_ARGS_PASSTHRU);
        PHP_MINIT(cairo_font)(INIT_FUNC_ARGS_PASSTHRU);
        PHP_MINIT(cairo_font_options)(INIT_FUNC_ARGS_PASSTHRU);
        PHP_MINIT(cairo_scaled_font)(INIT_FUNC_ARGS_PASSTHRU);
#if defined(CAIRO_HAS_FT_FONT) && defined(HAVE_FREETYPE)
        PHP_MINIT(cairo_ft_font)(INIT_FUNC_ARGS_PASSTHRU);
#endif
#if defined(CAIRO_HAS_QUARTZ_FONT)
        PHP_MINIT(cairo_quartz_font)(INIT_FUNC_ARGS_PASSTHRU);
#endif
#if defined(CAIRO_HAS_WIN32_FONT) && defined(HAVE_WIN32_FONT)
        PHP_MINIT(cairo_win32_font)(INIT_FUNC_ARGS_PASSTHRU);
#endif
        PHP_MINIT(cairo_surface)(INIT_FUNC_ARGS_PASSTHRU);
        PHP_MINIT(cairo_image_surface)(INIT_FUNC_ARGS_PASSTHRU);
        PHP_MINIT(cairo_sub_surface)(INIT_FUNC_ARGS_PASSTHRU);
        PHP_MINIT(cairo_recording_surface)(INIT_FUNC_ARGS_PASSTHRU);
        PHP_MINIT(cairo_pdf_surface)(INIT_FUNC_ARGS_PASSTHRU);
        PHP_MINIT(cairo_svg_surface)(INIT_FUNC_ARGS_PASSTHRU);
        PHP_MINIT(cairo_ps_surface)(INIT_FUNC_ARGS_PASSTHRU);
        PHP_MINIT(cairo_path)(INIT_FUNC_ARGS_PASSTHRU);
        PHP_MINIT(cairo_context)(INIT_FUNC_ARGS_PASSTHRU);
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
	cairo_functions,
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