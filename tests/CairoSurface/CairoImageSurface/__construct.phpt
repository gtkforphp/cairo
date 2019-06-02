--TEST--
new Cairo\Surface\Image [__construct() method ]
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$surface = new Cairo\Surface\Image(Cairo\Surface\ImageFormat::ARGB32, 50, 50);
var_dump($surface);

/* Wrong number args - 1 */
try {
    new Cairo\Surface\Image();
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 2 */
try {
    new Cairo\Surface\Image(Cairo\Surface\ImageFormat::ARGB32);
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 3 */
try {
    new Cairo\Surface\Image(Cairo\Surface\ImageFormat::ARGB32, 1);
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 4 */
try {
    new Cairo\Surface\Image(Cairo\Surface\ImageFormat::ARGB32, 1, 1, 1);
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 1 */
try {
    new Cairo\Surface\Image(array(), 1, 1);
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 2 */
try {
    new Cairo\Surface\Image(Cairo\Surface\ImageFormat::ARGB32, array(), 1);
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 3 */
try {
    new Cairo\Surface\Image(Cairo\Surface\ImageFormat::ARGB32, 1, array());
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Surface\Image)#%d (0) {
}
Cairo\Surface\Image::__construct() expects exactly 3 parameters, 0 given
Cairo\Surface\Image::__construct() expects exactly 3 parameters, 1 given
Cairo\Surface\Image::__construct() expects exactly 3 parameters, 2 given
Cairo\Surface\Image::__construct() expects exactly 3 parameters, 4 given
Cairo\Surface\Image::__construct() expects parameter 1 to be int, array given
Cairo\Surface\Image::__construct() expects parameter 2 to be int, array given
Cairo\Surface\Image::__construct() expects parameter 3 to be int, array given