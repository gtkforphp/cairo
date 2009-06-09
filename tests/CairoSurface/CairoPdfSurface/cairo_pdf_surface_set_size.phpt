--TEST--
cairo_pdf_surface_set_size() function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!in_array('PDF', cairo_available_surfaces())) die('skip - PDF surface not available');
?>
--FILE--
<?php
$surface = cairo_pdf_surface_create(NULL, 50, 50);
var_dump($surface);

cairo_pdf_surface_set_size($surface, 10, 10);

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// check number of args - should accept ONLY 3
cairo_pdf_surface_set_size();
cairo_pdf_surface_set_size($surface);
cairo_pdf_surface_set_size($surface, 1);
cairo_pdf_surface_set_size($surface, 1, 1, 1);

// check arg types, should be pdf surface object, int, int
cairo_pdf_surface_set_size(1, 1, 1);
cairo_pdf_surface_set_size($surface, array(), 1);
cairo_pdf_surface_set_size($surface, 1, array());
?>
--EXPECTF--
object(CairoPdfSurface)#%d (0) {
}

Warning: cairo_pdf_surface_set_size() expects exactly 3 parameters, 0 given in %s on line %d

Warning: cairo_pdf_surface_set_size() expects exactly 3 parameters, 1 given in %s on line %d

Warning: cairo_pdf_surface_set_size() expects exactly 3 parameters, 2 given in %s on line %d

Warning: cairo_pdf_surface_set_size() expects exactly 3 parameters, 4 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_pdf_surface_set_size() must be an instance of CairoPdfSurface, integer given

Warning: cairo_pdf_surface_set_size() expects parameter 1 to be CairoPdfSurface, integer given in %s on line %d

Warning: cairo_pdf_surface_set_size() expects parameter 2 to be double, array given in %s on line %d

Warning: cairo_pdf_surface_set_size() expects parameter 3 to be double, array given in %s on line %d