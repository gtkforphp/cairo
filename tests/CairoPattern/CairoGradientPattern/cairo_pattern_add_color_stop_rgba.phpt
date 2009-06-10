--TEST--
cairo_pattern_add_color_stop_rgba function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$pattern = cairo_pattern_create_linear(1, 2, 3, 4);
var_dump($pattern);

cairo_pattern_add_color_stop_rgba($pattern, 0.2, 0.8, 0.6, 0.5, 0.2);
var_dump(cairo_pattern_get_color_stop_rgba($pattern, 0));

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// requires 6 args
cairo_pattern_add_color_stop_rgba();
cairo_pattern_add_color_stop_rgba($pattern);
cairo_pattern_add_color_stop_rgba($pattern, 1);
cairo_pattern_add_color_stop_rgba($pattern, 1, 1);
cairo_pattern_add_color_stop_rgba($pattern, 1, 1, 1);
cairo_pattern_add_color_stop_rgba($pattern, 1, 1, 1, 1);
cairo_pattern_add_color_stop_rgba($pattern, 1, 1, 1, 1, 1, 1);

// arg types are CairoPattern, double, double, double, double, double
cairo_pattern_add_color_stop_rgba(1, 1, 1, 1, 1, 1);
cairo_pattern_add_color_stop_rgba($pattern, array(), 1, 1, 1, 1);
cairo_pattern_add_color_stop_rgba($pattern, 1, array(), 1, 1, 1);
cairo_pattern_add_color_stop_rgba($pattern, 1, 1, array(), 1, 1);
cairo_pattern_add_color_stop_rgba($pattern, 1, 1, 1, array(), 1);
cairo_pattern_add_color_stop_rgba($pattern, 1, 1, 1, 1, array());
?>
--EXPECTF--
object(CairoLinearGradient)#%d (0) {
}
array(4) {
  ["red"]=>
  float(0.8%A)
  ["green"]=>
  float(0.6%A)
  ["blue"]=>
  float(0.5%A)
  ["alpha"]=>
  float(0.2%A)
}

Warning: cairo_pattern_add_color_stop_rgba() expects exactly 6 parameters, 0 given in %s on line %d

Warning: cairo_pattern_add_color_stop_rgba() expects exactly 6 parameters, 1 given in %s on line %d

Warning: cairo_pattern_add_color_stop_rgba() expects exactly 6 parameters, 2 given in %s on line %d

Warning: cairo_pattern_add_color_stop_rgba() expects exactly 6 parameters, 3 given in %s on line %d

Warning: cairo_pattern_add_color_stop_rgba() expects exactly 6 parameters, 4 given in %s on line %d

Warning: cairo_pattern_add_color_stop_rgba() expects exactly 6 parameters, 5 given in %s on line %d

Warning: cairo_pattern_add_color_stop_rgba() expects exactly 6 parameters, 7 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_pattern_add_color_stop_rgba() must be an instance of CairoGradientPattern, integer given

Warning: cairo_pattern_add_color_stop_rgba() expects parameter 1 to be CairoGradientPattern, integer given in %s on line %d

Warning: cairo_pattern_add_color_stop_rgba() expects parameter 2 to be double, array given in %s on line %d

Warning: cairo_pattern_add_color_stop_rgba() expects parameter 3 to be double, array given in %s on line %d

Warning: cairo_pattern_add_color_stop_rgba() expects parameter 4 to be double, array given in %s on line %d

Warning: cairo_pattern_add_color_stop_rgba() expects parameter 5 to be double, array given in %s on line %d

Warning: cairo_pattern_add_color_stop_rgba() expects parameter 6 to be double, array given in %s on line %d