--TEST--
Cairo\Context->getFontFace() method
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

var_dump($orig_face = $context->getFontFace());

include(dirname(__FILE__) . '/create_toyfont.inc');
var_dump($fontface);

$context->setFontFace($fontface);
var_dump($face1 = $context->getFontFace());
var_dump($face1 === $fontface);
var_dump($orig_face === $face1);

try {
    $context->getFontFace('foo');
    trigger_error('getFontFace requires no args');
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
object(Cairo\FontFace\Toy)#%d (0) {
}
object(Cairo\FontFace\Toy)#%d (0) {
}
object(Cairo\FontFace\Toy)#%d (0) {
}
bool(true)
bool(false)
Cairo\Context::getFontFace() expects exactly 0 parameters, 1 given