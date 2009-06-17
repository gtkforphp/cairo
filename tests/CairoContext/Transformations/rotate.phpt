--TEST--
CairoContext->rotate() method
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

$context->rotate(5);

/* Wrong number args - expects 1 */
try {
    $context->rotate();
    trigger_error('rotate requires 1 arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - expects 1 */
try {
    $context->rotate(1,1);
    trigger_error('rotate requires 1 arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type, wants double */
try {
    $context->rotate(array());
    trigger_error('rotate requires double');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
CairoContext::rotate() expects exactly 1 parameter, 0 given
CairoContext::rotate() expects exactly 1 parameter, 2 given
CairoContext::rotate() expects parameter 1 to be double, array given