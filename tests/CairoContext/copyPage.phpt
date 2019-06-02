--TEST--
CairoContext->copyPage() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$surface = new Cairo\Surface\Image(Cairo\Surface\ImageFormat::ARGB32, 50, 50);
var_dump($surface);

$context = new CairoContext($surface);
var_dump($context);

$context->copyPage();
try {
    $context->copyPage('foo');
} catch (CairoException $e) {
    echo $e->getMessage();
}
?>
--EXPECTF--
object(Cairo\Surface\Image)#%d (0) {
}
object(CairoContext)#%d (0) {
}
CairoContext::copyPage() expects exactly 0 parameters, 1 given