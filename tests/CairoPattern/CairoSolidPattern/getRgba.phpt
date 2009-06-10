--TEST--
CairoSolidPattern->getRgba() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$red = 0.8;
$green = 0.6;
$blue = 0.5;
$alpha = 0.7;

$pattern = new CairoSolidPattern($red, $green, $blue, $alpha);
var_dump($pattern);

$values =$pattern->getRgba();
var_dump($values);
var_dump($red === $values['red']);
var_dump($green === $values['green']);
var_dump($blue === $values['blue']);
var_dump($alpha === $values['alpha']);

/* Total number of args needed = 0 */
try {
    $pattern->getRgba(1);
    trigger_error('getRgba with too many args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoSolidPattern)#%d (0) {
}
array(4) {
  ["red"]=>
  float(0.8)
  ["green"]=>
  float(0.6)
  ["blue"]=>
  float(0.5)
  ["alpha"]=>
  float(0.7)
}
bool(true)
bool(true)
bool(true)
bool(true)
CairoSolidPattern::getRgba() expects exactly 0 parameters, 1 given