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
?>
--EXPECTF--
string(%d) %s