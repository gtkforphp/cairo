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
#include "config.h"
#endif

#include <cairo.h>
#include <php.h>
#include <zend_exceptions.h>

#include <ext/eos_datastructures/php_eos_datastructures_api.h>

#include "php_cairo.h"
#include "php_cairo_internal.h"

#if CAIRO_HAS_PS_SURFACE
#include <cairo-ps.h>

zend_class_entry *ce_cairo_pssurface;
zend_class_entry *ce_cairo_pslevel;

/* ----------------------------------------------------------------
    Cairo\Surface\Svg Class API
------------------------------------------------------------------*/

ZEND_BEGIN_ARG_INFO(CairoPsSurface___construct_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, file)
	ZEND_ARG_INFO(0, width)
	ZEND_ARG_INFO(0, height)
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

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "zdd", &stream_zval, &width, &height) == FAILURE) {
		return;
	}

	surface_object = Z_CAIRO_SURFACE_P(getThis());
	if(!surface_object) {
            return;
        }

	/* special case - a NULL file is like an "in memory" surface
	   notice it uses the regular create cairo method, not create for stream */
	if(Z_TYPE_P(stream_zval) == IS_NULL) {
		surface_object->surface = cairo_ps_surface_create(NULL, width, height);
	/* Otherwise it can be a filename or a PHP stream */
	} else {
		if(Z_TYPE_P(stream_zval) == IS_STRING) {
			stream = php_stream_open_wrapper(Z_STRVAL_P(stream_zval), "w+b", REPORT_ERRORS, NULL);
			owned_stream = 1;
		} else if(Z_TYPE_P(stream_zval) == IS_RESOURCE) {
			php_stream_from_zval(stream, stream_zval);
		} else {
			zend_throw_exception(ce_cairo_exception, "CairoPsSurface::__construct() expects parameter 1 to be null, a string, or a stream resource", 0 TSRMLS_CC);
			return;
		}

		/* Pack TSRMLS info and stream into struct */
		closure = ecalloc(1, sizeof(stream_closure));
		closure->stream = stream;
		closure->owned_stream = owned_stream;

		surface_object->closure = closure;
		surface_object->surface = cairo_ps_surface_create_for_stream(php_cairo_write_func, (void *)closure, width, height);
	}

	php_cairo_throw_exception(cairo_surface_status(surface_object->surface));
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoPsSurface_setSize_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, width)
	ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()

/* {{{ proto void CairoPsSurface->setSize(double width, double height)
       Changes the size of a PS surface for the current (and subsequent) pages.
       This should be called before any drawing takes place on the surface */
PHP_METHOD(CairoPsSurface, setSize)
{
	double width = 0.0, height = 0.0;
	cairo_surface_object *surface_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "dd", &width, &height) == FAILURE) {
		return;
	}

	surface_object = Z_CAIRO_SURFACE_P(getThis());
	if(!surface_object) {
            return;
        }

	cairo_ps_surface_set_size(surface_object->surface, width, height);
	php_cairo_throw_exception(cairo_surface_status(surface_object->surface));
}
/* }}} */

/* {{{ proto void CairoPsSurface->restrictToLevel(int level)
       Restricts the generated PostSript file to level. */
PHP_METHOD(CairoPsSurface, restrictToLevel)
{
	cairo_surface_object *surface_object;
	zend_long level = CAIRO_PS_LEVEL_2;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "l", &level) == FAILURE) {
		return;
	}

	surface_object = Z_CAIRO_SURFACE_P(getThis());
	if(!surface_object) {
            return;
        }

	cairo_ps_surface_restrict_to_level(surface_object->surface, level);
	php_cairo_throw_exception(cairo_surface_status(surface_object->surface));
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoPsSurface_setEps_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, level)
ZEND_END_ARG_INFO()

/* {{{ proto void CairoPsSurface->setEps(boolean eps)
       If eps is TRUE, the PostScript surface will output Encapsulated PostScript. */
PHP_METHOD(CairoPsSurface, setEps)
{
	zend_bool eps = 0;
	cairo_surface_object *surface_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "b", &eps) == FAILURE) {
		return;
	}
        
	surface_object = Z_CAIRO_SURFACE_P(getThis());
	if(!surface_object) {
            return;
        }

	cairo_ps_surface_set_eps(surface_object->surface, eps);
	php_cairo_throw_exception(cairo_surface_status(surface_object->surface));
}
/* }}} */

/* {{{ proto boolean CairoPsSurface->getEps(void)
       Check whether the PostScript surface will output Encapsulated PostScript. */
PHP_METHOD(CairoPsSurface, getEps)
{
	cairo_surface_object *surface_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}

	surface_object = Z_CAIRO_SURFACE_P(getThis());
	if(!surface_object) {
            return;
        }
	RETURN_BOOL(cairo_ps_surface_get_eps(surface_object->surface));
}
/* }}} */

/* {{{ proto void CairoPsSurface->dscBeginSetup(void)
       This function indicates that subsequent calls to cairo_ps_surface_dsc_comment() should
       direct comments to the Setup section of the PostScript output. */
PHP_METHOD(CairoPsSurface, dscBeginSetup)
{
	cairo_surface_object *surface_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}

	surface_object = Z_CAIRO_SURFACE_P(getThis());
	if(!surface_object) {
            return;
        }
	cairo_ps_surface_dsc_begin_setup(surface_object->surface);
}
/* }}} */

/* {{{ proto void CairoPsSurface->dscBeginPageSetup(void)
       This indicates that subsequent calls to cairo_ps_surface_dsc_comment()
       should direct comments to the PageSetup section of the PostScript output.

       This function call is only needed for the first page of a surface.
       It should be called after any call to cairo_ps_surface_dsc_begin_setup()
       and before any drawing is performed to the surface. */
PHP_METHOD(CairoPsSurface, dscBeginPageSetup)
{
	cairo_surface_object *surface_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}

	surface_object = Z_CAIRO_SURFACE_P(getThis());
	if(!surface_object) {
            return;
        }
	cairo_ps_surface_dsc_begin_page_setup(surface_object->surface);
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoPsSurface_dscComment_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, comment)
ZEND_END_ARG_INFO()

/* {{{ proto void CairoPsSurface->dscComment(string comment)
       Emit a comment into the PostScript output for the given surface. */
PHP_METHOD(CairoPsSurface, dscComment)
{
	cairo_surface_object *surface_object;
	char *comment, *cairo_comment;
	size_t comment_len;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "s", &comment, &comment_len) == FAILURE) {
		return;
	}

	surface_object = Z_CAIRO_SURFACE_P(getThis());
	if(!surface_object) {
            return;
        }

	cairo_comment = estrdup(comment);
	cairo_ps_surface_dsc_comment(surface_object->surface, cairo_comment);
	efree(cairo_comment);

	php_cairo_throw_exception(cairo_surface_status(surface_object->surface));
}
/* }}} */

/* {{{ proto array CairoPsSurface::getLevels(void)
       Used to retrieve the list of supported levels. See cairo_ps_surface_restrict_to_level(). */
PHP_METHOD(CairoPsSurface, getLevels)
{
	const cairo_ps_level_t *levels;
	int num_levels, i;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}

	cairo_ps_get_levels(&levels, &num_levels);
	array_init(return_value);
	for(i = 0; i < num_levels; i++) {
		add_next_index_long(return_value, levels[i]);
	}
}
/* }}} */

ZEND_BEGIN_ARG_INFO(CairoPsSurface_long_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, level)
ZEND_END_ARG_INFO()

/* {{{ proto string CairoPsSurface::levelToString(level)
       Get the string representation of the given level id. */
PHP_METHOD(CairoPsSurface, levelToString)
{
	zend_long level;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "l", &level) == FAILURE) {
		return;
	}

        if( level > CAIRO_PS_LEVEL_3 ) {
            zend_throw_exception(ce_cairo_exception, "Cairo\\Surface\\Ps::levelToString(): level-parameter is invalid. Maximum level is 1.", CAIRO_PS_LEVEL_3);
            return;
        }
	RETURN_STRING(cairo_ps_level_to_string(level));
}
/* }}} */

/* ----------------------------------------------------------------
    Cairo\Surface\ps Definition and registration
------------------------------------------------------------------*/

/* {{{ cairo_ps_surface_methods[] */
const zend_function_entry cairo_ps_surface_methods[] = {
	PHP_ME(CairoPsSurface, __construct, CairoPsSurface___construct_args, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(CairoPsSurface, setSize, CairoPsSurface_setSize_args, ZEND_ACC_PUBLIC)
	PHP_ME(CairoPsSurface, restrictToLevel, CairoPsSurface_long_args, ZEND_ACC_PUBLIC)
	PHP_ME(CairoPsSurface, getLevels, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(CairoPsSurface, levelToString, CairoPsSurface_long_args, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(CairoPsSurface, setEps, CairoPsSurface_setEps_args, ZEND_ACC_PUBLIC)
	PHP_ME(CairoPsSurface, getEps, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CairoPsSurface, dscBeginSetup, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CairoPsSurface, dscBeginPageSetup, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CairoPsSurface, dscComment, CairoPsSurface_dscComment_args, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};
/* }}} */

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(cairo_ps_surface)
{
	zend_class_entry pssurface_ce;
	zend_class_entry pslevel_ce;

	INIT_NS_CLASS_ENTRY(pssurface_ce, CAIRO_NAMESPACE, ZEND_NS_NAME("Surface", "Ps"), cairo_ps_surface_methods);
	ce_cairo_pssurface = zend_register_internal_class_ex(&pssurface_ce, ce_cairo_surface);

        INIT_NS_CLASS_ENTRY(pslevel_ce, CAIRO_NAMESPACE, ZEND_NS_NAME("Surface", ZEND_NS_NAME("Ps", "Level")), NULL);
        ce_cairo_pslevel = zend_register_internal_class_ex(&pslevel_ce, php_eos_datastructures_get_enum_ce());
	ce_cairo_pslevel->ce_flags |= ZEND_ACC_FINAL;

        #define CAIRO_PSLEVEL_DECLARE_ENUM(name) \
            zend_declare_class_constant_long(ce_cairo_pslevel, #name, \
            sizeof(#name)-1, CAIRO_PS_## name);

        CAIRO_PSLEVEL_DECLARE_ENUM(LEVEL_2);
        CAIRO_PSLEVEL_DECLARE_ENUM(LEVEL_3);

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

