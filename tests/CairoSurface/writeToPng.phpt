--TEST--
CairoSurface::writeToPng() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!in_array('PNG', cairo_available_surfaces())) die('skip - PNG support not available');
?>
--FILE--
<?php
$surface = new CairoImageSurface(CairoFormat::ARGB32, 50, 50);
var_dump($surface);

$surface->writeToPng(dirname(__FILE__) . '/test.png');

$fp = fopen(dirname(__FILE__) . '/stream.png', 'wb');
$surface->writeToPng($fp);

/* Wrong number args - 1 */
try {
    $surface->writeToPng();
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 2 */
try {
    $surface->writeToPng('', 1);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg */
try {
    $surface->writeToPng(array());
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--CLEAN--
<?php
unlink(dirname(__FILE__) . '/test.png');
unlink(dirname(__FILE__) . '/stream.png');
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
CairoSurface::writeToPng() expects exactly 1 parameter, 0 given
CairoSurface::writeToPng() expects exactly 1 parameter, 2 given
CairoSurface::writeToPng() expects parameter 1 to be a string or a stream resource