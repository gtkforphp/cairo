--TEST--
CairoSvgSurface::versionToString() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!in_array('SVG', Cairo::availableSurfaces())) die('skip - SVG surface not available');
?>
--FILE--
<?php
echo CairoSvgSurface::versionToString(CairoSvgVersion::VERSION_1_1), PHP_EOL;

/* Wrong number args */
try {
    CairoSvgSurface::versionToString();
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args 2 */
try {
    CairoSvgSurface::versionToString(1, 1);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type */
try {
    CairoSvgSurface::versionToString(array());
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
SVG 1.1
CairoSvgSurface::versionToString() expects exactly 1 parameter, 0 given
CairoSvgSurface::versionToString() expects exactly 1 parameter, 2 given
CairoSvgSurface::versionToString() expects parameter 1 to be long, array given