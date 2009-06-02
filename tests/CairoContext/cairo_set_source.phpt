--TEST--
cairo_set_source function
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

$pattern = cairo_pattern_create_rgb(0.3, 0.3, 0.3);
var_dump($pattern);

cairo_set_source($context, $pattern);
var_dump(cairo_pattern_get_rgba(cairo_get_source($context)));
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
object(CairoSolidPattern)#%d (0) {
}
array(4) {
  ["red"]=>
  float(0.3)
  ["green"]=>
  float(0.3)
  ["blue"]=>
  float(0.3)
  ["alpha"]=>
  float(1)
}