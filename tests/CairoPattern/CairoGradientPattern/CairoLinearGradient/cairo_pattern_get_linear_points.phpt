--TEST--
cairo_pattern_get_linear_points function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$pattern = cairo_pattern_create_linear(1,2,3,4);
var_dump($pattern);

var_dump(cairo_pattern_get_linear_points($pattern));

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// requires 1 arg
cairo_pattern_get_linear_points();
cairo_pattern_get_linear_points($pattern, 1);

// arg type is CairoPattern
cairo_pattern_get_linear_points(1);
?>
--EXPECTF--
object(CairoLinearGradient)#%d (0) {
}
array(4) {
  ["x0"]=>
  float(1)
  ["y0"]=>
  float(2)
  ["x1"]=>
  float(3)
  ["y1"]=>
  float(4)
}

Warning: cairo_pattern_get_linear_points() expects exactly 1 parameter, 0 given in %s on line %d

Warning: cairo_pattern_get_linear_points() expects exactly 1 parameter, 2 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_pattern_get_linear_points() must be an instance of CairoLinearGradient, integer given

Warning: cairo_pattern_get_linear_points() expects parameter 1 to be CairoLinearGradient, integer given in %s on line %d