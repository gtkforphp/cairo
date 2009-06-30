--TEST--
cairo_toy_font_face_get_slant function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!class_exists('CairoToyFontFace')) die('skip - CairoToyFontFace not enabled');
?>
--FILE--
<?php
$c = cairo_font_face_create("sans-serif", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
var_dump(cairo_toy_font_face_get_slant($c));

$c = cairo_font_face_create("sans-serif", CAIRO_FONT_SLANT_ITALIC, CAIRO_FONT_WEIGHT_NORMAL);
var_dump(cairo_toy_font_face_get_slant($c));
?>
--EXPECTF--
int(0)
int(1)
