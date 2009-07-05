--TEST--
CairoContext->mask() function
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

$pattern = new CairoSolidPattern(0.3, 0.3, 0.3);
$context->mask($pattern);

/* wrong params */
try {
    $context->mask();
    trigger_error('Wrong params');
} 
catch (CairoException $ex) {
	echo $ex->getMessage(), PHP_EOL;
}
try {
    $context->mask($pattern, 1);
    trigger_error('Wrong params');
} 
catch (CairoException $ex) {
	echo $ex->getMessage(), PHP_EOL;
}

/* wrong type */
try {
	$context->mask(array());
	trigger_error('Wrong type');
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
CairoContext::mask() expects exactly 1 parameter, 0 given
CairoContext::mask() expects exactly 1 parameter, 2 given
CairoContext::mask() expects parameter 1 to be CairoPattern, array given