--TEST--
cairo_scaled_font_text_extents() function
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

var_dump(cairo_scaled_font_text_extents($scaledfont, 'foobar'));

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// check number of args - should accept ONLY 2
cairo_scaled_font_text_extents();
cairo_scaled_font_text_extents($scaledfont, 'foobar', 1);

// check arg types, should be scaledfont object
cairo_scaled_font_text_extents(1, 'foobar');
cairo_scaled_font_text_extents($scaledfont, array());
?>
--EXPECTF--
object(CairoToyFontFace)#%d (0) {
}
object(CairoScaledFont)#%d (0) {
}
array(6) {
  ["x_bearing"]=>
  float(%f)
  ["y_bearing"]=>
  float(%f)
  ["width"]=>
  float(%f)
  ["height"]=>
  float(%f)
  ["x_advance"]=>
  float(%f)
  ["y_advance"]=>
  float(%f)
}

Warning: cairo_scaled_font_text_extents() expects exactly 2 parameters, 0 given in %s on line %d

Warning: cairo_scaled_font_text_extents() expects exactly 2 parameters, 3 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_scaled_font_text_extents() must be an instance of CairoScaledFont, integer given

Warning: cairo_scaled_font_text_extents() expects parameter 1 to be CairoScaledFont, integer given in %s on line %d

Warning: cairo_scaled_font_text_extents() expects parameter 2 to be string, array given in %s on line %d
