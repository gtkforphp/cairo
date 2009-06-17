--TEST--
cairo_append_path() function
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

$path = cairo_copy_path($context);
var_dump($path);

cairo_append_path($context, $path);

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// check number of args - should accept 2
cairo_append_path();
cairo_append_path($context);
cairo_append_path($context, $path, 0);

// check arg types, should be context object, path object
cairo_append_path(1, $path);
cairo_append_path($context, 1);
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
object(CairoPath)#%d (0) {
}

Warning: cairo_append_path() expects exactly 2 parameters, 0 given in %s on line %d

Warning: cairo_append_path() expects exactly 2 parameters, 1 given in %s on line %d

Warning: cairo_append_path() expects exactly 2 parameters, 3 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_append_path() must be an instance of CairoContext, integer given

Warning: cairo_append_path() expects parameter 1 to be CairoContext, integer given in %s on line %d
CAUGHT ERROR: Argument 2 passed to cairo_append_path() must be an instance of CairoPath, integer given

Warning: cairo_append_path() expects parameter 2 to be CairoPath, integer given in %s on line %d