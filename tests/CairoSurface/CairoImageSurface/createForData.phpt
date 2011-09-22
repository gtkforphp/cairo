--TEST--
CairoImageSurface::createForData() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$surface = CairoImageSurface::createForData('', CairoFormat::ARGB32, 50, 50);
var_dump($surface);

/* Wrong number args - 1 */
try {
    CairoImageSurface::createForData();
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 2 */
try {
    CairoImageSurface::createForData('');
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 3 */
try {
    CairoImageSurface::createForData('', CairoFormat::ARGB32);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 4 */
try {
    CairoImageSurface::createForData('', CairoFormat::ARGB32, 1);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 5 */
try {
    CairoImageSurface::createForData('', CairoFormat::ARGB32, 1, 1, 1);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 1 */
try {
    CairoImageSurface::createForData(array(), 1, 1, 1);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 2 */
try {
    CairoImageSurface::createForData('', array(), 1, 1);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 3 */
try {
    CairoImageSurface::createForData('', 1, array(), 1);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 4 */
try {
    CairoImageSurface::createForData('', 1, 1, array());
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
CairoImageSurface::createForData() expects exactly 4 parameters, 0 given
CairoImageSurface::createForData() expects exactly 4 parameters, 1 given
CairoImageSurface::createForData() expects exactly 4 parameters, 2 given
CairoImageSurface::createForData() expects exactly 4 parameters, 3 given
CairoImageSurface::createForData() expects exactly 4 parameters, 5 given
CairoImageSurface::createForData() expects parameter 1 to be string, array given
CairoImageSurface::createForData() expects parameter 2 to be long, array given
CairoImageSurface::createForData() expects parameter 3 to be long, array given
CairoImageSurface::createForData() expects parameter 4 to be long, array given
