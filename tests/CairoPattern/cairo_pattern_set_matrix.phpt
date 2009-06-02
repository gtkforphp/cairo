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

cairo_pattern_set_matrix();
?>
--EXPECTF--
object(CairoSolidPattern)#%d (0) {
}
object(CairoMatrix)#%d (0) {
}

Warning: cairo_pattern_set_matrix() expects exactly 2 parameters, 0 given in %s on line %d