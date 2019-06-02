--TEST--
Cairo\Context->arc() method
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
	trigger_error('Cairo\Context::arc() expects 5 parameters!');
}

$context->arc(0, 0, 1, 0, 2 * M_PI);

/* wrong params */
try {
    $context->arc();
    trig_err();
} 
catch (TypeError $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->arc(1);
    trig_err();
} 
catch (TypeError $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->arc(1,1);
    trig_err();
} 
catch (TypeError $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->arc(1,1,1);
    trig_err();
} 
catch (TypeError $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->arc(1,1,1,1);
    trig_err();
} 
catch (TypeError $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->arc(1,1,1,1,1,1);
    trig_err();
} 
catch (TypeError $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

/* wrong types */
try {
    $context->arc(array(),1,1,1,1);
    trig_err();
} 
catch (TypeError $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->arc(1,array(),1,1,1);
    trig_err();
} 
catch (TypeError $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->arc(1,1,array(),1,1);
    trig_err();
} 
catch (TypeError $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->arc(1,1,1,array(),1);
    trig_err();
} 
catch (TypeError $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->arc(1,1,1,1,array());
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
Cairo\Context::arc() expects exactly 5 parameters, 0 given
Cairo\Context::arc() expects exactly 5 parameters, 1 given
Cairo\Context::arc() expects exactly 5 parameters, 2 given
Cairo\Context::arc() expects exactly 5 parameters, 3 given
Cairo\Context::arc() expects exactly 5 parameters, 4 given
Cairo\Context::arc() expects exactly 5 parameters, 6 given
Cairo\Context::arc() expects parameter 1 to be float, array given
Cairo\Context::arc() expects parameter 2 to be float, array given
Cairo\Context::arc() expects parameter 3 to be float, array given
Cairo\Context::arc() expects parameter 4 to be float, array given
Cairo\Context::arc() expects parameter 5 to be float, array given