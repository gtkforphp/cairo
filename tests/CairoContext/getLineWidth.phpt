--TEST--
Cairo\Context->getLineWidth() method
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
	$context->getLineWidth(1);
	trigger_error('Cairo\Context->getLineWidth() expects 1 param');
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
Cairo\Context::getLineWidth() expects exactly 0 parameters, 1 given