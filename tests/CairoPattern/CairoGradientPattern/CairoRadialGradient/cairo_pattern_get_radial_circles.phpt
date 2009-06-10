--TEST--
cairo_pattern_get_radial_circles function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$pattern = cairo_pattern_create_radial(0.5, 0.5, 0.25, 0.5, 0.5, 0.5);
var_dump($pattern);

var_dump(cairo_pattern_get_radial_circles($pattern));

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// requires 1 arg
cairo_pattern_get_radial_circles();
cairo_pattern_get_radial_circles($pattern, 1);

// arg type is CairoPattern
cairo_pattern_get_radial_circles(1);
?>
--EXPECTF--
object(CairoRadialGradient)#%d (0) {
}
array(6) {
  ["x0"]=>
  float(0.5)
  ["y0"]=>
  float(0.5)
  ["r0"]=>
  float(0.25)
  ["x1"]=>
  float(0.5)
  ["y1"]=>
  float(0.5)
  ["r1"]=>
  float(0.5)
}

Warning: cairo_pattern_get_radial_circles() expects exactly 1 parameter, 0 given in %s on line %d

Warning: cairo_pattern_get_radial_circles() expects exactly 1 parameter, 2 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_pattern_get_radial_circles() must be an instance of CairoRadialGradient, integer given

Warning: cairo_pattern_get_radial_circles() expects parameter 1 to be CairoRadialGradient, integer given in %s on line %d