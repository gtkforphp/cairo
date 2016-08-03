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

#ifndef PHP_CAIRO_INTERNAL_H
#define PHP_CAIRO_INTERNAL_H

#include <php.h>
#include <cairo.h>

extern zend_class_entry *ce_cairo_exception;
extern zend_class_entry *ce_cairo_status;
extern zend_class_entry *ce_cairo_matrix;

extern zend_class_entry *ce_cairo_surface;
extern zend_class_entry *ce_cairo_content;
extern zend_class_entry *ce_cairo_surfacetype;
extern zend_class_entry *ce_cairo_imagesurface;
extern zend_class_entry *ce_cairo_svgsurface;
extern zend_class_entry *ce_cairo_pdfsurface;
extern zend_class_entry *ce_cairo_pssurface;
extern zend_class_entry *ce_cairo_recordingsurface;
extern zend_class_entry *ce_cairo_subsurface;

extern zend_class_entry *ce_cairo_fontoptions;
extern zend_class_entry *ce_cairo_subpixelorder;
extern zend_class_entry *ce_cairo_hintstyle;
extern zend_class_entry *ce_cairo_hintmetrics;

extern zend_class_entry* php_cairo_get_pattern_ce(cairo_pattern_t *pattern);
extern zend_class_entry* php_cairo_get_surface_ce(cairo_surface_t *surface);
extern zend_class_entry* php_cairo_get_fontoptions_ce();

cairo_matrix_t *cairo_matrix_object_get_matrix(zval *zv);

extern cairo_status_t php_cairo_write_func(void *closure, const unsigned char *data, unsigned int length);

/* Classes to register */
PHP_MINIT_FUNCTION(cairo_pattern);
PHP_MINIT_FUNCTION(cairo_region);

PHP_MINIT_FUNCTION(cairo_matrix);
PHP_MINIT_FUNCTION(cairo_exception);
PHP_MINIT_FUNCTION(cairo_rectangle);
PHP_MINIT_FUNCTION(cairo_surface);

#endif /* PHP_CAIRO_INTERNAL_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
