--TEST--
CairoGradient->addColorStopRgb() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$pattern = new CairoLinearGradient(1, 2, 3, 4);
var_dump($pattern);

$pattern->addColorStopRgb(0.2, 0.8, 0.6, 0.5);
var_dump($pattern->getColorStopRgba(0));

/* Total number of args needed = 4 */
try {
    $pattern->addColorStopRgb();
    trigger_error('addColorStopRgb with no args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
try {
    $pattern->addColorStopRgb(1);
    trigger_error('addColorStopRgb with 1 arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
try {
    $pattern->addColorStopRgb(1, 1);
    trigger_error('addColorStopRgb with 2 args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
try {
    $pattern->addColorStopRgb(1, 1, 1);
    trigger_error('addColorStopRgb with 3 args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
try {
    $pattern->addColorStopRgb(1, 1, 1, 1, 1);
    trigger_error('addColorStopRgb with too many args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* All 4 args must be double/float or castable to double/float */
try {
    $pattern->addColorStopRgb(array(), 1, 1, 1);
    trigger_error('Arg 1 must be double');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
try {
    $pattern->addColorStopRgb(1, array(), 1, 1);
    trigger_error('Arg 2 must be double');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
try {
    $pattern->addColorStopRgb(1, 1, array(), 1);
    trigger_error('Arg 3 must be double');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
try {
    $pattern->addColorStopRgb(1, 1, 1, array());
    trigger_error('Arg 4 must be double');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
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
CairoGradientPattern::addColorStopRgb() expects exactly 4 parameters, 0 given
CairoGradientPattern::addColorStopRgb() expects exactly 4 parameters, 1 given
CairoGradientPattern::addColorStopRgb() expects exactly 4 parameters, 2 given
CairoGradientPattern::addColorStopRgb() expects exactly 4 parameters, 3 given
CairoGradientPattern::addColorStopRgb() expects exactly 4 parameters, 5 given
CairoGradientPattern::addColorStopRgb() expects parameter 1 to be double, array given
CairoGradientPattern::addColorStopRgb() expects parameter 2 to be double, array given
CairoGradientPattern::addColorStopRgb() expects parameter 3 to be double, array given
CairoGradientPattern::addColorStopRgb() expects parameter 4 to be double, array given