--TEST--
CairoContext->setLineWidth() method
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
    $context->setLineWidth();
    trigger_error('CairoContext->setLineWidth() expects 1 param');
} 
catch (CairoException $ex) {
	echo $ex->getMessage(), PHP_EOL;
}
try {
	$context->setLineWidth(1,1);
	trigger_error('CairoContext->setLineWidth() expects 1 param');
} 
catch (CairoException $ex) {
	echo $ex->getMessage(), PHP_EOL;
}

/* wrong types */
try {
    $context->setLineWidth(array());
    trigger_error('CairoContext->setLineWidth() expects a double');
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
CairoContext::setLineWidth() expects exactly 1 parameter, 0 given
CairoContext::setLineWidth() expects exactly 1 parameter, 2 given
CairoContext::setLineWidth() expects parameter 1 to be double, array given