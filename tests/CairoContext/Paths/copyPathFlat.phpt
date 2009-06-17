--TEST--
CairoContext->copyPathFlat() method
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

var_dump($context->copyPathFlat());

/* Wrong number args - expects 0 */
try {
    $context->copyPathFlat('foo');
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
CairoContext::copyPathFlat() expects exactly 0 parameters, 1 given