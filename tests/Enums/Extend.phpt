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
    int(0)
    ["REPEAT"]=>
    int(1)
    ["REFLECT"]=>
    int(2)
    ["PAD"]=>
    int(3)
  }
  ["__value"]=>
  int(0)
}