--TEST--
Cairo\Context->setFontMatrix() method
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

$context->setFontMatrix($matrix);
$matrix1 = $context->getFontMatrix();

var_dump($matrix === $matrix1);

$matrix2 = new Cairo\Matrix(5, 5);
$context->setFontMatrix($matrix2);
$matrix1 = $context->getFontMatrix();

var_dump($matrix2 === $matrix1);

try {
    $context->setFontMatrix();
    trigger_error('Set matrix requires one arg');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

try {
    $context->setFontMatrix(1, 1);
    trigger_error('Set matrix requires only one arg');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

try {
    $context->setFontMatrix(1);
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
Cairo\Context::setFontMatrix() expects exactly 1 parameter, 0 given
Cairo\Context::setFontMatrix() expects exactly 1 parameter, 2 given
Cairo\Context::setFontMatrix() expects parameter 1 to be Cairo\Matrix, int given