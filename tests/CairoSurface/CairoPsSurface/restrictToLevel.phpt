--TEST--
CairoPsSurface->restrictToLevel() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!in_array('PS', cairo_available_surfaces())) die('skip - PS surface not available');
?>
--FILE--
<?php
$surface = new CairoPsSurface(NULL, 50, 50);
var_dump($surface);

$surface->restrictToLevel(CairoPsLevel::LEVEL_2);

/* Wrong number args */
try {
    $surface->restrictToLevel();
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args 2 */
try {
    $surface->restrictToLevel(1, 1);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type */
try {
    $surface->restrictToLevel(array());
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoPsSurface)#%d (0) {
}
CairoPsSurface::restrictToLevel() expects exactly 1 parameter, 0 given
CairoPsSurface::restrictToLevel() expects exactly 1 parameter, 2 given
CairoPsSurface::restrictToLevel() expects parameter 1 to be long, array given