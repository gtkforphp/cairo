--TEST--
Cairo\Rectangle create/destroy handlers
--EXTENSIONS--
eos_datastructures
--SKIPIF--
<?php
include __DIR__ . '/../../skipif.inc';
?>
--FILE--
<?php
use Cairo\Rectangle;

$rect = new Rectangle();
unset($rect);

class neo extends Rectangle{
    public $x = 1;
    public $y = 2;
}

$mr_andersen = new neo();
var_dump($mr_andersen);
?>
--EXPECTF--
object(neo)#%d (4) {
  ["x"]=>
  int(1)
  ["y"]=>
  int(2)
  ["width"]=>
  int(0)
  ["height"]=>
  int(0)
}