--TEST--
Cairo\Surface->status() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$surface = new Cairo\Surface\Image(Cairo\Surface\ImageFormat::ARGB32, 50, 50);
var_dump($surface);

$status = $surface->status();

var_dump($status);
var_dump($status == CairoStatus::SUCCESS);

/* Wrong number args */
try {
    $surface->status('foo');
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Surface\Image)#%d (0) {
}
long(0)
bool(true)
Cairo\Surface::status() expects exactly 0 parameters, 1 given