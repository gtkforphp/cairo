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
    long(0)
    ["GOOD"]=>
    long(1)
    ["BEST"]=>
    long(2)
    ["NEAREST"]=>
    long(3)
    ["BILINEAR"]=>
    long(4)
    ["GAUSSIAN"]=>
    long(5)
  }
  ["__value"]=>
  long(0)
}