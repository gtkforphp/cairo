--TEST--
CairoToyFontFace::getFamily() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!class_exists('CairoToyFontFace')) die('skip - CairoToyFontFace not enabled');
?>
--FILE--
<?php
// Test with all parameters
$c = new CairoToyFontFace("sans-serif", CairoFontSlant::NORMAL, CairoFontWeight::NORMAL);
var_dump($c->getFamily());
?>
--EXPECTF--
string(10) "sans-serif"
