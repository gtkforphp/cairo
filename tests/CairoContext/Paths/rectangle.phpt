--TEST--
CairoContext->rectangle() method
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
	trigger_error('CairoContext::rectangle() expects 4 parameters!');
}

$context->rectangle(1, 1, 1, 1);

/* wrong params */
try {
    $context->rectangle();
    trig_err();
} 
catch (CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->rectangle(1);
    trig_err();
} 
catch (CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->rectangle(1,1);
    trig_err();
} 
catch (CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->rectangle(1,1,1);
    trig_err();
} 
catch (CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->rectangle(1,1,1,1,1);
    trig_err();
} 
catch (CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

/* wrong types */
try {
    $context->rectangle(array(),1,1,1);
    trig_err();
} 
catch (CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->rectangle(1,array(),1,1);
    trig_err();
} 
catch (CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->rectangle(1,1,array(),1);
    trig_err();
} 
catch (CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->rectangle(1,1,1,array());
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
CairoContext::rectangle() expects exactly 4 parameters, 0 given
CairoContext::rectangle() expects exactly 4 parameters, 1 given
CairoContext::rectangle() expects exactly 4 parameters, 2 given
CairoContext::rectangle() expects exactly 4 parameters, 3 given
CairoContext::rectangle() expects exactly 4 parameters, 5 given
CairoContext::rectangle() expects parameter 1 to be double, array given
CairoContext::rectangle() expects parameter 2 to be double, array given
CairoContext::rectangle() expects parameter 3 to be double, array given
CairoContext::rectangle() expects parameter 4 to be double, array given