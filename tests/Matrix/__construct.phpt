--TEST--
new Cairo\Matrix [__construct() method ]
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
use Cairo\Matrix;
use Cairo\Exception;

$matrix = new Matrix();
var_dump($matrix);

/* Wrong number args - can only have too many, any number between 0 and 6 is fine */
try {
    new Matrix(1, 1, 1, 1, 1, 1, 1);
    trigger_error('We should bomb here');
} catch (Exception $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 1 */
try {
    new Matrix(array());
    trigger_error('We should bomb here');
} catch (Exception $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 2 */
try {
    new CairoMatrix(1, array());
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 3 */
try {
    new Matrix(1, 1, array());
    trigger_error('We should bomb here');
} catch (Exception $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 4 */
try {
    new Matrix(1, 1, 1, array());
    trigger_error('We should bomb here');
} catch (Exception $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 5 */
try {
    new Matrix(1, 1, 1, 1, array());
    trigger_error('We should bomb here');
} catch (Exception $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 6 */
try {
    new Matrix(1, 1, 1, 1, 1, array());
    trigger_error('We should bomb here');
} catch (Exception $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Matrix)#%d (0) {
}
Cairo\Matrix::__construct() expects at most 6 parameters, 7 given
Cairo\Matrix::__construct() expects parameter 1 to be double, array given
Cairo\Matrix::__construct() expects parameter 2 to be double, array given
Cairo\Matrix::__construct() expects parameter 3 to be double, array given
Cairo\Matrix::__construct() expects parameter 4 to be double, array given
Cairo\Matrix::__construct() expects parameter 5 to be double, array given
Cairo\Matrix::__construct() expects parameter 6 to be double, array given