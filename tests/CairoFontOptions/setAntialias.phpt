--TEST--
CairoFontOptions->setAntialias() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$options = new CairoFontOptions();
var_dump($options);

$options->setAntialias(CairoAntialias::MODE_SUBPIXEL);

/* Wrong number args 1*/
try {
    $options->setAntialias();
    trigger_error('setAntialias requires 1 arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args 2 */
try {
    $options->setAntialias(CairoAntialias::MODE_SUBPIXEL, 1);
    trigger_error('setAntialias requires only 1 arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type - needs int */
try {
    $options->setAntialias(array());
    trigger_error('setAntialias requires int');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoFontOptions)#%d (0) {
}
CairoFontOptions::setAntialias() expects exactly 1 parameter, 0 given
CairoFontOptions::setAntialias() expects exactly 1 parameter, 2 given
CairoFontOptions::setAntialias() expects parameter 1 to be long, array given