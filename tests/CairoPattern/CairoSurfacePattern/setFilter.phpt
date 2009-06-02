--TEST--
CairoSurfacePattern->setFilter() method
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

$pattern->setFilter(CairoFilter::NEAREST);

$filter = $pattern->getFilter();
var_dump($filter);
var_dump($filter == CairoFilter::NEAREST);

try {
    $pattern->getFilter('foo');
} catch (CairoException $e) {
    echo $e->getMessage();
}
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoSurfacePattern)#%d (0) {
}
int(3)
bool(true)
CairoSurfacePattern::getFilter() expects exactly 0 parameters, 1 given