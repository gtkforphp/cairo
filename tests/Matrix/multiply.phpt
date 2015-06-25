--TEST--
Cairo\Matrix::multiply method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
use Cairo\Matrix;
use Cairo\Exception;

$matrix1 = new Matrix(0.1, 0.1);
$matrix2 = new Matrix(0.1);

var_dump(Matrix::multiply($matrix1, $matrix2));

/* Wrong number args */
try {
    Matrix::multiply();
    trigger_error('We should bomb here');
} catch (Exception $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args 2*/
try {
    Matrix::multiply(1);
    trigger_error('We should bomb here');
} catch (Exception $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args 3*/
try {
    Matrix::multiply(1, 1, 1);
    trigger_error('We should bomb here');
} catch (Exception $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 1*/
try {
    Matrix::multiply(1, $matrix2);
    trigger_error('We should bomb here');
} catch (Exception $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 2*/
try {
    Matrix::multiply($matrix1, 1);
    trigger_error('We should bomb here');
} catch (Exception $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Matrix)#%d (6) {
  ["xx"]=>
  float(%f)
  ["xy"]=>
  float(0)
  ["x0"]=>
  float(0)
  ["yx"]=>
  float(%f)
  ["yy"]=>
  float(1)
  ["y0"]=>
  float(0)
}
Cairo\Matrix::multiply() expects exactly 2 parameters, 0 given
Cairo\Matrix::multiply() expects exactly 2 parameters, 1 given
Cairo\Matrix::multiply() expects exactly 2 parameters, 3 given
Cairo\Matrix::multiply() expects parameter 1 to be Cairo\Matrix, integer given
Cairo\Matrix::multiply() expects parameter 2 to be Cairo\Matrix, integer given