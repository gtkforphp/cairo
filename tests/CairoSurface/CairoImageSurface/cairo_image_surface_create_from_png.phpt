--TEST--
cairo_image_surface_create_from_png() function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!in_array('PNG', cairo_available_surfaces())) die('skip - PNG support not available');
?>
--FILE--
<?php
$surface = cairo_image_surface_create_from_png(dirname(__FILE__) . '/red.png');
var_dump($surface);

$resource = fopen(dirname(__FILE__) . '/red.png', 'rw');
$surface = cairo_image_surface_create_from_png($resource);
var_dump($surface);
fclose($resource);

cairo_image_surface_create_from_png();
cairo_image_surface_create_from_png('', 1);

cairo_image_surface_create_from_png(array());
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoImageSurface)#%d (0) {
}

Warning: cairo_image_surface_create_from_png() expects exactly 1 parameter, 0 given in %s on line %d

Warning: cairo_image_surface_create_from_png() expects exactly 1 parameter, 2 given in %s on line %d

Warning: cairo_image_surface_create_from_png() expects parameter 1 to be a string or a stream resource in %s on line %d