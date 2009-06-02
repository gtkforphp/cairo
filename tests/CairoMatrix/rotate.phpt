--TEST--
CairoMatrix->rotate method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$matrix = new CairoMatrix();
var_dump($matrix);

$matrix->rotate(0.1);
?>
--EXPECTF--
object(CairoMatrix)#%d (0) {
}