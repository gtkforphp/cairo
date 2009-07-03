--TEST--
CairoScaledFont->textExtents() method
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

var_dump($scaled->textExtents('foobar'));

/* Wrong number args 1 */
try {
    $scaled->textExtents();
    trigger_error('textExtents requires one arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args 1 */
try {
    $scaled->textExtents('foo', 1);
    trigger_error('textExtents requires only one arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type */
try {
    $scaled->textExtents(array());
    trigger_error('textExtents requires one arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoToyFontFace)#%d (0) {
}
object(CairoScaledFont)#%d (0) {
}
array(6) {
  ["x_bearing"]=>
  float(%f)
  ["y_bearing"]=>
  float(%f)
  ["width"]=>
  float(%f)
  ["height"]=>
  float(%f)
  ["x_advance"]=>
  float(%f)
  ["y_advance"]=>
  float(%f)
}
CairoScaledFont::textExtents() expects exactly 1 parameter, 0 given
CairoScaledFont::textExtents() expects exactly 1 parameter, 2 given
CairoScaledFont::textExtents() expects parameter 1 to be string, array given
