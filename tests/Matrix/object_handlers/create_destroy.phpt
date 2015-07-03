--TEST--
Cairo\Matrix create/destroy handlers
--EXTENSIONS--
eos_datastructures
--SKIPIF--
<?php
include __DIR__ . '/../../skipif.inc';
?>
--FILE--
<?php
use Cairo\Matrix;

$matrix = new Matrix();
unset($matrix);

class neo extends Matrix{
    public $xx = 8;
    public $xy = 5;
}

$mr_andersen = new neo();
var_dump($mr_andersen);
?>
--EXPECTF--
object(neo)#%d (6) {
  ["xx"]=>
  float(8)
  ["xy"]=>
  float(5)
  ["x0"]=>
  float(0)
  ["yx"]=>
  float(0)
  ["yy"]=>
  float(0)
  ["y0"]=>
  float(0)
}