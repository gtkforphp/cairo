--TEST--
cairo_append_path function
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

$path = cairo_copy_path($context);
var_dump($path);

cairo_append_path($context, $path);

cairo_append_path();
?>
--EXPECTF--
object(CairoImageSurface)#1 (0) {
}
object(CairoContext)#2 (0) {
}
object(CairoPath)#3 (0) {
}

Warning: cairo_append_path() expects exactly 2 parameters, 0 given in %s on line %d