--TEST--
Cairo::version() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$version = Cairo::version();
var_dump($version);
?>
--EXPECTF--
int(%d)