--TEST--
CairoMatrix->transformPoint method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$matrix = new CairoMatrix();
var_dump($matrix);

var_dump($matrix->transformPoint(1.0, 1.0));

/* Wrong number args */
try {
    $matrix->transformPoint();
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args 2 */
try {
    $matrix->transformPoint(1);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args 3 */
try {
    $matrix->transformPoint(1, 1, 1);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 1 */
try {
    $matrix->transformPoint(array(), 1);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 2 */
try {
    $matrix->transformPoint(1, array());
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoMatrix)#%d (0) {
}
array(2) {
  ["x"]=>
  float(%f)
  ["y"]=>
  float(%f)
}
CairoMatrix::transformPoint() expects exactly 2 parameters, 0 given
CairoMatrix::transformPoint() expects exactly 2 parameters, 1 given
CairoMatrix::transformPoint() expects exactly 2 parameters, 3 given
CairoMatrix::transformPoint() expects parameter 1 to be double, array given
CairoMatrix::transformPoint() expects parameter 2 to be double, array given