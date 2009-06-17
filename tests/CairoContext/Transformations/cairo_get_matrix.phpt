--TEST--
cairo_get_matrix() function
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

var_dump($orig_matrix = cairo_get_matrix($context));

$matrix = cairo_matrix_init(5, 5);
var_dump($matrix);
var_dump($orig_matrix === $matrix);

cairo_set_matrix($context, $matrix);
var_dump($matrix1 = cairo_get_matrix($context));
var_dump($matrix1 === $matrix);
var_dump($orig_matrix === $matrix);

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// requires exactly 1 arg
cairo_get_matrix();
cairo_get_matrix($context, 1);

// arg types is CairoContext
cairo_get_matrix(1);

die; // DO NOT REMOVE THIS - fixes issue in 5.3 with GC giving bogus memleak reports
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
object(CairoMatrix)#%d (0) {
}
object(CairoMatrix)#%d (0) {
}
bool(false)
object(CairoMatrix)#%d (0) {
}
bool(true)
bool(false)

Warning: cairo_get_matrix() expects exactly 1 parameter, 0 given in %s on line %d

Warning: cairo_get_matrix() expects exactly 1 parameter, 2 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_get_matrix() must be an instance of CairoContext, integer given

Warning: cairo_get_matrix() expects parameter 1 to be CairoContext, integer given in %s on line %d