--TEST--
CairoSvgSurface->restrictToVersion() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!in_array('SVG', Cairo::availableSurfaces())) die('skip - SVG surface not available');
?>
--FILE--
<?php
$surface = new CairoSvgSurface(NULL, 50, 50);
var_dump($surface);

$surface->restrictToVersion(CairoSvgVersion::VERSION_1_1);

/* Wrong number args */
try {
    $surface->restrictToVersion();
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args 2 */
try {
    $surface->restrictToVersion(1, 1);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type */
try {
    $surface->restrictToVersion(array());
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoSvgSurface)#%d (0) {
}
CairoSvgSurface::restrictToVersion() expects exactly 1 parameter, 0 given
CairoSvgSurface::restrictToVersion() expects exactly 1 parameter, 2 given
CairoSvgSurface::restrictToVersion() expects parameter 1 to be long, array given