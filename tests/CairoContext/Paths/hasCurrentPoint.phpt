--TEST--
Cairo\Context->hasCurrentPoint() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!method_exists('Cairo\Context', 'hasCurrentPoint')) die('skip - Cairo\Context->hasCurrentPoint not available');
?>
--FILE--
<?php
$surface = new Cairo\Surface\Image(Cairo\Surface\ImageFormat::ARGB32, 50, 50);
var_dump($surface);

$context = new Cairo\Context($surface);
var_dump($context);

var_dump($context->hasCurrentPoint());

/* Wrong number args - expects 0 */
try {
    $context->hasCurrentPoint('foo');
    trigger_error('hasCurrentPoint requires 0 args');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Surface\Image)#%d (0) {
}
object(Cairo\Context)#%d (0) {
}
bool(false)
Cairo\Context::hasCurrentPoint() expects exactly 0 parameters, 1 given