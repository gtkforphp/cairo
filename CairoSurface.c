/* {{{ Class CairoSurface */

PHP_CAIRO_API static zend_class_entry * CairoSurface_ce_ptr = NULL;
static zend_object_handlers CairoSurface_handlers;

static cairo_status_t
_write_func(void *closure, const unsigned char *data, unsigned int length)
{
	int written;
	php_stream *zs = (php_stream *)closure ;
	written = php_stream_write(zs, data, length);
	if(written == length)
		return CAIRO_STATUS_SUCCESS;
	else {
		printf("is it an error ?");
	}
}

static cairo_status_t
_read_func(void *closure, const unsigned char *data, unsigned int length)
{
	int read;
	php_stream *zs = (php_stream *)closure;
	read = php_stream_read(zs, data, length);
	if(read == length)
		return CAIRO_STATUS_SUCCESS;
	else {
		printf("is it an error");
	}

}
	

/*
typedef struct _surface_object {
	zend_object std;
	cairo_surface_t *surface;
} surface_object;
*/

/* {{{ Methods */


/* {{{ proto void construct()
   */
PHP_METHOD(CairoSurface, __construct)
{
	zval * _this_zval;



	if (ZEND_NUM_ARGS()>0)	{
		WRONG_PARAM_COUNT;
		php_print("wtf");
		return;
	}

	php_print("No direct call for this constructor");


}
/* }}} __construct */



/* {{{ proto object createSimilar(int content, int width, int height)
   */
PHP_METHOD(CairoSurface, createSimilar)
{
	zend_class_entry *ce;
	zval * _this_zval = NULL;
	cairo_surface_t *sur;
	int content;
	long width = 0;
	long height = 0;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Olll", &_this_zval, CairoSurface_ce_ptr, &content, &width, &height) == FAILURE) {
		return;
	}

	surface_object *curr = (surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	sur = cairo_surface_create_similar(curr->surface, content, width, height);
	ce = get_CairoSurface_ce_ptr(sur);
	object_init_ex(return_value, ce);
	surface_object *sobj = (surface_object *)zend_objects_get_address(return_value TSRMLS_CC);
	sobj->surface = sur;

}
/* }}} createSimilar */


/* {{{ proto void finish()
   */
PHP_METHOD(CairoSurface, finish)
{

	zval * _this_zval = NULL;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoSurface_ce_ptr) == FAILURE) {
		return;
	}

	surface_object *curr = (surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_surface_finish(curr->surface);
}
/* }}} finish */



/* {{{ proto void flush()
   */
PHP_METHOD(CairoSurface, flush)
{

	zval * _this_zval = NULL;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoSurface_ce_ptr) == FAILURE) {
		return;
	}

	surface_object *curr = (surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	
	cairo_surface_flush(curr->surface);

}
/* }}} flush */



/* {{{ proto int getContent()
   */
PHP_METHOD(CairoSurface, getContent)
{

	zval * _this_zval = NULL;
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoSurface_ce_ptr) == FAILURE) {
		return;
	}

	surface_object *curr = (surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	
	RETURN_LONG(cairo_surface_get_content(curr->surface));
}
/* }}} getContent */



/* {{{ proto array getDeviceOffset()
   */
PHP_METHOD(CairoSurface, getDeviceOffset)
{

	zval * _this_zval = NULL;
	double x_offset, y_offset;
	
	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoSurface_ce_ptr) == FAILURE) {
		return;
	}

	surface_object *curr = (surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);

	cairo_surface_get_device_offset(curr->surface, &x_offset, &y_offset);

	array_init(return_value);
	add_assoc_double(return_value, "x", x_offset);
	add_assoc_double(return_value, "y", y_offset);

}
/* }}} getDeviceOffset */



/* {{{ proto object getFontOptions()
   */
PHP_METHOD(CairoSurface, getFontOptions)
{

	zval * _this_zval = NULL;
	
	cairo_font_options_t *options = cairo_font_options_create();
	

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoSurface_ce_ptr) == FAILURE) {
		return;
	}

	surface_object *curr = (surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	
	cairo_surface_get_font_options(curr->surface, options);
	object_init_ex(return_value, CairoFontOptions_ce_ptr);
	fontoptions_object *fobj = (fontoptions_object *)zend_objects_get_address(return_value TSRMLS_CC);
	fobj->fontoptions = options;

}
/* }}} getFontOptions */



/* {{{ proto void markDirtyRectangle([int x, int y, int width, int height])
   */
PHP_METHOD(CairoSurface, markDirtyRectangle)
{

	zval * _this_zval = NULL;
	long x = 0;
	long y = 0;
	long width = -1;
	long height = -1;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O|llll", &_this_zval, CairoSurface_ce_ptr, &x, &y, &width, &height) == FAILURE) {
		return;
	}
	surface_object *curr = (surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_surface_mark_dirty_rectangle(curr->surface, x, y, width, height);

}
/* }}} markDirtyRectangle */



/* {{{ proto void setDeviceOffset(float x_offset, float y_offset)
   */
PHP_METHOD(CairoSurface, setDeviceOffset)
{

	zval * _this_zval = NULL;
	double x_offset = 0.0;
	double y_offset = 0.0;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odd", &_this_zval, CairoSurface_ce_ptr, &x_offset, &y_offset) == FAILURE) {
		return;
	}

	surface_object *curr = (surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_surface_set_device_offset(curr->surface, x_offset, y_offset);

}
/* }}} setDeviceOffset */



/* {{{ proto void setFallbackResolution(float x_ppi, float y_ppi)
   */
PHP_METHOD(CairoSurface, setFallbackResolution)
{

	zval * _this_zval = NULL;
	double x_ppi = 0.0;
	double y_ppi = 0.0;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odd", &_this_zval, CairoSurface_ce_ptr, &x_ppi, &y_ppi) == FAILURE) {
		return;
	}

	surface_object *curr = (surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_surface_set_fallback_resolution(curr->surface, x_ppi, y_ppi);	

}
/* }}} setFallbackResolution */



/* {{{ proto void writeToPng(string file)
   */
PHP_METHOD(CairoSurface, writeToPng)
{

	zval * _this_zval = NULL;
	const char * file = NULL;
	int file_len = 0;
	cairo_status_t status;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Os", &_this_zval, CairoSurface_ce_ptr, &file, &file_len) == FAILURE) {
		return;
	}

	surface_object *curr = (surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	status = cairo_surface_write_to_png(curr->surface, file);

}
/* }}} writeToPng */


/* {{{ proto void writeToPngStream(stream file)
	*/
PHP_METHOD(CairoSurface, writeToPngStream)
{
	FILE *file;
	zval *_this_zval = NULL;
	cairo_status_t status;
	zval *zstream;
	php_stream *stream;
	int err;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Or", &_this_zval, CairoSurface_ce_ptr, &zstream)) {
		return;
	}
	
	surface_object *curr = (surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	php_stream_from_zval(stream, &zstream);
	status = cairo_surface_write_to_png_stream(curr->surface, _write_func, stream);

}

/* }}} writeToPngStream*/


static zend_function_entry CairoSurface_methods[] = {
	PHP_ME(CairoSurface, __construct, NULL, /**/ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(CairoSurface, createSimilar, CairoSurface__create_similar_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoSurface, finish, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoSurface, flush, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoSurface, getContent, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoSurface, getDeviceOffset, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoSurface, getFontOptions, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoSurface, markDirtyRectangle, CairoSurface__mark_dirty_rectangle_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoSurface, setDeviceOffset, CairoSurface__set_device_offset_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoSurface, setFallbackResolution, CairoSurface__set_fallback_resolution_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoSurface, writeToPng, CairoSurface__write_to_png_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoSurface, writeToPngStream, CairoSurface__write_to_png_stream_args, /**/ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

/* }}} Methods */


static void CairoSurface_object_dtor(void *object)
{
	surface_object *surface = (surface_object *)object;
	zend_hash_destroy(surface->std.properties);
	FREE_HASHTABLE(surface->std.properties);
	if(surface->surface){
		cairo_surface_finish(surface->surface);
		cairo_surface_destroy(surface->surface);
		
	}
	efree(object);
}

static zend_object_value CairoSurface_object_new(zend_class_entry *ce)
{
	zend_object_value retval;
	surface_object *surface;
	zval *temp;

	surface = emalloc(sizeof(surface_object));
	memset(surface,0,sizeof(surface_object));

	surface->std.ce = ce;

	ALLOC_HASHTABLE(surface->std.properties);
	zend_hash_init(surface->std.properties, 0, NULL, ZVAL_PTR_DTOR, 0);
	zend_hash_copy(surface->std.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref,(void *) &temp, sizeof(zval *));
	retval.handle = zend_objects_store_put(surface, NULL, (zend_objects_free_object_storage_t)CairoSurface_object_dtor, NULL TSRMLS_CC);
	retval.handlers = &CairoSurface_handlers;
	return retval;
}

static void class_init_CairoSurface(void)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "CairoSurface", CairoSurface_methods);
	CairoSurface_ce_ptr = zend_register_internal_class(&ce);
	CairoSurface_ce_ptr->create_object = CairoSurface_object_new;
	memcpy(&CairoSurface_handlers, zend_get_std_object_handlers(),sizeof(zend_object_handlers));
	CairoSurface_handlers.clone_obj = NULL;
}

/* }}} Class CairoSurface */

/* {{{ Class CairoImageSurface	-- done  :)*/

static zend_class_entry * CairoImageSurface_ce_ptr = NULL;
static zend_object_handlers CairoImageSurface_handlers;


/* {{{ Methods */


/* {{{ proto void construct(int format, int widthm, int height)
   */
PHP_METHOD(CairoImageSurface, __construct)
{
	zval * _this_zval;

	cairo_format_t format = 0;
	long widthm = 0;
	long height = 0;



	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lll", &format, &widthm, &height) == FAILURE) {
		return;
	}

	_this_zval = getThis();
	surface_object *curr = (surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	curr->surface = cairo_image_surface_create(format, widthm, height);

}
/* }}} __construct */



/* {{{ proto void createFromData(string obj, int format, int width, int height [, int stride])
   */
PHP_METHOD(CairoImageSurface, createFromData)
{

	zval * _this_zval = NULL;
	const char * buffer = NULL;
	int buffer_len = 0;
	long format = 0;
	long width = 0;
	long height = 0;
	long stride = -1;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Oslll|l", &_this_zval, CairoImageSurface_ce_ptr, &buffer, &buffer_len, &format, &width, &height, &stride) == FAILURE) {
		return;
	}

	surface_object *curr = (surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_surface_finish(curr->surface);
	cairo_surface_destroy(curr->surface);
	
	if(stride < 0 ){
		switch(format) {
			case CAIRO_FORMAT_ARGB32:
			case CAIRO_FORMAT_RGB24:
				stride = width * 4;
				break;
			case CAIRO_FORMAT_RGB16_565:
				stride = width * 2;
				break;
			case CAIRO_FORMAT_A8:
				stride = width;
				break;
			case CAIRO_FORMAT_A1:
				stride = (width + 1) / 8;
				break;
			default:
				php_error(E_WARNING, "Unknown format");
				return;
				
		}
	}
	/*
	if (height * stride > buffer_len) {
		php_error(E_WARNING,"buffer is not long enough");
		return;
	}
	*/
	curr->surface = cairo_image_surface_create_for_data(buffer, format, width, height, stride);

}
/* }}} createFromData */



/* {{{ proto void createFromPng(string file)
   */
PHP_METHOD(CairoImageSurface, createFromPng)
{

	zval * _this_zval = NULL;
	const char * file = NULL;
	int file_len = 0;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Os", &_this_zval, CairoImageSurface_ce_ptr, &file, &file_len) == FAILURE) {
		return;
	}

	surface_object *curr = (surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);

	curr->surface = cairo_image_surface_create_from_png(file);

}
/* }}} createFromPng */



/* {{{ proto void createFromPngStream(stream zstream)
 */

PHP_METHOD(CairoImageSurface, createFromPngStream)
{	
	FILE *file;
	zval *_this_zval = NULL;
	cairo_status_t status;
	zval *zstream;
	php_stream *stream;
	int err;
		
   if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Or", &_this_zval, CairoImageSurface_ce_ptr, &zstream)) {
		return;
	}
										
	surface_object *curr = (surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	
	php_stream_from_zval(stream, &zstream);
	curr->surface = cairo_image_surface_create_from_png_stream( _read_func, stream);


}

/* }}} createFromPngStream*/



/* {{{ proto string getData() -- not required
   */
PHP_METHOD(CairoImageSurface, getData)
{

	zval * _this_zval = NULL;
	char *str;


	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoImageSurface_ce_ptr) == FAILURE) {
		return;
	}

	surface_object *curr = (surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);

	
	str = cairo_image_surface_get_data(curr->surface);
	RETURN_STRING(str, 0);
}
/* }}} getData */



/* {{{ proto int getFormat()
   */
PHP_METHOD(CairoImageSurface, getFormat)
{
	zval * _this_zval = NULL;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoImageSurface_ce_ptr) == FAILURE) {
		return;
	}
	surface_object *curr = (surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	
	RETURN_LONG(cairo_image_surface_get_format(curr->surface));
}
/* }}} getFormat */



/* {{{ proto int getHeight()
   */
PHP_METHOD(CairoImageSurface, getHeight)
{
	zval * _this_zval = NULL;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoImageSurface_ce_ptr) == FAILURE) {
		return;
	}

	surface_object *curr = (surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	RETURN_LONG(cairo_image_surface_get_height(curr->surface));

}
/* }}} getHeight */



/* {{{ proto int getStride()
   */
PHP_METHOD(CairoImageSurface, getStride)
{
	zval * _this_zval = NULL;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoImageSurface_ce_ptr) == FAILURE) {
		return;
	}

	surface_object *curr = (surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	RETURN_LONG(cairo_image_surface_get_stride(curr->surface));

}
/* }}} getStride */



/* {{{ proto int getWidth()
   */
PHP_METHOD(CairoImageSurface, getWidth)
{
	zval * _this_zval = NULL;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoImageSurface_ce_ptr) == FAILURE) {
		return;
	}


	surface_object *curr = (surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);

	RETURN_LONG(cairo_image_surface_get_width(curr->surface));
}
/* }}} getWidth */


static zend_function_entry CairoImageSurface_methods[] = {
	PHP_ME(CairoImageSurface, __construct, CairoImageSurface____construct_args, /**/ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(CairoImageSurface, createFromData, CairoImageSurface__create_from_data_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoImageSurface, createFromPng, CairoImageSurface__create_from_png_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoImageSurface, createFromPngStream, CairoImageSurface__create_from_png_stream_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoImageSurface, getData, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoImageSurface, getFormat, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoImageSurface, getHeight, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoImageSurface, getStride, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoImageSurface, getWidth, NULL, /**/ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

/* }}} Methods */

static zend_object_value CairoImageSurface_object_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	retval = CairoSurface_object_new(ce TSRMLS_CC);
	retval.handlers = &CairoImageSurface_handlers;
	return retval;
}


static void class_init_CairoImageSurface(void)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "CairoImageSurface", CairoImageSurface_methods);
	CairoImageSurface_ce_ptr = zend_register_internal_class_ex(&ce, CairoSurface_ce_ptr, "CairoSurface" TSRMLS_CC);
	CairoImageSurface_ce_ptr->create_object = CairoImageSurface_object_new;
	memcpy(&CairoImageSurface_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
}

/* }}} Class CairoImageSurface */

/* {{{ Class CairoPDFSurface */

static zend_class_entry * CairoPDFSurface_ce_ptr = NULL;
static zend_object_handlers CairoPDFSurface_handlers;
/* {{{ Methods */


/* {{{ proto void construct(string file, float wpts, float hpts)
   */
PHP_METHOD(CairoPDFSurface, __construct)
{
	zval * _this_zval;
	zval *zstream = NULL;
	const char * file = NULL;
	int file_len = 0;
	double wpts = 0.0;
	double hpts = 0.0;
	php_stream *stream;
	int argc = ZEND_NUM_ARGS();
	zval ***args, *obj;

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

	surface_object *curr = (surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	
	obj = *(args[0]);
	if(Z_TYPE_P(obj) == IS_STRING) {
		file = Z_STRVAL_P(obj);
		curr->surface = cairo_pdf_surface_create(file, wpts, hpts);
	}
	else if(Z_TYPE_P(obj) == IS_RESOURCE)  {
		zstream = obj;
		php_stream_from_zval(stream, &zstream);	
		curr->surface = cairo_pdf_surface_create_for_stream(_write_func, stream, wpts, hpts);
	}
	else {
		printf("ERROR\n");
	}

	efree(args);
}
/* }}} __construct */



/* {{{ proto void setSize(float wptd, float hpts)
   */
PHP_METHOD(CairoPDFSurface, setSize)
{

	zval * _this_zval = NULL;
	double wpts = 0.0;
	double hpts = 0.0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odd", &_this_zval, CairoPDFSurface_ce_ptr, &wpts, &hpts) == FAILURE) {
		return;
	}

	surface_object *curr = (surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_pdf_surface_set_size(curr->surface, wpts, hpts);

}
/* }}} setSize */


static zend_function_entry CairoPDFSurface_methods[] = {
	PHP_ME(CairoPDFSurface, __construct, CairoPDFSurface____construct_args, /**/ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(CairoPDFSurface, setSize, CairoPDFSurface__set_size_args, /**/ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

/* }}} Methods */

static zend_object_value CairoPDFSurface_object_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	retval = CairoSurface_object_new(ce TSRMLS_CC);
	retval.handlers = &CairoPDFSurface_handlers;
	return retval;
}

static void class_init_CairoPDFSurface(void)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "CairoPDFSurface", CairoPDFSurface_methods);
	CairoPDFSurface_ce_ptr = zend_register_internal_class_ex(&ce, CairoSurface_ce_ptr, "CairoSurface" TSRMLS_CC);
	CairoPDFSurface_ce_ptr->create_object = CairoPDFSurface_object_new;
	memcpy(&CairoPDFSurface_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

}

/* }}} Class CairoPDFSurface */

/* {{{ Class CairoPSSurface */

static zend_class_entry * CairoPSSurface_ce_ptr = NULL;
static zend_object_handlers CairoPSSurface_handlers;
/* {{{ Methods */


/* {{{ proto void construct(string file | stream stream, float wpts, float hpts)
   */
PHP_METHOD(CairoPSSurface, __construct)
{
	zval * _this_zval;
	zval *zstream = NULL;
	const char * file = NULL;
	int file_len = 0;
	double wpts = 0.0;
	double hpts = 0.0;
	php_stream *stream;
	int argc = ZEND_NUM_ARGS();
	zval ***args, *obj;

	args = (zval **)safe_emalloc(argc, sizeof(zval *),0);
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
	surface_object *curr = (surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	
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



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoPSSurface_ce_ptr) == FAILURE) {
		return;
	}
	surface_object *curr = (surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_ps_surface_dsc_begin_page_setup(curr->surface);
	PHP_CAIRO_SURFACE_ERROR(curr->surface);



}
/* }}} dscBeginPageSetup */



/* {{{ proto void dscBeginSetup()
   */
PHP_METHOD(CairoPSSurface, dscBeginSetup)
{

	zval * _this_zval = NULL;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoPSSurface_ce_ptr) == FAILURE) {
		return;
	}

	surface_object *curr = (surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_ps_surface_dsc_begin_setup(curr->surface);
	PHP_CAIRO_SURFACE_ERROR(curr->surface);

}
/* }}} dscBeginSetup */



/* {{{ proto void dscComment()
   */
PHP_METHOD(CairoPSSurface, dscComment)
{

	zval * _this_zval = NULL;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoPSSurface_ce_ptr) == FAILURE) {
		return;
	}

	surface_object *curr = (surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	cairo_ps_surface_dsc_comment(curr->surface);
	PHP_CAIRO_SURFACE_ERROR(curr->surface);

}
/* }}} dscComment */



/* {{{ proto array getLevels() -- cairo 1.6
   */
PHP_METHOD(CairoPSSurface, getLevels)
{

	zval * _this_zval = NULL;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoPSSurface_ce_ptr) == FAILURE) {
		return;
	}

	surface_object *curr = (surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);


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



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoPSSurface_ce_ptr) == FAILURE) {
		return;
	}

	surface_object *curr = (surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);


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



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ol", &_this_zval, CairoPSSurface_ce_ptr, &level) == FAILURE) {
		return;
	}

	surface_object *curr = (surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);


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



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoPSSurface_ce_ptr) == FAILURE) {
		return;
	}

	surface_object *curr = (surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);


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



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Odd", &_this_zval, CairoPSSurface_ce_ptr, &wpts, &hpts) == FAILURE) {
		return;
	}

	surface_object *curr = (surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
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

static void class_init_CairoPSSurface(void)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "CairoPSSurface", CairoPSSurface_methods);
	CairoPSSurface_ce_ptr = zend_register_internal_class_ex(&ce, CairoSurface_ce_ptr, "CairoSurface" TSRMLS_CC);
	CairoPSSurface_ce_ptr->create_object = CairoPSSurface_object_new;
	memcpy(&CairoPSSurface_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
}

/* }}} Class CairoPSSurface */

/* {{{ Class CairoQuartzSurface */

static zend_class_entry * CairoQuartzSurface_ce_ptr = NULL;
static zend_object_handlers CairoQuartzSurface_handlers;
/* {{{ Methods */


/* {{{ proto void construct(float wpixels, float hpixels [, int format])
   */
PHP_METHOD(CairoQuartzSurface, __construct)
{
	zval * _this_zval;

	double wpixels = 0.0;
	double hpixels = 0.0;
	long format = 0;



	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dd|l", &wpixels, &hpixels, &format) == FAILURE) {
		return;
	}

	_this_zval = getThis();
	surface_object *curr = (surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);


	php_error(E_WARNING, "CANNOT BE CALLED"); RETURN_FALSE;

}
/* }}} __construct */


static zend_function_entry CairoQuartzSurface_methods[] = {
	PHP_ME(CairoQuartzSurface, __construct, CairoQuartzSurface____construct_args, /**/ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	{ NULL, NULL, NULL }
};

/* }}} Methods */

static zend_object_value CairoQuartzSurface_object_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	retval = CairoSurface_object_new(ce TSRMLS_CC);
	retval.handlers = &CairoQuartzSurface_handlers;
	return retval;
}

static void class_init_CairoQuartzSurface(void)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "CairoQuartzSurface", CairoQuartzSurface_methods);
	CairoQuartzSurface_ce_ptr = zend_register_internal_class_ex(&ce, CairoSurface_ce_ptr, "CairoSurface" TSRMLS_CC);
	CairoQuartzSurface_ce_ptr->create_object = CairoQuartzSurface_object_new;
	memcpy(&CairoQuartzSurface_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

}

/* }}} Class CairoQuartzSurface */

/* {{{ Class CairoSVGSurface */

static zend_class_entry * CairoSVGSurface_ce_ptr = NULL;
static zend_object_handlers CairoSVGSurface_handlers;


/* {{{ Methods */


/* {{{ proto void construct(string file, float wpts, float hpts)
   */
PHP_METHOD(CairoSVGSurface, __construct)
{
	zval * _this_zval;
	zval *zstream = NULL;
	const char * file = NULL;
	int file_len = 0;
	double wpts = 0.0;
	double hpts = 0.0;
	php_stream *stream;
	int argc = ZEND_NUM_ARGS();
	zval ***args, *obj;

	args = (zval **)safe_emalloc(argc, sizeof(zval *),0);
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
			printf("error!!!");
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
	surface_object *curr = (surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	
	obj = *(args[0]);
	if(Z_TYPE_P(obj) == IS_STRING) {
		file = Z_STRVAL_P(obj);
		curr->surface = cairo_svg_surface_create(file, wpts, hpts);
	}
	else if(Z_TYPE_P(obj) == IS_RESOURCE)  {
		zstream = obj;
		php_stream_from_zval(stream, &zstream);	
		curr->surface = cairo_svg_surface_create_for_stream(_write_func, stream, wpts, hpts);
	}
	else {
		printf("ERROR\n");
	}

	efree(args);


}
/* }}} __construct */


static zend_function_entry CairoSVGSurface_methods[] = {
	PHP_ME(CairoSVGSurface, __construct, CairoSVGSurface____construct_args, /**/ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	{ NULL, NULL, NULL }
};

/* }}} Methods */

static zend_object_value CairoSVGSurface_object_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	retval = CairoSurface_object_new(ce TSRMLS_CC);
	retval.handlers = &CairoSVGSurface_handlers;
	return retval;
}

static void class_init_CairoSVGSurface(void)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "CairoSVGSurface", CairoSVGSurface_methods);
	CairoSVGSurface_ce_ptr = zend_register_internal_class_ex(&ce, CairoSurface_ce_ptr, "CairoSurface" TSRMLS_CC);
	CairoSVGSurface_ce_ptr->create_object = CairoSVGSurface_object_new;
	memcpy(&CairoSVGSurface_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

}

/* }}} Class CairoSVGSurface */

/* {{{ Class CairoWin32Surface*/

static zend_class_entry * CairoWin32Surface_ce_ptr = NULL;
static zend_object_handlers CairoWin32Surface_handlers;

/* {{{ Methods */


/* {{{ proto void construct(int hdc)
   */
PHP_METHOD(CairoWin32Surface, __construct)
{
	zval * _this_zval;

	long hdc = 0;



	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &hdc) == FAILURE) {
		return;
	}

	_this_zval = getThis();
	surface_object *curr = (surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	curr->surface = cairo_win32_surface_create(hdc, NULL);
}
/* }}} __construct */


static zend_function_entry CairoWin32Surface_methods[] = {
	PHP_ME(CairoWin32Surface, __construct, NULL, /**/ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	{ NULL, NULL, NULL }
};

/* }}} Methods */

static zend_object_value CairoWin32Surface_object_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	retval = CairoSurface_object_new(ce TSRMLS_CC);
	retval.handlers = &CairoWin32Surface_handlers;
	return retval;
}

static void class_init_CairoWin32Surface(void)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "CairoWin32Surface", CairoWin32Surface_methods);
	CairoWin32Surface_ce_ptr = zend_register_internal_class_ex(&ce, CairoSurface_ce_ptr, "CairoSurface" TSRMLS_CC);
	CairoWin32Surface_ce_ptr->create_object = CairoWin32Surface_object_new;
	memcpy(&CairoWin32Surface_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

}

/* }}} Class CairoWin32Surface */

/* {{{ Class CairoXlibSurface */

static zend_class_entry * CairoXlibSurface_ce_ptr = NULL;
static zend_object_handlers CairoXlibSurface_handlers;
/* {{{ Methods */


/* {{{ proto void construct()
   */
PHP_METHOD(CairoXlibSurface, __construct)
{
	zval * _this_zval;



	if (ZEND_NUM_ARGS()>0)	{
		WRONG_PARAM_COUNT;
	}

	_this_zval = getThis();
	surface_object *curr = (surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);

	php_error(E_WARNING, "Cannot Be Initialized"); RETURN_FALSE;

}
/* }}} __construct */



/* {{{ proto int getDepth()
   */
PHP_METHOD(CairoXlibSurface, getDepth)
{

	zval * _this_zval = NULL;


	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoXlibSurface_ce_ptr) == FAILURE) {
		return;
	}

	surface_object *curr = (surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);

	RETURN_LONG(cairo_xlib_surface_get_depth(curr->surface));

}
/* }}} getDepth */



/* {{{ proto int getHeight()
   */
PHP_METHOD(CairoXlibSurface, getHeight)
{

	zval * _this_zval = NULL;


	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoXlibSurface_ce_ptr) == FAILURE) {
		return;
	}

	surface_object *curr = (surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	RETURN_LONG(cairo_xlib_surface_get_height(curr->surface));
	
}
/* }}} getHeight */



/* {{{ proto int getWidth()
   */
PHP_METHOD(CairoXlibSurface, getWidth)
{

	zval * _this_zval = NULL;


	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, CairoXlibSurface_ce_ptr) == FAILURE) {
		return;
	}

	surface_object *curr = (surface_object *)zend_objects_get_address(_this_zval TSRMLS_CC);
	RETURN_LONG(cairo_xlib_surface_get_width(curr->surface));
		
}
/* }}} getWidth */


static zend_function_entry CairoXlibSurface_methods[] = {
	PHP_ME(CairoXlibSurface, __construct, NULL, /**/ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(CairoXlibSurface, getDepth, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoXlibSurface, getHeight, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(CairoXlibSurface, getWidth, NULL, /**/ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

/* }}} Methods */

static zend_object_value CairoXlibSurface_object_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	retval = CairoSurface_object_new(ce TSRMLS_CC);
	retval.handlers = &CairoXlibSurface_handlers;
	return retval;
}

static void class_init_CairoXlibSurface(void)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "CairoXlibSurface", CairoXlibSurface_methods);
	CairoXlibSurface_ce_ptr = zend_register_internal_class_ex(&ce, CairoSurface_ce_ptr, "CairoSurface" TSRMLS_CC);
	CairoXlibSurface_ce_ptr->create_object = CairoXlibSurface_object_new;
	memcpy(&CairoXlibSurface_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

}

/* }}} Class CairoXlibSurface */

/* {{{ Helper Functions */
zend_class_entry * 
get_CairoSurface_ce_ptr(cairo_surface_t *surface)
{
	zend_class_entry *type;
	if(surface == NULL)
		return;
	
	switch(cairo_surface_get_type(surface)) {
		case CAIRO_SURFACE_TYPE_IMAGE:
			type = CairoImageSurface_ce_ptr;
			break;
		case CAIRO_SURFACE_TYPE_PDF:
			type = CairoPDFSurface_ce_ptr;
			break;
		case CAIRO_SURFACE_TYPE_PS:
			type = CairoPSSurface_ce_ptr;
			break;
		case CAIRO_SURFACE_TYPE_SVG:
			type = CairoSVGSurface_ce_ptr;
			break;
		case CAIRO_SURFACE_TYPE_WIN32:
			type = CairoWin32Surface_ce_ptr;
			break;
		case CAIRO_SURFACE_TYPE_XLIB:
			type = CairoXlibSurface_ce_ptr;
			break;
		case CAIRO_SURFACE_TYPE_QUARTZ:
			type = CairoQuartzSurface_ce_ptr;
			break;
		default:
			php_error(E_WARNING,"Unsupported Surface Type");
			return NULL;
	}
	return type;
}

/* }}} Helper Function*/


