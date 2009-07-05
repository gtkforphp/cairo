--TEST--
CairoContext->inStroke() method
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

var_dump($context->inStroke(1, 1));

/* Wrong number args */
try {
    $context->inStroke();
    trigger_error('inStroke requires 2 args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args */
try {
    $context->inStroke(1);
    trigger_error('inStroke requires 2 args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args */
try {
    $context->inStroke(1, 1, 1);
    trigger_error('inStroke requires only 2 args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type*/
try {
    $context->inStroke(array(), 1);
    trigger_error('inStroke requires double for arg 1');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type*/
try {
    $context->inStroke(1, array());
    trigger_error('inStroke requires double for arg 2');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
bool(false)
CairoContext::inStroke() expects exactly 2 parameters, 0 given
CairoContext::inStroke() expects exactly 2 parameters, 1 given
CairoContext::inStroke() expects exactly 2 parameters, 3 given
CairoContext::inStroke() expects parameter 1 to be double, array given
CairoContext::inStroke() expects parameter 2 to be double, array given