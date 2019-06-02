--TEST--
Cairo\FontOptions->equal() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$options = new Cairo\FontOptions();
var_dump($options);

$options2 = new Cairo\FontOptions();
var_dump($options->equal($options2));

/* Wrong number args 1*/
try {
    $options->equal();
    trigger_error('equal requires 1 arg');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args 2 */
try {
    $options->equal($options2, 1);
    trigger_error('equal requires only 1 arg');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type - needs cairofontoptions */
try {
    $options->equal(1);
    trigger_error('equal requires cairofontoptions instance');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\FontOptions)#%d (0) {
}
bool(true)
Cairo\FontOptions::equal() expects exactly 1 parameter, 0 given
Cairo\FontOptions::equal() expects exactly 1 parameter, 2 given
Cairo\FontOptions::equal() expects parameter 1 to be Cairo\FontOptions, int given