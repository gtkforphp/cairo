--TEST--
cairo_get_scaled_font() function
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

var_dump(cairo_get_scaled_font($context));

/* create scaled font with new font face, font options, matrix */
include(dirname(__FILE__) . '/create_toyfont.inc');
$matrix1 = cairo_matrix_init(1);
$matrix2 = cairo_matrix_init(1, 1);
$options = cairo_font_options_create();

$scaled = cairo_scaled_font_create($fontface, $matrix1, $matrix2, $options);

cairo_set_scaled_font($context, $scaled);
var_dump(cairo_get_scaled_font($context));

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// check number of args - wants 1
cairo_get_scaled_font();
cairo_get_scaled_font($context, 1);

// check arg types, should be CairoContext
cairo_get_scaled_font(array());

//die; // DO NOT REMOVE THIS - fixes issue in 5.3 with GC giving bogus memleak reports
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
object(CairoScaledFont)#%d (0) {
}
object(CairoScaledFont)#%d (0) {
}

Warning: cairo_get_scaled_font() expects exactly 1 parameter, 0 given in %s on line %d

Warning: cairo_get_scaled_font() expects exactly 1 parameter, 2 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_get_scaled_font() must be an instance of CairoContext, array given

Warning: cairo_get_scaled_font() expects parameter 1 to be CairoContext, array given in %s on line %d