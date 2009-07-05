--TEST--
CairoContext->setLineCap() method
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

$context->setLineCap(CairoLineCap::SQUARE);
var_dump($context->getLineCap());

/* Wrong number args - 1 */
try {
    $context->setLineCap();
    trigger_error('setLineCap requires 1 arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 2 */
try {
    $context->setLineCap(1, 1);
    trigger_error('setLineCap requires only 1 arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong args */
try {
    $context->setLineCap(array());
    trigger_error('setLineCap requires int');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
int(2)
CairoContext::setLineCap() expects exactly 1 parameter, 0 given
CairoContext::setLineCap() expects exactly 1 parameter, 2 given
CairoContext::setLineCap() expects parameter 1 to be long, array given