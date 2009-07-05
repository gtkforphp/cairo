--TEST--
CairoContext->setTolerance() method
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

$context->setTolerance(1);
var_dump($context->getOperator());


/* wrong params */
try {
	$context->setTolerance();
	trigger_error('CairoContext->setTolerance() expects 1 param');
} 
catch (CairoException $ex) {
	echo $ex->getMessage(), PHP_EOL;
}
try {
	$context->setOperator(1, 1);
	trigger_error('CairoContext->setTolerance() expects 1 param');
} 
catch (CairoException $ex) {
	echo $ex->getMessage(), PHP_EOL;
}

/* wrong type */
try {
	$context->setOperator(array());
	trigger_error('CairoContext->setTolerance() expects param 1 to be double');
} 
catch (CairoException $ex) {
	echo $ex->getMessage(), PHP_EOL;
}

?>
--EXPECTF--
object(CairoImageSurface)#1 (0) {
}
object(CairoContext)#2 (0) {
}
int(2)
CairoContext::setTolerance() expects exactly 1 parameter, 0 given
CairoContext::setOperator() expects exactly 1 parameter, 2 given
CairoContext::setOperator() expects parameter 1 to be long, array given