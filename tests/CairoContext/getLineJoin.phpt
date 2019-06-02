--TEST--
CairoContext->getLineJoin() method
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

var_dump($context->getLineJoin());

/* Wrong number args */
try {
    $context->getLineJoin('foobar');
    trigger_error('getLineJoin requires no args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Surface\Image)#%d (0) {
}
object(CairoContext)#%d (0) {
}
int(0)
CairoContext::getLineJoin() expects exactly 0 parameters, 1 given