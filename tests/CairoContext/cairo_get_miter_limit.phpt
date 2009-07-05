--TEST--
cairo_get_miter_limit() function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 50, 50);
var_dump($surface);

$context = cairo_create($surface);
var_dump($context);

var_dump(cairo_get_miter_limit($context));

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// check number of args - should accept ONLY 1
cairo_get_miter_limit();
cairo_get_miter_limit($context, 1);

// check arg types, should be context object
cairo_get_miter_limit(1);
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
float(10)

Warning: cairo_get_miter_limit() expects exactly 1 parameter, 0 given in %s on line %d

Warning: cairo_get_miter_limit() expects exactly 1 parameter, 2 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_get_miter_limit() must be an instance of CairoContext, integer given

Warning: cairo_get_miter_limit() expects parameter 1 to be CairoContext, integer given in %s on line %d