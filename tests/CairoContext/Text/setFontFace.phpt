--TEST--
CairoContext->setFontFace() method
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

include(dirname(__FILE__) . '/create_toyfont.inc');
var_dump($fontface);

$context->setFontFace($fontface);
$fontface1 = $context->getFontFace();

var_dump($fontface === $fontface1);

include(dirname(__FILE__) . '/create_toyfont.inc');
var_dump($fontface);

$context->setFontFace($fontface);
$fontface1 = $context->getFontFace();

var_dump($fontface1 === $fontface);

try {
    $context->setFontFace();
    trigger_error('setFontFace requires one arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

try {
    $context->setFontFace(1, 1);
    trigger_error('setFontFace requires only one arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

try {
    $context->setFontFace(1);
    trigger_error('setFontFace requires instanceof CairoFontFace');
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
bool(true)
object(CairoToyFontFace)#%d (0) {
}
bool(true)
CairoContext::setFontFace() expects exactly 1 parameter, 0 given
CairoContext::setFontFace() expects exactly 1 parameter, 2 given
CairoContext::setFontFace() expects parameter 1 to be CairoFontFace, integer given