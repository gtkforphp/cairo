--TEST--
Cairo\Pattern\Surface->getSurface() method
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
?>
--FILE--
<?php
$surface = new Cairo\Surface\Image(Cairo\Surface\ImageFormat::ARGB32, 50, 50);
var_dump($surface);

$pattern = new Cairo\Pattern\Surface($surface);
var_dump($pattern);

$surface2 = $pattern->getSurface();
var_dump($surface2);
var_dump($surface === $surface2);

/* Total number of args needed = 0 */
try {
    $pattern->getSurface(1);
    trigger_error('getSurface with too many args');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Surface\Image)#%d (0) {
}
object(Cairo\Pattern\Surface)#%d (0) {
}
object(Cairo\Surface\Image)#%d (0) {
}
bool(true)
Cairo\Pattern\Surface::getSurface() expects exactly 0 parameters, 1 given