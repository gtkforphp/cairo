--TEST--
cairo_ps_surface_set_eps() function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!in_array('PS', cairo_available_surfaces())) die('skip - PS surface not available');
if(!function_exists('cairo_ps_surface_set_eps')) die('skip - cairo_ps_surface_set_eps not available');
?>
--FILE--
<?php
$surface = cairo_ps_surface_create(NULL, 50, 50);
var_dump($surface);

cairo_ps_surface_set_eps($surface, true);

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// check number of args - should accept ONLY 2
cairo_ps_surface_set_eps();
cairo_ps_surface_set_eps($surface);
cairo_ps_surface_set_eps($surface, 1, 1);

// check arg types, should be ps surface object, boolean
cairo_ps_surface_set_eps(1, 1);
cairo_ps_surface_set_eps($surface, array());
?>
--EXPECTF--
object(CairoPsSurface)#%d (0) {
}

Warning: cairo_ps_surface_set_eps() expects exactly 2 parameters, 0 given in %s on line %d

Warning: cairo_ps_surface_set_eps() expects exactly 2 parameters, 1 given in %s on line %d

Warning: cairo_ps_surface_set_eps() expects exactly 2 parameters, 3 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_ps_surface_set_eps() must be an instance of CairoPsSurface, integer given

Warning: cairo_ps_surface_set_eps() expects parameter 1 to be CairoPsSurface, integer given in %s on line %d

Warning: cairo_ps_surface_set_eps() expects parameter 2 to be boolean, array given in %s on line %d