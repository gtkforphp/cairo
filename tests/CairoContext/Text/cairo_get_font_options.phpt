--TEST--
cairo_get_font_options() function
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

var_dump($orig_options = cairo_get_font_options($context));

$options = cairo_font_options_create();
var_dump($orig_options === $options);

cairo_set_font_options($context, $options);
var_dump($options1 = cairo_get_font_options($context));
var_dump($options1 === $options);
var_dump($orig_options === $options1);

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// check number of args - should accept ONLY 1
cairo_get_font_options();
cairo_get_font_options($context, 1);

// check arg types, should be context object
cairo_get_font_options(array());
die; // DO NOT REMOVE THIS - fixes issue in 5.3 with GC giving bogus memleak reports
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
object(CairoFontOptions)#%d (0) {
}
bool(false)
object(CairoFontOptions)#%d (0) {
}
bool(true)
bool(false)

Warning: cairo_get_font_options() expects exactly 1 parameter, 0 given in %s on line %d

Warning: cairo_get_font_options() expects exactly 1 parameter, 2 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_get_font_options() must be an instance of CairoContext, array given

Warning: cairo_get_font_options() expects parameter 1 to be CairoContext, array given in %s on line %d