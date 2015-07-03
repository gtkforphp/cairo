--TEST--
cairo class listing
--EXTENSIONS--
eos_datastructures
--SKIPIF--
<?php
include __DIR__ . '/skipif.inc';
?>
--FILE--
<?php
$ext = new ReflectionExtension('cairo');
var_dump($ext->getClassNames());
?>
--EXPECT--
array(14) {
  [0]=>
  string(15) "Cairo\Exception"
  [1]=>
  string(12) "Cairo\Status"
  [2]=>
  string(12) "Cairo\Matrix"
  [3]=>
  string(13) "Cairo\Pattern"
  [4]=>
  string(19) "Cairo\Pattern\Solid"
  [5]=>
  string(22) "Cairo\Pattern\Gradient"
  [6]=>
  string(29) "Cairo\Pattern\Gradient\Radial"
  [7]=>
  string(29) "Cairo\Pattern\Gradient\Linear"
  [8]=>
  string(21) "Cairo\Pattern\Surface"
  [9]=>
  string(18) "Cairo\Pattern\Mesh"
  [10]=>
  string(26) "Cairo\Pattern\RasterSource"
  [11]=>
  string(18) "Cairo\Pattern\Type"
  [12]=>
  string(12) "Cairo\Extend"
  [13]=>
  string(12) "Cairo\Filter"
}
