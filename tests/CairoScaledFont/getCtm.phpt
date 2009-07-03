--TEST--
CairoScaledFont->getCtm() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
include(dirname(__FILE__) . '/create_toyfont.inc');
var_dump($fontface);
$matrix1 = new CairoMatrix(1);
$matrix2 = new CairoMatrix(1,1);
$fontoptions = new CairoFontOptions();

$scaled = new CairoScaledFont($fontface, $matrix1, $matrix2, $fontoptions);
var_dump($scaled);

var_dump($scaled->getCtm());

/* Wrong number args */
try {
    $scaled->getCtm('foo');
    trigger_error('status requires only one arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

die; // GC issue, bogus memleaks reported without this
?>
--EXPECTF--
object(CairoToyFontFace)#%d (0) {
}
object(CairoScaledFont)#%d (0) {
}
object(CairoMatrix)#%d (0) {
}
CairoScaledFont::getCtm() expects exactly 0 parameters, 1 given
