--TEST--
cairo_pattern_get_matrix function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$pattern = cairo_pattern_create_rgb(0.8, 0.6, 0.5);
var_dump($pattern);

var_dump($orig_matrix = cairo_pattern_get_matrix($pattern));

$matrix = cairo_matrix_init(5, 5);
var_dump($matrix);
var_dump($orig_matrix === $matrix);

cairo_pattern_set_matrix($pattern, $matrix);
var_dump($matrix1 = cairo_pattern_get_matrix($pattern));
var_dump($matrix1 === $matrix);
var_dump($orig_matrix === $matrix);

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// requires exactly 1 arg
cairo_pattern_get_matrix();
cairo_pattern_get_matrix($pattern, 1);

// arg types is CairoPattern
cairo_pattern_get_matrix(1);

die; // DO NOT REMOVE THIS - fixes issue in 5.3 with GC giving bogus memleak reports
?>
--EXPECTF--
object(CairoSolidPattern)#%d (0) {
}
object(CairoMatrix)#%d (0) {
}
object(CairoMatrix)#%d (0) {
}
bool(false)
object(CairoMatrix)#%d (0) {
}
bool(true)
bool(false)

Warning: cairo_pattern_get_matrix() expects exactly 1 parameter, 0 given in %s on line %d

Warning: cairo_pattern_get_matrix() expects exactly 1 parameter, 2 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_pattern_get_matrix() must be an instance of CairoPattern, integer given

Warning: cairo_pattern_get_matrix() expects parameter 1 to be CairoPattern, integer given in %s on line %d
