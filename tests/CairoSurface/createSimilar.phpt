--TEST--
Cairo\Surface->createSimilar() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$surface = new Cairo\Surface\Image(Cairo\Surface\ImageFormat::ARGB32, 50, 50);
var_dump($surface);

$newsurface = $surface->createSimilar(Cairo\Surface\Content::COLOR, 10, 10);
var_dump($newsurface);

/* Wrong number args - 1 */
try {
    $surface->createSimilar();
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 2 */
try {
    $surface->createSimilar(Cairo\Surface\Content::COLOR);
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 3 */
try {
    $surface->createSimilar(Cairo\Surface\Content::COLOR, 10);
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 4 */
try {
    $surface->createSimilar(Cairo\Surface\Content::COLOR, 10, 10, 10);
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 1 */
try {
    $surface->createSimilar(array(), 10, 10);
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 2 */
try {
    $surface->createSimilar(Cairo\Surface\Content::COLOR, array(), 10);
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 3 */
try {
    $surface->createSimilar(Cairo\Surface\Content::COLOR, 10, array());
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Surface\Image)#%d (0) {
}
object(Cairo\Surface\Image)#%d (0) {
}
Cairo\Surface::createSimilar() expects exactly 3 parameters, 0 given
Cairo\Surface::createSimilar() expects exactly 3 parameters, 1 given
Cairo\Surface::createSimilar() expects exactly 3 parameters, 2 given
Cairo\Surface::createSimilar() expects exactly 3 parameters, 4 given
Cairo\Surface::createSimilar() expects parameter 1 to be int, array given
Cairo\Surface::createSimilar() expects parameter 2 to be float, array given
Cairo\Surface::createSimilar() expects parameter 3 to be float, array given