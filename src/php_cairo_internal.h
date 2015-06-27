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

extern zend_class_entry *ce_cairo_exception;

/* macros to make zpp to throw exceptions instead of errors */
#define PHP_CAIRO_EXCEPTIONS() \
		zend_error_handling error_handling; \
		zend_replace_error_handling(EH_THROW, ce_cairo_exception, &error_handling);

#define PHP_CAIRO_RESTORE() \
		zend_restore_error_handling(&error_handling)

/* Classes to register */
PHP_MINIT_FUNCTION(cairo_exception);
PHP_MINIT_FUNCTION(cairo_enum);
PHP_MINIT_FUNCTION(cairo_matrix);

#endif /* PHP_CAIRO_INTERNAL_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
