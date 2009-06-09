--TEST--
cairo_matrix_translate function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$matrix = cairo_matrix_init();
var_dump($matrix);

cairo_matrix_translate($matrix, 0.1, 0.1);

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// check number of args - should accept ONLY 3
cairo_matrix_translate();
cairo_matrix_translate($matrix);
cairo_matrix_translate($matrix, 1);
cairo_matrix_translate($matrix, 1, 1, 1);

// check arg types, should be matrix object, scalar (casts to float), scalar (casts to float)
cairo_matrix_translate(1, 1, 1);
cairo_matrix_translate($matrix, array(), 1);
cairo_matrix_translate($matrix, 1, array());
?>
--EXPECTF--
object(CairoMatrix)#%d (0) {
}

Warning: cairo_matrix_translate() expects exactly 3 parameters, 0 given in %s on line %d

Warning: cairo_matrix_translate() expects exactly 3 parameters, 1 given in %s on line %d

Warning: cairo_matrix_translate() expects exactly 3 parameters, 2 given in %s on line %d

Warning: cairo_matrix_translate() expects exactly 3 parameters, 4 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_matrix_translate() must be an instance of CairoMatrix, integer given

Warning: cairo_matrix_translate() expects parameter 1 to be CairoMatrix, integer given in %s on line %d

Warning: cairo_matrix_translate() expects parameter 2 to be double, array given in %s on line %d

Warning: cairo_matrix_translate() expects parameter 3 to be double, array given in %s on line %d