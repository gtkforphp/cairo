--TEST--
Cairo\Extend class constants
--EXTENSIONS--
eos_datastructures
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
?>
--FILE--
<?php
use Cairo\Extend;

$enum = new Extend(Extend::NONE);
var_dump($enum);
?>
--EXPECTF--
object(Cairo\Extend)#%d (2) {
  ["__elements"]=>
  array(4) {
    ["NONE"]=>
    long(0)
    ["REPEAT"]=>
    long(1)
    ["REFLECT"]=>
    long(2)
    ["PAD"]=>
    long(3)
  }
  ["__value"]=>
  long(0)
}