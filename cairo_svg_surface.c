/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2014 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Elizabeth Smith <auroraeosrose@php.net>                      |
  |         Michael Maclean <mgdm@php.net>                               |
  |         Mark Skilbeck <markskilbeck@php.net>                         |
  +----------------------------------------------------------------------+
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_cairo.h"
#include <zend_exceptions.h>

#if CAIRO_HAS_SVG_SURFACE
#include <cairo-svg.h>

zend_class_entry *cairo_ce_cairosvgsurface;
zend_class_entry *cairo_ce_cairosvgversion;

ZEND_BEGIN_ARG_INFO(CairoSvgSurface___construct_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, file)
	ZEND_ARG_INFO(0, width)
	ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoSvgSurface_restrictToVersion_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, version)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoSvgSurface_versionToString_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, version)
ZEND_END_ARG_INFO()

/* {{{ proto void __construct(string|resource file, float width, float height) 
       Creates a SVG surface of the specified size in points to be written to filename. */
PHP_METHOD(CairoSvgSurface, __construct)
{
	zval *stream_zval = NULL;
	stream_closure *closure;
	php_stream *stream = NULL;
	double width, height;
	zend_bool owned_stream = 0;
	cairo_surface_object *surface_object;

	PHP_CAIRO_ERROR_HANDLING(TRUE)
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zdd", &stream_zval, &width, &height) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(TRUE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(TRUE)

	surface_object = (cairo_surface_object *)zend_object_store_get_object(getThis() TSRMLS_CC);

	/* special case - a NULL file is like an "in memory" svg */
	if(Z_TYPE_P(stream_zval) == IS_NULL) {
		surface_object->surface = cairo_svg_surface_create(NULL, width, height);
	/* Otherwise it can be a filename or a PHP stream */
	} else {
		if(Z_TYPE_P(stream_zval) == IS_STRING) {
			stream = php_stream_open_wrapper(Z_STRVAL_P(stream_zval), "w+b", REPORT_ERRORS|ENFORCE_SAFE_MODE, NULL);
			owned_stream = 1;
		} else if(Z_TYPE_P(stream_zval) == IS_RESOURCE)  {
			php_stream_from_zval(stream, &stream_zval);	
		} else {
			zend_throw_exception(cairo_ce_cairoexception, "CairoSvgSurface::__construct() expects parameter 1 to be null, a string, or a stream resource", 0 TSRMLS_CC);
			return;
		}

		/* Pack TSRMLS info and stream into struct*/
		closure = ecalloc(1, sizeof(stream_closure));
		closure->stream = stream;
		closure->owned_stream = owned_stream;
#ifdef ZTS
		closure->TSRMLS_C = TSRMLS_C;
#endif
		surface_object->closure = closure;
		surface_object->surface = cairo_svg_surface_create_for_stream(php_cairo_write_func, (void *)closure, width, height);
	}

	php_cairo_throw_exception(cairo_surface_status(surface_object->surface) TSRMLS_CC);
}
/* }}} */

/* {{{ proto CairoSvgSurface cairo_svg_surface_create(string|resource file, float width, float height)
       Creates a SVG surface of the specified size in points to be written to filename. */
PHP_FUNCTION(cairo_svg_surface_create)
{
	zval *stream_zval = NULL;
	stream_closure *closure;
	php_stream *stream = NULL;
	double width, height;
	zend_bool owned_stream = 0;
	cairo_surface_object *surface_object;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zdd", &stream_zval, &width, &height) == FAILURE) {
		return;
	}

	object_init_ex(return_value, cairo_ce_cairosvgsurface);
	surface_object = (cairo_surface_object *)zend_object_store_get_object(return_value TSRMLS_CC);

	/* special case - a NULL file is like an "in memory" svg */
	if(Z_TYPE_P(stream_zval) == IS_NULL) {
		surface_object->surface = cairo_svg_surface_create(NULL, width, height);
	/* Otherwise it can be a filename or a PHP stream */
	} else {
		if(Z_TYPE_P(stream_zval) == IS_STRING) {
			stream = php_stream_open_wrapper(Z_STRVAL_P(stream_zval), "w+b", REPORT_ERRORS|ENFORCE_SAFE_MODE, NULL);
			owned_stream = 1;
		} else if(Z_TYPE_P(stream_zval) == IS_RESOURCE)  {
			php_stream_from_zval(stream, &stream_zval);	
		} else {
			zend_error(E_WARNING, "cairo_svg_surface_create() expects parameter 1 to be null, a string, or a stream resource");
			RETURN_NULL();
		}

		/* Pack TSRMLS info and stream into struct*/
		closure = ecalloc(1, sizeof(stream_closure));
		closure->stream = stream;
		closure->owned_stream = owned_stream;
#ifdef ZTS
		closure->TSRMLS_C = TSRMLS_C;
#endif
		surface_object->closure = closure;
		surface_object->surface = cairo_svg_surface_create_for_stream(php_cairo_write_func, (void *)closure, width, height);
	}

	php_cairo_trigger_error(cairo_surface_status(surface_object->surface) TSRMLS_CC);
}
/* }}} */

/* {{{ proto void cairo_svg_surface_restrict_to_version(CairoSvgSurface object, int version)
       proto void CairoSvgSurface->restrictToVersion(int version)
       Restricts the generated SVG file to version. This should be called before any drawing takes place on the surface */
PHP_FUNCTION(cairo_svg_surface_restrict_to_version)
{
	zval *surface_zval;
	long version;
	cairo_surface_object *surface_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ol", &surface_zval, cairo_ce_cairosvgsurface, &version) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	surface_object = (cairo_surface_object *)cairo_surface_object_get(surface_zval TSRMLS_CC);

	cairo_svg_surface_restrict_to_version(surface_object->surface, version);
	PHP_CAIRO_ERROR(cairo_surface_status(surface_object->surface));
}
/* }}} */

/* {{{ proto void cairo_svg_version_to_string(int version)
       Get the string representation of the given version id. This function will return NULL if version isn't valid. */
PHP_FUNCTION(cairo_svg_version_to_string)
{
	long version;
	const char *version_str;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &version) == FAILURE) {
		return;
	}
	
	if (version_str = cairo_svg_version_to_string(version)) {
		RETURN_STRING(version_str, 1);
	}
	RETURN_FALSE;
}
/* }}} */

/* {{{ proto void CairoSvgSurface::versionToString(int version)
       Get the string representation of the given version id. This function will return NULL if version isn't valid. */
PHP_METHOD(CairoSvgSurface, versionToString)
{
	long version;

	PHP_CAIRO_ERROR_HANDLING(TRUE)
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &version) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(TRUE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(TRUE)

	RETURN_STRING(cairo_svg_version_to_string(version), 1);
}
/* }}} */

/* {{{ proto array cairo_svg_get_versions()
       Used to retrieve the list of supported versions */
PHP_FUNCTION(cairo_svg_get_versions)
{
	const cairo_svg_version_t *versions = 0;
	int version_count = 0, i = 0;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "") == FAILURE) {
		return;
	}

	cairo_svg_get_versions(&versions, &version_count);
	array_init(return_value);

	for (i = 0; i < version_count; i++) {
		add_next_index_long(return_value, versions[i]);
	}
}
/* }}} */

/* {{{ proto array CairoSvgSurface::getVersions()
       Used to retrieve the list of supported versions */
PHP_METHOD(CairoSvgSurface, getVersions)
{
	const cairo_svg_version_t *versions = 0;
	int version_count = 0, i = 0;

	PHP_CAIRO_ERROR_HANDLING(TRUE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "") == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(TRUE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(TRUE)

	cairo_svg_get_versions(&versions, &version_count);
	array_init(return_value);

	for (i = 0; i < version_count; i++) {
		add_next_index_long(return_value, versions[i]);
	}
}
/* }}} */

/* {{{ cairo_svg_surface_methods[] */
const zend_function_entry cairo_svg_surface_methods[] = {
	PHP_ME(CairoSvgSurface, __construct, CairoSvgSurface___construct_args, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME_MAPPING(restrictToVersion, cairo_svg_surface_restrict_to_version, CairoSvgSurface_restrictToVersion_args, ZEND_ACC_PUBLIC)
	PHP_ME(CairoSvgSurface, versionToString, CairoSvgSurface_versionToString_args, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(CairoSvgSurface, getVersions, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	{NULL, NULL, NULL}
};
/* }}} */

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(cairo_svg_surface)
{
	zend_class_entry ce, version_ce;

	INIT_CLASS_ENTRY(ce, "CairoSvgSurface", cairo_svg_surface_methods);
	cairo_ce_cairosvgsurface = zend_register_internal_class_ex(&ce, cairo_ce_cairosurface, "CairoSurface" TSRMLS_CC);
	cairo_ce_cairosvgsurface->create_object = cairo_surface_object_new;

	INIT_CLASS_ENTRY(version_ce, "CairoSvgVersion", NULL);
	cairo_ce_cairosvgversion = zend_register_internal_class(&version_ce TSRMLS_CC);
	cairo_ce_cairosvgversion->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS | ZEND_ACC_FINAL_CLASS;

	#define REGISTER_CAIRO_VERSION_LONG_CONST(const_name, value) \
	zend_declare_class_constant_long(cairo_ce_cairosvgversion, const_name, sizeof(const_name)-1, (long)value TSRMLS_CC); \
	REGISTER_LONG_CONSTANT(#value,  value,  CONST_CS | CONST_PERSISTENT);

	REGISTER_CAIRO_VERSION_LONG_CONST("VERSION_1_1", CAIRO_SVG_VERSION_1_1);
	REGISTER_CAIRO_VERSION_LONG_CONST("VERSION_1_2", CAIRO_SVG_VERSION_1_2);

	return SUCCESS;
}

#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
