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
$c = new CairoToyFontFace();
var_dump($c);

// Test with 1 param
$c = new CairoToyFontFace("NotARealFont");
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

Fatal error: Uncaught exception 'CairoException' with message 'CairoToyFontFace::__construct() expects at least 1 parameter, 0 given' in %s:%d
Stack trace:
#0 %s(19): CairoToyFontFace->__construct()
#1 {main}
  thrown in %s on line %d
