--TEST--
cairo_status function
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

$status = cairo_status($context);
var_dump($status);

var_dump($status == CAIRO_STATUS_SUCCESS);

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// check number of args - should accept ONLY 1
cairo_status();
cairo_status($context, 1);

// check arg types, should be context object
cairo_status(1);
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
int(0)
bool(true)

Warning: cairo_status() expects exactly 1 parameter, 0 given in %s on line %d

Warning: cairo_status() expects exactly 1 parameter, 2 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_status() must be an instance of CairoContext, integer given

Warning: cairo_status() expects parameter 1 to be CairoContext, integer given in %s on line %d