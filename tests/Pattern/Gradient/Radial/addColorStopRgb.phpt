--TEST--
Cairo\Pattern\Gradient->addColorStopRgb() method
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

$pattern->addColorStopRgb(0.2, 0.8, 0.6, 0.5);
var_dump($pattern->getColorStopRgba(0));

/* Total number of args needed = 4 */
try {
    $pattern->addColorStopRgb();
    trigger_error('addColorStopRgb with no args');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
try {
    $pattern->addColorStopRgb(1);
    trigger_error('addColorStopRgb with 1 arg');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
try {
    $pattern->addColorStopRgb(1, 1);
    trigger_error('addColorStopRgb with 2 args');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
try {
    $pattern->addColorStopRgb(1, 1, 1);
    trigger_error('addColorStopRgb with 3 args');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
try {
    $pattern->addColorStopRgb(1, 1, 1, 1, 1);
    trigger_error('addColorStopRgb with too many args');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* All 4 args must be double/float or castable to double/float */
try {
    $pattern->addColorStopRgb(array(), 1, 1, 1);
    trigger_error('Arg 1 must be double');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
try {
    $pattern->addColorStopRgb(1, array(), 1, 1);
    trigger_error('Arg 2 must be double');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
try {
    $pattern->addColorStopRgb(1, 1, array(), 1);
    trigger_error('Arg 3 must be double');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
try {
    $pattern->addColorStopRgb(1, 1, 1, array());
    trigger_error('Arg 4 must be double');
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
  float(1)
}
Cairo\Pattern\Gradient::addColorStopRgb() expects exactly 4 parameters, 0 given
Cairo\Pattern\Gradient::addColorStopRgb() expects exactly 4 parameters, 1 given
Cairo\Pattern\Gradient::addColorStopRgb() expects exactly 4 parameters, 2 given
Cairo\Pattern\Gradient::addColorStopRgb() expects exactly 4 parameters, 3 given
Cairo\Pattern\Gradient::addColorStopRgb() expects exactly 4 parameters, 5 given
Cairo\Pattern\Gradient::addColorStopRgb() expects parameter 1 to be float, array given
Cairo\Pattern\Gradient::addColorStopRgb() expects parameter 2 to be float, array given
Cairo\Pattern\Gradient::addColorStopRgb() expects parameter 3 to be float, array given
Cairo\Pattern\Gradient::addColorStopRgb() expects parameter 4 to be float, array given