--TEST--
CairoMatrix::initTranslate function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$matrix = CairoMatrix::initTranslate(0.1, 0.1);
var_dump($matrix);

/* Wrong number args */
try {
    CairoMatrix::initTranslate();
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args 2 */
try {
    CairoMatrix::initTranslate(1);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Too many args */
try {
    CairoMatrix::initTranslate(1, 1, 1);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Bad arg type */
try {
    CairoMatrix::initTranslate(array(), 1);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Bad arg type 2*/
try {
    CairoMatrix::initTranslate(1, array());
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoMatrix)#%d (0) {
}
CairoMatrix::initTranslate() expects exactly 2 parameters, 0 given
CairoMatrix::initTranslate() expects exactly 2 parameters, 1 given
CairoMatrix::initTranslate() expects exactly 2 parameters, 3 given
CairoMatrix::initTranslate() expects parameter 1 to be double, array given
CairoMatrix::initTranslate() expects parameter 2 to be double, array given