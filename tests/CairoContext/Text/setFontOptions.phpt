--TEST--
Cairo\Context->setFontOptions() method
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

$options = new Cairo\FontOptions();
var_dump($options);

$context->setFontOptions($options);
$options1 = $context->getFontOptions();

var_dump($options === $options1);

$options2 = new Cairo\FontOptions();
$context->setFontOptions($options2);
$options1 = $context->getFontOptions();

var_dump($options2 === $options1);

try {
    $context->setFontOptions();
    trigger_error('setFontOptions requires one arg');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

try {
    $context->setFontOptions(1, 1);
    trigger_error('setFontOptions requires only one arg');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

try {
    $context->setFontOptions(1);
    trigger_error('setFontOptions requires instanceof Cairo\FontOptions');
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
object(Cairo\FontOptions)#%d (0) {
}
bool(true)
bool(true)
Cairo\Context::setFontOptions() expects exactly 1 parameter, 0 given
Cairo\Context::setFontOptions() expects exactly 1 parameter, 2 given
Cairo\Context::setFontOptions() expects parameter 1 to be Cairo\FontOptions, int given