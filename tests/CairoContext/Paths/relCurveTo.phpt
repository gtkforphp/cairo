--TEST--
Cairo\Context->relCurveTo() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$surface = new Cairo\Surface\Image(Cairo\Surface\ImageFormat::ARGB32, 50, 50);
var_dump($surface);

$context = new Cairo\Context($surface);
var_dump($context);

function trig_err()
{
	trigger_error('Cairo\Context::relCurveTo() expects 5 parameters!');
}

$context->curveTo(0, 0, 1, 0, 1, 1);
$context->relCurveTo(0, 0, 1, 0, 1, 1);

/* wrong params */
try {
    $context->relCurveTo();
    trig_err();
} 
catch (TypeError $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->relCurveTo(1);
    trig_err();
} 
catch (TypeError $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->relCurveTo(1,1);
    trig_err();
} 
catch (TypeError $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->relCurveTo(1,1,1);
    trig_err();
} 
catch (TypeError $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->relCurveTo(1,1,1,1);
    trig_err();
} 
catch (TypeError $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->relCurveTo(1,1,1,1,1);
    trig_err();
} 
catch (TypeError $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->relCurveTo(1,1,1,1,1,1,1);
    trig_err();
} 
catch (TypeError $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

/* wrong types */
try {
    $context->relCurveTo(array(),1,1,1,1,1);
    trig_err();
} 
catch (TypeError $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->relCurveTo(1,array(),1,1,1,1);
    trig_err();
} 
catch (TypeError $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->relCurveTo(1,1,array(),1,1,1);
    trig_err();
} 
catch (TypeError $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->relCurveTo(1,1,1,array(),1,1);
    trig_err();
} 
catch (TypeError $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->relCurveTo(1,1,1,1,array(),1);
    trig_err();
} 
catch (TypeError $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->relCurveTo(1,1,1,1,1,array());
    trig_err();
} 
catch (TypeError $ex) {
    echo $ex->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Surface\Image)#%d (0) {
}
object(Cairo\Context)#%d (0) {
}
Cairo\Context::relCurveTo() expects exactly 6 parameters, 0 given
Cairo\Context::relCurveTo() expects exactly 6 parameters, 1 given
Cairo\Context::relCurveTo() expects exactly 6 parameters, 2 given
Cairo\Context::relCurveTo() expects exactly 6 parameters, 3 given
Cairo\Context::relCurveTo() expects exactly 6 parameters, 4 given
Cairo\Context::relCurveTo() expects exactly 6 parameters, 5 given
Cairo\Context::relCurveTo() expects exactly 6 parameters, 7 given
Cairo\Context::relCurveTo() expects parameter 1 to be float, array given
Cairo\Context::relCurveTo() expects parameter 2 to be float, array given
Cairo\Context::relCurveTo() expects parameter 3 to be float, array given
Cairo\Context::relCurveTo() expects parameter 4 to be float, array given
Cairo\Context::relCurveTo() expects parameter 5 to be float, array given
Cairo\Context::relCurveTo() expects parameter 6 to be float, array given