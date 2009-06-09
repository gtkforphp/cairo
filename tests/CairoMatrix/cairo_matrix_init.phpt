--TEST--
cairo_matrix_init function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$matrix = cairo_matrix_init();
var_dump($matrix);

// check for too many args, accepts 0-6
cairo_matrix_init(1, 1, 1, 1, 1, 1, 1);

// check arg types, should be scalar (casts to float) x6
cairo_matrix_init(array(), 1, 1, 1, 1, 1);
cairo_matrix_init(1, array(), 1, 1, 1, 1);
cairo_matrix_init(1, 1, array(), 1, 1, 1);
cairo_matrix_init(1, 1, 1, array(), 1, 1);
cairo_matrix_init(1, 1, 1, 1, array(), 1);
cairo_matrix_init(1, 1, 1, 1, 1, array());
?>
--EXPECTF--
object(CairoMatrix)#%d (0) {
}

Warning: cairo_matrix_init() expects at most 6 parameters, 7 given in %s on line %d

Warning: cairo_matrix_init() expects parameter 1 to be double, array given in %s on line %d

Warning: cairo_matrix_init() expects parameter 2 to be double, array given in %s on line %d

Warning: cairo_matrix_init() expects parameter 3 to be double, array given in %s on line %d

Warning: cairo_matrix_init() expects parameter 4 to be double, array given in %s on line %d

Warning: cairo_matrix_init() expects parameter 5 to be double, array given in %s on line %d

Warning: cairo_matrix_init() expects parameter 6 to be double, array given in %s on line %d