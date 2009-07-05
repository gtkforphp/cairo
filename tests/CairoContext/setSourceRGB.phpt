--TEST--
CairoContext->setSourceRGB() method
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

$context->setSourceRGB(0.1, 0.1, 0.1);

/* Wrong number of args: 0 */
try {
    $context->setSourceRGB();
    trigger_error('setSourceRGB needs 3!');
} 
catch(CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->setSourceRGB(1);
    trigger_error('setSourceRGB needs 3!');
}
catch(CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->setSourceRGB(1, 1);
    trigger_error('setSourceRGB needs 3!');
} 
catch(CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->setSourceRGB(1, 1, 1, 1);
    trigger_error('setSourceRGB needs 3!');
} 
catch(CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

/* Wrong types */
try {
    $context->setSourceRGB(array(), 1, 1);
}
catch(CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->setSourceRGB(1, array(), 1);
} 
catch(CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->setSourceRGB(1, 1, array());
} 
catch(CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
CairoContext::setSourceRGB() expects exactly 3 parameters, 0 given
CairoContext::setSourceRGB() expects exactly 3 parameters, 1 given
CairoContext::setSourceRGB() expects exactly 3 parameters, 2 given
CairoContext::setSourceRGB() expects exactly 3 parameters, 4 given
CairoContext::setSourceRGB() expects parameter 1 to be double, array given
CairoContext::setSourceRGB() expects parameter 2 to be double, array given
CairoContext::setSourceRGB() expects parameter 3 to be double, array given