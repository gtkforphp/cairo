--TEST--
Cairo\Context->relMoveTo() method
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
	trigger_error('Cairo\Context::relMoveTo() expects 2 parameters!');
}

$context->moveTo(1, 1);
$context->relMoveTo(1, 1);

/* wrong params */
try {
    $context->relMoveTo();
    trig_err();
} 
catch (TypeError $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->relMoveTo(1);
    trig_err();
} 
catch (TypeError $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->relMoveTo(1,1, 1);
    trig_err();
} 
catch (TypeError $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

/* wrong types */
try {
    $context->relMoveTo(array(),1);
    trig_err();
} 
catch (TypeError $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->relMoveTo(1,array());
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
Cairo\Context::relMoveTo() expects exactly 2 parameters, 0 given
Cairo\Context::relMoveTo() expects exactly 2 parameters, 1 given
Cairo\Context::relMoveTo() expects exactly 2 parameters, 3 given
Cairo\Context::relMoveTo() expects parameter 1 to be float, array given
Cairo\Context::relMoveTo() expects parameter 2 to be float, array given