--TEST--
cairo_set_scaled_font() function
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

/* set font face, font options, matrix */
$orig_matrix = cairo_matrix_init();
cairo_set_matrix($context, $orig_matrix);
$orig_options = cairo_font_options_create();
cairo_set_font_options($context, $orig_options);
include(dirname(__FILE__) . '/create_toyfont.inc');
$orig_fontface = $fontface;
cairo_set_font_face($context, $orig_fontface);

/* create scaled font with new font face, font options, matrix */
include(dirname(__FILE__) . '/create_toyfont.inc');
$matrix1 = cairo_matrix_init(1);
$matrix2 = cairo_matrix_init(1, 1);
$options = cairo_font_options_create();

$scaled = cairo_scaled_font_create($fontface, $matrix1, $matrix2, $options);
var_dump($scaled);

cairo_set_scaled_font($context, $scaled);

/* compare new values to original values */
var_dump($matrix1 === $orig_matrix);
var_dump($fontface === $orig_fontface);
var_dump($options === $orig_options);

/* compare matrix, font face, font options, scaled font */
var_dump($matrix1 === cairo_get_font_matrix($context));
var_dump($fontface === cairo_get_font_face($context));
var_dump($options === cairo_get_font_options($context));
var_dump($scaled === cairo_get_scaled_font($context));

/* create scaled font with new font face, font options, matrix */
include(dirname(__FILE__) . '/create_toyfont.inc');
$matrix1 = cairo_matrix_init(1);
$matrix2 = cairo_matrix_init(1, 1);
$options = cairo_font_options_create();

$scaled = cairo_scaled_font_create($fontface, $matrix1, $matrix2, $options);

cairo_set_scaled_font($context, $scaled);

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// check number of args - wants 2
cairo_set_scaled_font();
cairo_set_scaled_font($context);
cairo_set_scaled_font($context, $scaled, 1);

// check arg types, should be CairoContext, CairoScaledFont
cairo_set_scaled_font(array(), $scaled);
cairo_set_scaled_font($context, array());

die; // DO NOT REMOVE THIS - fixes issue in 5.3 with GC giving bogus memleak reports
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
object(CairoScaledFont)#%d (0) {
}
bool(false)
bool(false)
bool(false)
bool(true)
bool(true)
bool(true)
bool(true)

Warning: cairo_set_scaled_font() expects exactly 2 parameters, 0 given in %s on line %d

Warning: cairo_set_scaled_font() expects exactly 2 parameters, 1 given in %s on line %d

Warning: cairo_set_scaled_font() expects exactly 2 parameters, 3 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_set_scaled_font() must be an instance of CairoContext, array given

Warning: cairo_set_scaled_font() expects parameter 1 to be CairoContext, array given in %s on line %d
CAUGHT ERROR: Argument 2 passed to cairo_set_scaled_font() must be an instance of CairoScaledFont, array given

Warning: cairo_set_scaled_font() expects parameter 2 to be CairoScaledFont, array given in %s on line %d
