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
?>
--EXPECTF--
object(CairoMatrix)#%d (0) {
}