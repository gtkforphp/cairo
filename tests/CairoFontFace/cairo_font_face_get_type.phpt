--TEST--
cairo_font_face_get_type() function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
include(dirname(__FILE__) . '/create_toyfont.inc');
var_dump($fontface);

var_dump(cairo_font_face_get_type($fontface));

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// requires exactly 1 arg
cairo_font_face_get_type();
cairo_font_face_get_type($fontface);

// arg type is CairoFontFace
cairo_font_face_get_type(1);
cairo_font_face_get_type($fontface);
?>
--EXPECTF--
object(CairoToyFontFace)#%d (0) {
}
int(0)

Warning: cairo_font_face_get_type() expects exactly 1 parameter, 0 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_font_face_get_type() must be an instance of CairoFontFace, integer given

Warning: cairo_font_face_get_type() expects parameter 1 to be CairoFontFace, integer given in %s on line %d