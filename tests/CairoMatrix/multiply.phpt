--TEST--
CairoMatrix::multiply method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$matrix1 = new CairoMatrix(0.1, 0.1);
$matrix2 = new CairoMatrix(0.1);

var_dump(CairoMatrix::multiply($matrix1, $matrix2));

/* Wrong number args */
try {
    CairoMatrix::multiply();
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args 2*/
try {
    CairoMatrix::multiply(1);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args 3*/
try {
    CairoMatrix::multiply(1, 1, 1);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 1*/
try {
    CairoMatrix::multiply(1, $matrix2);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 2*/
try {
    CairoMatrix::multiply($matrix1, 1);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoMatrix)#%d (0) {
}
CairoMatrix::multiply() expects exactly 2 parameters, 0 given
CairoMatrix::multiply() expects exactly 2 parameters, 1 given
CairoMatrix::multiply() expects exactly 2 parameters, 3 given
CairoMatrix::multiply() expects parameter 1 to be CairoMatrix, integer given
CairoMatrix::multiply() expects parameter 2 to be CairoMatrix, integer given