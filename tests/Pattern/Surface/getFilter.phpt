--TEST--
Cairo\Pattern\Surface->getFilter()
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

$pattern->setFilter(Cairo\Filter::GOOD);
$filter = $pattern->getFilter();
var_dump($filter);
var_dump($filter == Cairo\Filter::GOOD);

/* Total number of args needed = 0 */
try {
    $pattern->getFilter(1);
    trigger_error('getFilter with too many args');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Surface\Image)#%d (0) {
}
object(Cairo\Pattern\Surface)#%d (0) {
}
object(Cairo\Filter)#%d (2) {
  ["__elements"]=>
  array(6) {
    ["FAST"]=>
    int(0)
    ["GOOD"]=>
    int(1)
    ["BEST"]=>
    int(2)
    ["NEAREST"]=>
    int(3)
    ["BILINEAR"]=>
    int(4)
    ["GAUSSIAN"]=>
    int(5)
  }
  ["__value"]=>
  int(1)
}
bool(true)
Cairo\Pattern::getFilter() expects exactly 0 parameters, 1 given