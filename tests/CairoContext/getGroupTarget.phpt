--TEST--
Cairo\Context->getGroupTarget() method
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

$surface2 = $context->getGroupTarget();
var_dump($surface2);
var_dump($surface2 == $surface);

/* wrong params */
/* wrong params */
try {
	$context->getGroupTarget(1);
	trigger_error('getGroupTarget() expects 0 params');	
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
object(Cairo\Surface\Image)#%d (0) {
}
bool(true)
Cairo\Context::getGroupTarget() expects exactly 0 parameters, 1 given