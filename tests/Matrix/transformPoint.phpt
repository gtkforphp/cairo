--TEST--
Cairo\Matrix->transformPoint()
--EXTENSIONS--
eos_datastructures
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
?>
--FILE--
<?php
use Cairo\Matrix;
use TypeError as Exception;

$matrix = new Matrix(1, 1);
var_dump($matrix);

var_dump($matrix->transformPoint(1.0, 1.0));

/* Wrong number args */
try {
    $matrix->transformPoint();
    trigger_error('We should bomb here');
} catch (Exception $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args 2 */
try {
    $matrix->transformPoint(1);
    trigger_error('We should bomb here');
} catch (Exception $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args 3 */
try {
    $matrix->transformPoint(1, 1, 1);
    trigger_error('We should bomb here');
} catch (Exception $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 1 */
try {
    $matrix->transformPoint(array(), 1);
    trigger_error('We should bomb here');
} catch (Exception $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 2 */
try {
    $matrix->transformPoint(1, array());
    trigger_error('We should bomb here');
} catch (Exception $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Matrix)#%d (6) {
  ["xx"]=>
  float(1)
  ["xy"]=>
  float(0)
  ["x0"]=>
  float(0)
  ["yx"]=>
  float(1)
  ["yy"]=>
  float(0)
  ["y0"]=>
  float(0)
}
array(2) {
  ["x"]=>
  float(1)
  ["y"]=>
  float(1)
}
Cairo\Matrix::transformPoint() expects exactly 2 parameters, 0 given
Cairo\Matrix::transformPoint() expects exactly 2 parameters, 1 given
Cairo\Matrix::transformPoint() expects exactly 2 parameters, 3 given
Cairo\Matrix::transformPoint() expects parameter 1 to be float, array given
Cairo\Matrix::transformPoint() expects parameter 2 to be float, array given