--TEST--
CairoContext->paintWithAlpha() method
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

$context->paintWithAlpha(0);

/* Wrong number args */
try {
    $context->paintWithAlpha();
    trigger_error('paintWithAlpha requires 1 arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args */
try {
    $context->paintWithAlpha(1, 1);
    trigger_error('paintWithAlpha requires only 1 arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type */
try {
    $context->paintWithAlpha(array());
    trigger_error('paintWithAlpha requires double');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
CairoContext::paintWithAlpha() expects exactly 1 parameter, 0 given
CairoContext::paintWithAlpha() expects exactly 1 parameter, 2 given
CairoContext::paintWithAlpha() expects parameter 1 to be double, array given