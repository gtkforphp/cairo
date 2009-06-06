--TEST--
CairoPsSurface::levelToString() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!in_array('PS', cairo_available_surfaces())) die('skip - PS surface not available');
?>
--FILE--
<?php
echo CairoPsSurface::levelToString(CairoPsLevel::LEVEL_2);

/* Wrong number args */
CairoPsSurface::levelToString();

/* Wrong number args 2 */
CairoPsSurface::levelToString(1, 1);

/* Wrong arg type */
CairoPsSurface::levelToString(array());
?>
--EXPECTF--
PS Level 2
Warning: CairoPsSurface::levelToString() expects exactly 1 parameter, 0 given in %s on line %d

Warning: CairoPsSurface::levelToString() expects exactly 1 parameter, 2 given in %s on line %d

Warning: CairoPsSurface::levelToString() expects parameter 1 to be long, array given in %s on line %d