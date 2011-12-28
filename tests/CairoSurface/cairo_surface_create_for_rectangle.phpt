--TEST--
cairo_surface_create_for_rectangle () function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 50, 50);
var_dump($surface);

var_dump(cairo_surface_create_for_rectangle($surface, 0, 0, 25, 25));

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// check number of args - should accept ONLY 5
cairo_surface_create_for_rectangle ();
cairo_surface_create_for_rectangle ($surface);
cairo_surface_create_for_rectangle ($surface, 1);
cairo_surface_create_for_rectangle ($surface, 1, 1);
cairo_surface_create_for_rectangle ($surface, 1, 1, 1, 1);

// check arg types, should be surface object, int int, int
cairo_surface_create_for_rectangle (1, 1, 1, 1);
cairo_surface_create_for_rectangle ($surface, array(), 1, 1);
cairo_surface_create_for_rectangle ($surface, 1, array(), 1);
cairo_surface_create_for_rectangle ($surface, 1, 1, array());
?>
--EXPECTF--
object(CairoImageSurface)#1 (0) {
}
object(CairoSubSurface)#2 (0) {
}

Warning: cairo_surface_create_for_rectangle() expects exactly 5 parameters, 0 given in %s on line %d

Warning: cairo_surface_create_for_rectangle() expects exactly 5 parameters, 1 given in %s on line %d

Warning: cairo_surface_create_for_rectangle() expects exactly 5 parameters, 2 given in %s on line %d

Warning: cairo_surface_create_for_rectangle() expects exactly 5 parameters, 3 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_surface_create_for_rectangle() must be an instance of CairoSurface, integer given

Warning: cairo_surface_create_for_rectangle() expects exactly 5 parameters, 4 given in %s on line %d

Warning: cairo_surface_create_for_rectangle() expects exactly 5 parameters, 4 given in %s on line %d

Warning: cairo_surface_create_for_rectangle() expects exactly 5 parameters, 4 given in %s on line %d

Warning: cairo_surface_create_for_rectangle() expects exactly 5 parameters, 4 given in %s on line %d
