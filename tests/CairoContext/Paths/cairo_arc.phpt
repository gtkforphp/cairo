--TEST--
cairo_arc() function
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

cairo_arc($context, 0, 0, 1, 0, 2 * M_PI);

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

/* wrong params */
cairo_arc();
cairo_arc($context);
cairo_arc($context, 1);
cairo_arc($context, 1, 1);
cairo_arc($context, 1, 1, 1);
cairo_arc($context, 1, 1, 1, 1);
cairo_arc($context, 1, 1, 1, 1, 1, 1);

/* wrong types */
cairo_arc(1, 1, 1, 1, 1, 1);
cairo_arc($context, array(), 1, 1, 1, 1);
cairo_arc($context, 1, array(), 1, 1, 1);
cairo_arc($context, 1, 1, array(), 1, 1);
cairo_arc($context, 1, 1, 1, array(), 1);
cairo_arc($context, 1, 1, 1, 1, array());
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}

Warning: cairo_arc() expects exactly 6 parameters, 0 given in %s on line %d

Warning: cairo_arc() expects exactly 6 parameters, 1 given in %s on line %d

Warning: cairo_arc() expects exactly 6 parameters, 2 given in %s on line %d

Warning: cairo_arc() expects exactly 6 parameters, 3 given in %s on line %d

Warning: cairo_arc() expects exactly 6 parameters, 4 given in %s on line %d

Warning: cairo_arc() expects exactly 6 parameters, 5 given in %s on line %d

Warning: cairo_arc() expects exactly 6 parameters, 7 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_arc() must be an instance of CairoContext, integer given

Warning: cairo_arc() expects parameter 1 to be CairoContext, integer given in %s on line %d

Warning: cairo_arc() expects parameter 2 to be double, array given in %s on line %d

Warning: cairo_arc() expects parameter 3 to be double, array given in %s on line %d

Warning: cairo_arc() expects parameter 4 to be double, array given in %s on line %d

Warning: cairo_arc() expects parameter 5 to be double, array given in %s on line %d

Warning: cairo_arc() expects parameter 6 to be double, array given in %s on line %d