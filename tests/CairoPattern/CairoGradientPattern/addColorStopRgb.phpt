--TEST--
CairoGradient->addColorStopRgb() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$red = 0.8;
$green = 0.6;
$blue = 0.5;

$pattern = new CairoLinearGradient(1, 2, 3, 4);
var_dump($pattern);

$pattern->addColorStopRgb(0.2, $red, $green, $blue);
var_dump($pattern->getColorStopRgba(0));
?>
--EXPECTF--
object(CairoLinearGradient)#%d (0) {
}
array(4) {
  ["red"]=>
  float(0.8%A)
  ["green"]=>
  float(0.6%A)
  ["blue"]=>
  float(0.5%A)
  ["alpha"]=>
  float(1)
}