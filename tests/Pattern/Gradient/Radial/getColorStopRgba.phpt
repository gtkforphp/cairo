--TEST--
Cairo\Pattern\Gradient->getColorStopRgba() method
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

$pattern->addColorStopRgba(0.2, 0.8, 0.6, 0.5, 0.2);
var_dump($pattern->getColorStopRgba(0));

/* Total number of args needed = 1 */
try {
    $pattern->getColorStopRgba();
    trigger_error('getColorStopRgba with no args');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
try {
    $pattern->getColorStopRgba(1, 1);
    trigger_error('getColorStopRgba with too many args');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* arg must be int or castable to int */
try {
    $pattern->getColorStopRgba(array());
    trigger_error('Arg 1 must be int');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECT--
array(4) {
  ["red"]=>
  float(0.8)
  ["green"]=>
  float(0.6)
  ["blue"]=>
  float(0.5)
  ["alpha"]=>
  float(0.2)
}
Cairo\Pattern\Gradient::getColorStopRgba() expects exactly 1 parameter, 0 given
Cairo\Pattern\Gradient::getColorStopRgba() expects exactly 1 parameter, 2 given
Cairo\Pattern\Gradient::getColorStopRgba() expects parameter 1 to be int, array given