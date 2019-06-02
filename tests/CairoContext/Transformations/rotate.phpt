--TEST--
Cairo\Context->rotate() method
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

$context->rotate(5);

/* Wrong number args - expects 1 */
try {
    $context->rotate();
    trigger_error('rotate requires 1 arg');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - expects 1 */
try {
    $context->rotate(1,1);
    trigger_error('rotate requires 1 arg');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type, wants double */
try {
    $context->rotate(array());
    trigger_error('rotate requires double');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Surface\Image)#%d (0) {
}
object(Cairo\Context)#%d (0) {
}
Cairo\Context::rotate() expects exactly 1 parameter, 0 given
Cairo\Context::rotate() expects exactly 1 parameter, 2 given
Cairo\Context::rotate() expects parameter 1 to be float, array given