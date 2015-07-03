--TEST--
Cairo\Matrix->scale()
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

$matrix = new Matrix(1, 1, 1, 1, 1, 1);

$matrix->scale(2, 5);
var_dump($matrix);

/* Wrong number args */
try {
    $matrix->scale();
    trigger_error('We should bomb here');
} catch (Exception $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args 2 */
try {
    $matrix->scale(1);
    trigger_error('We should bomb here');
} catch (Exception $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args 3 */
try {
    $matrix->scale(1, 1, 1);
    trigger_error('We should bomb here');
} catch (Exception $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 1 */
try {
    $matrix->scale(array(), 1);
    trigger_error('We should bomb here');
} catch (Exception $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 2 */
try {
    $matrix->scale(1, array());
    trigger_error('We should bomb here');
} catch (Exception $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Matrix)#%d (6) {
  ["xx"]=>
  float(2)
  ["xy"]=>
  float(5)
  ["x0"]=>
  float(1)
  ["yx"]=>
  float(2)
  ["yy"]=>
  float(5)
  ["y0"]=>
  float(1)
}
Cairo\Matrix::scale() expects exactly 2 parameters, 0 given
Cairo\Matrix::scale() expects exactly 2 parameters, 1 given
Cairo\Matrix::scale() expects exactly 2 parameters, 3 given
Cairo\Matrix::scale() expects parameter 1 to be float, array given
Cairo\Matrix::scale() expects parameter 2 to be float, array given