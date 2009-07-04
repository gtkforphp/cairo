--TEST--
CairoContext->textExtents() method
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

var_dump($context->textExtents('foobar'));

/* Wrong number args 1 */
try {
    $context->textExtents();
    trigger_error('textExtents requires one arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args 1 */
try {
    $context->textExtents('foo', 1);
    trigger_error('textExtents requires only one arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type */
try {
    $context->textExtents(array());
    trigger_error('textExtents requires one arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
array(6) {
  ["x_bearing"]=>
  float(%f)
  ["y_bearing"]=>
  float(%f)
  ["width"]=>
  float(%f)
  ["height"]=>
  float(%f)
  ["x_advance"]=>
  float(%f)
  ["y_advance"]=>
  float(%f)
}
CairoContext::textExtents() expects exactly 1 parameter, 0 given
CairoContext::textExtents() expects exactly 1 parameter, 2 given
CairoContext::textExtents() expects parameter 1 to be string, array given