--TEST--
CairoSurfacePattern->getExtend() method
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

$extend = $pattern->getExtend();
var_dump($extend);
var_dump($extend == CairoExtend::NONE);

/* Total number of args needed = 0 */
try {
    $pattern->getExtend(1);
    trigger_error('getExtend with too many args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoSurfacePattern)#%d (0) {
}
int(0)
bool(true)
CairoSurfacePattern::getExtend() expects exactly 0 parameters, 1 given