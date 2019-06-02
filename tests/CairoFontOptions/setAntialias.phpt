--TEST--
Cairo\FontOptions->setAntialias() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$options = new Cairo\FontOptions();
var_dump($options);

$options->setAntialias(Cairo\Antialias::MODE_SUBPIXEL);

/* Wrong number args 1*/
try {
    $options->setAntialias();
    trigger_error('setAntialias requires 1 arg');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args 2 */
try {
    $options->setAntialias(Cairo\Antialias::MODE_SUBPIXEL, 1);
    trigger_error('setAntialias requires only 1 arg');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type - needs int */
try {
    $options->setAntialias(array());
    trigger_error('setAntialias requires int');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\FontOptions)#%d (0) {
}
Cairo\FontOptions::setAntialias() expects exactly 1 parameter, 0 given
Cairo\FontOptions::setAntialias() expects exactly 1 parameter, 2 given
Cairo\FontOptions::setAntialias() expects parameter 1 to be int, array given