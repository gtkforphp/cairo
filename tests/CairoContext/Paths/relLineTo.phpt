--TEST--
CairoContext->relLineTo() method
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
	trigger_error('CairoContext::relLineTo() expects 2 parameters!');
}

$context->lineTo(1, 1);
$context->relLineTo(1, 1);

/* wrong params */
try {
    $context->relLineTo();
    trig_err();
} 
catch (CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->relLineTo(1);
    trig_err();
} 
catch (CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->relLineTo(1,1, 1);
    trig_err();
} 
catch (CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

/* wrong types */
try {
    $context->relLineTo(array(),1);
    trig_err();
} 
catch (CairoException $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->relLineTo(1,array());
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
CairoContext::relLineTo() expects exactly 2 parameters, 0 given
CairoContext::relLineTo() expects exactly 2 parameters, 1 given
CairoContext::relLineTo() expects exactly 2 parameters, 3 given
CairoContext::relLineTo() expects parameter 1 to be double, array given
CairoContext::relLineTo() expects parameter 2 to be double, array given