--TEST--
new CairoSvgSurface [__construct() method ]
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$surface = new CairoSvgSurface(NULL, 50, 50);
var_dump($surface);

$surface = new CairoSvgSurface(dirname(__FILE__) . '/nametest.svg', 50, 50);
var_dump($surface);

$fp = fopen(dirname(__FILE__) . '/streamtest.svg', 'wb');
$surface = new CairoSvgSurface($fp, 50, 50);
var_dump($surface);

try {
    new CairoSvgSurface();
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage();
}
?>
--CLEAN--
<?php
unlink(dirname(__FILE__) . '/nametest.svg');
unlink(dirname(__FILE__) . '/streamtest.svg');
?>
--EXPECTF--
object(CairoSvgSurface)#%d (0) {
}
object(CairoSvgSurface)#%d (0) {
}
object(CairoSvgSurface)#%d (0) {
}
CairoSvgSurface::__construct() expects exactly 3 parameters, 0 given