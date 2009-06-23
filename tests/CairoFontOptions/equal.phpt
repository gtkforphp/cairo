--TEST--
CairoFontOptions->equal() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$options = new CairoFontOptions();
var_dump($options);

$options2 = new CairoFontOptions();
var_dump($options->equal($options2));

/* Wrong number args 1*/
try {
    $options->equal();
    trigger_error('equal requires 1 arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args 2 */
try {
    $options->equal($options2, 1);
    trigger_error('equal requires only 1 arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type - needs cairofontoptions */
try {
    $options->equal(1);
    trigger_error('equal requires cairofontoptions instance');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoFontOptions)#%d (0) {
}
bool(true)
CairoFontOptions::equal() expects exactly 1 parameter, 0 given
CairoFontOptions::equal() expects exactly 1 parameter, 2 given
CairoFontOptions::equal() expects parameter 1 to be CairoFontOptions, integer given