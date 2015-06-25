--TEST--
Cairo\Matrix::initIdentity method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
use Cairo\Matrix;
use Cairo\Exception;

$matrix = Matrix::initIdentity();
var_dump($matrix);

/* Wrong number args */
try {
    Matrix::initIdentity('foo');
    trigger_error('We should bomb here');
} catch (Exception $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Matrix)#%d (0) {
}
Cairo\Matrix::initIdentity() expects exactly 0 parameters, 1 given