--TEST--
Cairo\Surface\Image::createFromPng() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!in_array('PNG', Cairo::availableSurfaces())) die('skip - PNG support not available');
?>
--FILE--
<?php
$surface = Cairo\Surface\Image::createFromPng(dirname(__FILE__) . '/red.png');
var_dump($surface);

$resource = fopen(dirname(__FILE__) . '/red.png', 'rw');
$surface = Cairo\Surface\Image::createFromPng($resource);
var_dump($surface);
fclose($resource);

/* Wrong number args - 1 */
try {
    Cairo\Surface\Image::createFromPng();
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 2 */
try {
    Cairo\Surface\Image::createFromPng('', 1);
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg */
try {
    Cairo\Surface\Image::createFromPng(array());
    trigger_error('We should bomb here');
} catch (Cairo\Exception $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Surface\Image)#%d (0) {
}
object(Cairo\Surface\Image)#%d (0) {
}
Cairo\Surface\Image::createFromPng() expects exactly 1 parameter, 0 given
Cairo\Surface\Image::createFromPng() expects exactly 1 parameter, 2 given
Cairo\Surface\Image::createFromPng() expects parameter 1 to be a string or a stream resource