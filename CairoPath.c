#include "php_cairo_api.h"
#include "CairoPath.h"
#include "CairoExceptionMacro.h"
#include "php_cairo_ce_ptr.h"

/* {{{ Class CairoPath */

static zend_class_entry *CairoPath_ce_ptr = NULL;
/* {{{ Methods */


/* {{{ proto void construct()
   */
PHP_METHOD(CairoPath, __construct)
{

	php_error(E_WARNING, "Can not call directly"); RETURN_FALSE;

}
/* }}} __construct */



/* {{{ proto array toStr()
   */
PHP_METHOD(CairoPath, toStr)
{

	zval * _this_zval = NULL;
	path_object *curr;
	cairo_path_t *path;
	cairo_path_data_t *data;
	int i;
	char buf[200]; /* I think this is more than enough ... */


	_this_zval = getThis();

	curr = (path_object *)zend_objects_get_address(_this_zval TSRMLS_CC);

	path = curr->path;
	array_init(return_value);
	
	
	for (i = 0; i < path->num_data; i += path->data[i].header.length) {
		data = &path->data[i];
		switch (data->header.type) {
		case CAIRO_PATH_MOVE_TO:
			sprintf(buf, "move_to %f %f", data[1].point.x, data[1].point.y);
			add_next_index_string(return_value, buf, 1);
			break;
		case CAIRO_PATH_LINE_TO:
			sprintf(buf, "line_to %f %f", data[1].point.x, data[1].point.y);
			add_next_index_string(return_value, buf, 1);
			break;
		case CAIRO_PATH_CURVE_TO:
			sprintf(buf, "curve_to %f %f %f %f %f %f", data[1].point.x, data[1].point.y, data[2].point.x, data[2].point.y, data[3].point.x, data[3].point.y);
			add_next_index_string(return_value, buf, 1);
			break;
		case CAIRO_PATH_CLOSE_PATH:
			sprintf(buf, "close_path");
			add_next_index_string(return_value, buf, 1);
			break;
		}
		}

}
/* }}} str */


static zend_function_entry CairoPath_methods[] = {
	PHP_ME(CairoPath, __construct, NULL, /**/ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(CairoPath, toStr, NULL, /**/ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

/* }}} Methods */

static zend_object_handlers CairoPath_handlers;


static void CairoPath_object_dtor(void *object)
{
	path_object *path = (path_object *)object;
	zend_hash_destroy(path->std.properties);
	FREE_HASHTABLE(path->std.properties);

	if(path->path){
		cairo_path_destroy(path->path);
	}
	efree(object);
}

static zend_object_value CairoPath_object_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	path_object *path;
	zval *temp;

	path = emalloc(sizeof(path_object));
	memset(path,0,sizeof(path_object));
	path->std.ce = ce;
	ALLOC_HASHTABLE(path->std.properties);
	zend_hash_init(path->std.properties, 0, NULL, ZVAL_PTR_DTOR,0);
	zend_hash_copy(path->std.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref, (void *) &temp, sizeof(zval *));
	retval.handle = zend_objects_store_put(path, NULL, (zend_objects_free_object_storage_t)CairoPath_object_dtor, NULL TSRMLS_CC);
	retval.handlers = &CairoPath_handlers;
	return retval;
}

void class_init_CairoPath(TSRMLS_D)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "CairoPath", CairoPath_methods);
	CairoPath_ce_ptr = zend_register_internal_class(&ce TSRMLS_CC);
	CairoPath_ce_ptr->create_object = CairoPath_object_new;
	memcpy(&CairoPath_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	CairoPath_handlers.clone_obj = NULL;

}

/* }}} Class CairoPath */

PHP_CAIRO_API zend_class_entry * get_CairoPath_ce_ptr()
{
	return CairoPath_ce_ptr;
}


