--TEST--
cairo_pattern_get_radial_circles function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$pattern = cairo_pattern_create_radial(0.5, 0.5, 0.25, 0.5, 0.5, 0.5);
var_dump($pattern);

var_dump(cairo_pattern_get_radial_circles($pattern));
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