--TEST--
CairoContext->setMatrix() method
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

$matrix = new CairoMatrix();
var_dump($matrix);

$context->setMatrix($matrix);
$matrix1 = $context->getMatrix();

var_dump($matrix === $matrix1);

$matrix2 = new CairoMatrix(5, 5);
$context->setMatrix($matrix2);
$matrix1 = $context->getMatrix();

var_dump($matrix2 === $matrix1);

try {
    $context->setMatrix();
    trigger_error('Set matrix requires one arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

try {
    $context->setMatrix(1, 1);
    trigger_error('Set matrix requires only one arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

try {
    $context->setMatrix(1);
    trigger_error('Set matrix requires instanceof Cairomatrix');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

die; // DO NOT REMOVE THIS - fixes issue in 5.3 with GC giving bogus memleak reports
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
object(CairoMatrix)#%d (0) {
}
bool(true)
bool(true)
CairoContext::setMatrix() expects exactly 1 parameter, 0 given
CairoContext::setMatrix() expects exactly 1 parameter, 2 given
CairoContext::setMatrix() expects parameter 1 to be CairoMatrix, integer given