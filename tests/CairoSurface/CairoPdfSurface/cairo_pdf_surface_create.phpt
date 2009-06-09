--TEST--
cairo_pdf_surface_create() function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!in_array('PDF', cairo_available_surfaces())) die('skip - PDF surface not available');
?>
--FILE--
<?php
$surface = cairo_pdf_surface_create(NULL, 50, 50);
var_dump($surface);

$surface = cairo_pdf_surface_create(dirname(__FILE__) . '/nametest.pdf', 50, 50);
var_dump($surface);

$fp = fopen(dirname(__FILE__) . '/streamtest.pdf', 'wb');
$surface = cairo_pdf_surface_create($fp, 50, 50);
var_dump($surface);

// check number of args - should accept ONLY 3
cairo_pdf_surface_create();
cairo_pdf_surface_create(NULL);
cairo_pdf_surface_create(NULL, 1);
cairo_pdf_surface_create(NULL, 1, 1, 1);

// check arg types, should be null, string(filename) or stream, int, int
cairo_pdf_surface_create(1, 1, 1);
cairo_pdf_surface_create(NULL, array(), 1);
cairo_pdf_surface_create(NULL, 1, array());
?>
--CLEAN--
<?php
unlink(dirname(__FILE__) . '/nametest.pdf');
unlink(dirname(__FILE__) . '/streamtest.pdf');
?>
--EXPECTF--
object(CairoPdfSurface)#%d (0) {
}
object(CairoPdfSurface)#%d (0) {
}
object(CairoPdfSurface)#%d (0) {
}

Warning: cairo_pdf_surface_create() expects exactly 3 parameters, 0 given in %s on line %d

Warning: cairo_pdf_surface_create() expects exactly 3 parameters, 1 given in %s on line %d

Warning: cairo_pdf_surface_create() expects exactly 3 parameters, 2 given in %s on line %d

Warning: cairo_pdf_surface_create() expects exactly 3 parameters, 4 given in %s on line %d

Warning: cairo_pdf_surface_create() expects parameter 1 to be null, a string, or a stream resource in %s on line %d

Warning: cairo_pdf_surface_create() expects parameter 2 to be double, array given in %s on line %d

Warning: cairo_pdf_surface_create() expects parameter 3 to be double, array given in %s on line %d