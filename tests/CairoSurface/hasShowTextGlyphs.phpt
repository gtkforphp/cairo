--TEST--
Cairo\Surface->hasShowTextGlyphs() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!method_exists('Cairo\Surface', 'hasShowTextGlyphs')) die('skip - Cairo\Surface->hasShowTextGlyphs not available');
?>
--FILE--
<?php
$surface = new Cairo\Surface\Image(Cairo\Surface\ImageFormat::ARGB32, 50, 50);
var_dump($surface);

var_dump($surface->hasShowTextGlyphs());

/* Wrong number args */
try {
    $surface->hasShowTextGlyphs('foo');
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Surface\Image)#%d (0) {
}
bool(false)
Cairo\Surface::hasShowTextGlyphs() expects exactly 0 parameters, 1 given