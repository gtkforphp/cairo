--TEST--
Cairo\Context->setScaledFont() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$surface = new Cairo\Surface\Image(Cairo\Surface\ImageFormat::ARGB32, 50, 50);
var_dump($surface);

$context = new Cairo\Context($surface);
var_dump($context);

/* set font face, font options, matrix */
$orig_matrix = new Cairo\Matrix();
$context->setFontMatrix($orig_matrix);
$orig_options = new Cairo\FontOptions();
$context->setFontOptions($orig_options);
include(dirname(__FILE__) . '/create_toyfont.inc');
$orig_fontface = $fontface;
$context->setFontFace($orig_fontface);

/* create scaled font with new font face, font options, matrix */
include(dirname(__FILE__) . '/create_toyfont.inc');
$matrix1 = new Cairo\Matrix(1);
$matrix2 = new Cairo\Matrix(1,1);
$fontoptions = new Cairo\FontOptions();

$scaled = new Cairo\ScaledFont($fontface, $matrix1, $matrix2, $fontoptions);
var_dump($scaled);

$context->setScaledFont($scaled);

/* compare new values to original values */
var_dump($matrix1 === $orig_matrix);
var_dump($fontface === $orig_fontface);
var_dump($fontoptions === $orig_options);

/* compare matrix, font face, font options, scaled font */
var_dump($matrix1 === $context->getFontMatrix());
var_dump($fontface === $context->getFontFace());
var_dump($fontoptions === $context->getFontOptions());
var_dump($scaled === $context->getScaledFont());

/* create scaled font with new font face, font options, matrix */
include(dirname(__FILE__) . '/create_toyfont.inc');
$matrix1 = new Cairo\Matrix(1);
$matrix2 = new Cairo\Matrix(1,1);
$fontoptions = new Cairo\FontOptions();

$scaled = new Cairo\ScaledFont($fontface, $matrix1, $matrix2, $fontoptions);

$context->setScaledFont($scaled);

try {
    $context->setScaledFont();
    trigger_error('setScaledFont requires one arg');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

try {
    $context->setScaledFont(1, 1);
    trigger_error('setScaledFont requires only one arg');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

try {
    $context->setScaledFont(1);
    trigger_error('setScaledFont requires instanceof Cairo\ScaledFont');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

die; // DO NOT REMOVE THIS - fixes issue in 5.3 with GC giving bogus memleak reports
?>
--EXPECTF--
object(Cairo\Surface\Image)#%d (0) {
}
object(Cairo\Context)#%d (0) {
}
object(Cairo\ScaledFont)#%d (0) {
}
bool(false)
bool(false)
bool(false)
bool(true)
bool(true)
bool(true)
bool(true)
Cairo\Context::setScaledFont() expects exactly 1 parameter, 0 given
Cairo\Context::setScaledFont() expects exactly 1 parameter, 2 given
Cairo\Context::setScaledFont() expects parameter 1 to be Cairo\ScaledFont, int given