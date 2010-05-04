--TEST--
cairo_win32_font_face_create() function
--SKIPIF--
<?php
if(!extension_loaded('cairo'))
	die('skip - Cairo extension not available');
if(!function_exists('cairo_win32_font_face_create'))
	die('skip - cairo_win32_font_face_create not available');
?>
--FILE--
<?php
$f_opts = array(
	'lfFaceName' => 'Impact',
	'lfWeight' => CairoWin32FontWeight::BOLD
);

$font_face = cairo_win32_font_face_create();
var_dump($font_face);

$font_face = cairo_win32_font_face_create($f_opts);
var_dump($font_face);

$font_face = cairo_win32_font_face_create(1);
var_dump($font_face);

$font_face = cairo_win32_font_face_create($f_opts, 1);
var_dump($font_face);

?>
--EXPECTF--
object(CairoWin32FontFace)#%d (0) {
}
object(CairoWin32FontFace)#%d (0) {
}

Warning: cairo_win32_font_face_create() expects parameter 1 to be array, integer given in %s on line %d
NULL

Warning: cairo_win32_font_face_create() expects at most 1 parameter, 2 given in %s on line %d
NULL