--TEST--
CairoFontFace->getType() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
include(dirname(__FILE__) . '/create_toyfont.inc');
var_dump($fontface);

var_dump($fontface->getType());

try {
    $fontface->getType('foo');
    trigger_error('CairoFontFace->getType requires no arguments');
} catch (CairoException $e) {
    echo $e->getMessage();
}
?>
--EXPECTF--
object(CairoToyFontFace)#%d (0) {
}
int(0)
CairoFontFace::getType() expects exactly 0 parameters, 1 given