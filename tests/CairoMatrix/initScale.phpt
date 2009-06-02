--TEST--
CairoMatrix::initScale() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$matrix = CairoMatrix::initScale(0.1, 0.1);
var_dump($matrix);
?>
--EXPECTF--
object(CairoMatrix)#%d (0) {
}