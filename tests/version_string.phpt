--TEST--
Cairo\version_string()
--EXTENSIONS--
eos_datastructures
--SKIPIF--
<?php
include __DIR__ . '/skipif.inc';
?>
--FILE--
<?php
$version = Cairo\version_string();
var_dump($version);

Cairo\version_string('foo');
?>
--EXPECTF--
string(%d) "%d.%d.%d"

Warning: Cairo\version_string() expects exactly 0 parameters, 1 given in %s on line %d