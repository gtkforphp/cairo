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

/* set font face, font options, matrix */
$orig_matrix = new CairoMatrix();
$context->setFontMatrix($orig_matrix);
$orig_options = new CairoFontOptions();
$context->setFontOptions($orig_options);
include(dirname(__FILE__) . '/create_toyfont.inc');
$orig_fontface = $fontface;
$context->setFontFace($orig_fontface);

/* create scaled font with new font face, font options, matrix */
$matrix1 = new CairoMatrix(1);
$matrix2 = new CairoMatrix(1,1);
$fontoptions = new CairoFontOptions();

$scaled = new CairoScaledFont($fontface, $matrix1, $matrix2, $fontoptions);
var_dump($scaled);

$context->setScaledFont($scaled);

/* compare new values to original values */
var_dump($matrix1 === $orig_matrix);
var_dump($fonface === $orig_fontface);
var_dump($fontoptions === $orig_options);

/* compare matrix, font face, font options, scaled font */
var_dump($matrix1 === $context->getFontMatrix());
var_dump($fonface === $context->getFontFace());
var_dump($fontoptions === $context->getFontOptions());
var_dump($scaled === $context->getScaledFont());
die;










try {
    $context->setScaledFont();
    trigger_error('setScaledFont requires one arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

try {
    $context->setScaledFont(1, 1);
    trigger_error('setScaledFont requires only one arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

try {
    $context->setScaledFont(1);
    trigger_error('setScaledFont requires instanceof CairoScaledFont');
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
object(CairoToyFontFace)#%d (0) {
}
bool(true)
object(CairoToyFontFace)#%d (0) {
}
bool(true)
CairoContext::setFontFace() expects exactly 1 parameter, 0 given
CairoContext::setFontFace() expects exactly 1 parameter, 2 given
CairoContext::setFontFace() expects parameter 1 to be CairoFontFace, integer given