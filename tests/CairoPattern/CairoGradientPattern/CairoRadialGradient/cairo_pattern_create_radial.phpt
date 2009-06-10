--TEST--
cairo_pattern_create_radial function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$pattern = cairo_pattern_create_radial(0.5, 0.5, 0.25, 0.5, 0.5, 0.5);
var_dump($pattern);

// requires 6 args
cairo_pattern_create_radial();
cairo_pattern_create_radial(1);
cairo_pattern_create_radial(1, 1);
cairo_pattern_create_radial(1, 1, 1);
cairo_pattern_create_radial(1, 1, 1, 1);
cairo_pattern_create_radial(1, 1, 1, 1, 1);
cairo_pattern_create_radial(1, 1, 1, 1, 1, 1, 1);

// arg types are all double
cairo_pattern_create_radial(array(), 1, 1, 1, 1, 1);
cairo_pattern_create_radial(1, array(), 1, 1, 1, 1);
cairo_pattern_create_radial(1, 1, array(), 1, 1, 1);
cairo_pattern_create_radial(1, 1, 1, array(), 1, 1);
cairo_pattern_create_radial(1, 1, 1, 1, array(), 1);
cairo_pattern_create_radial(1, 1, 1, 1, 1, array());
?>
--EXPECTF--
object(CairoRadialGradient)#%d (0) {
}

Warning: cairo_pattern_create_radial() expects exactly 6 parameters, 0 given in %s on line %d

Warning: cairo_pattern_create_radial() expects exactly 6 parameters, 1 given in %s on line %d

Warning: cairo_pattern_create_radial() expects exactly 6 parameters, 2 given in %s on line %d

Warning: cairo_pattern_create_radial() expects exactly 6 parameters, 3 given in %s on line %d

Warning: cairo_pattern_create_radial() expects exactly 6 parameters, 4 given in %s on line %d

Warning: cairo_pattern_create_radial() expects exactly 6 parameters, 5 given in %s on line %d

Warning: cairo_pattern_create_radial() expects exactly 6 parameters, 7 given in %s on line %d

Warning: cairo_pattern_create_radial() expects parameter 1 to be double, array given in %s on line %d

Warning: cairo_pattern_create_radial() expects parameter 2 to be double, array given in %s on line %d

Warning: cairo_pattern_create_radial() expects parameter 3 to be double, array given in %s on line %d

Warning: cairo_pattern_create_radial() expects parameter 4 to be double, array given in %s on line %d

Warning: cairo_pattern_create_radial() expects parameter 5 to be double, array given in %s on line %d

Warning: cairo_pattern_create_radial() expects parameter 6 to be double, array given in %s on line %d