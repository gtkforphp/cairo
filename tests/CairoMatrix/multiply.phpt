--TEST--
CairoMatrix->multiply method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$matrix = new CairoMatrix();
var_dump($matrix);

$matrix1 = new CairoMatrix(0.1, 0.1);
$matrix2 = new CairoMatrix(0.1);

$matrix->multiply($matrix1, $matrix2);
?>
--EXPECTF--
object(CairoMatrix)#%d (0) {
}