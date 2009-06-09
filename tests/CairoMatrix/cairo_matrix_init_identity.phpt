--TEST--
cairo_matrix_init_identity function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$matrix = cairo_matrix_init_identity();
var_dump($matrix);

// check number of args - should accept none
cairo_matrix_init_identity('foo');
?>
--EXPECTF--
object(CairoMatrix)#%d (0) {
}

Warning: cairo_matrix_init_identity() expects exactly 0 parameters, 1 given in %s on line %d