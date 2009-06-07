--TEST--
CairoImageSurface->getWidth() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$surface = new CairoImageSurface(CairoFormat::ARGB32, 50, 50);
var_dump($surface);

var_dump($surface->getWidth());

/* Wrong number args */
try {
    $surface->getWidth('foo');
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
int(50)
CairoImageSurface::getWidth() expects exactly 0 parameters, 1 given