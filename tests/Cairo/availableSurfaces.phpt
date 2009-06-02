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
?>
--EXPECT--
bool(true)
string(5) "IMAGE"
