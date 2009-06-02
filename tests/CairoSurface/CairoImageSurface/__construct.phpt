--TEST--
new CairoImageSurface [__construct() method ]
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$surface = new CairoImageSurface(CairoFormat::ARGB32, 50, 50);
var_dump($surface);

try {
    new CairoImageSurface();
    trigger_error('CairoException was not thrown for CairoImageSurface constructor');
} catch (CairoException $e) {
    echo $e->getMessage();
}
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
CairoImageSurface::__construct() expects exactly 3 parameters, 0 given