--TEST--
CairoContext->selectFontFace() method
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

$context->selectFontFace('sans-serif');
$fontface = $context->getFontFace();
var_dump($fontface);

/* Wrong number args */
try {
    $context->selectFontFace();
    trigger_error('selectFontFace requires at least one arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - too many */
try {
    $context->selectFontFace('sans-serif', CairoFontSlant::NORMAL, CairoFontWeight::NORMAL, 1);
    trigger_error('selectFontFace requires at least one arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type - string */
try {
    $context->selectFontFace(array());
    trigger_error('selectFontFace requires a string font name');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type - int */
try {
    $context->selectFontFace('sans-serif', array());
    trigger_error('selectFontFace requires an int font slant');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type - int */
try {
    $context->selectFontFace('sans-serif', CairoFontSlant::NORMAL, array());
    trigger_error('selectFontFace requires an int font weight');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
object(CairoToyFontFace)#%d (0) {
}
CairoContext::selectFontFace() expects at least 1 parameter, 0 given
CairoContext::selectFontFace() expects at most 3 parameters, 4 given
CairoContext::selectFontFace() expects parameter 1 to be string, array given
CairoContext::selectFontFace() expects parameter 2 to be long, array given
CairoContext::selectFontFace() expects parameter 3 to be long, array given