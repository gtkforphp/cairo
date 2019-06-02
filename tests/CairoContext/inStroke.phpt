--TEST--
Cairo\Context->inStroke() method
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

var_dump($context->inStroke(1, 1));

/* Wrong number args */
try {
    $context->inStroke();
    trigger_error('inStroke requires 2 args');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args */
try {
    $context->inStroke(1);
    trigger_error('inStroke requires 2 args');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args */
try {
    $context->inStroke(1, 1, 1);
    trigger_error('inStroke requires only 2 args');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type*/
try {
    $context->inStroke(array(), 1);
    trigger_error('inStroke requires double for arg 1');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type*/
try {
    $context->inStroke(1, array());
    trigger_error('inStroke requires double for arg 2');
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
Cairo\Context::inStroke() expects exactly 2 parameters, 0 given
Cairo\Context::inStroke() expects exactly 2 parameters, 1 given
Cairo\Context::inStroke() expects exactly 2 parameters, 3 given
Cairo\Context::inStroke() expects parameter 1 to be float, array given
Cairo\Context::inStroke() expects parameter 2 to be float, array given