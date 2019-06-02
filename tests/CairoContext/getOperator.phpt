--TEST--
Cairo\Context->getOperator() function
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

$context->setOperator(CAIRO_FORMAT_ARGB32);
var_dump($context->getOperator());

try {
    $context->getOperator(1);
    trigger_error('Cairo\Context->getOperator expects 0 parameters.');
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
long(0)
Cairo\Context::getOperator() expects exactly 0 parameters, 1 given