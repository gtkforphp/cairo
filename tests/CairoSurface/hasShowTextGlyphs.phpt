--TEST--
CairoSurface->hasShowTextGlyphs() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!method_exists('CairoSurface', 'hasShowTextGlyphs')) die('skip - CairoSurface->hasShowTextGlyphs not available');
?>
--FILE--
<?php
$surface = new CairoImageSurface(CairoFormat::ARGB32, 50, 50);
var_dump($surface);

var_dump($surface->hasShowTextGlyphs());

/* Wrong number args */
try {
    $surface->hasShowTextGlyphs('foo');
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
bool(false)
CairoSurface::hasShowTextGlyphs() expects exactly 0 parameters, 1 given