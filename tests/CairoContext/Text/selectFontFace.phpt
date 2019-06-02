--TEST--
Cairo\Context->selectFontFace() method
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

$context->selectFontFace('sans-serif');
$fontface = $context->getFontFace();
var_dump($fontface);

/* Wrong number args */
try {
    $context->selectFontFace();
    trigger_error('selectFontFace requires at least one arg');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - too many */
try {
    $context->selectFontFace('sans-serif', Cairo\FontSlant::NORMAL, Cairo\FontWeight::NORMAL, 1);
    trigger_error('selectFontFace requires at least one arg');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type - string */
try {
    $context->selectFontFace(array());
    trigger_error('selectFontFace requires a string font name');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type - int */
try {
    $context->selectFontFace('sans-serif', array());
    trigger_error('selectFontFace requires an int font slant');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type - int */
try {
    $context->selectFontFace('sans-serif', Cairo\FontSlant::NORMAL, array());
    trigger_error('selectFontFace requires an int font weight');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Surface\Image)#%d (0) {
}
object(Cairo\Context)#%d (0) {
}
object(Cairo\FontFace\Toy)#%d (0) {
}
Cairo\Context::selectFontFace() expects at least 1 parameter, 0 given
Cairo\Context::selectFontFace() expects at most 3 parameters, 4 given
Cairo\Context::selectFontFace() expects parameter 1 to be string, array given
Cairo\Context::selectFontFace() expects parameter 2 to be int, array given
Cairo\Context::selectFontFace() expects parameter 3 to be int, array given