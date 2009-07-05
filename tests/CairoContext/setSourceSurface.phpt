--TEST--
CairoContext->setSourceSurface() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$surface = new CairoImageSurface(CAIRO_FORMAT_ARGB32, 50, 50);
var_dump($surface);

$context = new CairoContext($surface);
var_dump($context);

$pattern = new CairoSolidPattern(0.3, 0.3, 0.3);
var_dump($pattern);

$context->setSource($pattern);

$surface2 = new CairoImageSurface(CAIRO_FORMAT_ARGB32, 50, 50);
var_dump($surface2);

$context->setSourceSurface($surface2, 5, 5);
var_dump($context);

/* Wrong number args */
try {
    $context->setSourceSurface();
    trigger_error('setSourceSurface requires at leastone arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args */
try {
    $context->setSourceSurface($surface2, 1, 1, 1);
    trigger_error('setSourceSurface requires no more than 3 args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type */
try {
    $context->setSourceSurface(array());
    trigger_error('setSourceSurface expects instanceof CairoPattern');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type */
try {
    $context->setSourceSurface($surface2, array());
    trigger_error('setSourceSurface expects instanceof CairoPattern');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type */
try {
    $context->setSourceSurface($surface2, 1, array());
    trigger_error('setSourceSurface expects double');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
object(CairoSolidPattern)#%d (0) {
}
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
CairoContext::setSourceSurface() expects at least 1 parameter, 0 given
CairoContext::setSourceSurface() expects at most 3 parameters, 4 given
CairoContext::setSourceSurface() expects parameter 1 to be CairoSurface, array given
CairoContext::setSourceSurface() expects parameter 2 to be double, array given
CairoContext::setSourceSurface() expects parameter 3 to be double, array given
