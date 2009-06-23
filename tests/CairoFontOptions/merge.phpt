--TEST--
CairoFontOptions->merge() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$options = new CairoFontOptions();
var_dump($options);

$options2 = new CairoFontOptions();
$options->merge($options2);

/* Wrong number args 1*/
try {
    $options->merge();
    trigger_error('merge requires 1 arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args 2 */
try {
    $options->merge($options2, 1);
    trigger_error('merge requires only 1 arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type - needs cairofontoptions */
try {
    $options->merge(1);
    trigger_error('merge requires cairofontoptions instance');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoFontOptions)#%d (0) {
}
CairoFontOptions::merge() expects exactly 1 parameter, 0 given
CairoFontOptions::merge() expects exactly 1 parameter, 2 given
CairoFontOptions::merge() expects parameter 1 to be CairoFontOptions, integer given