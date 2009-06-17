--TEST--
cairo_has_current_point() function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!function_exists('cairo_has_current_point')) die('skip - cairo_has_current_point not available');
?>
--FILE--
<?php
$surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 50, 50);
var_dump($surface);

$context = cairo_create($surface);
var_dump($context);

var_dump(cairo_has_current_point($context));

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// check number of args - should accept 1
cairo_has_current_point();
cairo_has_current_point($context, 1);

// check arg types, should be context object
cairo_has_current_point(1);
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
bool(false)

Warning: cairo_has_current_point() expects exactly 1 parameter, 0 given in %s on line %d

Warning: cairo_has_current_point() expects exactly 1 parameter, 2 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_has_current_point() must be an instance of CairoContext, integer given

Warning: cairo_has_current_point() expects parameter 1 to be CairoContext, integer given in %s on line %d