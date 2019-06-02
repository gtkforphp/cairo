--TEST--
Cairo\Context->scale() method
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

$context->scale(5, 5);

/* Wrong number args - expects 2 */
try {
    $context->scale();
    trigger_error('scale requires 2 args');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - expects 2 */
try {
    $context->scale(1);
    trigger_error('scale requires 2 args');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - expects 2 */
try {
    $context->scale(1,1,1);
    trigger_error('scale requires 2 args');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type, wants double, double */
try {
    $context->scale(array(), 1);
    trigger_error('scale requires double, double');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type, wants double, double */
try {
    $context->scale(1, array());
    trigger_error('scale requires double, double');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Surface\Image)#%d (0) {
}
object(Cairo\Context)#%d (0) {
}
Cairo\Context::scale() expects exactly 2 parameters, 0 given
Cairo\Context::scale() expects exactly 2 parameters, 1 given
Cairo\Context::scale() expects exactly 2 parameters, 3 given
Cairo\Context::scale() expects parameter 1 to be float, array given
Cairo\Context::scale() expects parameter 2 to be float, array given