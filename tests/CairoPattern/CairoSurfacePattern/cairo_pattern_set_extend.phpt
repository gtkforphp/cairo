--TEST--
cairo_pattern_set_extend function
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

cairo_pattern_set_extend($pattern, CAIRO_EXTEND_PAD);

$extend = cairo_pattern_get_extend($pattern);
var_dump($extend);
var_dump($extend == CAIRO_EXTEND_PAD);

cairo_pattern_set_extend();
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoSurfacePattern)#%d (0) {
}
int(3)
bool(true)

Warning: cairo_pattern_set_extend() expects exactly 2 parameters, 0 given in %s on line %d