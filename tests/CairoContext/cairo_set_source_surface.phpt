--TEST--
cairo_set_source_surface() function
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

$surface2 = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 50, 50);
var_dump($surface2);

$pattern = cairo_pattern_create_rgb(0.5, 0.5, 0.5);
var_dump($pattern);

cairo_set_source($context, $pattern);

cairo_set_source_surface($context, $surface2, 5, 5);

function bad_class($errno, $errstr) {
  echo 'CAUGHT ERROR: ' , $errstr, PHP_EOL;
}

set_error_handler('bad_class', E_RECOVERABLE_ERROR);

/* wrong params */
cairo_set_source_surface();
cairo_set_source_surface($context);
cairo_set_source_surface($context, $surface2, 5, 5, 5);

/* wrong types */
cairo_set_source_surface(1, $surface2);
cairo_set_source_surface($context, 1);
cairo_set_source_surface($context, $surface2, array());
cairo_set_source_surface($context, $surface2, 5, array());

?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
object(CairoImageSurface)#%d (0) {
}
object(CairoSolidPattern)#%d (0) {
}

Warning: cairo_set_source_surface() expects at least 2 parameters, 0 given in %s on line %d

Warning: cairo_set_source_surface() expects at least 2 parameters, 1 given in %s on line %d

Warning: cairo_set_source_surface() expects at most 4 parameters, 5 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_set_source_surface() must be an instance of CairoContext, integer given

Warning: cairo_set_source_surface() expects parameter 1 to be CairoContext, integer given in %s on line %d
CAUGHT ERROR: Argument 2 passed to cairo_set_source_surface() must be an instance of CairoSurface, integer given

Warning: cairo_set_source_surface() expects parameter 2 to be CairoSurface, integer given in %s on line %d

Warning: cairo_set_source_surface() expects parameter 3 to be double, array given in %s on line %d

Warning: cairo_set_source_surface() expects parameter 4 to be double, array given in %s on line %d