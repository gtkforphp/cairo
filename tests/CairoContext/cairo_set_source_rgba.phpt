--TEST--
cairo_set_source_rgba() function
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

cairo_set_source_rgba($context, 0.1, 0.1, 0.1, 0.5);
cairo_set_source_rgba($context, "0.1", "0.1", "0.1", "0.5");
cairo_set_source_rgba($context, "foo", "baz", "bar", "baz");

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
    echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

cairo_set_source_rgba(new stdClass, 0.1, 0.1, 0.1, 0.5);
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}

Warning: cairo_set_source_rgba() expects parameter 2 to be double, string given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_set_source_rgba() must be an instance of CairoContext, instance of stdClass given

Warning: cairo_set_source_rgba() expects parameter 1 to be CairoContext, object given in %s on line %d
