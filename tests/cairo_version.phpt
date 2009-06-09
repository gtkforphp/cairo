--TEST--
cairo_version() function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$version = cairo_version();
var_dump($version);

cairo_version('foo');
?>
--EXPECTF--
int(%d)

Warning: cairo_version() expects exactly 0 parameters, 1 given in %s on line %d