--TEST--
CairoContext->transform() method
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

$matrix = new CairoMatrix(1, 0, 0, 1);
var_dump($matrix);

$context->transform($matrix);

/* Wrong number args - expects 1 */
try {
    $context->transform();
    trigger_error('transform requires 1 arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - expects 1 */
try {
    $context->transform($matrix, 1);
    trigger_error('transform requires 1 arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type, wants matrix object */
try {
    $context->transform(1);
    trigger_error('transform requires cairomatrix object');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
object(CairoMatrix)#%d (0) {
}
CairoContext::transform() expects exactly 1 parameter, 0 given
CairoContext::transform() expects exactly 1 parameter, 2 given
CairoContext::transform() expects parameter 1 to be CairoMatrix, integer given