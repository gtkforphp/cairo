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

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
    echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// 5 args
cairo_set_source_rgba();
cairo_set_source_rgba($context);
cairo_set_source_rgba($context, 1);
cairo_set_source_rgba($context, 1, 1);
cairo_set_source_rgba($context, 1, 1, 1);
cairo_set_source_rgba($context, 1, 1, 1, 1, 1);

// types
cairo_set_source_rgba(array(), 1, 1, 1, 1);
cairo_set_source_rgba($context, array(), 1, 1, 1);
cairo_set_source_rgba($context, 1, array(), 1, 1);
cairo_set_source_rgba($context, 1, 1, array(), 1);
cairo_set_source_rgba($context, 1, 1, 1, array());
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}

Warning: cairo_set_source_rgba() expects exactly 5 parameters, 0 given in %s on line %d

Warning: cairo_set_source_rgba() expects exactly 5 parameters, 1 given in %s on line %d

Warning: cairo_set_source_rgba() expects exactly 5 parameters, 2 given in %s on line %d

Warning: cairo_set_source_rgba() expects exactly 5 parameters, 3 given in %s on line %d

Warning: cairo_set_source_rgba() expects exactly 5 parameters, 4 given in %s on line %d

Warning: cairo_set_source_rgba() expects exactly 5 parameters, 6 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_set_source_rgba() must be an instance of CairoContext, array given

Warning: cairo_set_source_rgba() expects parameter 1 to be CairoContext, array given in %s on line %d

Warning: cairo_set_source_rgba() expects parameter 2 to be double, array given in %s on line %d

Warning: cairo_set_source_rgba() expects parameter 3 to be double, array given in %s on line %d

Warning: cairo_set_source_rgba() expects parameter 4 to be double, array given in %s on line %d

Warning: cairo_set_source_rgba() expects parameter 5 to be double, array given in %s on line %d