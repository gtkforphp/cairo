--TEST--
cairo_image_surface_create() function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 50, 50);
var_dump($surface);

cairo_image_surface_create();
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}

Warning: cairo_image_surface_create() expects exactly 3 parameters, 0 given in %s on line %d