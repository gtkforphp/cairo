--TEST--
CairoContext->setFontOptions() method
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

$options = new CairoFontOptions();
var_dump($options);

$context->setFontOptions($options);
$options1 = $context->getFontOptions();

var_dump($options === $options1);

$options2 = new CairoFontOptions();
$context->setFontOptions($options2);
$options1 = $context->getFontOptions();

var_dump($options2 === $options1);

try {
    $context->setFontOptions();
    trigger_error('setFontOptions requires one arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

try {
    $context->setFontOptions(1, 1);
    trigger_error('setFontOptions requires only one arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

try {
    $context->setFontOptions(1);
    trigger_error('setFontOptions requires instanceof CairoFontOptions');
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
object(CairoFontOptions)#%d (0) {
}
bool(true)
bool(true)
CairoContext::setFontOptions() expects exactly 1 parameter, 0 given
CairoContext::setFontOptions() expects exactly 1 parameter, 2 given
CairoContext::setFontOptions() expects parameter 1 to be CairoFontOptions, integer given