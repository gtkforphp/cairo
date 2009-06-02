--TEST--
CairoMatrix::initIdentity method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$matrix = CairoMatrix::initIdentity();
var_dump($matrix);
?>
--EXPECTF--
object(CairoMatrix)#%d (0) {
}