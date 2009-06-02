--TEST--
cairo_matrix_init_identity function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$matrix = cairo_matrix_init_identity();
var_dump($matrix);
?>
--EXPECTF--
object(CairoMatrix)#%d (0) {
}