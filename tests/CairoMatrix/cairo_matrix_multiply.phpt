--TEST--
cairo_matrix_multiply function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$matrix = cairo_matrix_init();
var_dump($matrix);

$matrix1 = cairo_matrix_init_translate(0.1, 0.1);
$matrix2 = cairo_matrix_init_rotate(0.1);
$matrix = cairo_matrix_multiply($matrix1, $matrix2);
var_dump($matrix);
?>
--EXPECTF--
object(CairoMatrix)#%d (0) {
}
object(CairoMatrix)#%d (0) {
}
