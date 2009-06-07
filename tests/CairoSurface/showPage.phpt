--TEST--
CairoSurface->showPage() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!method_exists('CairoSurface', 'showPage')) die('skip - CairoSurface->showPage not available');
?>
--FILE--
<?php
$surface = new CairoImageSurface(CairoFormat::ARGB32, 50, 50);
var_dump($surface);

$surface->showPage();

/* Wrong number args */
try {
    $surface->showPage('foo');
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
CairoSurface::showPage() expects exactly 0 parameters, 1 given