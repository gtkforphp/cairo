--TEST--
CairoContext->arc() method
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
	trigger_error('CairoContext::arc() expects 5 parameters!');
}

$context->arc(0, 0, 1, 0, 2 * M_PI);

/* wrong params */
try {
    $context->arc();
    trig_err();
} 
catch (CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->arc(1);
    trig_err();
} 
catch (CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->arc(1,1);
    trig_err();
} 
catch (CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->arc(1,1,1);
    trig_err();
} 
catch (CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->arc(1,1,1,1);
    trig_err();
} 
catch (CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->arc(1,1,1,1,1,1);
    trig_err();
} 
catch (CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

/* wrong types */
try {
    $context->arc(array(),1,1,1,1);
    trig_err();
} 
catch (CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->arc(1,array(),1,1,1);
    trig_err();
} 
catch (CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->arc(1,1,array(),1,1);
    trig_err();
} 
catch (CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->arc(1,1,1,array(),1);
    trig_err();
} 
catch (CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->arc(1,1,1,1,array());
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
CairoContext::arc() expects exactly 5 parameters, 0 given
CairoContext::arc() expects exactly 5 parameters, 1 given
CairoContext::arc() expects exactly 5 parameters, 2 given
CairoContext::arc() expects exactly 5 parameters, 3 given
CairoContext::arc() expects exactly 5 parameters, 4 given
CairoContext::arc() expects exactly 5 parameters, 6 given
CairoContext::arc() expects parameter 1 to be double, array given
CairoContext::arc() expects parameter 2 to be double, array given
CairoContext::arc() expects parameter 3 to be double, array given
CairoContext::arc() expects parameter 4 to be double, array given
CairoContext::arc() expects parameter 5 to be double, array given