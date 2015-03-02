--TEST--
cairo_scaled_font_get_type() function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!function_exists('cairo_scaled_font_get_type')) die('skip - cairo_scaled_font_get_type not available');
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

var_dump(cairo_scaled_font_get_type($scaledfont));

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// requires exactly 1 arg
cairo_scaled_font_get_type();
cairo_scaled_font_get_type($scaledfont);

// arg type is CairoScaledFont
cairo_scaled_font_get_type(1);
cairo_scaled_font_get_type($scaledfont);
?>
--EXPECTF--
object(CairoToyFontFace)#%d (0) {
}
object(CairoScaledFont)#%d (0) {
}
int(%d)

Warning: cairo_scaled_font_get_type() expects exactly 1 parameter, 0 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_scaled_font_get_type() must be an instance of CairoScaledFont, integer given

Warning: cairo_scaled_font_get_type() expects parameter 1 to be CairoScaledFont, integer given in %s on line %d
