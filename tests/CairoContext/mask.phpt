--TEST--
Cairo\Context->mask() function
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

$pattern = new Cairo\Pattern\Solid(0.3, 0.3, 0.3);
$context->mask($pattern);

/* wrong params */
try {
    $context->mask();
    trigger_error('Wrong params');
} 
catch (TypeError $ex) {
	echo $ex->getMessage(), PHP_EOL;
}
try {
    $context->mask($pattern, 1);
    trigger_error('Wrong params');
} 
catch (TypeError $ex) {
	echo $ex->getMessage(), PHP_EOL;
}

/* wrong type */
try {
	$context->mask(array());
	trigger_error('Wrong type');
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
Cairo\Context::mask() expects exactly 1 parameter, 0 given
Cairo\Context::mask() expects exactly 1 parameter, 2 given
Cairo\Context::mask() expects parameter 1 to be CairoPattern, array given