--TEST--
cairo_font_face_get_family function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!class_exists('CairoToyFontFace')) die('skip - CairoToyFontFace not enabled');
?>
--FILE--
<?php
// Test with all parameters
$c = cairo_font_face_create("sans-serif", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
var_dump(cairo_font_face_get_family($c));
?>
--EXPECTF--
string(10) "sans-serif"
