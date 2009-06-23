--TEST--
CairoFontOptions->setHintStyle() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$options = new CairoFontOptions();
var_dump($options);

$options->setHintStyle(CairoHintStyle::STYLE_FULL);

/* Wrong number args 1*/
try {
    $options->setHintStyle();
    trigger_error('setHintStyle requires 1 arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args 2 */
try {
    $options->setHintStyle(CairoHintStyle::STYLE_FULL, 1);
    trigger_error('setHintStyle requires only 1 arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type - needs int */
try {
    $options->setHintStyle(array());
    trigger_error('setHintStyle requires int');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoFontOptions)#%d (0) {
}
CairoFontOptions::setHintStyle() expects exactly 1 parameter, 0 given
CairoFontOptions::setHintStyle() expects exactly 1 parameter, 2 given
CairoFontOptions::setHintStyle() expects parameter 1 to be long, array given