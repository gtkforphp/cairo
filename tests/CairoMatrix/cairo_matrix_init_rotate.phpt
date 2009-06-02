--TEST--
cairo_matrix_init_rotate function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$matrix = cairo_matrix_init_rotate(0.1);
var_dump($matrix);
?>
--EXPECTF--
object(CairoMatrix)#%d (0) {
}