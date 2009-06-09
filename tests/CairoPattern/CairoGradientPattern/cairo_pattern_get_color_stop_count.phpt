--TEST--
cairo_pattern_get_color_stop_count function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$red = 0.8;
$green = 0.6;
$blue = 0.5;
$alpha = 0.2;

$pattern = cairo_pattern_create_linear(1, 2, 3, 4);
var_dump($pattern);

var_dump(cairo_pattern_get_color_stop_count($pattern));
cairo_pattern_add_color_stop_rgba($pattern, 0.2, $red, $green, $blue, $alpha);
cairo_pattern_add_color_stop_rgba($pattern, 0.4, $red, $green, $blue, $alpha);
cairo_pattern_add_color_stop_rgba($pattern, 0.5, $red, $green, $blue, $alpha);
var_dump(cairo_pattern_get_color_stop_count($pattern));

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// requires 2 args
cairo_pattern_get_color_stop_count();
cairo_pattern_get_color_stop_count($pattern);
cairo_pattern_get_color_stop_count($pattern, 1, 1);

// arg types are CairoPattern, int
cairo_pattern_get_color_stop_count(1, 1);
cairo_pattern_get_color_stop_count($pattern, array());
?>
--EXPECTF--
object(CairoLinearGradient)#%d (0) {
}
int(0)
int(3)