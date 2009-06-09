--TEST--
cairo_ps_surface_get_eps() function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!in_array('PS', cairo_available_surfaces())) die('skip - PS surface not available');
if(!function_exists('cairo_ps_surface_get_eps')) die('skip - cairo_ps_surface_get_eps not available');
?>
--FILE--
<?php
$surface = cairo_ps_surface_create(NULL, 50, 50);
var_dump($surface);

var_dump(cairo_ps_surface_get_eps($surface));

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// check number of args - should accept ONLY 1
cairo_ps_surface_get_eps();
cairo_ps_surface_get_eps($surface, 1);

// check arg types, should be ps surface object
cairo_ps_surface_get_eps(null);
?>
--EXPECTF--
object(CairoPsSurface)#%d (0) {
}
bool(false)

Warning: cairo_ps_surface_get_eps() expects exactly 1 parameter, 0 given in %s on line %d

Warning: cairo_ps_surface_get_eps() expects exactly 1 parameter, 2 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_ps_surface_get_eps() must be an instance of CairoPsSurface, null given

Warning: cairo_ps_surface_get_eps() expects parameter 1 to be CairoPsSurface, null given in %s on line %d