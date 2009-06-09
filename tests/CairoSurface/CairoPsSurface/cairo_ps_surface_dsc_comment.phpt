--TEST--
cairo_ps_surface_dsc_comment() function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!in_array('PS', cairo_available_surfaces())) die('skip - PS surface not available');
?>
--FILE--
<?php
$surface = cairo_ps_surface_create(NULL, 50, 50);
var_dump($surface);

cairo_ps_surface_dsc_comment($surface, '%%Title: My excellent document');

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// check number of args - should accept ONLY 2
cairo_ps_surface_dsc_comment();
cairo_ps_surface_dsc_comment($surface);
cairo_ps_surface_dsc_comment($surface, 1, 1);

// check arg types, should be ps surface object, boolean
cairo_ps_surface_dsc_comment(1, 1);
cairo_ps_surface_dsc_comment($surface, array());
?>
--EXPECTF--
object(CairoPsSurface)#%d (0) {
}

Warning: cairo_ps_surface_dsc_comment() expects exactly 2 parameters, 0 given in %s on line %d

Warning: cairo_ps_surface_dsc_comment() expects exactly 2 parameters, 1 given in %s on line %d

Warning: cairo_ps_surface_dsc_comment() expects exactly 2 parameters, 3 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_ps_surface_dsc_comment() must be an instance of CairoPsSurface, integer given

Warning: cairo_ps_surface_dsc_comment() expects parameter 1 to be CairoPsSurface, integer given in %s on line %d

Warning: cairo_ps_surface_dsc_comment() expects parameter 2 to be string, array given in %s on line %d