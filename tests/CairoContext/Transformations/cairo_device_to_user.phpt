--TEST--
cairo_device_to_user function
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

var_dump(cairo_device_to_user($context, 5, 5));

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// check number of args - should accept 3
cairo_device_to_user();
cairo_device_to_user($context);
cairo_device_to_user($context, 1);
cairo_device_to_user($context, 1, 1, 1);

// check arg types, should be context object, double double
cairo_device_to_user(1, 1, 1);
cairo_device_to_user($context, array(), 1);
cairo_device_to_user($context, 1, array());
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

Warning: cairo_device_to_user() expects exactly 3 parameters, 0 given in %s on line %d

Warning: cairo_device_to_user() expects exactly 3 parameters, 1 given in %s on line %d

Warning: cairo_device_to_user() expects exactly 3 parameters, 2 given in %s on line %d

Warning: cairo_device_to_user() expects exactly 3 parameters, 4 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_device_to_user() must be an instance of CairoContext, integer given

Warning: cairo_device_to_user() expects parameter 1 to be CairoContext, integer given in %s on line %d

Warning: cairo_device_to_user() expects parameter 2 to be double, array given in %s on line %d

Warning: cairo_device_to_user() expects parameter 3 to be double, array given in %s on line %d