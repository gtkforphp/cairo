--TEST--
cairo_pattern_create_for_surface function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 50, 50);
var_dump($surface);

$pattern = cairo_pattern_create_for_surface($surface);
var_dump($pattern);

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// requires exactly 1 arg
cairo_pattern_create_for_surface();
cairo_pattern_create_for_surface($surface, 1);

// arg types is CairoSurface
cairo_pattern_create_for_surface(1);
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoSurfacePattern)#%d (0) {
}

Warning: cairo_pattern_create_for_surface() expects exactly 1 parameter, 0 given in %s on line %d

Warning: cairo_pattern_create_for_surface() expects exactly 1 parameter, 2 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_pattern_create_for_surface() must be an instance of CairoSurface, integer given

Warning: cairo_pattern_create_for_surface() expects parameter 1 to be CairoSurface, integer given in %s on line %d