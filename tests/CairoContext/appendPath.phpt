--TEST--
Cairo->appendPath() method
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

$path = $context->copyPath();
var_dump($path);

$context->appendPath($path);
try {
    $context->appendPath();
} catch (CairoException $e) {
    echo $e->getMessage();
}
?>
--EXPECTF--
object(CairoImageSurface)#1 (0) {
}
object(CairoContext)#2 (0) {
}
object(CairoPath)#3 (0) {
}
CairoContext::appendPath() expects exactly 1 parameter, 0 given