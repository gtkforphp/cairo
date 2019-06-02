--TEST--
CairoContext->popGroupToSource() method
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

$context->pushGroup();
$context->popGroupToSource();

var_dump($context->getSource());

/* wrong params */
try {
	$context->popGroupToSource(1);
	trigger_error('popGroupToSource() expects 0 params');	
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
object(Cairo\SurfacePattern)#%d (0) {
}
CairoContext::popGroupToSource() expects exactly 0 parameters, 1 given