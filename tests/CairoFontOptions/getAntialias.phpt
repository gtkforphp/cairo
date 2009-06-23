--TEST--
CairoFontOptions->getAntialias() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$options = new CairoFontOptions();
var_dump($options);

var_dump($options->getAntialias());

/* Wrong number args */
try {
    $options->getAntialias('foo');
    trigger_error('getAntialias requires no args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoFontOptions)#%d (0) {
}
int(0)
CairoFontOptions::getAntialias() expects exactly 0 parameters, 1 given