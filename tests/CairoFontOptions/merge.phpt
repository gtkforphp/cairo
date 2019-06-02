--TEST--
Cairo\FontOptions->merge() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$options = new Cairo\FontOptions();
var_dump($options);

$options2 = new Cairo\FontOptions();
$options->merge($options2);

/* Wrong number args 1*/
try {
    $options->merge();
    trigger_error('merge requires 1 arg');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args 2 */
try {
    $options->merge($options2, 1);
    trigger_error('merge requires only 1 arg');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type - needs cairofontoptions */
try {
    $options->merge(1);
    trigger_error('merge requires cairofontoptions instance');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\FontOptions)#%d (0) {
}
Cairo\FontOptions::merge() expects exactly 1 parameter, 0 given
Cairo\FontOptions::merge() expects exactly 1 parameter, 2 given
Cairo\FontOptions::merge() expects parameter 1 to be Cairo\FontOptions, int given