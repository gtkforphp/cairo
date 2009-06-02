--TEST--
cairo_pattern_status function
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

$status = cairo_pattern_status($pattern);
var_dump($status);
var_dump($status == CAIRO_STATUS_SUCCESS);

cairo_pattern_status();
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoSurfacePattern)#%d (0) {
}
int(0)
bool(true)

Warning: cairo_pattern_status() expects exactly 1 parameter, 0 given in %s on line %d