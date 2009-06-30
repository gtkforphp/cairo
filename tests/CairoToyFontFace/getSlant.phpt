--TEST--
CairoToyFontFace::getSlant() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!class_exists('CairoToyFontFace')) die('skip - CairoToyFontFace not enabled');
?>
--FILE--
<?php
// Test with all parameters
$c = new CairoToyFontFace("sans-serif", CairoFontSlant::NORMAL, CairoFontWeight::NORMAL);
var_dump($c->getSlant());

$c = new CairoToyFontFace("sans-serif", CairoFontSlant::ITALIC, CairoFontWeight::NORMAL);
var_dump($c->getSlant());
?>
--EXPECTF--
int(0)
int(1)
