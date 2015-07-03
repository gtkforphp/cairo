--TEST--
Cairo\Rectangle->__construct() extended
--EXTENSIONS--
eos_datastructures
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
?>
--FILE--
<?php
use Cairo\Rectangle;
use Cairo\Exception;

class Bad extends Rectangle {
    public function __construct() {
    }
}

$fail = new Bad();

var_dump($fail);
?>
--EXPECTF--
object(Bad)#%d (4) {
  ["x"]=>
  int(0)
  ["y"]=>
  int(0)
  ["width"]=>
  int(0)
  ["height"]=>
  int(0)
}