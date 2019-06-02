--TEST--
Cairo\Context->showText() method
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

$context->showText('foobar');

/* Wrong number args 1 */
try {
    $context->showText();
    trigger_error('showText requires one arg');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args 1 */
try {
    $context->showText('foo', 1);
    trigger_error('showText requires only one arg');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type */
try {
    $context->showText(array());
    trigger_error('showText requires one arg');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Surface\Image)#%d (0) {
}
object(Cairo\Context)#%d (0) {
}
Cairo\Context::showText() expects exactly 1 parameter, 0 given
Cairo\Context::showText() expects exactly 1 parameter, 2 given
Cairo\Context::showText() expects parameter 1 to be string, array given