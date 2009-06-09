--TEST--
cairo_pattern_get_type() function
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

var_dump(cairo_pattern_get_type($pattern));

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// requires exactly 1 arg
cairo_pattern_get_type();
cairo_pattern_get_type($pattern);

// arg type is CairoSurface
cairo_pattern_get_type(1);
cairo_pattern_get_type($pattern);
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoSurfacePattern)#%d (0) {
}
int(1)

Warning: cairo_pattern_get_type() expects exactly 1 parameter, 0 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_pattern_get_type() must be an instance of CairoPattern, integer given

Warning: cairo_pattern_get_type() expects parameter 1 to be CairoPattern, integer given in %s on line %d