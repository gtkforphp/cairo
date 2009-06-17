--TEST--
CairoContext->translate() method
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

$context->translate(5, 5);

/* Wrong number args - expects 2 */
try {
    $context->translate();
    trigger_error('translate requires 2 args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - expects 2 */
try {
    $context->translate(1);
    trigger_error('translate requires 2 args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - expects 2 */
try {
    $context->translate(1,1,1);
    trigger_error('translate requires 2 args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type, wants double, double */
try {
    $context->translate(array(), 1);
    trigger_error('translate requires double, double');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type, wants double, double */
try {
    $context->translate(1, array());
    trigger_error('translate requires double, double');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
CairoContext::translate() expects exactly 2 parameters, 0 given
CairoContext::translate() expects exactly 2 parameters, 1 given
CairoContext::translate() expects exactly 2 parameters, 3 given
CairoContext::translate() expects parameter 1 to be double, array given
CairoContext::translate() expects parameter 2 to be double, array given