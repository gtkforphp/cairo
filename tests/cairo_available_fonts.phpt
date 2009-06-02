--TEST--
cairo_available_fonts() function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$surfaces = cairo_available_fonts();
var_dump(is_array($surfaces));
var_dump($surfaces[0]);

$surfaces = cairo_available_fonts('foo');
?>
--EXPECTF--
bool(true)
string(%d) %s

Warning: cairo_available_fonts() expects exactly 0 parameters, 1 given in %s on line %d