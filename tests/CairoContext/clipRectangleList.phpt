--TEST--
CairoContext->clipRectangleList() method
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

var_dump($context->clipRectangleList());

try {
    $context->clipRectangleList('foo');
} catch (CairoException $e) {
    echo $e->getMessage();
}
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
array(1) {
  [0]=>
  array(4) {
    ["x"]=>
    float(0)
    ["y"]=>
    float(0)
    ["width"]=>
    float(50)
    ["height"]=>
    float(50)
  }
}
CairoContext::clipRectangleList() expects exactly 0 parameters, 1 given