--TEST--
cairo_pattern_get_linear_points function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$pattern = cairo_pattern_create_linear(1,2,3,4);
var_dump($pattern);

var_dump(cairo_pattern_get_linear_points($pattern));
?>
--EXPECTF--
object(CairoLinearGradient)#%d (0) {
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