--TEST--
Cairo\Surface->getFallbackResolution() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!method_exists('Cairo\Surface', 'getFallbackResolution')) die('skip - Cairo\Surface->getFallbackResolution not available');
?>
--FILE--
<?php
$surface = new Cairo\Surface\Image(Cairo\Surface\ImageFormat::ARGB32, 50, 50);
var_dump($surface);

var_dump($surface->getFallbackResolution());

/* Wrong number args */
try {
    $surface->getFallbackResolution('foo');
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Surface\Image)#%d (0) {
}
array(2) {
  [0]=>
  float(%d)
  [1]=>
  float(%d)
}
Cairo\Surface::getFallbackResolution() expects exactly 0 parameters, 1 given