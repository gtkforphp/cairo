--TEST--
cairo_scaled_font_get_font_face() function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!function_exists('cairo_scaled_font_get_font_face')) die('skip - cairo_scaled_font_get_font_face not available');
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

var_dump(cairo_scaled_font_get_font_face($scaledfont));

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// check number of args - should accept ONLY 1
cairo_scaled_font_get_font_face();
cairo_scaled_font_get_font_face($scaledfont, 1);

// check arg types, should be scaledfont object
cairo_scaled_font_get_font_face(1);
?>
--EXPECTF--
object(CairoToyFontFace)#%d (0) {
}
object(CairoScaledFont)#%d (0) {
}
object(CairoToyFontFace)#%d (0) {
}

Warning: cairo_scaled_font_get_font_face() expects exactly 1 parameter, 0 given in %s on line %d

Warning: cairo_scaled_font_get_font_face() expects exactly 1 parameter, 2 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_scaled_font_get_font_face() must be an instance of CairoScaledFont, integer given

Warning: cairo_scaled_font_get_font_face() expects parameter 1 to be CairoScaledFont, integer given in %s on line %d
