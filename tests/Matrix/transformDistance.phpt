--TEST--
Cairo\Matrix->transformDistance method
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

var_dump($matrix->transformDistance(1.0, 1.0));

/* Wrong number args */
try {
    $matrix->transformDistance();
    trigger_error('We should bomb here');
} catch (Exception $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args 2 */
try {
    $matrix->transformDistance(1);
    trigger_error('We should bomb here');
} catch (Exception $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args 3 */
try {
    $matrix->transformDistance(1, 1, 1);
    trigger_error('We should bomb here');
} catch (Exception $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 1 */
try {
    $matrix->transformDistance(array(), 1);
    trigger_error('We should bomb here');
} catch (Exception $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 2 */
try {
    $matrix->transformDistance(1, array());
    trigger_error('We should bomb here');
} catch (Exception $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Matrix)#%d (0) {
}
array(2) {
  ["x"]=>
  float(%f)
  ["y"]=>
  float(%f)
}
Cairo\Matrix::transformDistance() expects exactly 2 parameters, 0 given
Cairo\Matrix::transformDistance() expects exactly 2 parameters, 1 given
Cairo\Matrix::transformDistance() expects exactly 2 parameters, 3 given
Cairo\Matrix::transformDistance() expects parameter 1 to be double, array given
Cairo\Matrix::transformDistance() expects parameter 2 to be double, array given