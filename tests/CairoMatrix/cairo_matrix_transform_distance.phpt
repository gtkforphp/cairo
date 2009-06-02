--TEST--
cairo_matrix_transform_distance function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$matrix = cairo_matrix_init();
var_dump($matrix);

var_dump(cairo_matrix_transform_distance($matrix, 1.0, 1.0));
?>
--EXPECTF--
object(CairoMatrix)#%d (0) {
}
array(2) {
  ["x"]=>
  float(%f)
  ["y"]=>
  float(%f)
}