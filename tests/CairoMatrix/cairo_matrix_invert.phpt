--TEST--
cairo_matrix_invert function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$matrix = cairo_matrix_init();
var_dump($matrix);

cairo_matrix_invert($matrix);

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// requires exactly 1 arg
cairo_matrix_invert();
cairo_matrix_invert($matrix, 2);

// check arg types, should be matrix object
cairo_matrix_invert(1);
?>
--EXPECTF--
object(CairoMatrix)#%d (0) {
}

Warning: cairo_matrix_invert() expects exactly 1 parameter, 0 given in %s on line %d

Warning: cairo_matrix_invert() expects exactly 1 parameter, 2 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_matrix_invert() must be an instance of CairoMatrix, integer given

Warning: cairo_matrix_invert() expects parameter 1 to be CairoMatrix, integer given in %s on line %d