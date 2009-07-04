--TEST--
CairoContext->setScaledFont() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$surface = new CairoImageSurface(CairoFormat::ARGB32, 50, 50);
var_dump($surface);

$context = new CairoContext($surface);
var_dump($context);

var_dump($context->getScaledFont());

/* create scaled font with new font face, font options, matrix */
include(dirname(__FILE__) . '/create_toyfont.inc');
$matrix1 = new CairoMatrix(1);
$matrix2 = new CairoMatrix(1,1);
$fontoptions = new CairoFontOptions();

$scaled = new CairoScaledFont($fontface, $matrix1, $matrix2, $fontoptions);

$context->setScaledFont($scaled);
var_dump($context->getScaledFont());

try {
    $context->getScaledFont('foo');
    trigger_error('getScaledFont requires one arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

die; // DO NOT REMOVE THIS - fixes issue in 5.3 with GC giving bogus memleak reports
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
object(CairoScaledFont)#%d (0) {
}
object(CairoScaledFont)#%d (0) {
}
CairoContext::getScaledFont() expects exactly 0 parameters, 1 given