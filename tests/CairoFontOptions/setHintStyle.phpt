--TEST--
Cairo\FontOptions->setHintStyle() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$options = new Cairo\FontOptions();
var_dump($options);

$options->setHintStyle(Cairo\HintStyle::STYLE_FULL);

/* Wrong number args 1*/
try {
    $options->setHintStyle();
    trigger_error('setHintStyle requires 1 arg');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args 2 */
try {
    $options->setHintStyle(Cairo\HintStyle::STYLE_FULL, 1);
    trigger_error('setHintStyle requires only 1 arg');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type - needs int */
try {
    $options->setHintStyle(array());
    trigger_error('setHintStyle requires int');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\FontOptions)#%d (0) {
}
Cairo\FontOptions::setHintStyle() expects exactly 1 parameter, 0 given
Cairo\FontOptions::setHintStyle() expects exactly 1 parameter, 2 given
Cairo\FontOptions::setHintStyle() expects parameter 1 to be int, array given