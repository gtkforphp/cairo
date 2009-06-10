--TEST--
CairoLinearGradient->getPoints() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$pattern = new CairoLinearGradient(1,2,3,4);
var_dump($pattern);

var_dump($pattern->getPoints());

/* Total number of args needed = 0 */
try {
    $pattern->getPoints(1);
    trigger_error('getPoints with too many args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoLinearGradient)#%d (0) {
}
array(4) {
  ["x0"]=>
  float(1)
  ["y0"]=>
  float(2)
  ["x1"]=>
  float(3)
  ["y1"]=>
  float(4)
}
CairoLinearGradient::getPoints() expects exactly 0 parameters, 1 given