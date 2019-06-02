--TEST--
Cairo::versionString() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$version = Cairo::versionString();
var_dump($version);

/* Wrong number args */
try {
    Cairo::versionString('foo');
    trigger_error('Cairo::versionString should take no arguments');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
string(%d) %s
Cairo::versionString() expects exactly 0 parameters, 1 given