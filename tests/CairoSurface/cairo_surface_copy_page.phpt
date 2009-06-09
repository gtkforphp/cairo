--TEST--
cairo_surface_copy_page() function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!function_exists('cairo_surface_copy_page')) die('skip - cairo_surface_copy_page not available');
?>
--FILE--
<?php
$surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 50, 50);
var_dump($surface);

cairo_surface_copy_page($surface);

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// check number of args - should accept ONLY 1
cairo_surface_copy_page();
cairo_surface_copy_page($surface, 1);

// check arg types, should be surface object
cairo_surface_copy_page(1);
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}

Warning: cairo_surface_copy_page() expects exactly 1 parameter, 0 given in %s on line %d

Warning: cairo_surface_copy_page() expects exactly 1 parameter, 2 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_surface_copy_page() must be an instance of CairoSurface, integer given

Warning: cairo_surface_copy_page() expects parameter 1 to be CairoSurface, integer given in %s on line %d