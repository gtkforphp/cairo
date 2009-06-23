--TEST--
cairo_font_options_set_subpixel_order() function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$options = cairo_font_options_create();
var_dump($options);

cairo_font_options_set_subpixel_order($options, CAIRO_SUBPIXEL_ORDER_RGB);

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// check number of args - should accept ONLY 2
cairo_font_options_set_subpixel_order();
cairo_font_options_set_subpixel_order($options);
cairo_font_options_set_subpixel_order($options, CAIRO_SUBPIXEL_ORDER_RGB, 1);

// check arg types, should be fontoptions objects
cairo_font_options_set_subpixel_order(1, CAIRO_SUBPIXEL_ORDER_RGB);
cairo_font_options_set_subpixel_order($options, array());
?>
--EXPECTF--
object(CairoFontOptions)#%d (0) {
}

Warning: cairo_font_options_set_subpixel_order() expects exactly 2 parameters, 0 given in %s on line %d

Warning: cairo_font_options_set_subpixel_order() expects exactly 2 parameters, 1 given in %s on line %d

Warning: cairo_font_options_set_subpixel_order() expects exactly 2 parameters, 3 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_font_options_set_subpixel_order() must be an instance of CairoFontOptions, integer given

Warning: cairo_font_options_set_subpixel_order() expects parameter 1 to be CairoFontOptions, integer given in %s on line %d

Warning: cairo_font_options_set_subpixel_order() expects parameter 2 to be long, array given in %s on line %d