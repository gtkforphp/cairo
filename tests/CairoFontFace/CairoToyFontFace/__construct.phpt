--TEST--
CairoToyFontFace::__construct() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
// Test with all parameters
$c = new CairoToyFontFace("sans-serif", CairoFontSlant::NORMAL, CairoFontWeight::NORMAL);
var_dump($c);

// Test with 1 param
$c = new CairoToyFontFace("sans-serif");
var_dump($c);

// test with 2 params
$c = new CairoToyFontFace("sans-serif", CairoFontSlant::NORMAL);
var_dump($c);

// test with 3 params, 1 null
$c = new CairoToyFontFace("sans-serif", null, CairoFontWeight::NORMAL);
var_dump($c);

// We shouldn't accept 0 args
try {
    $c = new CairoToyFontFace();
} catch (CairoException $e) {
    var_dump($e->getMessage());
}
var_dump($c);

// Test with 1 param
$c = new CairoToyFontFace("NotARealFont");
var_dump($c);

// Test with a silly param
$o = array();
try {
    $c = new CairoToyFontFace($o);
} catch (CairoException $e) {
    var_dump($e->getMessage());
}
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
string(69) "CairoToyFontFace::__construct() expects at least 1 parameter, 0 given"
object(CairoToyFontFace)#2 (0) {
}
object(CairoToyFontFace)#1 (0) {
}
string(77) "CairoToyFontFace::__construct() expects parameter 1 to be string, array given"
object(CairoToyFontFace)#1 (0) {
}
