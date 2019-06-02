--TEST--
Cairo\Context->setLineCap() method
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

$context->setLineCap(Cairo\LineCap::SQUARE);
var_dump($context->getLineCap());

/* Wrong number args - 1 */
try {
    $context->setLineCap();
    trigger_error('setLineCap requires 1 arg');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 2 */
try {
    $context->setLineCap(1, 1);
    trigger_error('setLineCap requires only 1 arg');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong args */
try {
    $context->setLineCap(array());
    trigger_error('setLineCap requires int');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Surface\Image)#%d (0) {
}
object(Cairo\Context)#%d (0) {
}
long(2)
Cairo\Context::setLineCap() expects exactly 1 parameter, 0 given
Cairo\Context::setLineCap() expects exactly 1 parameter, 2 given
Cairo\Context::setLineCap() expects parameter 1 to be int, array given