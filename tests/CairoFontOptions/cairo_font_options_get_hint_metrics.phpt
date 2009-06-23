--TEST--
cairo_font_options_get_hint_metrics() function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$options = cairo_font_options_create();
var_dump($options);

var_dump(cairo_font_options_get_hint_metrics($options));

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// check number of args - should accept ONLY 1
cairo_font_options_get_hint_metrics();
cairo_font_options_get_hint_metrics($options, 1);

// check arg types, should be options object
cairo_font_options_get_hint_metrics(1);
?>
--EXPECTF--
object(CairoFontOptions)#%d (0) {
}
int(0)

Warning: cairo_font_options_get_hint_metrics() expects exactly 1 parameter, 0 given in %s on line %d

Warning: cairo_font_options_get_hint_metrics() expects exactly 1 parameter, 2 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_font_options_get_hint_metrics() must be an instance of CairoFontOptions, integer given

Warning: cairo_font_options_get_hint_metrics() expects parameter 1 to be CairoFontOptions, integer given in %s on line %d