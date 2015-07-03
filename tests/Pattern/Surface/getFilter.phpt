--TEST--
CairoSurfacePattern->getFilter() method
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

$pattern->setFilter(CairoFilter::GOOD);
$filter = $pattern->getFilter();
var_dump($filter);
var_dump($filter == CairoFilter::GOOD);

/* Total number of args needed = 0 */
try {
    $pattern->getFilter(1);
    trigger_error('getFilter with too many args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoSurfacePattern)#%d (0) {
}
int(1)
bool(true)
CairoSurfacePattern::getFilter() expects exactly 0 parameters, 1 given