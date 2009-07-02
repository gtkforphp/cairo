--TEST--
CairoToyFontFace::getWeight() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!class_exists('CairoToyFontFace')) die('skip - CairoToyFontFace not enabled');
?>
--FILE--
<?php
// Test with all parameters
$c = new CairoToyFontFace("sans-serif", CairoFontWeight::NORMAL, CairoFontWeight::NORMAL);
var_dump($c->getWeight());

$c = new CairoToyFontFace("sans-serif", CairoFontWeight::NORMAL, CairoFontWeight::BOLD);
var_dump($c->getWeight());
?>
--EXPECTF--
int(0)
int(1)
