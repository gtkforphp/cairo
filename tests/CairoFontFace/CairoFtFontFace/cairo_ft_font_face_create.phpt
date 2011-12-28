--TEST--
cairo_ft_font_face_create() function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!function_exists('cairo_ft_font_face_create')) die('skip - cairo_ft_font_face_create not available');
?>
--FILE--
<?php
$fontFile = dirname(__FILE__) . "/Vera.ttf";

// Test with 1 param
$c = cairo_ft_font_face_create($fontFile);
var_dump($c);

// test with 2 params
$c = cairo_ft_font_face_create($fontFile, 0);
var_dump($c);

// We shouldn't accept 0 args
$c = cairo_ft_font_face_create();
var_dump($c);

// Test with 1 param
$c = cairo_ft_font_face_create("NotARealFont");
var_dump($c);

// Test with a silly param
$c = cairo_ft_font_face_create(array());
var_dump($c); 

// Test with a broken font
$c = cairo_ft_font_face_create(dirname(__FILE__) . '/broken.ttf');
var_dump($c);
?>
--EXPECTF--
object(CairoFtFontFace)#1 (0) {
}
object(CairoFtFontFace)#2 (0) {
}

Warning: cairo_ft_font_face_create() expects at least 1 parameter, 0 given in %s on line 13
NULL

Warning: cairo_ft_font_face_create(NotARealFont): failed to open stream: No such file or directory in %s on line 17
NULL

Warning: cairo_ft_font_face_create expects parameter 1 to be a string or a stream resource in %s on line 21
NULL

Warning: cairo_ft_font_face_create(): An error occurred opening the file: %s in %s on line 25
NULL
