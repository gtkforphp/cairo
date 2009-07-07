--TEST--
cairo_set_source function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 50, 50);
var_dump($surface);

$context = cairo_create($surface);
var_dump($context);

$pattern = cairo_pattern_create_rgb(0.3, 0.3, 0.3);
var_dump($pattern);

cairo_set_source($context, $pattern);
var_dump(cairo_pattern_get_rgba(cairo_get_source($context)));

$pattern = cairo_pattern_create_rgb(0.5, 0.5, 0.5);
var_dump($pattern);

cairo_set_source($context, $pattern);

var_dump(cairo_pattern_get_rgba(cairo_get_source($context)));

function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

/* wrong params */
cairo_set_source();
cairo_set_source($context);
cairo_set_source($context, $pattern, 1);

/* wrong types */
cairo_set_source(1, $pattern);
cairo_set_source($context, 1);

// DO NOT REMOVE: workaround for GC-related bug in 5.3
die;
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
object(CairoSolidPattern)#%d (0) {
}
array(4) {
  ["red"]=>
  float(0.3)
  ["green"]=>
  float(0.3)
  ["blue"]=>
  float(0.3)
  ["alpha"]=>
  float(1)
}
object(CairoSolidPattern)#%d (0) {
}
array(4) {
  ["red"]=>
  float(0.5)
  ["green"]=>
  float(0.5)
  ["blue"]=>
  float(0.5)
  ["alpha"]=>
  float(1)
}

Warning: cairo_set_source() expects exactly 2 parameters, 0 given in %s on line %d

Warning: cairo_set_source() expects exactly 2 parameters, 1 given in %s on line %d

Warning: cairo_set_source() expects exactly 2 parameters, 3 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_set_source() must be an instance of CairoContext, integer given

Warning: cairo_set_source() expects parameter 1 to be CairoContext, integer given in %s on line %d
CAUGHT ERROR: Argument 2 passed to cairo_set_source() must be an instance of CairoPattern, integer given

Warning: cairo_set_source() expects parameter 2 to be CairoPattern, integer given in %s on line %d
