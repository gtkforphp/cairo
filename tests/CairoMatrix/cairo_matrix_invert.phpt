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
?>
--EXPECTF--
object(CairoMatrix)#%d (0) {
}