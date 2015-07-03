--TEST--
cairo extension class listing
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
array(17) {
  [0]=>
  string(13) "Cairo\Pattern"
  [1]=>
  string(19) "Cairo\Pattern\Solid"
  [2]=>
  string(22) "Cairo\Pattern\Gradient"
  [3]=>
  string(29) "Cairo\Pattern\Gradient\Radial"
  [4]=>
  string(29) "Cairo\Pattern\Gradient\Linear"
  [5]=>
  string(21) "Cairo\Pattern\Surface"
  [6]=>
  string(18) "Cairo\Pattern\Mesh"
  [7]=>
  string(26) "Cairo\Pattern\RasterSource"
  [8]=>
  string(18) "Cairo\Pattern\Type"
  [9]=>
  string(12) "Cairo\Extend"
  [10]=>
  string(12) "Cairo\Filter"
  [11]=>
  string(15) "Cairo\Rectangle"
  [12]=>
  string(12) "Cairo\Matrix"
  [13]=>
  string(15) "Cairo\Exception"
  [14]=>
  string(12) "Cairo\Status"
  [15]=>
  string(12) "Cairo\Region"
  [16]=>
  string(20) "Cairo\Region\Overlap"
}
