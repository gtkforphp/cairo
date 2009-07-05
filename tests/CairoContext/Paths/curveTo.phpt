--TEST--
CairoContext->curveTo() method
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

function trig_err()
{
	trigger_error('CairoContext::curveTo() expects 5 parameters!');
}

$context->curveTo(0, 0, 1, 0, 1, 1);

/* wrong params */
try {
    $context->curveTo();
    trig_err();
} 
catch (CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->curveTo(1);
    trig_err();
} 
catch (CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->curveTo(1,1);
    trig_err();
} 
catch (CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->curveTo(1,1,1);
    trig_err();
} 
catch (CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->curveTo(1,1,1,1);
    trig_err();
} 
catch (CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->curveTo(1,1,1,1,1);
    trig_err();
} 
catch (CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->curveTo(1,1,1,1,1,1,1);
    trig_err();
} 
catch (CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

/* wrong types */
try {
    $context->curveTo(array(),1,1,1,1,1);
    trig_err();
} 
catch (CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->curveTo(1,array(),1,1,1,1);
    trig_err();
} 
catch (CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->curveTo(1,1,array(),1,1,1);
    trig_err();
} 
catch (CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->curveTo(1,1,1,array(),1,1);
    trig_err();
} 
catch (CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->curveTo(1,1,1,1,array(),1);
    trig_err();
} 
catch (CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->curveTo(1,1,1,1,1,array());
    trig_err();
} 
catch (CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
CairoContext::curveTo() expects exactly 6 parameters, 0 given
CairoContext::curveTo() expects exactly 6 parameters, 1 given
CairoContext::curveTo() expects exactly 6 parameters, 2 given
CairoContext::curveTo() expects exactly 6 parameters, 3 given
CairoContext::curveTo() expects exactly 6 parameters, 4 given
CairoContext::curveTo() expects exactly 6 parameters, 5 given
CairoContext::curveTo() expects exactly 6 parameters, 7 given
CairoContext::curveTo() expects parameter 1 to be double, array given
CairoContext::curveTo() expects parameter 2 to be double, array given
CairoContext::curveTo() expects parameter 3 to be double, array given
CairoContext::curveTo() expects parameter 4 to be double, array given
CairoContext::curveTo() expects parameter 5 to be double, array given
CairoContext::curveTo() expects parameter 6 to be double, array given