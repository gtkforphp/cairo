--TEST--
CairoContext->setFontSize() method
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

$context->setFontSize(15);

$context->setFontMatrix(new CairoMatrix(5, 5));

$context->setFontSize(10);

/* Wrong number args */
try {
    $context->setFontSize();
    trigger_error('setFontSize requires at least one arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - too many */
try {
    $context->setFontSize(15, 1);
    trigger_error('setFontSize requires only one arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type - double */
try {
    $context->setFontSize(array());
    trigger_error('setFontSize requires a double');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

die; // bogus memleak report - GC bug - is getting REALLY annoying
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
CairoContext::setFontSize() expects exactly 1 parameter, 0 given
CairoContext::setFontSize() expects exactly 1 parameter, 2 given
CairoContext::setFontSize() expects parameter 1 to be double, array given
