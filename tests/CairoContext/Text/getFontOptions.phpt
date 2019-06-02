--TEST--
Cairo\Context->getFontOptions() method
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

var_dump($orig_options = $context->getFontOptions());

$options = new Cairo\FontOptions();
var_dump($orig_options === $options);

$context->setFontOptions($options);
var_dump($options1 = $context->getFontOptions());
var_dump($options1 === $options);
var_dump($orig_options === $options1);

try {
    $context->getFontOptions('foo');
    trigger_error('getFontOptions requires no args');
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
bool(false)
object(Cairo\FontOptions)#%d (0) {
}
bool(true)
bool(false)
Cairo\Context::getFontOptions() expects exactly 0 parameters, 1 given