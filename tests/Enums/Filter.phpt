--TEST--
Cairo\Filter class constants
--EXTENSIONS--
eos_datastructures
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
?>
--FILE--
<?php
use Cairo\Filter;

$enum = new Filter(Filter::FAST);
var_dump($enum);
?>
--EXPECTF--
object(Cairo\Filter)#%d (2) {
  ["__elements"]=>
  array(6) {
    ["FAST"]=>
    int(0)
    ["GOOD"]=>
    int(1)
    ["BEST"]=>
    int(2)
    ["NEAREST"]=>
    int(3)
    ["BILINEAR"]=>
    int(4)
    ["GAUSSIAN"]=>
    int(5)
  }
  ["__value"]=>
  int(0)
}