--TEST--
new Cairo\ScaledFont [ __construct() method ]
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
include(dirname(__FILE__) . '/create_toyfont.inc');
var_dump($fontface);
$matrix1 = new Cairo\Matrix(1);
$matrix2 = new Cairo\Matrix(1,1);
$fontoptions = new Cairo\FontOptions();

$scaled = new Cairo\ScaledFont($fontface, $matrix1, $matrix2, $fontoptions);
var_dump($scaled);

/* Wrong number args - 1 */
try {
    new Cairo\ScaledFont();
    trigger_error('CairoScaled font requires 4 args, none given');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 2 */
try {
    new Cairo\ScaledFont($fontface);
    trigger_error('CairoScaled font requires 4 args, 1 given');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 3 */
try {
    new Cairo\ScaledFont($fontface, $matrix1);
    trigger_error('CairoScaled font requires 4 args, 2 given');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 4 */
try {
    new Cairo\ScaledFont($fontface, $matrix1, $matrix2);
    trigger_error('CairoScaled font requires 4 args, 3 given');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 5 */
try {
    new Cairo\ScaledFont($fontface, $matrix1, $matrix2, $fontoptions, 1);
    trigger_error('CairoScaled font requires 4 args, 5 given');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong Arg type 1 */
try {
    new Cairo\ScaledFont(array(), $matrix1, $matrix2, $fontoptions);
    trigger_error('CairoScaled font requires Cairo\FontFace as first parameter');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong Arg type 2 */
try {
    new Cairo\ScaledFont($fontface, array(), $matrix2, $fontoptions);
    trigger_error('CairoScaled font requires Cairo\FontFace as second parameter');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong Arg type 3 */
try {
    new Cairo\ScaledFont($fontface, $matrix1, array(), $fontoptions);
    trigger_error('CairoScaled font requires Cairo\FontFace as third parameter');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong Arg type 4 */
try {
    new Cairo\ScaledFont($fontface, $matrix1, $matrix2, array());
    trigger_error('CairoScaled font requires Cairo\FontFace as fourth parameter');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\FontFace\Toy)#%d (0) {
}
object(Cairo\ScaledFont)#%d (0) {
}
Cairo\ScaledFont::__construct() expects exactly 4 parameters, 0 given
Cairo\ScaledFont::__construct() expects exactly 4 parameters, 1 given
Cairo\ScaledFont::__construct() expects exactly 4 parameters, 2 given
Cairo\ScaledFont::__construct() expects exactly 4 parameters, 3 given
Cairo\ScaledFont::__construct() expects exactly 4 parameters, 5 given
Cairo\ScaledFont::__construct() expects parameter 1 to be Cairo\FontFace, array given
Cairo\ScaledFont::__construct() expects parameter 2 to be Cairo\Matrix, array given
Cairo\ScaledFont::__construct() expects parameter 3 to be Cairo\Matrix, array given
Cairo\ScaledFont::__construct() expects parameter 4 to be Cairo\FontOptions, array given