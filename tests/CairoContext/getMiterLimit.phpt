--TEST--
Cairo->getMiterLimit() method
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

$context->setMiterLimit(1);
var_dump($context->getMiterLimit());

/* wrong params */
try {
    $context->getMiterLimit('foobar');
    trigger_error('Cairo->getMiterLimit() expects no params');
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
CairoContext::getMiterLimit() expects exactly 0 parameters, 1 given