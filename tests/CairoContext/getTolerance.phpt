--TEST--
Cairo\Context->getTolerance() function
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

$context->setTolerance(1);
var_dump($context->getTolerance());

try {
    $context->getTolerance(1);
    trigger_error('Cairo\Context->getTolerance expects 0 parameters.');
} 
catch (TypeError $ex) {
	echo $ex->getMessage(), PHP_EOL;
}

?>
--EXPECTF--
object(Cairo\Surface\Image)#1 (0) {
}
object(Cairo\Context)#2 (0) {
}
float(1)
Cairo\Context::getTolerance() expects exactly 0 parameters, 1 given