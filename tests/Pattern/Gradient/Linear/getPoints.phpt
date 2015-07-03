--TEST--
Cairo\Pattern\Gradient\Linear->getPoints() method
--EXTENSIONS--
eos_datastructures
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
?>
--FILE--
<?php
use Cairo\Pattern\Gradient\Linear;

$pattern = new Linear(1,2,3,4);
var_dump($pattern);

var_dump($pattern->getPoints());

/* Total number of args needed = 0 */
try {
    $pattern->getPoints(1);
    trigger_error('getPoints with too many args');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Pattern\Gradient\Linear)#%d (0) {
}
array(4) {
  ["x0"]=>
  float(1)
  ["y0"]=>
  float(2)
  ["x1"]=>
  float(3)
  ["y1"]=>
  float(4)
}
Cairo\Pattern\Gradient\Linear::getPoints() expects exactly 0 parameters, 1 given