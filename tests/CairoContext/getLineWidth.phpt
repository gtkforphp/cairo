--TEST--
CairoContext->getLineWidth() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$surface = new CairoImageSurface(CairoFormat::ARGB32, 50, 50);
var_dump($surface);

$context = new CairoContext($surface);
var_dump($context);

$context->setLineWidth(1);
var_dump($context->getLineWidth());


/* wrong params */
try {
	$context->getLineWidth(1);
	trigger_error('CairoContext->getLineWidth() expects 1 param');
} 
catch (CairoException $ex) {
	echo $ex->getMessage(), PHP_EOL;
}

?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
float(1)
CairoContext::getLineWidth() expects exactly 0 parameters, 1 given