--TEST--
cairo_pattern_set_filter function
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

cairo_pattern_set_filter($pattern, CAIRO_FILTER_NEAREST);

$filter = cairo_pattern_get_filter($pattern);
var_dump($filter);
var_dump($filter == CAIRO_FILTER_NEAREST);

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// requires exactly 2 args
cairo_pattern_set_filter();
cairo_pattern_set_filter($pattern);
cairo_pattern_set_filter($pattern, 1, 1);

// arg type are CairoPattern, int
cairo_pattern_set_filter(1, 1);
cairo_pattern_set_filter($pattern, array());
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoSurfacePattern)#%d (0) {
}
int(3)
bool(true)

Warning: cairo_pattern_set_filter() expects exactly 2 parameters, 0 given in %s on line %d

Warning: cairo_pattern_set_filter() expects exactly 2 parameters, 1 given in %s on line %d

Warning: cairo_pattern_set_filter() expects exactly 2 parameters, 3 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_pattern_set_filter() must be an instance of CairoSurfacePattern, integer given

Warning: cairo_pattern_set_filter() expects parameter 1 to be CairoSurfacePattern, integer given in %s on line %d

Warning: cairo_pattern_set_filter() expects parameter 2 to be long, array given in %s on line %d