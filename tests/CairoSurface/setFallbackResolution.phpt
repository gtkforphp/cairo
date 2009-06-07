--TEST--
CairoSurface->setFallbackResolution() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$surface = new CairoImageSurface(CairoFormat::ARGB32, 50, 50);
var_dump($surface);

$surface->setFallbackResolution(10, 10);

/* Wrong number args - 1 */
try {
    $surface->setFallbackResolution();
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 2 */
try {
    $surface->setFallbackResolution(10);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 3 */
try {
    $surface->setFallbackResolution(10, 10, 10);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 1 */
try {
    $surface->setFallbackResolution(array(), 10);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 2 */
try {
    $surface->setFallbackResolution(10, array());
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
CairoSurface::setFallbackResolution() expects exactly 2 parameters, 0 given
CairoSurface::setFallbackResolution() expects exactly 2 parameters, 1 given
CairoSurface::setFallbackResolution() expects exactly 2 parameters, 3 given
CairoSurface::setFallbackResolution() expects parameter 1 to be double, array given
CairoSurface::setFallbackResolution() expects parameter 2 to be double, array given