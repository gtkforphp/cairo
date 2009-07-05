--TEST--
CairoContext->setAntialias() method
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

$context->setAntialias(CairoAntialias::MODE_GRAY);
var_dump($context->getAntialias());

/* Wrong number args - 1 */
try {
    $context->setAntialias(1, 1);
    trigger_error('setAntialias requires 0 or 1 args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong args */
try {
    $context->setAntialias(array());
    trigger_error('setAntialias requires int');
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
CairoContext::setAntialias() expects at most 1 parameter, 2 given
CairoContext::setAntialias() expects parameter 1 to be long, array given