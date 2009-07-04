--TEST--
cairo_show_text() function
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

cairo_show_text($context, 'foobar');

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// check number of args - should accept ONLY 2
cairo_show_text();
cairo_show_text($context);
cairo_show_text($context, 'foobar', 1);

// check arg types, should be context object, string
cairo_show_text(array(), 'foobar');
cairo_show_text($context, array());
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
CairoContext::showText() expects exactly 1 parameter, 0 given
CairoContext::showText() expects exactly 1 parameter, 2 given
CairoContext::showText() expects parameter 1 to be string, array given