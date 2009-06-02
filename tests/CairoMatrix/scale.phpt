--TEST--
CairoMatrix->scale method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$matrix = new CairoMatrix();
var_dump($matrix);

$matrix->scale(0.1, 0.1);
?>
--EXPECTF--
object(CairoMatrix)#%d (0) {
}