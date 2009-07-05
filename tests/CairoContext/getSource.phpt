--TEST--
CairoContext->getSource() method
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

$pattern = $context->getSource();
var_dump($pattern);

/* Wrong number args */
try {
    $context->getSource('foobar');
    trigger_error('getSource requires no arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
object(CairoSolidPattern)#%d (0) {
}
CairoContext::getSource() expects exactly 0 parameters, 1 given