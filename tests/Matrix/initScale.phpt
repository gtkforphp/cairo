--TEST--
Cairo\Matrix::initScale() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
use Cairo\Matrix;
use TypeError as Exception;

$matrix = Matrix::initScale(0.1, 0.1);
var_dump($matrix);

/* Wrong number args */
try {
    Matrix::initScale();
    trigger_error('We should bomb here');
} catch (Exception $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args 2 */
try {
    Matrix::initScale(1);
    trigger_error('We should bomb here');
} catch (Exception $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args 3 */
try {
    Matrix::initScale(1, 1, 1);
    trigger_error('We should bomb here');
} catch (Exception $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 1 */
try {
    Matrix::initScale(array(), 1);
    trigger_error('We should bomb here');
} catch (Exception $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 2 */
try {
    Matrix::initScale(1, array());
    trigger_error('We should bomb here');
} catch (Exception $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Matrix)#%d (6) {
  ["xx"]=>
  float(0.1)
  ["xy"]=>
  float(0)
  ["x0"]=>
  float(0)
  ["yx"]=>
  float(0)
  ["yy"]=>
  float(0.1)
  ["y0"]=>
  float(0)
}
Cairo\Matrix::initScale() expects exactly 2 parameters, 0 given
Cairo\Matrix::initScale() expects exactly 2 parameters, 1 given
Cairo\Matrix::initScale() expects exactly 2 parameters, 3 given
Cairo\Matrix::initScale() expects parameter 1 to be float, array given
Cairo\Matrix::initScale() expects parameter 2 to be float, array given