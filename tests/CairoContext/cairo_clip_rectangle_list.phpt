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

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// check number of args - should accept ONLY 1
cairo_clip_rectangle_list();
cairo_clip_rectangle_list($context, 1);

// check arg types, should be CairoContext
cairo_clip_rectangle_list(1);
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

Warning: cairo_clip_rectangle_list() expects exactly 1 parameter, 2 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_clip_rectangle_list() must be an instance of CairoContext, integer given

Warning: cairo_clip_rectangle_list() expects parameter 1 to be CairoContext, integer given in %s on line %d