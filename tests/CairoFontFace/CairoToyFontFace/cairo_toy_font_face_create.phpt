--TEST--
cairo_toy_font_face_create() function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!function_exists('cairo_toy_font_face_create')) die('skip - cairo_toy_font_face_create not available');
?>
--FILE--
<?php
// Test with all parameters
$c = cairo_toy_font_face_create("sans-serif", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
var_dump($c);

// Test with 1 param
$c = cairo_toy_font_face_create("sans-serif");
var_dump($c);

// test with 2 params
$c = cairo_toy_font_face_create("sans-serif", CAIRO_FONT_SLANT_NORMAL);
var_dump($c);

// test with 3 params, 1 null
$c = cairo_toy_font_face_create("sans-serif", null, CAIRO_FONT_WEIGHT_NORMAL);
var_dump($c);

// We shouldn't accept 0 args
$c = cairo_toy_font_face_create();
var_dump($c);

// Test with 1 param
$c = cairo_toy_font_face_create("NotARealFont");
var_dump($c);

// Test with a silly param
$c = cairo_toy_font_face_create(array());
var_dump($c);
?>
--EXPECTF--
object(CairoToyFontFace)#%d (0) {
}
object(CairoToyFontFace)#%d (0) {
}
object(CairoToyFontFace)#%d (0) {
}
object(CairoToyFontFace)#%d (0) {
}

Warning: cairo_toy_font_face_create() expects at least 1 parameter, 0 given in %s on line %d
NULL
object(CairoToyFontFace)#2 (0) {
}

Warning: cairo_toy_font_face_create() expects parameter 1 to be string, array given in %s on line %d
NULL
