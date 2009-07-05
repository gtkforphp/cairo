--TEST--
CairoContext->getOperator() function
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

try {
    $context->getOperator(1);
    trigger_error('CairoContext->getOperator expects 0 parameters.');
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
CairoContext::getOperator() expects exactly 0 parameters, 1 given