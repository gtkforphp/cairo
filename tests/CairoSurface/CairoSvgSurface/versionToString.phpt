--TEST--
CairoSvgSurface::versionToString() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!in_array('SVG', cairo_available_surfaces())) die('skip - SVG surface not available');
?>
--FILE--
<?php
echo CairoSvgSurface::versionToString(CairoSvgVersion::VERSION_1_1);

/* Wrong number args */
CairoSvgSurface::versionToString();

/* Wrong number args 2 */
CairoSvgSurface::versionToString(1, 1);

/* Wrong arg type */
CairoSvgSurface::versionToString(array());
?>
--EXPECTF--
SVG 1.1
Warning: CairoSvgSurface::versionToString() expects exactly 1 parameter, 0 given in %s on line %d

Warning: CairoSvgSurface::versionToString() expects exactly 1 parameter, 2 given in %s on line %d

Warning: CairoSvgSurface::versionToString() expects parameter 1 to be long, array given in %s on line %d