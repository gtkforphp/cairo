--TEST--
cairo_pattern_add_color_stop_rgb function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$pattern = cairo_pattern_create_linear(1, 2, 3, 4);
var_dump($pattern);

cairo_pattern_add_color_stop_rgb($pattern, 0.2, 0.8, 0.6, 0.5);
var_dump(cairo_pattern_get_color_stop_rgba($pattern, 0));

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// requires 5 args
cairo_pattern_add_color_stop_rgb();
cairo_pattern_add_color_stop_rgb($pattern);
cairo_pattern_add_color_stop_rgb($pattern, 1);
cairo_pattern_add_color_stop_rgb($pattern, 1, 1);
cairo_pattern_add_color_stop_rgb($pattern, 1, 1, 1);
cairo_pattern_add_color_stop_rgb($pattern, 1, 1, 1, 1, 1);

// arg types are CairoPattern, double, double, double, double
cairo_pattern_add_color_stop_rgb(1, 1, 1, 1, 1);
cairo_pattern_add_color_stop_rgb($pattern, array(), 1, 1, 1);
cairo_pattern_add_color_stop_rgb($pattern, 1, array(), 1, 1);
cairo_pattern_add_color_stop_rgb($pattern, 1, 1, array(), 1);
cairo_pattern_add_color_stop_rgb($pattern, 1, 1, 1, array());
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
  float(1)
}

Warning: cairo_pattern_add_color_stop_rgb() expects exactly 5 parameters, 0 given in %s on line %d

Warning: cairo_pattern_add_color_stop_rgb() expects exactly 5 parameters, 1 given in %s on line %d

Warning: cairo_pattern_add_color_stop_rgb() expects exactly 5 parameters, 2 given in %s on line %d

Warning: cairo_pattern_add_color_stop_rgb() expects exactly 5 parameters, 3 given in %s on line %d

Warning: cairo_pattern_add_color_stop_rgb() expects exactly 5 parameters, 4 given in %s on line %d

Warning: cairo_pattern_add_color_stop_rgb() expects exactly 5 parameters, 6 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_pattern_add_color_stop_rgb() must be an instance of CairoGradientPattern, integer given

Warning: cairo_pattern_add_color_stop_rgb() expects parameter 1 to be CairoGradientPattern, integer given in %s on line %d

Warning: cairo_pattern_add_color_stop_rgb() expects parameter 2 to be double, array given in %s on line %d

Warning: cairo_pattern_add_color_stop_rgb() expects parameter 3 to be double, array given in %s on line %d

Warning: cairo_pattern_add_color_stop_rgb() expects parameter 4 to be double, array given in %s on line %d

Warning: cairo_pattern_add_color_stop_rgb() expects parameter 5 to be double, array given in %s on line %d