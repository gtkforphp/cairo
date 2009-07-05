--TEST--
CairoContext->popGroup() method
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

$context->pushGroup();
$pattern = $context->popGroup();
var_dump($pattern);

/* Wrong number args */
try {
    $context->popGroup('foo');
    trigger_error('popGroup requires only one arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
object(CairoSurfacePattern)#%d (0) {
}
CairoContext::popGroup() expects exactly 0 parameters, 1 given