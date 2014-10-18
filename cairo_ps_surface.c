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
  +----------------------------------------------------------------------+
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_cairo.h"
#include "zend_exceptions.h"

#if CAIRO_HAS_PS_SURFACE
#include <cairo-ps.h>

zend_class_entry *cairo_ce_cairopssurface;
zend_class_entry *cairo_ce_cairopslevel;

ZEND_BEGIN_ARG_INFO(CairoPsSurface___construct_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, file)
	ZEND_ARG_INFO(0, width)
	ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoPsSurface_setSize_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, width)
	ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoPsSurface_long_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, level)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoPsSurface_setEps_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, level)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(CairoPsSurface_dscComment_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, comment)
ZEND_END_ARG_INFO()

/* {{{ proto void CairoPsSurface->__construct(string|resource file, float width, float height) 
       Creates a PS surface of the specified size in points to be written to filename. */
PHP_METHOD(CairoPsSurface, __construct)
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
	owned_stream = 0;

	/* special case - a NULL file is like an "in memory" surface
	   notice it uses the regular create cairo method, not create for stream */
	if(Z_TYPE_P(stream_zval) == IS_NULL) {
		surface_object->surface = cairo_ps_surface_create(NULL, width, height);
	/* Otherwise it can be a filename or a PHP stream */
	} else {
		if(Z_TYPE_P(stream_zval) == IS_STRING) {
			stream = php_stream_open_wrapper(Z_STRVAL_P(stream_zval), "w+b", REPORT_ERRORS|ENFORCE_SAFE_MODE, NULL);
			owned_stream = 1;
		} else if(Z_TYPE_P(stream_zval) == IS_RESOURCE) {
			php_stream_from_zval(stream, &stream_zval);
		} else {
			zend_throw_exception(cairo_ce_cairoexception, "CairoPsSurface::__construct() expects parameter 1 to be null, a string, or a stream resource", 0 TSRMLS_CC);
			return;
		}

		/* Pack TSRMLS info and stream into struct */
		closure = ecalloc(1, sizeof(stream_closure));
		closure->stream = stream;
		closure->owned_stream = owned_stream;
#ifdef ZTS
		closure->TSRMLS_C = TSRMLS_C;
#endif

		surface_object->closure = closure;
		surface_object->surface = cairo_ps_surface_create_for_stream(php_cairo_write_func, (void *)closure, width, height);
	}

	php_cairo_throw_exception(cairo_surface_status(surface_object->surface) TSRMLS_CC);
}
/* }}} */

/* {{{ proto CairoPsSurface cairo_ps_surface_create(string|resource file, float width, float height)
       Creates a PS surface of the specified size in points to be written to filename. */
PHP_FUNCTION(cairo_ps_surface_create)
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

	object_init_ex(return_value, cairo_ce_cairopssurface);
	surface_object = (cairo_surface_object *)zend_object_store_get_object(return_value TSRMLS_CC);

	/* special case - a NULL file is like an "in memory" surface
	   notice it uses the regular create cairo method, not create for stream */
	if(Z_TYPE_P(stream_zval) == IS_NULL) {
		surface_object->surface = cairo_ps_surface_create(NULL, width, height);
	/* Otherwise it can be a filename or a PHP stream */
	} else {
		if(Z_TYPE_P(stream_zval) == IS_STRING) {
			stream = php_stream_open_wrapper(Z_STRVAL_P(stream_zval), "w+b", REPORT_ERRORS|ENFORCE_SAFE_MODE, NULL);
			owned_stream = 1;
		} else if(Z_TYPE_P(stream_zval) == IS_RESOURCE)  {
			php_stream_from_zval(stream, &stream_zval);	
		} else {
			 zend_error(E_WARNING, "cairo_ps_surface_create() expects parameter 1 to be null, a string, or a stream resource");
			 RETURN_NULL();
		}

		/* Pack TSRMLS info and stream into struct */
		closure = ecalloc(1, sizeof(stream_closure));
		closure->stream = stream;
		closure->owned_stream = owned_stream;
#ifdef ZTS
		closure->TSRMLS_C = TSRMLS_C;
#endif

		surface_object->closure = closure;
		surface_object->surface = cairo_ps_surface_create_for_stream(php_cairo_write_func, (void *)closure, width, height);
	}

	php_cairo_trigger_error(cairo_surface_status(surface_object->surface) TSRMLS_CC);
}
/* }}} */

/* {{{ proto void cairo_ps_surface_set_size(CairoPsSurface object, double width, double height)
       proto void CairoPsSurface->setSize(double width, double height)
       Changes the size of a PS surface for the current (and subsequent) pages.
       This should be called before any drawing takes place on the surface */
PHP_FUNCTION(cairo_ps_surface_set_size)
{
	zval *surface_zval;
	double width = 0.0, height = 0.0;
	cairo_surface_object *surface_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odd", &surface_zval, cairo_ce_cairopssurface, &width, &height) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	surface_object = (cairo_surface_object *)cairo_surface_object_get(surface_zval TSRMLS_CC);

	cairo_ps_surface_set_size(surface_object->surface, width, height);
	PHP_CAIRO_ERROR(cairo_surface_status(surface_object->surface));
}
/* }}} */

#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 6, 0)
/* {{{ proto void cairo_ps_surface_restrict_to_level(CairoPsSurface object, int level)
       proto void CairoPsSurface->restrictToLevel(int level)
       Restricts the generated PostSript file to level. */
PHP_FUNCTION(cairo_ps_surface_restrict_to_level)
{
	zval *surface_zval;
	cairo_surface_object *surface_object;
	long level = CAIRO_PS_LEVEL_2;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ol", &surface_zval, cairo_ce_cairopssurface, &level) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	surface_object = (cairo_surface_object *)cairo_surface_object_get(surface_zval TSRMLS_CC);

	cairo_ps_surface_restrict_to_level(surface_object->surface, level);
	PHP_CAIRO_ERROR(cairo_surface_status(surface_object->surface));
}
/* }}} */

/* {{{ proto void cairo_ps_surface_set_eps(CairoPsSurface object, boolean eps)
       proto void CairoPsSurface->setEps(boolean eps)
       If eps is TRUE, the PostScript surface will output Encapsulated PostScript. */
PHP_FUNCTION(cairo_ps_surface_set_eps)
{
	zval *surface_zval;
	zend_bool eps = 0;
	cairo_surface_object *surface_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ob", &surface_zval, cairo_ce_cairopssurface, &eps) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	surface_object = (cairo_surface_object *)cairo_surface_object_get(surface_zval TSRMLS_CC);

	cairo_ps_surface_set_eps(surface_object->surface, eps);
	PHP_CAIRO_ERROR(cairo_surface_status(surface_object->surface));
}
/* }}} */

/* {{{ proto boolean cairo_ps_surface_get_eps(CairoPsSurface object)
       proto boolean CairoPsSurface->getEps(void)
       Check whether the PostScript surface will output Encapsulated PostScript. */
PHP_FUNCTION(cairo_ps_surface_get_eps)
{
	zval *surface_zval;
	cairo_surface_object *surface_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &surface_zval, cairo_ce_cairopssurface) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	surface_object = (cairo_surface_object *)cairo_surface_object_get(surface_zval TSRMLS_CC);
	RETURN_BOOL(cairo_ps_surface_get_eps(surface_object->surface));
}
/* }}} */
#endif

/* {{{ proto void cairo_ps_surface_dsc_begin_setup(CairoPsSurface surface)
       proto void CairoPsSurface->dscBeginSetup(void)
       This function indicates that subsequent calls to cairo_ps_surface_dsc_comment() should
       direct comments to the Setup section of the PostScript output. */
PHP_FUNCTION(cairo_ps_surface_dsc_begin_setup)
{
	zval *surface_zval;
	cairo_surface_object *surface_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &surface_zval, cairo_ce_cairopssurface) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	surface_object = (cairo_surface_object *)cairo_surface_object_get(surface_zval TSRMLS_CC);
	cairo_ps_surface_dsc_begin_setup(surface_object->surface);
}
/* }}} */

/* {{{ proto void cairo_ps_surface_dsc_begin_page_setup(CairoPsSurface surface)
       proto void CairoPsSurface->dscBeginPageSetup(void)
       This indicates that subsequent calls to cairo_ps_surface_dsc_comment()
       should direct comments to the PageSetup section of the PostScript output.

       This function call is only needed for the first page of a surface.
       It should be called after any call to cairo_ps_surface_dsc_begin_setup()
       and before any drawing is performed to the surface. */
PHP_FUNCTION(cairo_ps_surface_dsc_begin_page_setup)
{
	zval *surface_zval;
	cairo_surface_object *surface_object;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &surface_zval, cairo_ce_cairopssurface) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	surface_object = (cairo_surface_object *)cairo_surface_object_get(surface_zval TSRMLS_CC);
	cairo_ps_surface_dsc_begin_page_setup(surface_object->surface);
}
/* }}} */

/* {{{ proto void cairo_ps_surface_dsc_comment(CairoPsSurface surface, string comment)
       proto void CairoPsSurface->dscComment(string comment)
       Emit a comment into the PostScript output for the given surface. */
PHP_FUNCTION(cairo_ps_surface_dsc_comment)
{
	zval *surface_zval;
	cairo_surface_object *surface_object;
	char *comment, *cairo_comment;
	int comment_len;

	PHP_CAIRO_ERROR_HANDLING(FALSE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Os", &surface_zval, cairo_ce_cairopssurface, &comment, &comment_len) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(FALSE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(FALSE)

	surface_object = (cairo_surface_object *)cairo_surface_object_get(surface_zval TSRMLS_CC);

	cairo_comment = estrdup(comment);
	cairo_ps_surface_dsc_comment(surface_object->surface, cairo_comment);
	efree(cairo_comment);

	PHP_CAIRO_ERROR(cairo_surface_status(surface_object->surface));
}
/* }}} */

#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 6, 0)
/* {{{ proto array cairo_ps_get_levels(void)
       Used to retrieve the list of supported levels. See cairo_ps_surface_restrict_to_level(). */
PHP_FUNCTION(cairo_ps_get_levels)
{
	const cairo_ps_level_t *levels;
	int num_levels, i;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "") == FAILURE) {
		return;
	}

	cairo_ps_get_levels(&levels, &num_levels);
	array_init(return_value);
	for(i = 0; i < num_levels; i++) {
		add_next_index_long(return_value, levels[i]);
	}
}
/* }}} */

/* {{{ proto array CairoPsSurface::getLevels(void)
       Used to retrieve the list of supported levels. See cairo_ps_surface_restrict_to_level(). */
PHP_METHOD(CairoPsSurface, getLevels)
{
	const cairo_ps_level_t *levels;
	int num_levels, i;

	PHP_CAIRO_ERROR_HANDLING(TRUE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "") == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(TRUE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(TRUE)

	cairo_ps_get_levels(&levels, &num_levels);
	array_init(return_value);
	for(i = 0; i < num_levels; i++) {
		add_next_index_long(return_value, levels[i]);
	}
}
/* }}} */

/* {{{ proto string cairo_ps_level_to_string(long level)
       Get the string representation of the given level id. */
PHP_FUNCTION(cairo_ps_level_to_string)
{
	long level;
	const char *level_str;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "l", &level) == FAILURE) {
		return;
	}
	
	if (level_str = cairo_ps_level_to_string(level)) {
		RETURN_STRING(level_str, 1);
	}
	
	RETURN_FALSE;
}
/* }}} */

/* {{{ proto string CairoPsSurface::levelToString(level)
       Get the string representation of the given level id. */
PHP_METHOD(CairoPsSurface, levelToString)
{
	long level;

	PHP_CAIRO_ERROR_HANDLING(TRUE)
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "l", &level) == FAILURE) {
		PHP_CAIRO_RESTORE_ERRORS(TRUE)
		return;
	}
	PHP_CAIRO_RESTORE_ERRORS(TRUE)

	RETURN_STRING(cairo_ps_level_to_string(level), 1);
}
/* }}} */
#endif

/* {{{ cairo_ps_surface_methods[] */
const zend_function_entry cairo_ps_surface_methods[] = {
	PHP_ME(CairoPsSurface, __construct, CairoPsSurface___construct_args, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME_MAPPING(setSize, cairo_ps_surface_set_size, CairoPsSurface_setSize_args, ZEND_ACC_PUBLIC)
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 6, 0)
	PHP_ME_MAPPING(restrictToLevel, cairo_ps_surface_restrict_to_level, CairoPsSurface_long_args, ZEND_ACC_PUBLIC)
	PHP_ME(CairoPsSurface, getLevels, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(CairoPsSurface, levelToString, CairoPsSurface_long_args, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME_MAPPING(setEps, cairo_ps_surface_set_eps, CairoPsSurface_setEps_args, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(getEps, cairo_ps_surface_get_eps, NULL, ZEND_ACC_PUBLIC)
#endif
	PHP_ME_MAPPING(dscBeginSetup, cairo_ps_surface_dsc_begin_setup, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(dscBeginPageSetup, cairo_ps_surface_dsc_begin_page_setup, NULL, ZEND_ACC_PUBLIC)
	PHP_ME_MAPPING(dscComment, cairo_ps_surface_dsc_comment, CairoPsSurface_dscComment_args, ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};
/* }}} */

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(cairo_ps_surface)
{
	zend_class_entry pssurface_ce;
	zend_class_entry pslevel_ce;

	INIT_CLASS_ENTRY(pssurface_ce, "CairoPsSurface", cairo_ps_surface_methods);
	cairo_ce_cairopssurface = zend_register_internal_class_ex(&pssurface_ce, cairo_ce_cairosurface, "CairoSurface" TSRMLS_CC);
	cairo_ce_cairopssurface->create_object = cairo_surface_object_new;

	INIT_CLASS_ENTRY(pslevel_ce, "CairoPsLevel", NULL);
	cairo_ce_cairopslevel = zend_register_internal_class(&pslevel_ce TSRMLS_CC);
	cairo_ce_cairopslevel->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS | ZEND_ACC_FINAL_CLASS;

	#define REGISTER_CAIRO_PSLEVEL_LONG_CONST(const_name, value) \
	zend_declare_class_constant_long(cairo_ce_cairopslevel, const_name, sizeof(const_name)-1, (long)value TSRMLS_CC); \
	REGISTER_LONG_CONSTANT(#value,  value,  CONST_CS | CONST_PERSISTENT);

#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 4, 0)
	REGISTER_CAIRO_PSLEVEL_LONG_CONST("LEVEL_2", CAIRO_PS_LEVEL_2);
	REGISTER_CAIRO_PSLEVEL_LONG_CONST("LEVEL_3", CAIRO_PS_LEVEL_3);
#endif

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
