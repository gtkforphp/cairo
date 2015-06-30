--TEST--
Cairo\Matrix->invert method
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

$matrix->invert();

/* Wrong number args */
try {
    $matrix->invert('foo');
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
Cairo\Matrix::invert() expects exactly 0 parameters, 1 given