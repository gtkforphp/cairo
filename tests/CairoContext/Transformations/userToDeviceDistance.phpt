--TEST--
CairoContext->userToDeviceDistance() method
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

var_dump($context->userToDeviceDistance(5, 5));

/* Wrong number args - 1 */
try {
    $context->userToDeviceDistance();
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 2 */
try {
    $context->userToDeviceDistance(10);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 3 */
try {
    $context->userToDeviceDistance(10, 10, 10);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 1 */
try {
    $context->userToDeviceDistance(array(), 10);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 2 */
try {
    $context->userToDeviceDistance(10, array());
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
array(2) {
  [0]=>
  float(5)
  [1]=>
  float(5)
}
CairoContext::userToDeviceDistance() expects exactly 2 parameters, 0 given
CairoContext::userToDeviceDistance() expects exactly 2 parameters, 1 given
CairoContext::userToDeviceDistance() expects exactly 2 parameters, 3 given
CairoContext::userToDeviceDistance() expects parameter 1 to be double, array given
CairoContext::userToDeviceDistance() expects parameter 2 to be double, array given