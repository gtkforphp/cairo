--TEST--
cairo_clip_rectangle_list function
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

var_dump(cairo_clip_rectangle_list($context));
cairo_clip_rectangle_list();
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
array(1) {
  [0]=>
  array(4) {
    ["x"]=>
    float(0)
    ["y"]=>
    float(0)
    ["width"]=>
    float(50)
    ["height"]=>
    float(50)
  }
}

Warning: cairo_clip_rectangle_list() expects exactly 1 parameter, 0 given in %s on line %d