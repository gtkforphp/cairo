--TEST--
Cairo\Context->setSourceSurface() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$surface = new Cairo\Surface\Image(CAIRO_FORMAT_ARGB32, 50, 50);
var_dump($surface);

$context = new Cairo\Context($surface);
var_dump($context);

$pattern = new Cairo\Pattern\Solid(0.3, 0.3, 0.3);
var_dump($pattern);

$context->setSource($pattern);

$surface2 = new Cairo\Surface\Image(CAIRO_FORMAT_ARGB32, 50, 50);
var_dump($surface2);

$context->setSourceSurface($surface2, 5, 5);
var_dump($context);

/* Wrong number args */
try {
    $context->setSourceSurface();
    trigger_error('setSourceSurface requires at leastone arg');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args */
try {
    $context->setSourceSurface($surface2, 1, 1, 1);
    trigger_error('setSourceSurface requires no more than 3 args');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type */
try {
    $context->setSourceSurface(array());
    trigger_error('setSourceSurface expects instanceof CairoPattern');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type */
try {
    $context->setSourceSurface($surface2, array());
    trigger_error('setSourceSurface expects instanceof CairoPattern');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type */
try {
    $context->setSourceSurface($surface2, 1, array());
    trigger_error('setSourceSurface expects double');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Surface\Image)#%d (0) {
}
object(Cairo\Context)#%d (0) {
}
object(Cairo\Pattern\Solid)#%d (0) {
}
object(Cairo\Surface\Image)#%d (0) {
}
object(Cairo\Context)#%d (0) {
}
Cairo\Context::setSourceSurface() expects at least 1 parameter, 0 given
Cairo\Context::setSourceSurface() expects at most 3 parameters, 4 given
Cairo\Context::setSourceSurface() expects parameter 1 to be Cairo\Surface, array given
Cairo\Context::setSourceSurface() expects parameter 2 to be float, array given
Cairo\Context::setSourceSurface() expects parameter 3 to be float, array given
