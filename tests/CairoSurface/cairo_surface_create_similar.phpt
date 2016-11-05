--TEST--
cairo_surface_create_similar () function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 50, 50);
var_dump($surface);

var_dump(cairo_surface_create_similar($surface, CAIRO_CONTENT_COLOR, 10, 10));

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// check number of args - should accept ONLY 4
cairo_surface_create_similar ();
cairo_surface_create_similar ($surface);
cairo_surface_create_similar ($surface, 1);
cairo_surface_create_similar ($surface, 1, 1);
cairo_surface_create_similar ($surface, 1, 1, 1, 1);

// check arg types, should be surface object, int int, int
cairo_surface_create_similar (1, 1, 1, 1);
cairo_surface_create_similar ($surface, array(), 1, 1);
cairo_surface_create_similar ($surface, 1, array(), 1);
cairo_surface_create_similar ($surface, 1, 1, array());
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoImageSurface)#%d (0) {
}

Warning: cairo_surface_create_similar() expects exactly 4 parameters, 0 given in %s on line %d

Warning: cairo_surface_create_similar() expects exactly 4 parameters, 1 given in %s on line %d

Warning: cairo_surface_create_similar() expects exactly 4 parameters, 2 given in %s on line %d

Warning: cairo_surface_create_similar() expects exactly 4 parameters, 3 given in %s on line %d

Warning: cairo_surface_create_similar() expects exactly 4 parameters, 5 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_surface_create_similar() must be an instance of CairoSurface, integer given

Warning: cairo_surface_create_similar() expects parameter 1 to be CairoSurface, integer given in %s on line %d

Warning: cairo_surface_create_similar() expects parameter 2 to be long, array given in %s on line %d

Warning: cairo_surface_create_similar() expects parameter 3 to be long, array given in %s on line %d

Warning: cairo_surface_create_similar() expects parameter 4 to be long, array given in %s on line %d
