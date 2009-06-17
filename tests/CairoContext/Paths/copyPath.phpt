--TEST--
CairoContext->copyPath() method
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

var_dump($context->copyPath());

/* Wrong number args - expects 0 */
try {
    $context->copyPath('foo');
    trigger_error('identityMatrix requires 0 args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
object(CairoPath)#%d (0) {
}
CairoContext::copyPath() expects exactly 0 parameters, 1 given