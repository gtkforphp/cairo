--TEST--
CairoGradient->addColorStopRgba() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$pattern = new CairoLinearGradient(1, 2, 3, 4);
var_dump($pattern);

$pattern->addColorStopRgba(0.2, 0.8, 0.6, 0.5, 0.2);
var_dump($pattern->getColorStopRgba(0));

/* Total number of args needed = 5 */
try {
    $pattern->addColorStopRgba();
    trigger_error('addColorStopRgba with no args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
try {
    $pattern->addColorStopRgba(1);
    trigger_error('addColorStopRgba with 1 arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
try {
    $pattern->addColorStopRgba(1, 1);
    trigger_error('addColorStopRgba with 2 args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
try {
    $pattern->addColorStopRgba(1, 1, 1);
    trigger_error('addColorStopRgba with 3 args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
try {
    $pattern->addColorStopRgba(1, 1, 1, 1);
    trigger_error('addColorStopRgba with 4 args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
try {
    $pattern->addColorStopRgba(1, 1, 1, 1, 1, 1);
    trigger_error('addColorStopRgba with too many args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* All 5 args must be double/float or castable to double/float */
try {
    $pattern->addColorStopRgba(array(), 1, 1, 1, 1);
    trigger_error('Arg 1 must be double');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
try {
    $pattern->addColorStopRgba(1, array(), 1, 1, 1);
    trigger_error('Arg 2 must be double');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
try {
    $pattern->addColorStopRgba(1, 1, array(), 1, 1);
    trigger_error('Arg 3 must be double');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
try {
    $pattern->addColorStopRgba(1, 1, 1, array(), 1);
    trigger_error('Arg 4 must be double');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
try {
    $pattern->addColorStopRgba(1, 1, 1, 1, array());
    trigger_error('Arg 5 must be double');
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
  float(0.2%A)
}
CairoGradientPattern::addColorStopRgba() expects exactly 5 parameters, 0 given
CairoGradientPattern::addColorStopRgba() expects exactly 5 parameters, 1 given
CairoGradientPattern::addColorStopRgba() expects exactly 5 parameters, 2 given
CairoGradientPattern::addColorStopRgba() expects exactly 5 parameters, 3 given
CairoGradientPattern::addColorStopRgba() expects exactly 5 parameters, 4 given
CairoGradientPattern::addColorStopRgba() expects exactly 5 parameters, 6 given
CairoGradientPattern::addColorStopRgba() expects parameter 1 to be double, array given
CairoGradientPattern::addColorStopRgba() expects parameter 2 to be double, array given
CairoGradientPattern::addColorStopRgba() expects parameter 3 to be double, array given
CairoGradientPattern::addColorStopRgba() expects parameter 4 to be double, array given
CairoGradientPattern::addColorStopRgba() expects parameter 5 to be double, array given