--TEST--
cairo_mask() function
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

$pattern = cairo_pattern_create_rgb(0.3, 0.3, 0.3);
var_dump($pattern);

cairo_mask($context, $pattern);

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// check number of args - should accept 1 or 2
cairo_mask();
cairo_mask($context);
cairo_mask($context, $pattern, 1);

// check arg types, should be int
cairo_mask(1, $pattern);
cairo_mask($context, array());
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
object(CairoSolidPattern)#%d (0) {
}

Warning: cairo_mask() expects exactly 2 parameters, 0 given in %s on line %d

Warning: cairo_mask() expects exactly 2 parameters, 1 given in %s on line %d

Warning: cairo_mask() expects exactly 2 parameters, 3 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_mask() must be an instance of CairoContext, integer given

Warning: cairo_mask() expects parameter 1 to be CairoContext, integer given in %s on line %d
CAUGHT ERROR: Argument 2 passed to cairo_mask() must be an instance of CairoPattern, array given

Warning: cairo_mask() expects parameter 2 to be CairoPattern, array given in %s on line %d