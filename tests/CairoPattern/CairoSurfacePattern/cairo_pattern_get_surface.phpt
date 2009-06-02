--TEST--
cairo_pattern_get_surface function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 50, 50);
var_dump($surface);

$pattern = cairo_pattern_create_for_surface($surface);
var_dump($pattern);

$surface2 = cairo_pattern_get_surface($pattern);
var_dump($surface2);
var_dump($surface === $surface2);

cairo_pattern_get_surface();
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoSurfacePattern)#%d (0) {
}
object(CairoImageSurface)#%d (0) {
}
bool(false)

Warning: cairo_pattern_get_surface() expects exactly 1 parameter, 0 given in %s on line %d