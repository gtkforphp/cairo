--TEST--
Cairo\Context->getAntialias() method
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

var_dump($context->getAntialias());

/* Wrong number args */
try {
    $context->getAntialias('foobar');
    trigger_error('getAntialias requires no args');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Surface\Image)#%d (0) {
}
object(Cairo\Context)#%d (0) {
}
long(0)
Cairo\Context::getAntialias() expects exactly 0 parameters, 1 given