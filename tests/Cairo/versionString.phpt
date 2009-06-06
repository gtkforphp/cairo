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

Cairo::versionString('foo');
?>
--EXPECTF--
string(%d) %s

Warning: Cairo::versionString() expects exactly 0 parameters, 1 given in %s on line %d