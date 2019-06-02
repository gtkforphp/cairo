--TEST--
Cairo\Context->userToDeviceDistance() method
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

var_dump($context->userToDeviceDistance(5, 5));

/* Wrong number args - 1 */
try {
    $context->userToDeviceDistance();
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 2 */
try {
    $context->userToDeviceDistance(10);
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 3 */
try {
    $context->userToDeviceDistance(10, 10, 10);
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 1 */
try {
    $context->userToDeviceDistance(array(), 10);
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 2 */
try {
    $context->userToDeviceDistance(10, array());
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Surface\Image)#%d (0) {
}
object(Cairo\Context)#%d (0) {
}
array(2) {
  [0]=>
  float(5)
  [1]=>
  float(5)
}
Cairo\Context::userToDeviceDistance() expects exactly 2 parameters, 0 given
Cairo\Context::userToDeviceDistance() expects exactly 2 parameters, 1 given
Cairo\Context::userToDeviceDistance() expects exactly 2 parameters, 3 given
Cairo\Context::userToDeviceDistance() expects parameter 1 to be float, array given
Cairo\Context::userToDeviceDistance() expects parameter 2 to be float, array given