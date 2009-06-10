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

$pattern->setExtend(CairoExtend::PAD);

$extend = $pattern->getExtend();
var_dump($extend);
var_dump($extend == CairoExtend::PAD);

/* Total number of args needed = 1 */
try {
    $pattern->setExtend();
    trigger_error('setExtend with no args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
try {
    $pattern->setExtend(1, 1);
    trigger_error('setExtend with too many args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* arg must be int or castable to int */
try {
    $pattern->setExtend(array());
    trigger_error('Arg 1 must be int');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoSurfacePattern)#%d (0) {
}
int(3)
bool(true)
CairoSurfacePattern::setExtend() expects exactly 1 parameter, 0 given
CairoSurfacePattern::setExtend() expects exactly 1 parameter, 2 given
CairoSurfacePattern::setExtend() expects parameter 1 to be long, array given