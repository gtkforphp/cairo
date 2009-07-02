--TEST--
cairo_pop_group_to_source function
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

cairo_push_group($context);

cairo_pop_group_to_source($context);
var_dump(cairo_get_source($context));

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

/* wrong parameters */
cairo_pop_group_to_source();
cairo_pop_group_to_source($context, 1);

/* wrong type */
cairo_pop_group_to_source(1);

?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
object(CairoSurfacePattern)#%d (0) {
}

Warning: cairo_pop_group_to_source() expects exactly 1 parameter, 0 given in %s on line %d

Warning: cairo_pop_group_to_source() expects exactly 1 parameter, 2 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_pop_group_to_source() must be an instance of CairoContext, integer given

Warning: cairo_pop_group_to_source() expects parameter 1 to be CairoContext, integer given in %s on line %d