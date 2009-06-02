--TEST--
CairoMatrix->invert method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$matrix = new CairoMatrix();
var_dump($matrix);

$matrix->invert();

?>
--EXPECTF--
object(CairoMatrix)#%d (0) {
}