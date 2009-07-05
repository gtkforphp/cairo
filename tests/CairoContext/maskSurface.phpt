--TEST--
CairoContext->maskSurface() function
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

$surface2 = new CairoImageSurface(CairoFormat::ARGB32, 50, 50);
var_dump($surface2);

$context->maskSurface($surface2, 5, 1);

/* wrong params */
try {
    $context->maskSurface();
    trigger_error('maskSurface expects at least 1 param');
} 
catch (CairoException $ex) {
	echo $ex->getMessage(), PHP_EOL;
}
try {
    $context->maskSurface($surface2, 1, 1, 1);
    trigger_error('maskSurface expects at most 3 params');
} 
catch (CairoException $ex) {
	echo $ex->getMessage(), PHP_EOL;
}

/* wrong type */
try {
	$context->maskSurface(array());
	trigger_error('maskSurface arg 1 expects CairoSurface');
}
catch (CairoException $ex) {
	echo $ex->getMessage(), PHP_EOL;
}

/* wrong type */
try {
	$context->maskSurface($surface2, array());
	trigger_error('maskSurface arg 2 expects double');
}
catch (CairoException $ex) {
	echo $ex->getMessage(), PHP_EOL;
}

/* wrong type */
try {
	$context->maskSurface($surface2, 1, array());
	trigger_error('maskSurface arg 1 expects double');
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
object(CairoImageSurface)#%d (0) {
}
CairoContext::maskSurface() expects at least 1 parameter, 0 given
CairoContext::maskSurface() expects at most 3 parameters, 4 given
CairoContext::maskSurface() expects parameter 1 to be CairoSurface, array given
CairoContext::maskSurface() expects parameter 2 to be double, array given
CairoContext::maskSurface() expects parameter 3 to be double, array given