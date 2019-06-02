--TEST--
Cairo\Context->lineTo() method
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
	trigger_error('Cairo\Context::lineTo() expects 2 parameters!');
}

$context->lineTo(1, 1);

/* wrong params */
try {
    $context->lineTo();
    trig_err();
} 
catch (TypeError $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->lineTo(1);
    trig_err();
} 
catch (TypeError $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->lineTo(1,1, 1);
    trig_err();
} 
catch (TypeError $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

/* wrong types */
try {
    $context->lineTo(array(),1);
    trig_err();
} 
catch (TypeError $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->lineTo(1,array());
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
Cairo\Context::lineTo() expects exactly 2 parameters, 0 given
Cairo\Context::lineTo() expects exactly 2 parameters, 1 given
Cairo\Context::lineTo() expects exactly 2 parameters, 3 given
Cairo\Context::lineTo() expects parameter 1 to be float, array given
Cairo\Context::lineTo() expects parameter 2 to be float, array given