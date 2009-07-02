--TEST--
cairo_scaled_font_create() function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
include(dirname(__FILE__) . '/create_toyfont.inc');
var_dump($fontface);

$matrix1 = cairo_matrix_init(1);
$matrix2 = cairo_matrix_init(1, 1);
$options = cairo_font_options_create();

$scaledfont = cairo_scaled_font_create($fontface, $matrix1, $matrix2, $options);
var_dump($scaledfont);

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// check number of args - wants 4
cairo_scaled_font_create();
cairo_scaled_font_create($fontface);
cairo_scaled_font_create($fontface, $matrix1);
cairo_scaled_font_create($fontface, $matrix1, $matrix2);
cairo_scaled_font_create($fontface, $matrix1, $matrix2, $options, 1);

// check arg types, should be CairoFontFace, CairoMatrix, CairoMatrix, CairoFontOptions
cairo_scaled_font_create(array(), $matrix1, $matrix2, $options);
cairo_scaled_font_create($fontface, array(), $matrix2, $options);
cairo_scaled_font_create($fontface, $matrix1, array(), $options);
cairo_scaled_font_create($fontface, $matrix1, $matrix2, array());
?>
--EXPECTF--
object(CairoToyFontFace)#%d (0) {
}
object(CairoScaledFont)#%d (0) {
}

Warning: cairo_scaled_font_create() expects exactly 4 parameters, 0 given in %s on line %d

Warning: cairo_scaled_font_create() expects exactly 4 parameters, 1 given in %s on line %d

Warning: cairo_scaled_font_create() expects exactly 4 parameters, 2 given in %s on line %d

Warning: cairo_scaled_font_create() expects exactly 4 parameters, 3 given in %s on line %d

Warning: cairo_scaled_font_create() expects exactly 4 parameters, 5 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_scaled_font_create() must be an instance of CairoFontFace, array given

Warning: cairo_scaled_font_create() expects parameter 1 to be CairoFontFace, array given in %s on line %d
CAUGHT ERROR: Argument 2 passed to cairo_scaled_font_create() must be an instance of CairoMatrix, array given

Warning: cairo_scaled_font_create() expects parameter 2 to be CairoMatrix, array given in %s on line %d
CAUGHT ERROR: Argument 3 passed to cairo_scaled_font_create() must be an instance of CairoMatrix, array given

Warning: cairo_scaled_font_create() expects parameter 3 to be CairoMatrix, array given in %s on line %d
CAUGHT ERROR: Argument 4 passed to cairo_scaled_font_create() must be an instance of CairoFontOptions, array given

Warning: cairo_scaled_font_create() expects parameter 4 to be CairoFontOptions, array given in %s on line %d