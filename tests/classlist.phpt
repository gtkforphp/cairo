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
array(6) {
  [0]=>
  string(15) "Cairo\Exception"
  [1]=>
  string(12) "Cairo\Status"
  [2]=>
  string(12) "Cairo\Matrix"
  [3]=>
  string(18) "Cairo\Pattern\Type"
  [4]=>
  string(12) "Cairo\Extend"
  [5]=>
  string(12) "Cairo\Filter"
}
