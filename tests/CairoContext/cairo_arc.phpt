--TEST--
cairo_arc function
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

cairo_arc($context, 0, 0, 1, 0, 2 * M_PI);

cairo_arc();
?>
--EXPECTF--
object(CairoImageSurface)#1 (0) {
}
object(CairoContext)#2 (0) {
}

Warning: cairo_arc() expects exactly 6 parameters, 0 given in %s on line %d