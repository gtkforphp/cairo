--TEST--
Cairo\version()
--EXTENSIONS--
eos_datastructures
--SKIPIF--
<?php
include __DIR__ . '/skipif.inc';
?>
--FILE--
<?php
$version = Cairo\version();
var_dump($version);

Cairo\version('foo');
?>
--EXPECTF--
int(%d)

Warning: Cairo\version() expects exactly 0 parameters, 1 given in %s on line %d