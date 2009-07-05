--TEST--
cairo_font_extents() function
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

var_dump(cairo_font_extents($context));

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// check number of args - should accept ONLY 1
cairo_font_extents();
cairo_font_extents($context, 1);

// check arg types, should be context object
cairo_font_extents(array());
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
array(5) {
  ["ascent"]=>
  float(%f)
  ["descent"]=>
  float(%f)
  ["height"]=>
  float(%f)
  ["max_x_advance"]=>
  float(%f)
  ["max_y_advance"]=>
  float(%f)
}

Warning: cairo_font_extents() expects exactly 1 parameter, 0 given in %s on line %d

Warning: cairo_font_extents() expects exactly 1 parameter, 2 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_font_extents() must be an instance of CairoContext, array given

Warning: cairo_font_extents() expects parameter 1 to be CairoContext, array given in %s on line %d