--TEST--
phpversion value
--EXTENSIONS--
eos_datastructures
--SKIPIF--
<?php
include __DIR__ . '/skipif.inc';
?>
--FILE--
<?php
var_dump(phpversion('cairo'));
?>
--EXPECTF--
string(%d) "%d.%d.%d%s"
