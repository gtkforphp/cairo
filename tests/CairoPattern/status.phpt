--TEST--
CairoPattern->status() method
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

$status = $pattern->status();
var_dump($status);
var_dump($status == CairoStatus::SUCCESS);

try {
    $pattern->status('foo');
    trigger_error('status requires no args');
} catch (CairoException $e) {
    echo $e->getMessage();
}
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoSurfacePattern)#%d (0) {
}
int(0)
bool(true)
CairoPattern::status() expects exactly 0 parameters, 1 given