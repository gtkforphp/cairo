--TEST--
CairoContext->setFillRule() method
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

$context->setFillRule(CairoFillRule::EVEN_ODD);
var_dump($context->getFillRule());

/* Wrong number args - 1 */
try {
    $context->setFillRule();
    trigger_error('setFillRule requires 1 arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 2 */
try {
    $context->setFillRule(1, 1);
    trigger_error('setFillRule requires only 1 arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong args */
try {
    $context->setFillRule(array());
    trigger_error('setFillRule requires int');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
int(1)
CairoContext::setFillRule() expects exactly 1 parameter, 0 given
CairoContext::setFillRule() expects exactly 1 parameter, 2 given
CairoContext::setFillRule() expects parameter 1 to be long, array given