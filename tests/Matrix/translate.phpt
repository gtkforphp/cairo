--TEST--
Cairo\Matrix->translate method
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

$matrix = new Matrix();
var_dump($matrix);

$matrix->translate(0.1, 0.1);

/* Wrong number args */
try {
    $matrix->translate();
    trigger_error('We should bomb here');
} catch (Exception $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args 2 */
try {
    $matrix->translate(1);
    trigger_error('We should bomb here');
} catch (Exception $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Too many args */
try {
    $matrix->translate(1, 1, 1);
    trigger_error('We should bomb here');
} catch (Exception $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Bad arg type */
try {
    $matrix->translate(array(), 1);
    trigger_error('We should bomb here');
} catch (Exception $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Bad arg type 2*/
try {
    $matrix->translate(1, array());
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
  float(0)
  ["yy"]=>
  float(1)
  ["y0"]=>
  float(0)
}
Cairo\Matrix::translate() expects exactly 2 parameters, 0 given
Cairo\Matrix::translate() expects exactly 2 parameters, 1 given
Cairo\Matrix::translate() expects exactly 2 parameters, 3 given
Cairo\Matrix::translate() expects parameter 1 to be float, array given
Cairo\Matrix::translate() expects parameter 2 to be float, array given