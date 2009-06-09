--TEST--
cairo_svg_version_to_string() function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!in_array('SVG', cairo_available_surfaces())) die('skip - SVG surface not available');
?>
--FILE--
<?php
echo cairo_svg_version_to_string(CAIRO_SVG_VERSION_1_1), PHP_EOL;

// check number of args - should accept ONLY 1
cairo_svg_version_to_string();
cairo_svg_version_to_string(1, 1);

// check arg types, should be int
cairo_svg_version_to_string(array());
?>
--EXPECTF--
SVG 1.1

Warning: cairo_svg_version_to_string() expects exactly 1 parameter, 0 given in %s on line %d

Warning: cairo_svg_version_to_string() expects exactly 1 parameter, 2 given in %s on line %d

Warning: cairo_svg_version_to_string() expects parameter 1 to be long, array given in %s on line %d