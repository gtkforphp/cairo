--TEST--
CairoFontOptions->setHintMetrics() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$options = new CairoFontOptions();
var_dump($options);

$options->setHintMetrics(CairoHintMetrics::METRICS_ON);

/* Wrong number args 1*/
try {
    $options->setHintMetrics();
    trigger_error('setHintMetrics requires 1 arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args 2 */
try {
    $options->setHintMetrics(CairoHintMetrics::METRICS_ON, 1);
    trigger_error('setHintMetrics requires only 1 arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type - needs int */
try {
    $options->setHintMetrics(array());
    trigger_error('setHintMetrics requires int');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoFontOptions)#%d (0) {
}
CairoFontOptions::setHintMetrics() expects exactly 1 parameter, 0 given
CairoFontOptions::setHintMetrics() expects exactly 1 parameter, 2 given
CairoFontOptions::setHintMetrics() expects parameter 1 to be long, array given