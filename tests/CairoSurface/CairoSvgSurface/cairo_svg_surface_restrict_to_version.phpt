--TEST--
cairo_svg_surface_restrict_to_version() function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!in_array('SVG', cairo_available_surfaces())) die('skip - SVG surface not available');
?>
--FILE--
<?php
$surface = cairo_svg_surface_create(NULL, 50, 50);
var_dump($surface);

cairo_svg_surface_restrict_to_version($surface, CAIRO_SVG_VERSION_1_1);

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// check number of args - should accept ONLY 2
cairo_svg_surface_restrict_to_version();
cairo_svg_surface_restrict_to_version($surface);
cairo_svg_surface_restrict_to_version($surface, 1, 1);

// check arg types, should be svg surface object, int
cairo_svg_surface_restrict_to_version(1, 1, 1);
cairo_svg_surface_restrict_to_version($surface, array());
?>
--EXPECTF--
object(CairoSvgSurface)#%d (0) {
}

Warning: cairo_svg_surface_restrict_to_version() expects exactly 2 parameters, 0 given in %s on line %d

Warning: cairo_svg_surface_restrict_to_version() expects exactly 2 parameters, 1 given in %s on line %d

Warning: cairo_svg_surface_restrict_to_version() expects exactly 2 parameters, 3 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_svg_surface_restrict_to_version() must be an instance of CairoSvgSurface, integer given

Warning: cairo_svg_surface_restrict_to_version() expects exactly 2 parameters, 3 given in %s on line %d

Warning: cairo_svg_surface_restrict_to_version() expects parameter 2 to be long, array given in %s on line %d