--TEST--
CairoContext->setOperator() method
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

$context->setOperator(CAIRO_FORMAT_ARGB32);
var_dump($context->getOperator());


/* wrong params */
try {
	$context->setOperator();
	trigger_error('CairoContext->setOperator() expects 1 param');
} 
catch (CairoException $ex) {
	echo $ex->getMessage(), PHP_EOL;
}
try {
	$context->setOperator(CAIRO_FORMAT_ARGB32, 1);
	trigger_error('CairoContext->setOperator() expects 1 param');
} 
catch (CairoException $ex) {
	echo $ex->getMessage(), PHP_EOL;
}

/* wrong type */
try {
	$context->setOperator(array());
	trigger_error('CairoContext->setOperator() expects 1 param');
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
int(0)
CairoContext::setOperator() expects exactly 1 parameter, 0 given
CairoContext::setOperator() expects exactly 1 parameter, 2 given
CairoContext::setOperator() expects parameter 1 to be long, array given