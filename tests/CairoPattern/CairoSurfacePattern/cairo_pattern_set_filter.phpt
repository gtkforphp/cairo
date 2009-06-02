--TEST--
cairo_pattern_set_filter function
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

cairo_pattern_set_filter($pattern, CAIRO_FILTER_NEAREST);

$filter = cairo_pattern_get_filter($pattern);
var_dump($filter);
var_dump($filter == CAIRO_FILTER_NEAREST);

cairo_pattern_set_filter();
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoSurfacePattern)#%d (0) {
}
int(3)
bool(true)

Warning: cairo_pattern_set_filter() expects exactly 2 parameters, 0 given in %s on line %d