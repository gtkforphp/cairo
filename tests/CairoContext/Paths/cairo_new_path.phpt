--TEST--
cairo_new_path() function
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

cairo_line_to($context, 5, 5);

var_dump(cairo_get_current_point($context));

cairo_new_path($context);

var_dump(cairo_get_current_point($context));

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// check number of args - should accept 1
cairo_new_path();
cairo_new_path($context, 1);

// check arg types, should be context object
cairo_new_path(1);
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
array(2) {
  [0]=>
  float(5)
  [1]=>
  float(5)
}
array(2) {
  [0]=>
  float(0)
  [1]=>
  float(0)
}

Warning: cairo_new_path() expects exactly 1 parameter, 0 given in %s on line %d

Warning: cairo_new_path() expects exactly 1 parameter, 2 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_new_path() must be an instance of CairoContext, integer given

Warning: cairo_new_path() expects parameter 1 to be CairoContext, integer given in %s on line %d