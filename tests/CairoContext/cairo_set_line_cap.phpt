--TEST--
cairo_set_line_cap() function
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

cairo_set_line_cap($context, CAIRO_LINE_CAP_SQUARE);
var_dump(cairo_get_line_cap($context));

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// check number of args - should accept 2
cairo_set_line_cap();
cairo_set_line_cap($context);
cairo_set_line_cap($context, 1, 1);

// check arg types, should be int
cairo_set_line_cap(1, 1);
cairo_set_line_cap($context, array());
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
int(2)

Warning: cairo_set_line_cap() expects exactly 2 parameters, 0 given in %s on line %d

Warning: cairo_set_line_cap() expects exactly 2 parameters, 1 given in %s on line %d

Warning: cairo_set_line_cap() expects exactly 2 parameters, 3 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_set_line_cap() must be an instance of CairoContext, integer given

Warning: cairo_set_line_cap() expects parameter 1 to be CairoContext, integer given in %s on line %d

Warning: cairo_set_line_cap() expects parameter 2 to be long, array given in %s on line %d