--TEST--
Cairo\Rectangle get_properties handler
--EXTENSIONS--
eos_datastructures
--SKIPIF--
<?php
include __DIR__ . '/../../skipif.inc';
?>
--FILE--
<?php
use Cairo\Rectangle;

$rect = new Rectangle(6, 5, 4, 3);
var_dump($rect);
print_r($rect);

?>
--EXPECTF--
object(Cairo\Rectangle)#%d (4) {
  ["x"]=>
  int(6)
  ["y"]=>
  int(5)
  ["width"]=>
  int(4)
  ["height"]=>
  int(3)
}
Cairo\Rectangle Object
(
    [x] => 6
    [y] => 5
    [width] => 4
    [height] => 3
)
