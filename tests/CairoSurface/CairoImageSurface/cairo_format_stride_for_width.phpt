--TEST--
cairo_format_stride_for_width() function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!function_exists('cairo_format_stride_for_width')) die('skip - cairo_format_stride_for_width not available');
?>
--FILE--
<?php
echo cairo_format_stride_for_width(1, 5), PHP_EOL;

/* Wrong number args */
cairo_format_stride_for_width();

/* Wrong number args 2 */
cairo_format_stride_for_width(1);

/* Wrong number args 3 */
cairo_format_stride_for_width(1, 1, 1);

/* Wrong arg type */
cairo_format_stride_for_width(array(), 1);

/* Wrong arg type */
cairo_format_stride_for_width(1, array());
?>
--EXPECTF--
20

Warning: cairo_format_stride_for_width() expects exactly 2 parameters, 0 given in %s on line %d

Warning: cairo_format_stride_for_width() expects exactly 2 parameters, 1 given in %s on line %d

Warning: cairo_format_stride_for_width() expects exactly 2 parameters, 3 given in %s on line %d

Warning: cairo_format_stride_for_width() expects parameter 1 to be long, array given in %s on line %d

Warning: cairo_format_stride_for_width() expects parameter 2 to be long, array given in %s on line %d