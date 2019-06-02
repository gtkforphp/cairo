--TEST--
Cairo\Context->rectangle() method
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
	trigger_error('Cairo\Context::rectangle() expects 4 parameters!');
}

$context->rectangle(1, 1, 1, 1);

/* wrong params */
try {
    $context->rectangle();
    trig_err();
} 
catch (TypeError $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->rectangle(1);
    trig_err();
} 
catch (TypeError $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->rectangle(1,1);
    trig_err();
} 
catch (TypeError $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->rectangle(1,1,1);
    trig_err();
} 
catch (TypeError $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->rectangle(1,1,1,1,1);
    trig_err();
} 
catch (TypeError $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

/* wrong types */
try {
    $context->rectangle(array(),1,1,1);
    trig_err();
} 
catch (TypeError $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->rectangle(1,array(),1,1);
    trig_err();
} 
catch (TypeError $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->rectangle(1,1,array(),1);
    trig_err();
} 
catch (TypeError $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->rectangle(1,1,1,array());
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
Cairo\Context::rectangle() expects exactly 4 parameters, 0 given
Cairo\Context::rectangle() expects exactly 4 parameters, 1 given
Cairo\Context::rectangle() expects exactly 4 parameters, 2 given
Cairo\Context::rectangle() expects exactly 4 parameters, 3 given
Cairo\Context::rectangle() expects exactly 4 parameters, 5 given
Cairo\Context::rectangle() expects parameter 1 to be float, array given
Cairo\Context::rectangle() expects parameter 2 to be float, array given
Cairo\Context::rectangle() expects parameter 3 to be float, array given
Cairo\Context::rectangle() expects parameter 4 to be float, array given