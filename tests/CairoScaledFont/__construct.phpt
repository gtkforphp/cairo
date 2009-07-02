--TEST--
new CairoScaledFont [ __construct() method ]
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

/* Wrong number args - 1 */
try {
    new CairoScaledFont();
    trigger_error('CairoScaled font requires 4 args, none given');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 2 */
try {
    new CairoScaledFont($fontface);
    trigger_error('CairoScaled font requires 4 args, 1 given');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 3 */
try {
    new CairoScaledFont($fontface, $matrix1);
    trigger_error('CairoScaled font requires 4 args, 2 given');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 4 */
try {
    new CairoScaledFont($fontface, $matrix1, $matrix2);
    trigger_error('CairoScaled font requires 4 args, 3 given');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 5 */
try {
    new CairoScaledFont($fontface, $matrix1, $matrix2, $fontoptions, 1);
    trigger_error('CairoScaled font requires 4 args, 5 given');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong Arg type 1 */
try {
    new CairoScaledFont(array(), $matrix1, $matrix2, $fontoptions);
    trigger_error('CairoScaled font requires CairoFontFace as first parameter');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong Arg type 2 */
try {
    new CairoScaledFont($fontface, array(), $matrix2, $fontoptions);
    trigger_error('CairoScaled font requires CairoFontFace as second parameter');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong Arg type 3 */
try {
    new CairoScaledFont($fontface, $matrix1, array(), $fontoptions);
    trigger_error('CairoScaled font requires CairoFontFace as third parameter');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong Arg type 4 */
try {
    new CairoScaledFont($fontface, $matrix1, $matrix2, array());
    trigger_error('CairoScaled font requires CairoFontFace as fourth parameter');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoToyFontFace)#%d (0) {
}
object(CairoScaledFont)#%d (0) {
}
CairoScaledFont::__construct() expects exactly 4 parameters, 0 given
CairoScaledFont::__construct() expects exactly 4 parameters, 1 given
CairoScaledFont::__construct() expects exactly 4 parameters, 2 given
CairoScaledFont::__construct() expects exactly 4 parameters, 3 given
CairoScaledFont::__construct() expects exactly 4 parameters, 5 given
CairoScaledFont::__construct() expects parameter 1 to be CairoFontFace, array given
CairoScaledFont::__construct() expects parameter 2 to be CairoMatrix, array given
CairoScaledFont::__construct() expects parameter 3 to be CairoMatrix, array given
CairoScaledFont::__construct() expects parameter 4 to be CairoFontOptions, array given