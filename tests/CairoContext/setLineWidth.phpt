--TEST--
Cairo\Context->setLineWidth() method
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

$context->setLineWidth(1);
var_dump($context->getLineWidth());

/* wrong params */
try {
    $context->setLineWidth();
    trigger_error('Cairo\Context->setLineWidth() expects 1 param');
} 
catch (TypeError $ex) {
	echo $ex->getMessage(), PHP_EOL;
}
try {
	$context->setLineWidth(1,1);
	trigger_error('Cairo\Context->setLineWidth() expects 1 param');
} 
catch (TypeError $ex) {
	echo $ex->getMessage(), PHP_EOL;
}

/* wrong types */
try {
    $context->setLineWidth(array());
    trigger_error('Cairo\Context->setLineWidth() expects a double');
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
Cairo\Context::setLineWidth() expects exactly 1 parameter, 0 given
Cairo\Context::setLineWidth() expects exactly 1 parameter, 2 given
Cairo\Context::setLineWidth() expects parameter 1 to be float, array given