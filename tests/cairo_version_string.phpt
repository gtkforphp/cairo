--TEST--
cairo_version_string() function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$version = cairo_version_string();
var_dump($version);

cairo_version_string('foo');
?>
--EXPECTF--
string(%d) %s

Warning: cairo_version_string() expects exactly 0 parameters, 1 given in %s on line %d