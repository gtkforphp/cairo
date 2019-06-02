--TEST--
Cairo\Context->newPath() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$surface = new Cairo\Surface\Image(Cairo\Surface\ImageFormat::ARGB32, 50, 50);
var_dump($surface);

$context = new Cairo\Context($surface);
var_dump($context);

$context->lineTo(5, 5);
var_dump($context->getCurrentPoint());

$context->newPath();
var_dump($context->getCurrentPoint());

/* Wrong number args - expects 0 */
try {
    $context->newPath('foo');
    trigger_error('newPath requires 0 args');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Surface\Image)#%d (0) {
}
object(Cairo\Context)#%d (0) {
}
array(2) {
  [0]=>
  float(5)
  [1]=>
  float(5)
}
array(2) {
  [0]=>
  float(0)
  [1]=>
  float(0)
}
Cairo\Context::newPath() expects exactly 0 parameters, 1 given