--TEST--
CairoPsSurface->getEps() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!in_array('PS', Cairo::availableSurfaces())) die('skip - PS surface not available');
if(!method_exists('CairoPsSurface', 'getEps')) die('skip - CairoPsSurface->getEps not available');
?>
--FILE--
<?php
$surface = new CairoPsSurface(NULL, 50, 50);
var_dump($surface);

var_dump($surface->getEps());

/* Wrong number args */
try {
    $surface->getEps('foo');
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoPsSurface)#%d (0) {
}
bool(false)
CairoPsSurface::getEps() expects exactly 0 parameters, 1 given