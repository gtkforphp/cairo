--TEST--
Cairo::availableFonts() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$surfaces = Cairo::availableFonts();
var_dump(is_array($surfaces));
var_dump($surfaces[0]);
?>
--EXPECTF--
bool(true)
string(%d) %s