--TEST--
cairo_pattern_get_filter function
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

cairo_pattern_set_filter($pattern, CAIRO_FILTER_GOOD);
$filter = cairo_pattern_get_filter($pattern);
var_dump($filter);
var_dump($filter == CAIRO_FILTER_GOOD);

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// requires exactly 1 arg
cairo_pattern_get_filter();
cairo_pattern_get_filter($pattern, 1);

// arg type is CairoPattern
cairo_pattern_get_filter(1);
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoSurfacePattern)#%d (0) {
}
int(1)
bool(true)

Warning: cairo_pattern_get_filter() expects exactly 1 parameter, 0 given in %s on line %d

Warning: cairo_pattern_get_filter() expects exactly 1 parameter, 2 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_pattern_get_filter() must be an instance of CairoSurfacePattern, integer given

Warning: cairo_pattern_get_filter() expects parameter 1 to be CairoSurfacePattern, integer given in %s on line %d