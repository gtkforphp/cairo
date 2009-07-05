--TEST--
cairo_set_font_matrix() function
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

$matrix = cairo_matrix_init();
var_dump($matrix);

cairo_set_font_matrix($context, $matrix);
$matrix1 = cairo_get_font_matrix($context);

var_dump($matrix === $matrix1);

$matrix2 = cairo_matrix_init(5, 5);
cairo_set_font_matrix($context, $matrix2);
$matrix1 = cairo_get_font_matrix($context);

var_dump($matrix2 === $matrix1);

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// check number of args - should accept ONLY 2
cairo_set_font_matrix();
cairo_set_font_matrix($context);
cairo_set_font_matrix($context, $matrix2, 1);

// check arg types, should be context object, cairo matrix
cairo_set_font_matrix(array(), $matrix2);
cairo_set_font_matrix($context, array());

die; // DO NOT REMOVE THIS - fixes issue in 5.3 with GC giving bogus memleak reports
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
object(CairoMatrix)#%d (0) {
}
bool(true)
bool(true)

Warning: cairo_set_font_matrix() expects exactly 2 parameters, 0 given in %s on line %d

Warning: cairo_set_font_matrix() expects exactly 2 parameters, 1 given in %s on line %d

Warning: cairo_set_font_matrix() expects exactly 2 parameters, 3 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_set_font_matrix() must be an instance of CairoContext, array given

Warning: cairo_set_font_matrix() expects parameter 1 to be CairoContext, array given in %s on line %d
CAUGHT ERROR: Argument 2 passed to cairo_set_font_matrix() must be an instance of CairoMatrix, array given

Warning: cairo_set_font_matrix() expects parameter 2 to be CairoMatrix, array given in %s on line %d