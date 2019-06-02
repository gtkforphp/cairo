--TEST--
Cairo\Context->restore() method
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

$context->save();
$context->restore();

/* restore without save */
try {
    $context->restore();
    trigger_error('save requires only one arg');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args */
try {
    $context->restore('foo');
    trigger_error('save requires only one arg');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Surface\Image)#%d (0) {
}
object(Cairo\Context)#%d (0) {
}
cairo_restore() without matching cairo_save()
Cairo\Context::restore() expects exactly 0 parameters, 1 given
