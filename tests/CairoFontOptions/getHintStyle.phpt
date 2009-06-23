--TEST--
CairoFontOptions->getHintStyle() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$options = new CairoFontOptions();
var_dump($options);

var_dump($options->getHintStyle());

/* Wrong number args */
try {
    $options->getHintStyle('foo');
    trigger_error('getHintStyle requires no args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoFontOptions)#%d (0) {
}
int(0)
CairoFontOptions::getHintStyle() expects exactly 0 parameters, 1 given