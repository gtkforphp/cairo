--TEST--
cairo_pattern_create_linear function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$pattern = cairo_pattern_create_linear(1,2,3,4);
var_dump($pattern);

// requires 4 args
cairo_pattern_create_linear();
cairo_pattern_create_linear(1);
cairo_pattern_create_linear(1, 1);
cairo_pattern_create_linear(1, 1, 1);
cairo_pattern_create_linear(1, 1, 1, 1, 1);

// arg types are all double
cairo_pattern_create_linear(array(), 1, 1, 1);
cairo_pattern_create_linear(1, array(), 1, 1);
cairo_pattern_create_linear(1, 1, array(), 1);
cairo_pattern_create_linear(1, 1, 1, array());
?>
--EXPECTF--
object(CairoLinearGradient)#%d (0) {
}

Warning: cairo_pattern_create_linear() expects exactly 4 parameters, 0 given in %s on line %d

Warning: cairo_pattern_create_linear() expects exactly 4 parameters, 1 given in %s on line %d

Warning: cairo_pattern_create_linear() expects exactly 4 parameters, 2 given in %s on line %d

Warning: cairo_pattern_create_linear() expects exactly 4 parameters, 3 given in %s on line %d

Warning: cairo_pattern_create_linear() expects exactly 4 parameters, 5 given in %s on line %d

Warning: cairo_pattern_create_linear() expects parameter 1 to be double, array given in %s on line %d

Warning: cairo_pattern_create_linear() expects parameter 2 to be double, array given in %s on line %d

Warning: cairo_pattern_create_linear() expects parameter 3 to be double, array given in %s on line %d

Warning: cairo_pattern_create_linear() expects parameter 4 to be double, array given in %s on line %d