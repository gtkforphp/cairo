--TEST--
CairoContext->getGroupTarget() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$surface = new Cairo\Surface\Image(Cairo\Surface\ImageFormat::ARGB32, 50, 50);
var_dump($surface);

$context = new CairoContext($surface);
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
catch (CairoException $ex) {
	echo $ex->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Surface\Image)#%d (0) {
}
object(CairoContext)#%d (0) {
}
object(Cairo\Surface\Image)#%d (0) {
}
bool(true)
CairoContext::getGroupTarget() expects exactly 0 parameters, 1 given