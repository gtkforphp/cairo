--TEST--
CairoContext->hasCurrentPoint() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!method_exists('CairoContext', 'hasCurrentPoint')) die('skip - CairoContext->hasCurrentPoint not available');
?>
--FILE--
<?php
$surface = new CairoImageSurface(CairoFormat::ARGB32, 50, 50);
var_dump($surface);

$context = new CairoContext($surface);
var_dump($context);

var_dump($context->hasCurrentPoint());

/* Wrong number args - expects 0 */
try {
    $context->hasCurrentPoint('foo');
    trigger_error('hasCurrentPoint requires 0 args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
bool(false)
CairoContext::hasCurrentPoint() expects exactly 0 parameters, 1 given