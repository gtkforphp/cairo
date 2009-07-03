--TEST--
CairoContext->getFontFace() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$surface = new CairoImageSurface(CairoFormat::ARGB32, 50, 50);
var_dump($surface);

$context = new CairoContext($surface);
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
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

die; // DO NOT REMOVE THIS - fixes issue in 5.3 with GC giving bogus memleak reports
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
object(CairoToyFontFace)#%d (0) {
}
object(CairoToyFontFace)#%d (0) {
}
object(CairoToyFontFace)#%d (0) {
}
bool(true)
bool(false)
CairoContext::getFontFace() expects exactly 0 parameters, 1 given