--TEST--
Cairo\Context->setFontSize() method
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

$context->setFontSize(15);

$context->setFontMatrix(new Cairo\Matrix(5, 5));

$context->setFontSize(10);

/* Wrong number args */
try {
    $context->setFontSize();
    trigger_error('setFontSize requires at least one arg');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - too many */
try {
    $context->setFontSize(15, 1);
    trigger_error('setFontSize requires only one arg');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type - double */
try {
    $context->setFontSize(array());
    trigger_error('setFontSize requires a double');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

die; // bogus memleak report - GC bug - is getting REALLY annoying
?>
--EXPECTF--
object(Cairo\Surface\Image)#%d (0) {
}
object(Cairo\Context)#%d (0) {
}
Cairo\Context::setFontSize() expects exactly 1 parameter, 0 given
Cairo\Context::setFontSize() expects exactly 1 parameter, 2 given
Cairo\Context::setFontSize() expects parameter 1 to be float, array given
