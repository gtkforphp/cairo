--TEST--
Cairo::availableSurfaces() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$surfaces = Cairo::availableSurfaces();
var_dump(is_array($surfaces));
var_dump($surfaces[0]);

Cairo::availableSurfaces('foo');
?>
--EXPECTF--
bool(true)
string(5) "IMAGE"

Warning: Cairo::availableSurfaces() expects exactly 0 parameters, 1 given in %s on line %d