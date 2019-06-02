--TEST--
Cairo\Surface\Image::createForData() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$surface = Cairo\Surface\Image::createForData('', Cairo\Surface\ImageFormat::ARGB32, 50, 50);
var_dump($surface);

/* Wrong number args - 1 */
try {
    Cairo\Surface\Image::createForData();
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 2 */
try {
    Cairo\Surface\Image::createForData('');
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 3 */
try {
    Cairo\Surface\Image::createForData('', Cairo\Surface\ImageFormat::ARGB32);
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 4 */
try {
    Cairo\Surface\Image::createForData('', Cairo\Surface\ImageFormat::ARGB32, 1);
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 5 */
try {
    Cairo\Surface\Image::createForData('', Cairo\Surface\ImageFormat::ARGB32, 1, 1, 1);
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 1 */
try {
    Cairo\Surface\Image::createForData(array(), 1, 1, 1);
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 2 */
try {
    Cairo\Surface\Image::createForData('', array(), 1, 1);
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 3 */
try {
    Cairo\Surface\Image::createForData('', 1, array(), 1);
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 4 */
try {
    Cairo\Surface\Image::createForData('', 1, 1, array());
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Surface\Image)#%d (0) {
}
Cairo\Surface\Image::createForData() expects exactly 4 parameters, 0 given
Cairo\Surface\Image::createForData() expects exactly 4 parameters, 1 given
Cairo\Surface\Image::createForData() expects exactly 4 parameters, 2 given
Cairo\Surface\Image::createForData() expects exactly 4 parameters, 3 given
Cairo\Surface\Image::createForData() expects exactly 4 parameters, 5 given
Cairo\Surface\Image::createForData() expects parameter 1 to be string, array given
Cairo\Surface\Image::createForData() expects parameter 2 to be int, array given
Cairo\Surface\Image::createForData() expects parameter 3 to be int, array given
Cairo\Surface\Image::createForData() expects parameter 4 to be int, array given
