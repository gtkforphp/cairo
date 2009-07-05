--TEST--
CairoContext->moveTo() method
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
	trigger_error('CairoContext::moveTo() expects 2 parameters!');
}

$context->moveTo(1, 1);

/* wrong params */
try {
    $context->moveTo();
    trig_err();
} 
catch (CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->moveTo(1);
    trig_err();
} 
catch (CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->moveTo(1,1, 1);
    trig_err();
} 
catch (CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

/* wrong types */
try {
    $context->moveTo(array(),1);
    trig_err();
} 
catch (CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->moveTo(1,array());
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
CairoContext::moveTo() expects exactly 2 parameters, 0 given
CairoContext::moveTo() expects exactly 2 parameters, 1 given
CairoContext::moveTo() expects exactly 2 parameters, 3 given
CairoContext::moveTo() expects parameter 1 to be double, array given
CairoContext::moveTo() expects parameter 2 to be double, array given