--TEST--
cairo_ps_surface_restrict_to_level() function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!in_array('PS', cairo_available_surfaces())) die('skip - PS surface not available');
if(!function_exists('cairo_ps_surface_restrict_to_level')) die('skip - cairo_ps_surface_restrict_to_level not available');
?>
--FILE--
<?php
$surface = cairo_ps_surface_create(NULL, 50, 50);
var_dump($surface);

cairo_ps_surface_restrict_to_level($surface, CAIRO_PS_LEVEL_2);

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// check number of args - should accept ONLY 2
cairo_ps_surface_restrict_to_level();
cairo_ps_surface_restrict_to_level($surface);
cairo_ps_surface_restrict_to_level($surface, 1, 1);

// check arg types, should be ps surface object, int
cairo_ps_surface_restrict_to_level(1, 1);
cairo_ps_surface_restrict_to_level($surface, array());
?>
--EXPECTF--
object(CairoPsSurface)#%d (0) {
}

Warning: cairo_ps_surface_restrict_to_level() expects exactly 2 parameters, 0 given in %s on line %d

Warning: cairo_ps_surface_restrict_to_level() expects exactly 2 parameters, 1 given in %s on line %d

Warning: cairo_ps_surface_restrict_to_level() expects exactly 2 parameters, 3 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_ps_surface_restrict_to_level() must be an instance of CairoPsSurface, integer given

Warning: cairo_ps_surface_restrict_to_level() expects parameter 1 to be CairoPsSurface, integer given in %s on line %d

Warning: cairo_ps_surface_restrict_to_level() expects parameter 2 to be long, array given in %s on line %d