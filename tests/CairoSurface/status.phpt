--TEST--
CairoSurface->status() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$surface = new CairoImageSurface(CairoFormat::ARGB32, 50, 50);
var_dump($surface);

$status = $surface->status();

var_dump($status);
var_dump($status == CairoStatus::SUCCESS);

/* Wrong number args */
try {
    $surface->status('foo');
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
int(0)
bool(true)
CairoSurface::status() expects exactly 0 parameters, 1 given