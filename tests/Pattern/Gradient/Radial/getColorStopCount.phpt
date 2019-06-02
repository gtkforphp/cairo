--TEST--
Cairo\Pattern\Gradient->getColorStopCount() method
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

$red = 0.8;
$green = 0.6;
$blue = 0.5;
$alpha = 0.2;

var_dump($pattern->getColorStopCount());
$pattern->addColorStopRgba(0.2, $red, $green, $blue, $alpha);
$pattern->addColorStopRgba(0.4, $red, $green, $blue, $alpha);
$pattern->addColorStopRgba(0.6, $red, $green, $blue, $alpha);
var_dump($pattern->getColorStopCount());

/* Total number of args needed = 0 */
try {
    $pattern->getColorStopCount(1);
    trigger_error('getColorStopCount with too many args');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECT--
long(0)
long(3)
Cairo\Pattern\Gradient::getColorStopCount() expects exactly 0 parameters, 1 given