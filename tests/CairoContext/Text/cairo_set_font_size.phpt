--TEST--
cairo_set_font_size() function
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

cairo_set_font_size($context, 15);

cairo_set_font_matrix($context, cairo_matrix_init(5, 15));

cairo_set_font_size($context, 10);

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// check number of args - should accept ONLY 2
cairo_set_font_size();
cairo_set_font_size($context);
cairo_set_font_size($context, 1, 1);

// check arg types, should be context object, double
cairo_set_font_size(array(), 1);
cairo_set_font_size($context, array());

// DO NOT REMOVE: workaround for GC-related bug in 5.3 
die;
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}

Warning: cairo_set_font_size() expects exactly 2 parameters, 0 given in %s on line %d

Warning: cairo_set_font_size() expects exactly 2 parameters, 1 given in %s on line %d

Warning: cairo_set_font_size() expects exactly 2 parameters, 3 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_set_font_size() must be an instance of CairoContext, array given

Warning: cairo_set_font_size() expects parameter 1 to be CairoContext, array given in %s on line %d

Warning: cairo_set_font_size() expects parameter 2 to be double, array given in %s on line %d
