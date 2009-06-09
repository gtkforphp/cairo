--TEST--
cairo_ps_surface_dsc_begin_page_setup() function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!in_array('PS', cairo_available_surfaces())) die('skip - PS surface not available');
?>
--FILE--
<?php
$surface = cairo_ps_surface_create(NULL, 50, 50);
var_dump($surface);

cairo_ps_surface_dsc_begin_page_setup($surface);

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// check number of args - should accept ONLY 1
cairo_ps_surface_dsc_begin_page_setup();
cairo_ps_surface_dsc_begin_page_setup($surface, 1);

// check arg types, should be ps surface object
cairo_ps_surface_dsc_begin_page_setup(null);
?>
--EXPECTF--
object(CairoPsSurface)#%d (0) {
}

Warning: cairo_ps_surface_dsc_begin_page_setup() expects exactly 1 parameter, 0 given in %s on line %d

Warning: cairo_ps_surface_dsc_begin_page_setup() expects exactly 1 parameter, 2 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_ps_surface_dsc_begin_page_setup() must be an instance of CairoPsSurface, null given

Warning: cairo_ps_surface_dsc_begin_page_setup() expects parameter 1 to be CairoPsSurface, null given in %s on line %d