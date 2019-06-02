--TEST--
Cairo\Context->setSourceRGBA() method
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

$context->setSourceRGBA(0.1, 0.1, 0.1, 0.5);

try {
    $context->setSourceRGBA("1", "1", "1", "0");
} catch (TypeError $e) {
    echo $e->getMessage();
}

try {
    $context->setSourceRGBA("1.0", "1.0", "1.0", "0.0");
} catch (TypeError $e) {
    echo $e->getMessage();
}

try {
    $context->setSourceRGBA("foo", "bar", "baz", "foo");
} catch (TypeError $e) {
    echo $e->getMessage();
}

?>
--EXPECTF--
object(Cairo\Surface\Image)#%d (0) {
}
object(Cairo\Context)#%d (0) {
}
Cairo\Context::setSourceRGBA() expects parameter 1 to be float, string given
