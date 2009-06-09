--TEST--
CairoMatrix::initRotate function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$matrix = CairoMatrix::initRotate(0.1);
var_dump($matrix);

/* Wrong number args */
try {
    CairoMatrix::initRotate();
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args 2 */
try {
    CairoMatrix::initRotate(1, 1);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type */
try {
    CairoMatrix::initRotate(array());
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoMatrix)#%d (0) {
}
CairoMatrix::initRotate() expects exactly 1 parameter, 0 given
CairoMatrix::initRotate() expects exactly 1 parameter, 2 given
CairoMatrix::initRotate() expects parameter 1 to be double, array given