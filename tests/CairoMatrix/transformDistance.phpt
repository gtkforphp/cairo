--TEST--
CairoMatrix->transformDistance method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$matrix = new CairoMatrix();
var_dump($matrix);

var_dump($matrix->transformDistance(1.0, 1.0));
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