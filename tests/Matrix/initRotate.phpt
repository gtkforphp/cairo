--TEST--
Cairo\Matrix::initRotate function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
use Cairo\Matrix;
use Cairo\Exception;

$matrix = Matrix::initRotate(0.1);
var_dump($matrix);

/* Wrong number args */
try {
    Matrix::initRotate();
    trigger_error('We should bomb here');
} catch (Exception $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args 2 */
try {
    Matrix::initRotate(1, 1);
    trigger_error('We should bomb here');
} catch (Exception $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type */
try {
    Matrix::initRotate(array());
    trigger_error('We should bomb here');
} catch (Exception $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Matrix)#%d (0) {
}
Cairo\Matrix::initRotate() expects exactly 1 parameter, 0 given
Cairo\Matrix::initRotate() expects exactly 1 parameter, 2 given
Cairo\Matrix::initRotate() expects parameter 1 to be double, array given