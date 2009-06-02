--TEST--
cairo_get_target error conditions
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

cairo_get_target();
cairo_get_target($context, 'foobar');
cairo_get_target('foobar');
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}

Warning: cairo_get_target() expects exactly 1 parameter, 0 given in %s on line %d

Warning: cairo_get_target() expects exactly 1 parameter, 2 given in %s on line %d

Catchable fatal error: Argument 1 passed to cairo_get_target() must be an instance of CairoContext, string given in %s on line %d