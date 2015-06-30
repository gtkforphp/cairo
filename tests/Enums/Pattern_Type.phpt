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
    int(0)
    ["SURFACE"]=>
    int(1)
    ["LINEAR"]=>
    int(2)
    ["RADIAL"]=>
    int(3)
    ["MESH"]=>
    int(4)
    ["RASTER_SOURCE"]=>
    int(5)
  }
  ["__value"]=>
  int(0)
}