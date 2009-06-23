--TEST--
CairoFontOptions->setSubpixelOrder() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$options = new CairoFontOptions();
var_dump($options);

$options->setSubpixelOrder(CairoSubpixelOrder::ORDER_RGB);

/* Wrong number args 1*/
try {
    $options->setSubpixelOrder();
    trigger_error('setSubpixelOrder requires 1 arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args 2 */
try {
    $options->setSubpixelOrder(CairoSubpixelOrder::ORDER_RGB, 1);
    trigger_error('setSubpixelOrder requires only 1 arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type - needs int */
try {
    $options->setSubpixelOrder(array());
    trigger_error('setSubpixelOrder requires int');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoFontOptions)#%d (0) {
}
CairoFontOptions::setSubpixelOrder() expects exactly 1 parameter, 0 given
CairoFontOptions::setSubpixelOrder() expects exactly 1 parameter, 2 given
CairoFontOptions::setSubpixelOrder() expects parameter 1 to be long, array given