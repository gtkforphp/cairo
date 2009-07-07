--TEST--
cairo_mask_surface() function
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

$surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 50, 50);
var_dump($surface);

cairo_mask_surface($context, $surface, 1, 1);

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// check number of args - should accept 2 or 3 or 4
cairo_mask_surface();
cairo_mask_surface($context);
cairo_mask_surface($context, $surface, 1, 1, 1);

// check arg types, should be int
cairo_mask_surface(1, $surface);
cairo_mask_surface($context, array());
cairo_mask_surface($context, $surface, array());
cairo_mask_surface($context, $surface, 1, array());

// DO NOT REMOVE: workaround for GC-related bug in 5.3
die;
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
object(CairoImageSurface)#%d (0) {
}

Warning: cairo_mask_surface() expects at least 2 parameters, 0 given in %s on line %d

Warning: cairo_mask_surface() expects at least 2 parameters, 1 given in %s on line %d

Warning: cairo_mask_surface() expects at most 4 parameters, 5 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_mask_surface() must be an instance of CairoContext, integer given

Warning: cairo_mask_surface() expects parameter 1 to be CairoContext, integer given in %s on line %d
CAUGHT ERROR: Argument 2 passed to cairo_mask_surface() must be an instance of CairoSurface, array given

Warning: cairo_mask_surface() expects parameter 2 to be CairoSurface, array given in %s on line %d

Warning: cairo_mask_surface() expects parameter 3 to be double, array given in %s on line %d

Warning: cairo_mask_surface() expects parameter 4 to be double, array given in %s on line %d
