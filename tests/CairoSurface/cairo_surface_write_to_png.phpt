--TEST--
cairo_surface_write_to_png() function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!in_array('PNG', cairo_available_surfaces())) die('skip - PNG support not available');
?>
--FILE--
<?php
$surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 50, 50);
var_dump($surface);

cairo_surface_write_to_png($surface, dirname(__FILE__) . '/test.png');

$fp = fopen(dirname(__FILE__) . '/stream.png', 'wb');
cairo_surface_write_to_png($surface, $fp);

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// check number of args - should accept ONLY 2
cairo_surface_write_to_png();
cairo_surface_write_to_png($surface);
cairo_surface_write_to_png($surface, 1, 1);

// check arg types, should be surface object, string or resource
cairo_surface_write_to_png(1, $fp);
cairo_surface_write_to_png($surface, 1);
?>
--CLEAN--
<?php
unlink(dirname(__FILE__) . '/test.png');
unlink(dirname(__FILE__) . '/stream.png');
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}

Warning: cairo_surface_write_to_png() expects exactly 2 parameters, 0 given in %s on line %d

Warning: cairo_surface_write_to_png() expects exactly 2 parameters, 1 given in %s on line %d

Warning: cairo_surface_write_to_png() expects exactly 2 parameters, 3 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_surface_write_to_png() must be an instance of CairoSurface, integer given

Warning: cairo_surface_write_to_png() expects parameter 1 to be CairoSurface, integer given in %s on line %d

Warning: cairo_surface_write_to_png() expects parameter 1 to be a string or a stream resource in %s on line %d
