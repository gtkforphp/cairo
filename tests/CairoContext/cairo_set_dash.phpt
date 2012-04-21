--TEST--
cairo_set_dash function
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

cairo_set_dash($context, array(1,2,3));
var_dump(cairo_get_dash($context));

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// check number of args - should accept 2 or 3
cairo_set_dash();
cairo_set_dash($context);
cairo_set_dash($context, array(), 3, 3);

// check arg types, should be context object, array of double, double
cairo_set_dash(1, array(1, 2,3), 3);
cairo_set_dash($context, 1, 3);
cairo_set_dash($context, array(1, 2,3), array());
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
array(2) {
  ["dashes"]=>
  array(3) {
    [0]=>
    float(1)
    [1]=>
    float(2)
    [2]=>
    float(3)
  }
  ["offset"]=>
  float(0)
}

Warning: cairo_set_dash() expects at least 2 parameters, 0 given in %s on line %d

Warning: cairo_set_dash() expects at least 2 parameters, 1 given in %s on line %d

Warning: cairo_set_dash() expects at most 3 parameters, 4 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_set_dash() must be an instance of CairoContext, integer given

Warning: cairo_set_dash() expects parameter 1 to be CairoContext, integer given in %s on line %d
CAUGHT ERROR: Argument 2 passed to cairo_set_dash() must be %s array, integer given

Warning: cairo_set_dash() expects parameter 2 to be array, integer given in %s on line %d

Warning: cairo_set_dash() expects parameter 3 to be double, array given in %s on line %d
