--TEST--
CairoContext->setLineJoin() method
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

$context->setLineJoin(CairoLineJoin::BEVEL);
var_dump($context->getLineJoin());

/* Wrong number args - 1 */
try {
    $context->setLineJoin();
    trigger_error('setLineJoin requires 1 arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 2 */
try {
    $context->setLineJoin(1, 1);
    trigger_error('setLineJoin requires only 1 arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong args */
try {
    $context->setLineJoin(array());
    trigger_error('setLineJoin requires int');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Surface\Image)#%d (0) {
}
object(CairoContext)#%d (0) {
}
int(2)
CairoContext::setLineJoin() expects exactly 1 parameter, 0 given
CairoContext::setLineJoin() expects exactly 1 parameter, 2 given
CairoContext::setLineJoin() expects parameter 1 to be long, array given