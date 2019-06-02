--TEST--
Cairo\FontOptions->hash() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$options = new Cairo\FontOptions();
var_dump($options);

var_dump($options->hash());

/* Wrong number args */
try {
    $options->hash('foo');
    trigger_error('hash requires no args');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\FontOptions)#%d (0) {
}
long(0)
Cairo\FontOptions::hash() expects exactly 0 parameters, 1 given