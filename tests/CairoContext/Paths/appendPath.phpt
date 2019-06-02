--TEST--
Cairo\Context->appendPath() method
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

$path = $context->copyPath();
var_dump($path);

$context->appendPath($path);

/* Wrong number args - expects 1 */
try {
    $context->appendPath();
    trigger_error('appendPath requires 0 args');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - expects 1 */
try {
    $context->appendPath($path, 1);
    trigger_error('appendPath requires 0 args');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* incorrect args, expects cairopath*/
try {
    $context->appendPath(1);
    trigger_error('appendPath requires 0 args');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Surface\Image)#%d (0) {
}
object(Cairo\Context)#%d (0) {
}
object(Cairo\Path)#%d (0) {
}
Cairo\Context::appendPath() expects exactly 1 parameter, 0 given
Cairo\Context::appendPath() expects exactly 1 parameter, 2 given
Cairo\Context::appendPath() expects parameter 1 to be Cairo\Path, int given