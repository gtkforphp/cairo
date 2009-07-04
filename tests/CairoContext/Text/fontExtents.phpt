--TEST--
CairoContext->fontExtents() method
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

var_dump($context->fontExtents());

/* Wrong number args */
try {
    $context->fontExtents('foo');
    trigger_error('fontExtents requires only one arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
array(5) {
  ["ascent"]=>
  float(%f)
  ["descent"]=>
  float(%f)
  ["height"]=>
  float(%f)
  ["max_x_advance"]=>
  float(%f)
  ["max_y_advance"]=>
  float(%f)
}
CairoContext::fontExtents() expects exactly 0 parameters, 1 given