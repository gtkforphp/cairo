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

Cairo::version('foo');
?>
--EXPECTF--
int(%d)

Warning: Cairo::version() expects exactly 0 parameters, 1 given in %s on line %d