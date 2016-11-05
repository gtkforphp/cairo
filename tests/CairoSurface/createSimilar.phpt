--TEST--
CairoSurface->createSimilar() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$surface = new CairoImageSurface(CairoFormat::ARGB32, 50, 50);
var_dump($surface);

$newsurface = $surface->createSimilar(CairoContent::COLOR, 10, 10);
var_dump($newsurface);

/* Wrong number args - 1 */
try {
    $surface->createSimilar();
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 2 */
try {
    $surface->createSimilar(CairoContent::COLOR);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 3 */
try {
    $surface->createSimilar(CairoContent::COLOR, 10);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 4 */
try {
    $surface->createSimilar(CairoContent::COLOR, 10, 10, 10);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 1 */
try {
    $surface->createSimilar(array(), 10, 10);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 2 */
try {
    $surface->createSimilar(CairoContent::COLOR, array(), 10);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 3 */
try {
    $surface->createSimilar(CairoContent::COLOR, 10, array());
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
CairoSurface::createSimilar() expects exactly 3 parameters, 0 given
CairoSurface::createSimilar() expects exactly 3 parameters, 1 given
CairoSurface::createSimilar() expects exactly 3 parameters, 2 given
CairoSurface::createSimilar() expects exactly 3 parameters, 4 given
CairoSurface::createSimilar() expects parameter 1 to be long, array given
CairoSurface::createSimilar() expects parameter 2 to be long, array given
CairoSurface::createSimilar() expects parameter 3 to be long, array given
