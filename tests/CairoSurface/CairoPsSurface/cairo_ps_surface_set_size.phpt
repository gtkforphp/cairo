--TEST--
cairo_ps_surface_set_size() function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!in_array('PS', cairo_available_surfaces())) die('skip - PS surface not available');
?>
--FILE--
<?php
$surface = cairo_ps_surface_create(NULL, 50, 50);
var_dump($surface);

cairo_ps_surface_set_size($surface, 10, 10);

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// check number of args - should accept ONLY 3
cairo_ps_surface_set_size();
cairo_ps_surface_set_size($surface);
cairo_ps_surface_set_size($surface, 1);
cairo_ps_surface_set_size($surface, 1, 1, 1);

// check arg types, should be pdf surface object, int, int
cairo_ps_surface_set_size(1, 1, 1);
cairo_ps_surface_set_size($surface, array(), 1);
cairo_ps_surface_set_size($surface, 1, array());
?>
--EXPECTF--
object(CairoPsSurface)#%d (0) {
}

Warning: cairo_ps_surface_set_size() expects exactly 3 parameters, 0 given in %s on line %d

Warning: cairo_ps_surface_set_size() expects exactly 3 parameters, 1 given in %s on line %d

Warning: cairo_ps_surface_set_size() expects exactly 3 parameters, 2 given in %s on line %d

Warning: cairo_ps_surface_set_size() expects exactly 3 parameters, 4 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_ps_surface_set_size() must be an instance of CairoPsSurface, integer given

Warning: cairo_ps_surface_set_size() expects parameter 1 to be CairoPsSurface, integer given in %s on line %d

Warning: cairo_ps_surface_set_size() expects parameter 2 to be double, array given in %s on line %d

Warning: cairo_ps_surface_set_size() expects parameter 3 to be double, array given in %s on line %d