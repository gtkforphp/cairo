--TEST--
CairoContext->inFill() method
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

var_dump($context->inFill(1, 1));

/* Wrong number args */
try {
    $context->inFill();
    trigger_error('inFill requires 2 args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args */
try {
    $context->inFill(1);
    trigger_error('inFill requires 2 args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args */
try {
    $context->inFill(1, 1, 1);
    trigger_error('inFill requires only 2 args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type*/
try {
    $context->inFill(array(), 1);
    trigger_error('inFill requires double for arg 1');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type*/
try {
    $context->inFill(1, array());
    trigger_error('inFill requires double for arg 2');
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
CairoContext::inFill() expects exactly 2 parameters, 0 given
CairoContext::inFill() expects exactly 2 parameters, 1 given
CairoContext::inFill() expects exactly 2 parameters, 3 given
CairoContext::inFill() expects parameter 1 to be double, array given
CairoContext::inFill() expects parameter 2 to be double, array given