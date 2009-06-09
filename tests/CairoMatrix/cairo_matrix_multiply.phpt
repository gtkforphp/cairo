--TEST--
cairo_matrix_multiply function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$matrix1 = cairo_matrix_init_translate(0.1, 0.1);
$matrix2 = cairo_matrix_init_rotate(0.1);

$matrix = cairo_matrix_multiply($matrix1, $matrix2);
var_dump($matrix);

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// check number of args - should accept ONLY 2
cairo_matrix_multiply();
cairo_matrix_multiply($matrix1);
cairo_matrix_multiply($matrix1, $matrix2, 1);

// check arg types, should be matrix object, matrix object
cairo_matrix_multiply($matrix1, 1);
cairo_matrix_multiply(1, $matrix2);
?>
--EXPECTF--
object(CairoMatrix)#%d (0) {
}

Warning: cairo_matrix_multiply() expects exactly 2 parameters, 0 given in %s on line %d

Warning: cairo_matrix_multiply() expects exactly 2 parameters, 1 given in %s on line %d

Warning: cairo_matrix_multiply() expects exactly 2 parameters, 3 given in %s on line %d
CAUGHT ERROR: Argument 2 passed to cairo_matrix_multiply() must be an instance of CairoMatrix, integer given

Warning: cairo_matrix_multiply() expects parameter 2 to be CairoMatrix, integer given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_matrix_multiply() must be an instance of CairoMatrix, integer given

Warning: cairo_matrix_multiply() expects parameter 1 to be CairoMatrix, integer given in %s on line %d