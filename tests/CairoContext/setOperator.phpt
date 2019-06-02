--TEST--
Cairo\Context->setOperator() method
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


/* wrong params */
try {
	$context->setOperator();
	trigger_error('Cairo\Context->setOperator() expects 1 param');
} 
catch (TypeError $ex) {
	echo $ex->getMessage(), PHP_EOL;
}
try {
	$context->setOperator(CAIRO_FORMAT_ARGB32, 1);
	trigger_error('Cairo\Context->setOperator() expects 1 param');
} 
catch (TypeError $ex) {
	echo $ex->getMessage(), PHP_EOL;
}

/* wrong type */
try {
	$context->setOperator(array());
	trigger_error('Cairo\Context->setOperator() expects 1 param');
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
Cairo\Context::setOperator() expects exactly 1 parameter, 0 given
Cairo\Context::setOperator() expects exactly 1 parameter, 2 given
Cairo\Context::setOperator() expects parameter 1 to be int, array given