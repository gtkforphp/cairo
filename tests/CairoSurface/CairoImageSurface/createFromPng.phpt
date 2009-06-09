--TEST--
CairoImageSurface::createFromPng() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!in_array('PNG', Cairo::availableSurfaces())) die('skip - PNG support not available');
?>
--FILE--
<?php
$surface = CairoImageSurface::createFromPng(dirname(__FILE__) . '/red.png');
var_dump($surface);

$resource = fopen(dirname(__FILE__) . '/red.png', 'rw');
$surface = CairoImageSurface::createFromPng($resource);
var_dump($surface);
fclose($resource);

/* Wrong number args - 1 */
try {
    CairoImageSurface::createFromPng();
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 2 */
try {
    CairoImageSurface::createFromPng('', 1);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg */
try {
    CairoImageSurface::createFromPng(array());
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoImageSurface)#%d (0) {
}
CairoImageSurface::createFromPng() expects exactly 1 parameter, 0 given
CairoImageSurface::createFromPng() expects exactly 1 parameter, 2 given
CairoImageSurface::createFromPng() expects parameter 1 to be a string or a stream resource