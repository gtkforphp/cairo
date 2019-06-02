--TEST--
Cairo\Context->setAntialias() method
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

$context->setAntialias(Cairo\Antialias::MODE_GRAY);
var_dump($context->getAntialias());

/* Wrong number args - 1 */
try {
    $context->setAntialias(1, 1);
    trigger_error('setAntialias requires 0 or 1 args');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong args */
try {
    $context->setAntialias(array());
    trigger_error('setAntialias requires int');
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
Cairo\Context::setAntialias() expects at most 1 parameter, 2 given
Cairo\Context::setAntialias() expects parameter 1 to be int, array given