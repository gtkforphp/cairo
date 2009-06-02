--TEST--
CairoRadialGradient->getCircles() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$pattern = new CairoRadialGradient(0.5, 0.5, 0.25, 0.5, 0.5, 0.5);
var_dump($pattern);

var_dump($pattern->getCircles());
?>
--EXPECTF--
object(CairoRadialGradient)#%d (0) {
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