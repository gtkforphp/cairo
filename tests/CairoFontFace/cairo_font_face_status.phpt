--TEST--
cairo_font_face_status() function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
include(dirname(__FILE__) . '/create_toyfont.inc');
var_dump($fontface);

$status = cairo_font_face_status($fontface);
var_dump($status);

var_dump($status == CAIRO_STATUS_SUCCESS);

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// check number of args - should accept ONLY 1
cairo_font_face_status();
cairo_font_face_status($fontface, 1);

// check arg types, should be fontface object
cairo_font_face_status(1);
?>
--EXPECTF--
object(CairoToyFontFace)#%d (0) {
}
int(0)
bool(true)

Warning: cairo_font_face_status() expects exactly 1 parameter, 0 given in %s on line %d

Warning: cairo_font_face_status() expects exactly 1 parameter, 2 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_font_face_status() must be an instance of CairoFontFace, integer given

Warning: cairo_font_face_status() expects parameter 1 to be CairoFontFace, integer given in %s on line %d