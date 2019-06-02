--TEST--
Cairo\FontFace\Toy::getSlant() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!class_exists('Cairo\FontFace\Toy')) die('skip - Cairo\FontFace\Toy not enabled');
?>
--FILE--
<?php
// Test with all parameters
$c = new Cairo\FontFace\Toy("sans-serif", Cairo\FontSlant::NORMAL, Cairo\FontWeight::NORMAL);
var_dump($c->getSlant());

$c = new Cairo\FontFace\Toy("sans-serif", Cairo\FontSlant::ITALIC, Cairo\FontWeight::NORMAL);
var_dump($c->getSlant());
?>
--EXPECTF--
long(0)
long(1)
