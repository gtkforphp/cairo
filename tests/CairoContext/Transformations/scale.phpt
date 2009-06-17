--TEST--
CairoContext->scale() method
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

$context->scale(5, 5);

/* Wrong number args - expects 2 */
try {
    $context->scale();
    trigger_error('scale requires 2 args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - expects 2 */
try {
    $context->scale(1);
    trigger_error('scale requires 2 args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - expects 2 */
try {
    $context->scale(1,1,1);
    trigger_error('scale requires 2 args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type, wants double, double */
try {
    $context->scale(array(), 1);
    trigger_error('scale requires double, double');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type, wants double, double */
try {
    $context->scale(1, array());
    trigger_error('scale requires double, double');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
CairoContext::scale() expects exactly 2 parameters, 0 given
CairoContext::scale() expects exactly 2 parameters, 1 given
CairoContext::scale() expects exactly 2 parameters, 3 given
CairoContext::scale() expects parameter 1 to be double, array given
CairoContext::scale() expects parameter 2 to be double, array given