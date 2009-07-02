--TEST--
cairo_scaled_font_glyph_extents() function
--SKIPIF--
<?php
die('skip - Glyph support not complete');
?>
--FILE--
<?php
include(dirname(__FILE__) . '/create_toyfont.inc');
var_dump($fontface);

$matrix1 = cairo_matrix_init(1);
$matrix2 = cairo_matrix_init(1, 1);
$options = cairo_font_options_create();

$scaledfont = cairo_scaled_font_create($fontface, $matrix1, $matrix2, $options);
var_dump($scaledfont);
?>
--EXPECT--