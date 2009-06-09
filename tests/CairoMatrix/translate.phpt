--TEST--
CairoMatrix->translate method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$matrix = new CairoMatrix();
var_dump($matrix);

$matrix->translate(0.1, 0.1);

/* Wrong number args */
try {
    $matrix->translate();
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args 2 */
try {
    $matrix->translate(1);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Too many args */
try {
    $matrix->translate(1, 1, 1);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Bad arg type */
try {
    $matrix->translate(array(), 1);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Bad arg type 2*/
try {
    $matrix->translate(1, array());
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoMatrix)#%d (0) {
}
CairoMatrix::translate() expects exactly 2 parameters, 0 given
CairoMatrix::translate() expects exactly 2 parameters, 1 given
CairoMatrix::translate() expects exactly 2 parameters, 3 given
CairoMatrix::translate() expects parameter 1 to be double, array given
CairoMatrix::translate() expects parameter 2 to be double, array given