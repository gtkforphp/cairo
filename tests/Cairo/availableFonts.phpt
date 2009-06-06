--TEST--
Cairo::availableFonts() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$fonts = Cairo::availableFonts();
var_dump(is_array($fonts));
var_dump($fonts[0]);

Cairo::availableFonts('foo');
?>
--EXPECTF--
bool(true)
string(%d) %s

Warning: Cairo::availableFonts() expects exactly 0 parameters, 1 given in %s on line %d