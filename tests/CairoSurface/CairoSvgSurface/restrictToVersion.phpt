--TEST--
Cairo\Surface\Svg->restrictToVersion() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!in_array('SVG', Cairo::availableSurfaces())) die('skip - SVG surface not available');
?>
--FILE--
<?php
$surface = new Cairo\Surface\Svg(NULL, 50, 50);
var_dump($surface);

$surface->restrictToVersion(Cairo\Surface\Svg\Version::VERSION_1_1);

/* Wrong number args */
try {
    $surface->restrictToVersion();
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args 2 */
try {
    $surface->restrictToVersion(1, 1);
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type */
try {
    $surface->restrictToVersion(array());
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Surface\Svg)#%d (0) {
}
Cairo\Surface\Svg::restrictToVersion() expects exactly 1 parameter, 0 given
Cairo\Surface\Svg::restrictToVersion() expects exactly 1 parameter, 2 given
Cairo\Surface\Svg::restrictToVersion() expects parameter 1 to be int, array given