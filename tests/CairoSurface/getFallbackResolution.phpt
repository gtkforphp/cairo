--TEST--
CairoSurface->getFallbackResolution() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!method_exists('CairoSurface', 'getFallbackResolution')) die('skip - CairoSurface->getFallbackResolution not available');
?>
--FILE--
<?php
$surface = new CairoImageSurface(CairoFormat::ARGB32, 50, 50);
var_dump($surface);

var_dump($surface->getFallbackResolution());

/* Wrong number args */
try {
    $surface->getFallbackResolution('foo');
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
array(2) {
  [0]=>
  float(%d)
  [1]=>
  float(%d)
}
CairoSurface::getFallbackResolution() expects exactly 0 parameters, 1 given