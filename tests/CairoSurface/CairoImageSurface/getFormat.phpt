--TEST--
CairoImageSurface->getFormat() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$surface = new CairoImageSurface(CairoFormat::ARGB32, 50, 50);
var_dump($surface);

var_dump($surface->getFormat());

/* Wrong number args */
try {
    $surface->getFormat('foo');
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
int(0)
CairoImageSurface::getFormat() expects exactly 0 parameters, 1 given