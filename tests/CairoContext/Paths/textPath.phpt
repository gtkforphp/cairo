--TEST--
Cairo\Context->textPath() method
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

$context->textPath('foobar');

/* Wrong number args 1 */
try {
    $context->textPath();
    trigger_error('textPath requires one arg');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args 1 */
try {
    $context->textPath('foo', 1);
    trigger_error('textPath requires only one arg');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type */
try {
    $context->textPath(array());
    trigger_error('textPath requires one arg');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Surface\Image)#%d (0) {
}
object(Cairo\Context)#%d (0) {
}
Cairo\Context::textPath() expects exactly 1 parameter, 0 given
Cairo\Context::textPath() expects exactly 1 parameter, 2 given
Cairo\Context::textPath() expects parameter 1 to be string, array given