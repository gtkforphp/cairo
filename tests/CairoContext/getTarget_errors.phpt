--TEST--
Cairo\Context->getTarget() error conditions
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

try {
	$context->getTarget('foobar');
	echo 'Exception not thrown properly';
} catch (TypeError $e) {
	echo $e->getMessage();
}
?>
--EXPECTF--
object(Cairo\Surface\Image)#%d (0) {
}
object(Cairo\Context)#%d (0) {
}
Cairo\Context::getTarget() expects exactly 0 parameters, 1 given