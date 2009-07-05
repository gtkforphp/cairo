--TEST--
CairoContext->relCurveTo() method
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
	trigger_error('CairoContext::relCurveTo() expects 5 parameters!');
}

$context->curveTo(0, 0, 1, 0, 1, 1);
$context->relCurveTo(0, 0, 1, 0, 1, 1);

/* wrong params */
try {
    $context->relCurveTo();
    trig_err();
} 
catch (CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->relCurveTo(1);
    trig_err();
} 
catch (CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->relCurveTo(1,1);
    trig_err();
} 
catch (CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->relCurveTo(1,1,1);
    trig_err();
} 
catch (CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->relCurveTo(1,1,1,1);
    trig_err();
} 
catch (CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->relCurveTo(1,1,1,1,1);
    trig_err();
} 
catch (CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->relCurveTo(1,1,1,1,1,1,1);
    trig_err();
} 
catch (CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

/* wrong types */
try {
    $context->relCurveTo(array(),1,1,1,1,1);
    trig_err();
} 
catch (CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->relCurveTo(1,array(),1,1,1,1);
    trig_err();
} 
catch (CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->relCurveTo(1,1,array(),1,1,1);
    trig_err();
} 
catch (CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->relCurveTo(1,1,1,array(),1,1);
    trig_err();
} 
catch (CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->relCurveTo(1,1,1,1,array(),1);
    trig_err();
} 
catch (CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->relCurveTo(1,1,1,1,1,array());
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
CairoContext::relCurveTo() expects exactly 6 parameters, 0 given
CairoContext::relCurveTo() expects exactly 6 parameters, 1 given
CairoContext::relCurveTo() expects exactly 6 parameters, 2 given
CairoContext::relCurveTo() expects exactly 6 parameters, 3 given
CairoContext::relCurveTo() expects exactly 6 parameters, 4 given
CairoContext::relCurveTo() expects exactly 6 parameters, 5 given
CairoContext::relCurveTo() expects exactly 6 parameters, 7 given
CairoContext::relCurveTo() expects parameter 1 to be double, array given
CairoContext::relCurveTo() expects parameter 2 to be double, array given
CairoContext::relCurveTo() expects parameter 3 to be double, array given
CairoContext::relCurveTo() expects parameter 4 to be double, array given
CairoContext::relCurveTo() expects parameter 5 to be double, array given
CairoContext::relCurveTo() expects parameter 6 to be double, array given