--TEST--
cairo_image_surface_get_format() function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 50, 50);
var_dump($surface);

var_dump(strlen(cairo_image_surface_get_data($surface)));

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// check number of args - should accept ONLY 1
cairo_image_surface_get_data();
cairo_image_surface_get_data($surface, 1);

// check arg types, should be an image surface object
cairo_image_surface_get_data(null);
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
int(10000)

Warning: cairo_image_surface_get_data() expects exactly 1 parameter, 0 given in %s on line %d

Warning: cairo_image_surface_get_data() expects exactly 1 parameter, 2 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_image_surface_get_data() must be an instance of CairoImageSurface, null given

Warning: cairo_image_surface_get_data() expects parameter 1 to be CairoImageSurface, null given in %s on line %d
