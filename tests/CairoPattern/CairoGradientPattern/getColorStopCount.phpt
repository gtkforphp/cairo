--TEST--
CairoGradient->getColorStopCount() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$red = 0.8;
$green = 0.6;
$blue = 0.5;
$alpha = 0.2;

$pattern = new CairoLinearGradient(1, 2, 3, 4);
var_dump($pattern);

var_dump($pattern->getColorStopCount());
$pattern->addColorStopRgba(0.2, $red, $green, $blue, $alpha);
$pattern->addColorStopRgba(0.4, $red, $green, $blue, $alpha);
$pattern->addColorStopRgba(0.6, $red, $green, $blue, $alpha);
var_dump($pattern->getColorStopCount());
?>
--EXPECTF--
object(CairoLinearGradient)#%d (0) {
}
int(0)
int(3)