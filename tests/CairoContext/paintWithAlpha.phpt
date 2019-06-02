--TEST--
Cairo\Context->paintWithAlpha() method
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

$context->paintWithAlpha(0);

/* Wrong number args */
try {
    $context->paintWithAlpha();
    trigger_error('paintWithAlpha requires 1 arg');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args */
try {
    $context->paintWithAlpha(1, 1);
    trigger_error('paintWithAlpha requires only 1 arg');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type */
try {
    $context->paintWithAlpha(array());
    trigger_error('paintWithAlpha requires double');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Surface\Image)#%d (0) {
}
object(Cairo\Context)#%d (0) {
}
Cairo\Context::paintWithAlpha() expects exactly 1 parameter, 0 given
Cairo\Context::paintWithAlpha() expects exactly 1 parameter, 2 given
Cairo\Context::paintWithAlpha() expects parameter 1 to be float, array given