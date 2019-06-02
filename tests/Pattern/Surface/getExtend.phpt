--TEST--
Cairo\Pattern\Surface->getExtend()
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
?>
--FILE--
<?php
$surface = new Cairo\Surface\Image(Cairo\Surface\ImageFormat::ARGB32, 50, 50);
var_dump($surface);

$pattern = new Cairo\Pattern\Surface($surface);
var_dump($pattern);

$extend = $pattern->getExtend();
var_dump($extend);
var_dump($extend == Cairo\Extend::NONE);

/* Total number of args needed = 0 */
try {
    $pattern->getExtend(1);
    trigger_error('getExtend with too many args');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Surface\Image)#%d (0) {
}
object(Cairo\Pattern\Surface)#%d (0) {
}
object(Cairo\Extend)#%d (2) {
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
  long(0)
}
bool(true)
Cairo\Pattern::getExtend() expects exactly 0 parameters, 1 given