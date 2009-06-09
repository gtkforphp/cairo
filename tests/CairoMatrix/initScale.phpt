--TEST--
CairoMatrix::initScale() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$matrix = CairoMatrix::initScale(0.1, 0.1);
var_dump($matrix);

/* Wrong number args */
try {
    CairoMatrix::initScale();
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args 2 */
try {
    CairoMatrix::initScale(1);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args 3 */
try {
    CairoMatrix::initScale(1, 1, 1);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 1 */
try {
    CairoMatrix::initScale(array(), 1);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 2 */
try {
    CairoMatrix::initScale(1, array());
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoMatrix)#%d (0) {
}
CairoMatrix::initScale() expects exactly 2 parameters, 0 given
CairoMatrix::initScale() expects exactly 2 parameters, 1 given
CairoMatrix::initScale() expects exactly 2 parameters, 3 given
CairoMatrix::initScale() expects parameter 1 to be double, array given
CairoMatrix::initScale() expects parameter 2 to be double, array given