--TEST--
Cairo->getMiterLimit() method
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

$context->setMiterLimit(1);
var_dump($context->getMiterLimit());

/* wrong params */
try {
    $context->getMiterLimit('foobar');
    trigger_error('Cairo->getMiterLimit() expects no params');
} 
catch (TypeError $ex) {
	echo $ex->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Surface\Image)#%d (0) {
}
object(Cairo\Context)#%d (0) {
}
float(1)
Cairo\Context::getMiterLimit() expects exactly 0 parameters, 1 given