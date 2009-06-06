--TEST--
CairoPsSurface::getLevels() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!in_array('PS', cairo_available_surfaces())) die('skip - PS surface not available');
?>
--FILE--
<?php
var_dump(CairoPsSurface::getLevels());

/* Wrong number args */
CairoPsSurface::getLevels('foo');
?>
--EXPECTF--
array(2) {
  [0]=>
  int(0)
  [1]=>
  int(1)
}

Warning: CairoPsSurface::getLevels() expects exactly 0 parameters, 1 given in %s on line %d