--TEST--
Cairo\Pattern->setExtend() method [using Surface]
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
?>
--FILE--
<?php
use Cairo\Surface\Image;
use Cairo\Pattern\Surface;

$surface = new Image(Cairo\Surface\ImageFormat::ARGB32, 50, 50);
var_dump($surface);

$pattern = new Surface($surface);
var_dump($pattern);

$pattern->setExtend(Cairo\Extend::PAD);

$extend = $pattern->getExtend();
var_dump($extend);
var_dump($extend == Cairo\Extend::PAD);

/* Total number of args needed = 1 */
try {
    $pattern->setExtend();
    trigger_error('setExtend with no args');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
try {
    $pattern->setExtend(1, 1);
    trigger_error('setExtend with too many args');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* arg must be int or castable to int */
try {
    $pattern->setExtend(array());
    trigger_error('Arg 1 must be int');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Surface\Image)#%d (0) {
}
object(Cairo\Pattern\Surface)#%d (0) {
}
object(Cairo\Extend)#3 (2) {
  ["__elements"]=>
  array(4) {
    ["NONE"]=>
    long(0)
    ["REPEAT"]=>
    long(1)
    ["REFLECT"]=>
    long(2)
    ["PAD"]=>
    long(3)
  }
  ["__value"]=>
  long(3)
}
bool(true)
Cairo\Pattern::setExtend() expects exactly 1 parameter, 0 given
Cairo\Pattern::setExtend() expects exactly 1 parameter, 2 given
Cairo\Pattern::setExtend() expects parameter 1 to be int, array given