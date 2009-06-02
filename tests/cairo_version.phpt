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
?>
--EXPECTF--
int(%d)