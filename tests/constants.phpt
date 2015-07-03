--TEST--
Cairo namespaced constants
--EXTENSIONS--
eos_datastructures
--SKIPIF--
<?php
include __DIR__ . '/skipif.inc';
?>
--FILE--
<?php
var_dump(Cairo\VERSION);
var_dump(Cairo\VERSION_STRING);
?>
--EXPECTF--
int(%d)
string(%d) "%d.%d.%d"