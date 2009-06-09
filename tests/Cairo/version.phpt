--TEST--
Cairo::version() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$version = Cairo::version();
var_dump($version);

/* Wrong number args */
try {
    Cairo::version('foo');
    trigger_error('Cairo::version should take no arguments');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
int(%d)
Cairo::version() expects exactly 0 parameters, 1 given