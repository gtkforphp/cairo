--TEST--
cairo_matrix_init_translate function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$matrix = cairo_matrix_init_translate(0.1, 0.1);
var_dump($matrix);
?>
--EXPECTF--
object(CairoMatrix)#%d (0) {
}