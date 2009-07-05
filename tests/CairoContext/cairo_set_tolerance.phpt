--TEST--
cairo_set_tolerance() function
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

cairo_set_tolerance($context, 7);
var_dump(cairo_get_tolerance($context));

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// check number of args - should accept 1 or 2
cairo_set_tolerance();
cairo_set_tolerance($context);
cairo_set_tolerance($context, 1, 1);

// check arg types, should be int
cairo_set_tolerance(1, 1);
cairo_set_tolerance($context, array());
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
float(7)

Warning: cairo_set_tolerance() expects exactly 2 parameters, 0 given in %s on line %d

Warning: cairo_set_tolerance() expects exactly 2 parameters, 1 given in %s on line %d

Warning: cairo_set_tolerance() expects exactly 2 parameters, 3 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_set_tolerance() must be an instance of CairoContext, integer given

Warning: cairo_set_tolerance() expects parameter 1 to be CairoContext, integer given in %s on line %d

Warning: cairo_set_tolerance() expects parameter 2 to be double, array given in %s on line %d