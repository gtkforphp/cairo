--TEST--
Cairo\Context->setSourceRGB() method
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

$context->setSourceRGB(0.1, 0.1, 0.1);

/* Wrong number of args: 0 */
try {
    $context->setSourceRGB();
    trigger_error('setSourceRGB needs 3!');
} 
catch(TypeError $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->setSourceRGB(1);
    trigger_error('setSourceRGB needs 3!');
}
catch(TypeError $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->setSourceRGB(1, 1);
    trigger_error('setSourceRGB needs 3!');
} 
catch(TypeError $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->setSourceRGB(1, 1, 1, 1);
    trigger_error('setSourceRGB needs 3!');
} 
catch(TypeError $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

/* Wrong types */
try {
    $context->setSourceRGB(array(), 1, 1);
}
catch(TypeError $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->setSourceRGB(1, array(), 1);
} 
catch(TypeError $ex) {
    echo $ex->getMessage(), PHP_EOL;
}

try {
    $context->setSourceRGB(1, 1, array());
} 
catch(TypeError $ex) {
    echo $ex->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Surface\Image)#%d (0) {
}
object(Cairo\Context)#%d (0) {
}
Cairo\Context::setSourceRGB() expects exactly 3 parameters, 0 given
Cairo\Context::setSourceRGB() expects exactly 3 parameters, 1 given
Cairo\Context::setSourceRGB() expects exactly 3 parameters, 2 given
Cairo\Context::setSourceRGB() expects exactly 3 parameters, 4 given
Cairo\Context::setSourceRGB() expects parameter 1 to be float, array given
Cairo\Context::setSourceRGB() expects parameter 2 to be float, array given
Cairo\Context::setSourceRGB() expects parameter 3 to be float, array given