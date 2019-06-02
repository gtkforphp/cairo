--TEST--
Cairo\Surface->copyPage() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!method_exists('Cairo\Surface', 'copyPage')) die('skip - Cairo\Surface->copyPage not available');
?>
--FILE--
<?php
$surface = new Cairo\Surface\Image(Cairo\Surface\ImageFormat::ARGB32, 50, 50);
var_dump($surface);

$surface->copyPage();

/* Wrong number args */
try {
    $surface->copyPage('foo');
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Surface\Image)#%d (0) {
}
Cairo\Surface::copyPage() expects exactly 0 parameters, 1 given