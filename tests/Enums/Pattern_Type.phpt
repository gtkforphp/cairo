--TEST--
Cairo\Pattern\Type class constants
--EXTENSIONS--
eos_datastructures
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
?>
--FILE--
<?php
use Cairo\Pattern\Type;

$enum = new Type(Type::SOLID);
var_dump($enum);
?>
--EXPECTF--
object(Cairo\Pattern\Type)#%d (2) {
  ["__elements"]=>
  array(6) {
    ["SOLID"]=>
    long(0)
    ["SURFACE"]=>
    long(1)
    ["LINEAR"]=>
    long(2)
    ["RADIAL"]=>
    long(3)
    ["MESH"]=>
    long(4)
    ["RASTER_SOURCE"]=>
    long(5)
  }
  ["__value"]=>
  long(0)
}