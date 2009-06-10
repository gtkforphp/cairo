--TEST--
cairo_pattern_set_matrix function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$pattern = cairo_pattern_create_rgb(0.8, 0.6, 0.5);
var_dump($pattern);

$matrix = cairo_matrix_init();
var_dump($matrix);

cairo_pattern_set_matrix($pattern, $matrix);
$matrix1 = cairo_pattern_get_matrix($pattern);
var_dump($matrix === $matrix1);

$matrix2 = cairo_matrix_init(5, 5);
cairo_pattern_set_matrix($pattern, $matrix2);
$matrix1 = cairo_pattern_get_matrix($pattern);
var_dump($matrix2 === $matrix1);

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// requires exactly 2 args
cairo_pattern_set_matrix();
cairo_pattern_set_matrix($pattern);
cairo_pattern_set_matrix($pattern, $matrix, 1);

// arg types are CairoSurface and CairoMatrix
cairo_pattern_set_matrix(1, $matrix);
cairo_pattern_set_matrix($pattern, 1);

die; // DO NOT REMOVE THIS - fixes issue in 5.3 with GC giving bogus memleak reports
?>
--EXPECTF--
object(CairoSolidPattern)#%d (0) {
}
object(CairoMatrix)#%d (0) {
}
bool(true)
bool(true)

Warning: cairo_pattern_set_matrix() expects exactly 2 parameters, 0 given in %s on line %d

Warning: cairo_pattern_set_matrix() expects exactly 2 parameters, 1 given in %s on line %d

Warning: cairo_pattern_set_matrix() expects exactly 2 parameters, 3 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_pattern_set_matrix() must be an instance of CairoPattern, integer given

Warning: cairo_pattern_set_matrix() expects parameter 1 to be CairoPattern, integer given in %s on line %d
CAUGHT ERROR: Argument 2 passed to cairo_pattern_set_matrix() must be an instance of CairoMatrix, integer given

Warning: cairo_pattern_set_matrix() expects parameter 2 to be CairoMatrix, integer given in %s on line %d