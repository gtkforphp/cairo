--TEST--
Cairo\Context->transform() method
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

$matrix = new Cairo\Matrix(1, 0, 0, 1);
var_dump($matrix);

$context->transform($matrix);

/* Wrong number args - expects 1 */
try {
    $context->transform();
    trigger_error('transform requires 1 arg');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - expects 1 */
try {
    $context->transform($matrix, 1);
    trigger_error('transform requires 1 arg');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type, wants matrix object */
try {
    $context->transform(1);
    trigger_error('transform requires cairomatrix object');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Surface\Image)#%d (0) {
}
object(Cairo\Context)#%d (0) {
}
object(Cairo\Matrix)#%d (0) {
}
Cairo\Context::transform() expects exactly 1 parameter, 0 given
Cairo\Context::transform() expects exactly 1 parameter, 2 given
Cairo\Context::transform() expects parameter 1 to be Cairo\Matrix, int given