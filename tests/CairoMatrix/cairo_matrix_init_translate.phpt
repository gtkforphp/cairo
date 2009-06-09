--TEST--
cairo_matrix_init_translate function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$matrix = cairo_matrix_init_translate(0.1, 0.1);
var_dump($matrix);

// check number of args - should accept ONLY 2
cairo_matrix_init_translate();
cairo_matrix_init_translate(1);
cairo_matrix_init_translate(1, 1, 1);

// check arg types, should be scalar (casts to float), scalar (casts to float)
cairo_matrix_init_translate(array(), 1);
cairo_matrix_init_translate(1, array());
?>
--EXPECTF--
object(CairoMatrix)#%d (0) {
}

Warning: cairo_matrix_init_translate() expects exactly 2 parameters, 0 given in %s on line %d

Warning: cairo_matrix_init_translate() expects exactly 2 parameters, 1 given in %s on line %d

Warning: cairo_matrix_init_translate() expects exactly 2 parameters, 3 given in %s on line %d

Warning: cairo_matrix_init_translate() expects parameter 1 to be double, array given in %s on line %d

Warning: cairo_matrix_init_translate() expects parameter 2 to be double, array given in %s on line %d