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

#include "php_cairo_api.h"
#include "php_cairo_internal.h"
#include <zend_exceptions.h>

#if CAIRO_HAS_PS_SURFACE
#include <cairo-ps.h>
/* {{{ Class CairoPSSurface */

static zend_class_entry * CairoPSSurface_ce_ptr = NULL;
static zend_object_handlers CairoPSSurface_handlers;

ZEND_BEGIN_ARG_INFO_EX(CairoPSSurface____construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, wpts)
  ZEND_ARG_INFO(0, hpts)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(CairoPSSurface__dsc_comment_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
  ZEND_ARG_INFO(0, comment)	
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(CairoPSSurface__restrict_to_level_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, level)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(CairoPSSurface__set_size_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, wpts)
  ZEND_ARG_INFO(0, hpts)
ZEND_END_ARG_INFO()

/* {{{ Methods */


/* {{{ proto void construct(string file | stream stream, float wpts, float hpts)
   another utterly messed up constructor... */
PHP_METHOD(CairoPSSurface, __construct)
{
	zval * _this_zval;
	zval *zstream = NULL;
	const char * file = NULL;
	int file_len = 0;
	double wpts = 0.0;
	double hpts = 0.0;
	php_stream *stream;
	zval ***args, *obj;
	cairo_surface_object *curr;
	int argc = ZEND_NUM_ARGS();	
	args = (zval ***)safe_emalloc(argc, sizeof(zval *),0);
	if(ZEND_NUM_ARGS() == 0 ||
		zend_get_parameters_array_ex(argc, args) == FAILURE) {
		printf("ERROR");
		efree(args);
		WRONG_PARAM_COUNT;
	}

	obj = *(args[1]);
	switch(Z_TYPE_P(obj)) {
		case IS_DOUBLE:
			wpts = Z_DVAL_P(obj);
			break;
		case IS_LONG:
			wpts = Z_LVAL_P(obj);
			break;
		default :
			printf("Error!!!");
			return;
	}
	
	obj = *(args[2]);

	switch(Z_TYPE_P(obj)) {
		case IS_DOUBLE:
			hpts = Z_DVAL_P(obj);
			break;
		case IS_LONG:
			hpts = Z_LVAL_P(obj);
			break;
		default :
			printf("Error!!!");
			return;
	}


	_this_zval = getThis();
	curr = (cairo_surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	
	obj = *(args[0]);
	if(Z_TYPE_P(obj) == IS_STRING) {
		file = Z_STRVAL_P(obj);
		curr->surface = cairo_ps_surface_create(file, wpts, hpts);
	}
	else if(Z_TYPE_P(obj) == IS_RESOURCE)  {
		zstream = obj;
		php_stream_from_zval(stream, &zstream);	
		curr->surface = cairo_ps_surface_create_for_stream(_write_func, stream, wpts, hpts);
	}
	else {
		printf("ERROR\n");
	}

	efree(args);




}
/* }}} __construct */



/* {{{ proto void dscBeginPageSetup()
   */
PHP_METHOD(CairoPSSurface, dscBeginPageSetup)
{

	zval * _this_zval = NULL;
	cairo_surface_object *curr;


	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoPSSurface_ce_ptr) == FAILURE) {
		return;
	}
	curr = (cairo_surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_ps_surface_dsc_begin_page_setup(curr->surface);
	PHP_CAIRO_SURFACE_ERROR(curr->surface);



}
/* }}} dscBeginPageSetup */



/* {{{ proto void dscBeginSetup()
   */
PHP_METHOD(CairoPSSurface, dscBeginSetup)
{

	zval * _this_zval = NULL;
	cairo_surface_object *curr;


	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoPSSurface_ce_ptr) == FAILURE) {
		return;
	}

	curr = (cairo_surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_ps_surface_dsc_begin_setup(curr->surface);
	PHP_CAIRO_SURFACE_ERROR(curr->surface);

}
/* }}} dscBeginSetup */



/* {{{ proto void dscComment(string comment)
   */
PHP_METHOD(CairoPSSurface, dscComment)
{

	zval * _this_zval = NULL;
	cairo_surface_object *curr;
	const char *comment = NULL;
	int comment_len = 0;


	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Os", &_this_zval, CairoPSSurface_ce_ptr, &comment, &comment_len) == FAILURE) {
		return;
	}

	curr = (cairo_surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_ps_surface_dsc_comment(curr->surface, comment);
	PHP_CAIRO_SURFACE_ERROR(curr->surface);

}
/* }}} dscComment */



/* {{{ proto array getLevels() -- cairo 1.6
   */
PHP_METHOD(CairoPSSurface, getLevels)
{

	zval * _this_zval = NULL;
	cairo_surface_object *curr;


	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoPSSurface_ce_ptr) == FAILURE) {
		return;
	}

	curr = (cairo_surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);


	array_init(return_value);

	do {
		/* ONLY for CAIRO 1.6 */
	} while (0);
}
/* }}} getLevels */



/* {{{ proto string getLevelString() --cairo 1.6
   */
PHP_METHOD(CairoPSSurface, getLevelString)
{

	zval * _this_zval = NULL;
	cairo_surface_object *curr;


	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoPSSurface_ce_ptr) == FAILURE) {
		return;
	}

	curr = (cairo_surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);


	do {
		/* ONLY for CAIRO 1.6*/
	} while (0);
}
/* }}} getLevelString */



/* {{{ proto void restrictToLevel(int level) --cairo 1.6
   */
PHP_METHOD(CairoPSSurface, restrictToLevel)
{

	zval * _this_zval = NULL;
	long level = 0;
	cairo_surface_object *curr;


	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ol", &_this_zval, CairoPSSurface_ce_ptr, &level) == FAILURE) {
		return;
	}

	curr = (cairo_surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);


	do {
		/* ONLY for CAIRO 1.6 */
	} while (0);
}
/* }}} restrictToLevel */



/* {{{ proto void setEps() --cairo 1.6
   */
PHP_METHOD(CairoPSSurface, setEps)
{

	zval * _this_zval = NULL;
	cairo_surface_object *curr;


	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoPSSurface_ce_ptr) == FAILURE) {
		return;
	}

	curr = (cairo_surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);


	do {
		/* ONLY for CAIRO 1.6 */
	} while (0);
}
/* }}} setEps */



/* {{{ proto void setSize(float wpts, float hpts)
   */
PHP_METHOD(CairoPSSurface, setSize)
{

	zval * _this_zval = NULL;
	double wpts = 0.0;
	double hpts = 0.0;
	cairo_surface_object *curr;


	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odd", &_this_zval, CairoPSSurface_ce_ptr, &wpts, &hpts) == FAILURE) {
		return;
	}

	curr = (cairo_surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_ps_surface_set_size(curr->surface, wpts, hpts);

}
/* }}} setSize */


static zend_function_entry CairoPSSurface_methods[] = {
	PHP_ME(CairoPSSurface, __construct, CairoPSSurface____construct_args, /**/ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(CairoPSSurface, dscBeginPageSetup, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoPSSurface, dscBeginSetup, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoPSSurface, dscComment, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoPSSurface, getLevels, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoPSSurface, getLevelString, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoPSSurface, restrictToLevel, CairoPSSurface__restrict_to_level_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoPSSurface, setEps, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoPSSurface, setSize, CairoPSSurface__set_size_args, /**/ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

/* }}} Methods */

static zend_object_value CairoPSSurface_object_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	retval = CairoSurface_object_new(ce TSRMLS_CC);
	retval.handlers = &CairoPSSurface_handlers;
	return retval;
}

void class_init_CairoPSSurface(TSRMLS_D)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "CairoPSSurface", CairoPSSurface_methods);
	CairoPSSurface_ce_ptr = zend_register_internal_class_ex(&ce, get_CairoSurface_ce_ptr(NULL), "CairoSurface" TSRMLS_CC);
	CairoPSSurface_ce_ptr->create_object = CairoPSSurface_object_new;
	memcpy(&CairoPSSurface_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
}

/* }}} Class CairoPSSurface */

/* Helper Function - used in CairoSurface, NOT EXPORTED */
zend_class_entry *  get_CairoPsSurface_ce_ptr()
{
	return CairoPSSurface_ce_ptr;
}

#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw = 4 ts = 4 fdm = marker
 * vim<600: noet sw = 4 ts = 4
 */