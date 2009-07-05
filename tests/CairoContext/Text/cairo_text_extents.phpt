--TEST--
cairo_text_extents() function
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

var_dump(cairo_text_extents($context, 'foobar'));

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// check number of args - should accept ONLY 2
cairo_text_extents();
cairo_text_extents($context);
cairo_text_extents($context, 'foobar', 1);

// check arg types, should be context object, string
cairo_text_extents(array(), 'foobar');
cairo_text_extents($context, array());
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
array(6) {
  ["x_bearing"]=>
  float(%f)
  ["y_bearing"]=>
  float(%f)
  ["width"]=>
  float(%f)
  ["height"]=>
  float(%f)
  ["x_advance"]=>
  float(%f)
  ["y_advance"]=>
  float(%f)
}

Warning: cairo_text_extents() expects exactly 2 parameters, 0 given in %s on line %d

Warning: cairo_text_extents() expects exactly 2 parameters, 1 given in %s on line %d

Warning: cairo_text_extents() expects exactly 2 parameters, 3 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_text_extents() must be an instance of CairoContext, array given

Warning: cairo_text_extents() expects parameter 1 to be CairoContext, array given in %s on line %d

Warning: cairo_text_extents() expects parameter 2 to be string, array given in %s on line %d