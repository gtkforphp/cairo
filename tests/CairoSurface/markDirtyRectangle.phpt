--TEST--
CairoSurface->markDirtyRectangle() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$surface = new CairoImageSurface(CairoFormat::ARGB32, 50, 50);
var_dump($surface);

$surface->markDirtyRectangle(10, 10, 10, 10);

/* Wrong number args - 1 */
try {
    $surface->markDirtyRectangle();
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 2 */
try {
    $surface->markDirtyRectangle(10);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 3 */
try {
    $surface->markDirtyRectangle(10, 10);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 4 */
try {
    $surface->markDirtyRectangle(10, 10);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 5 */
try {
    $surface->markDirtyRectangle(10, 10, 10, 10, 10);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 1 */
try {
    $surface->markDirtyRectangle(array(), 10, 10, 10);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 2 */
try {
    $surface->markDirtyRectangle(10, array(), 10, 10);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 3 */
try {
    $surface->markDirtyRectangle(10, 10, array(), 10);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 3 */
try {
    $surface->markDirtyRectangle(10, 10, 10, array());
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
CairoSurface::markDirtyRectangle() expects exactly 4 parameters, 0 given
CairoSurface::markDirtyRectangle() expects exactly 4 parameters, 1 given
CairoSurface::markDirtyRectangle() expects exactly 4 parameters, 2 given
CairoSurface::markDirtyRectangle() expects exactly 4 parameters, 2 given
CairoSurface::markDirtyRectangle() expects exactly 4 parameters, 5 given
CairoSurface::markDirtyRectangle() expects parameter 1 to be double, array given
CairoSurface::markDirtyRectangle() expects parameter 2 to be double, array given
CairoSurface::markDirtyRectangle() expects parameter 3 to be double, array given
CairoSurface::markDirtyRectangle() expects parameter 4 to be double, array given