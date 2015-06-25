--TEST--
Cairo\Matrix->rotate method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
use Cairo\Matrix;
use Cairo\Exception;

$matrix = new Matrix();
var_dump($matrix);

$matrix->rotate(0.1);

/* Wrong number args */
try {
    $matrix->rotate();
    trigger_error('We should bomb here');
} catch (Exception $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args 2 */
try {
    $matrix->rotate(1, 1);
    trigger_error('We should bomb here');
} catch (Exception $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type */
try {
    $matrix->rotate(array());
    trigger_error('We should bomb here');
} catch (Exception $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Matrix)#%d (0) {
}
Cairo\Matrix::rotate() expects exactly 1 parameter, 0 given
Cairo\Matrix::rotate() expects exactly 1 parameter, 2 given
Cairo\Matrix::rotate() expects parameter 1 to be double, array given