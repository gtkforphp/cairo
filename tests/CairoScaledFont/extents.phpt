--TEST--
CairoScaledFont->extents() method
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

var_dump($scaled->extents());

/* Wrong number args */
try {
    $scaled->extents('foo');
    trigger_error('status requires only one arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoToyFontFace)#%d (0) {
}
object(CairoScaledFont)#%d (0) {
}
array(5) {
  ["ascent"]=>
  float(0.90%A)
  ["descent"]=>
  float(0.21%A)
  ["height"]=>
  float(1.14%A)
  ["max_x_advance"]=>
  float(2.66%A)
  ["max_y_advance"]=>
  float(0%A)
}
CairoScaledFont::extents() expects exactly 0 parameters, 1 given