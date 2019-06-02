--TEST--
Cairo\Context->setMatrix() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$surface = new Cairo\Surface\Image(Cairo\Surface\ImageFormat::ARGB32, 50, 50);
var_dump($surface);

$context = new Cairo\Context($surface);
var_dump($context);

$matrix = new Cairo\Matrix();
var_dump($matrix);

$context->setMatrix($matrix);
$matrix1 = $context->getMatrix();

var_dump($matrix === $matrix1);

$matrix2 = new Cairo\Matrix(5, 5);
$context->setMatrix($matrix2);
$matrix1 = $context->getMatrix();

var_dump($matrix2 === $matrix1);

try {
    $context->setMatrix();
    trigger_error('Set matrix requires one arg');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

try {
    $context->setMatrix(1, 1);
    trigger_error('Set matrix requires only one arg');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

try {
    $context->setMatrix(1);
    trigger_error('Set matrix requires instanceof Cairomatrix');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

die; // DO NOT REMOVE THIS - fixes issue in 5.3 with GC giving bogus memleak reports
?>
--EXPECTF--
object(Cairo\Surface\Image)#%d (0) {
}
object(Cairo\Context)#%d (0) {
}
object(Cairo\Matrix)#%d (0) {
}
bool(true)
bool(true)
Cairo\Context::setMatrix() expects exactly 1 parameter, 0 given
Cairo\Context::setMatrix() expects exactly 1 parameter, 2 given
Cairo\Context::setMatrix() expects parameter 1 to be Cairo\Matrix, int given