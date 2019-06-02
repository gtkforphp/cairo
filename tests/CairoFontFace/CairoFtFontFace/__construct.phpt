--TEST--
CairoFtFontFace::__construct()
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!function_exists('cairo_ft_font_face_create')) die('skip - cairo_ft_font_face_create not available');
?>
--FILE--
<?php
$fontFile = dirname(__FILE__) . "/Vera.ttf";

// Test with 1 param
$c = new CairoFtFontFace($fontFile);
var_dump($c);

// test with 2 params
$c = new CairoFtFontFace($fontFile, 0);
var_dump($c);

// We shouldn't accept 0 args
try {
    $c = new CairoFtFontFace();
} catch (TypeError $e) {
    var_dump($e->getMessage());
}
var_dump($c);

// Test with 1 param
try {
    $c = new CairoFtFontFace("NotARealFont");
} catch (TypeError $e) {
    var_dump($e->getMessage());
}
var_dump($c);

// Test with a silly param
try {
    $c = new CairoFtFontFace(array());
} catch (TypeError $e) {
    var_dump($e->getMessage());
}
var_dump($c); 

// Test with a broken font
try {
    $c = new CairoFtFontFace(dirname(__FILE__) . '/broken.ttf');
} catch (TypeError $e) {
    var_dump($e->getMessage());
}
var_dump($c);
?>
--EXPECTF--
object(CairoFtFontFace)#1 (0) {
}
object(CairoFtFontFace)#2 (0) {
}
string(68) "CairoFtFontFace::__construct() expects at least 1 parameter, 0 given"
object(CairoFtFontFace)#2 (0) {
}
string(92) "CairoFtFontFace::__construct(NotARealFont): failed to open stream: No such file or directory"
object(CairoFtFontFace)#2 (0) {
}
string(86) "CairoFtFontFace::__construct() expects parameter 1 to be a string or a stream resource"
object(CairoFtFontFace)#2 (0) {
}
string(91) "CairoFtFontFace::__construct(): An error occurred opening the file invalid stream operation"
object(CairoFtFontFace)#2 (0) {
}
