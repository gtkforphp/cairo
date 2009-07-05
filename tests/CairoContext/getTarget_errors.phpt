--TEST--
CairoContext->getTarget() error conditions
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

try {
	$context->getTarget('foobar');
	echo 'Exception not thrown properly';
} catch (CairoException $e) {
	echo $e->getMessage();
}
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
CairoContext::getTarget() expects exactly 0 parameters, 1 given