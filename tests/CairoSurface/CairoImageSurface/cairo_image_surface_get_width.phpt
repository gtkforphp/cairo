--TEST--
cairo_image_surface_get_width() function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 50, 50);
var_dump($surface);

var_dump(cairo_image_surface_get_width($surface));

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// check number of args - should accept ONLY 1
cairo_image_surface_get_width();
cairo_image_surface_get_width($surface, 1);

// check arg types, should be an image surface object
cairo_image_surface_get_width(null);
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
int(50)

Warning: cairo_image_surface_get_width() expects exactly 1 parameter, 0 given in %s on line %d

Warning: cairo_image_surface_get_width() expects exactly 1 parameter, 2 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_image_surface_get_width() must be an instance of CairoImageSurface, null given

Warning: cairo_image_surface_get_width() expects parameter 1 to be CairoImageSurface, null given in %s on line %d