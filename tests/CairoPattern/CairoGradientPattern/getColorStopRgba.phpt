--TEST--
CairoGradient->getColorStopRgba() method
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

/* Total number of args needed = 1 */
try {
    $pattern->getColorStopRgba();
    trigger_error('getColorStopRgba with no args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
try {
    $pattern->getColorStopRgba(1, 1);
    trigger_error('getColorStopRgba with too many args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* arg must be int or castable to int */
try {
    $pattern->getColorStopRgba(array());
    trigger_error('Arg 1 must be int');
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
CairoGradientPattern::getColorStopRgba() expects exactly 1 parameter, 0 given
CairoGradientPattern::getColorStopRgba() expects exactly 1 parameter, 2 given
CairoGradientPattern::getColorStopRgba() expects parameter 1 to be long, array given