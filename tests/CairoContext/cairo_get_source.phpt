--TEST--
cairo_get_source function
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

$pattern = cairo_get_source($context);
var_dump($pattern);

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
            echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

$pattern = cairo_get_source(new stdClass);
var_dump($pattern);
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
object(CairoSolidPattern)#%d (0) {
}
CAUGHT ERROR: Argument 1 passed to cairo_get_source() must be an instance of CairoContext, instance of stdClass given

Warning: cairo_get_source() expects parameter 1 to be CairoContext, object given in %s on line %d
NULL
