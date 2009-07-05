--TEST--
CairoContext->getTolerance() function
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
var_dump($context->getTolerance());

try {
    $context->getTolerance(1);
    trigger_error('CairoContext->getTolerance expects 0 parameters.');
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
float(1)
CairoContext::getTolerance() expects exactly 0 parameters, 1 given