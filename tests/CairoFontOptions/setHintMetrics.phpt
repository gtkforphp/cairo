--TEST--
Cairo\FontOptions->setHintMetrics() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$options = new Cairo\FontOptions();
var_dump($options);

$options->setHintMetrics(Cairo\HintMetrics::METRICS_ON);

/* Wrong number args 1*/
try {
    $options->setHintMetrics();
    trigger_error('setHintMetrics requires 1 arg');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args 2 */
try {
    $options->setHintMetrics(Cairo\HintMetrics::METRICS_ON, 1);
    trigger_error('setHintMetrics requires only 1 arg');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type - needs int */
try {
    $options->setHintMetrics(array());
    trigger_error('setHintMetrics requires int');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\FontOptions)#%d (0) {
}
Cairo\FontOptions::setHintMetrics() expects exactly 1 parameter, 0 given
Cairo\FontOptions::setHintMetrics() expects exactly 1 parameter, 2 given
Cairo\FontOptions::setHintMetrics() expects parameter 1 to be int, array given