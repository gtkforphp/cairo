--TEST--
CairoContext->setMiterLimit() method
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

$context->setMiterLimit(1);
var_dump($context->getMiterLimit());


/* Wrong number args - 1 */
try {
    $context->setMiterLimit();
    trigger_error('setMiterLimit requires 1 arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 2 */
try {
    $context->setMiterLimit(1, 1);
    trigger_error('setMiterLimit requires only 1 arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong args */
try {
    $context->setMiterLimit(array());
    trigger_error('setMiterLimit requires double');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
float(1)
CairoContext::setMiterLimit() expects exactly 1 parameter, 0 given
CairoContext::setMiterLimit() expects exactly 1 parameter, 2 given
CairoContext::setMiterLimit() expects parameter 1 to be double, array given