--TEST--
Cairo\Context->getMatrix() method
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

var_dump($orig_matrix = $context->getMatrix());

$matrix = new Cairo\Matrix(5, 5);
var_dump($matrix);
var_dump($orig_matrix === $matrix);

$context->setMatrix($matrix);
var_dump($matrix1 = $context->getMatrix());
var_dump($matrix1 === $matrix);
var_dump($orig_matrix === $matrix);

try {
    $context->getMatrix('foo');
    trigger_error('get matrix requires no args');
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
object(Cairo\Matrix)#%d (0) {
}
bool(false)
object(Cairo\Matrix)#%d (0) {
}
bool(true)
bool(false)
Cairo\Context::getMatrix() expects exactly 0 parameters, 1 given