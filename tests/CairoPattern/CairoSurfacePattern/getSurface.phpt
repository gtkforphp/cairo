--TEST--
CairoSurfacePattern->getSurface() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$surface = new CairoImageSurface(CairoFormat::ARGB32, 50, 50);
var_dump($surface);

$pattern = new CairoSurfacePattern($surface);
var_dump($pattern);

$surface2 = $pattern->getSurface();
var_dump($surface2);
var_dump($surface === $surface2);

try {
    $pattern->getSurface('foo');
} catch (CairoException $e) {
    echo $e->getMessage();
}
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoSurfacePattern)#%d (0) {
}
object(CairoImageSurface)#%d (0) {
}
bool(true)
CairoSurfacePattern::getSurface() expects exactly 0 parameters, 1 given