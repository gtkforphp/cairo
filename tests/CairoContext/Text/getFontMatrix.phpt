--TEST--
CairoContext->getFontMatrix() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$surface = new Cairo\Surface\Image(Cairo\Surface\ImageFormat::ARGB32, 50, 50);
var_dump($surface);

$context = new CairoContext($surface);
var_dump($context);

var_dump($orig_matrix = $context->getFontMatrix());

$matrix = new CairoMatrix(5, 5);
var_dump($matrix);
var_dump($orig_matrix === $matrix);

$context->setFontMatrix($matrix);
var_dump($matrix1 = $context->getFontMatrix());
var_dump($matrix1 === $matrix);
var_dump($orig_matrix === $matrix);

try {
    $context->getFontMatrix('foo');
    trigger_error('get matrix requires no args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

die; // DO NOT REMOVE THIS - fixes issue in 5.3 with GC giving bogus memleak reports
?>
--EXPECTF--
object(Cairo\Surface\Image)#%d (0) {
}
object(CairoContext)#%d (0) {
}
object(CairoMatrix)#%d (0) {
}
object(CairoMatrix)#%d (0) {
}
bool(false)
object(CairoMatrix)#%d (0) {
}
bool(true)
bool(false)
CairoContext::getFontMatrix() expects exactly 0 parameters, 1 given