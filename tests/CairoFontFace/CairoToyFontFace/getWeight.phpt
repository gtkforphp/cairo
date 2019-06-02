--TEST--
Cairo\FontFace\Toy::getWeight() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!class_exists('Cairo\FontFace\Toy')) die('skip - Cairo\FontFace\Toy not enabled');
?>
--FILE--
<?php
// Test with all parameters
$c = new Cairo\FontFace\Toy("sans-serif", Cairo\FontWeight::NORMAL, Cairo\FontWeight::NORMAL);
var_dump($c->getWeight());

$c = new Cairo\FontFace\Toy("sans-serif", Cairo\FontWeight::NORMAL, Cairo\FontWeight::BOLD);
var_dump($c->getWeight());
?>
--EXPECTF--
long(0)
long(1)
