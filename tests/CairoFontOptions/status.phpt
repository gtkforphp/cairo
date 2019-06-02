--TEST--
Cairo\FontOptions->status() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$options = new Cairo\FontOptions();
var_dump($options);

$status = $options->status();
var_dump($status);
var_dump($status == CairoStatus::SUCCESS);

/* Wrong number args */
try {
    $options->status('foo');
    trigger_error('status requires no args');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\FontOptions)#%d (0) {
}
long(0)
bool(true)
Cairo\FontOptions::status() expects exactly 0 parameters, 1 given