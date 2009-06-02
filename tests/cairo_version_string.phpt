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
?>
--EXPECTF--
string(%d) %s