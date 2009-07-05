--TEST--
cairo_set_font_options() function
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

$options = cairo_font_options_create();
var_dump($options);

cairo_set_font_options($context, $options);
$options1 = cairo_get_font_options($context);

var_dump($options === $options1);

$options2 = cairo_font_options_create();
cairo_set_font_options($context, $options2);
$options1 = cairo_get_font_options($context);

var_dump($options2 === $options1);

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// check number of args - should accept ONLY 2
cairo_set_font_options();
cairo_set_font_options($context);
cairo_set_font_options($context, $options2, 1);

// check arg types, should be context object, cairo matrix
cairo_set_font_options(array(), $options2);
cairo_set_font_options($context, array());

die; // DO NOT REMOVE THIS - fixes issue in 5.3 with GC giving bogus memleak reports
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
object(CairoFontOptions)#%d (0) {
}
bool(true)
bool(true)

Warning: cairo_set_font_options() expects exactly 2 parameters, 0 given in %s on line %d

Warning: cairo_set_font_options() expects exactly 2 parameters, 1 given in %s on line %d

Warning: cairo_set_font_options() expects exactly 2 parameters, 3 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_set_font_options() must be an instance of CairoContext, array given

Warning: cairo_set_font_options() expects parameter 1 to be CairoContext, array given in %s on line %d
CAUGHT ERROR: Argument 2 passed to cairo_set_font_options() must be an instance of CairoFontOptions, array given

Warning: cairo_set_font_options() expects parameter 2 to be CairoFontOptions, array given in %s on line %d