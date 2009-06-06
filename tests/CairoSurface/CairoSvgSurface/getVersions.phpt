--TEST--
CairoSvgSurface::getVersions() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!in_array('SVG', cairo_available_surfaces())) die('skip - SVG surface not available');
?>
--FILE--
<?php
var_dump(CairoSvgSurface::getVersions());

/* Wrong number args */
CairoSvgSurface::getVersions('foo');
?>
--EXPECTF--
array(2) {
  [0]=>
  int(0)
  [1]=>
  int(1)
}

Warning: CairoSvgSurface::getVersions() expects exactly 0 parameters, 1 given in %s on line %d