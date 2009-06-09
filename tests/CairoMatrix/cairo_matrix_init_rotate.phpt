--TEST--
cairo_matrix_init_rotate function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$matrix = cairo_matrix_init_rotate(0.1);
var_dump($matrix);

// check number of args - should accept ONLY 1
cairo_matrix_init_rotate();
cairo_matrix_init_rotate(1, 1);

// check arg types, should be scalar (casts to float)
cairo_matrix_init_rotate(array());
?>
--EXPECTF--
object(CairoMatrix)#%d (0) {
}

Warning: cairo_matrix_init_rotate() expects exactly 1 parameter, 0 given in %s on line %d

Warning: cairo_matrix_init_rotate() expects exactly 1 parameter, 2 given in %s on line %d

Warning: cairo_matrix_init_rotate() expects parameter 1 to be double, array given in %s on line %d