--TEST--
cairo_pattern_get_extend function
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

$extend = cairo_pattern_get_extend($pattern);
var_dump($extend);
var_dump($extend == CAIRO_EXTEND_NONE);

$pattern = cairo_pattern_create_linear(1, 2, 3, 4);
var_dump($pattern);

$extend = cairo_pattern_get_extend($pattern);
var_dump($extend);
var_dump($extend == CAIRO_EXTEND_PAD);

// requires 1 arg
cairo_pattern_get_extend();
cairo_pattern_get_extend($pattern, 1);

// arg types is CairoPattern
cairo_pattern_get_extend(1);
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoSurfacePattern)#%d (0) {
}
int(0)
bool(true)
object(CairoLinearGradient)#%d (0) {
}
int(3)
bool(true)

Warning: cairo_pattern_get_extend() expects exactly 1 parameter, 0 given in %s on line %d

Warning: cairo_pattern_get_extend() expects exactly 1 parameter, 2 given in %s on line %d

Warning: cairo_pattern_get_extend() expects parameter 1 to be CairoSurfacePattern, integer given in %s on line %d