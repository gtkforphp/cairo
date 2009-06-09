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

/* Wrong number args */
try {
    CairoMatrix::initIdentity('foo');
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoMatrix)#%d (0) {
}
CairoMatrix::initIdentity() expects exactly 0 parameters, 1 given