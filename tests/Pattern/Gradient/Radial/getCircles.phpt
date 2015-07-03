--TEST--
Cairo\Pattern\Gradient\Radial->getCircles() method
--EXTENSIONS--
eos_datastructures
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
?>
--FILE--
<?php
use Cairo\Pattern\Gradient\Radial;

$pattern = new Radial(0.5, 0.5, 0.25, 0.5, 0.5, 0.5);
var_dump($pattern);

var_dump($pattern->getCircles());

/* Total number of args needed = 0 */
try {
    $pattern->getCircles(1);
    trigger_error('getCircles with too many args');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Pattern\Gradient\Radial)#%d (0) {
}
array(6) {
  ["x0"]=>
  float(0.5)
  ["y0"]=>
  float(0.5)
  ["r0"]=>
  float(0.25)
  ["x1"]=>
  float(0.5)
  ["y1"]=>
  float(0.5)
  ["r1"]=>
  float(0.5)
}
Cairo\Pattern\Gradient\Radial::getCircles() expects exactly 0 parameters, 1 given