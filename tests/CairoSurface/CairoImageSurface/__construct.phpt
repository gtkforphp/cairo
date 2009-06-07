--TEST--
new CairoImageSurface [__construct() method ]
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$surface = new CairoImageSurface(CairoFormat::ARGB32, 50, 50);
var_dump($surface);

/* Wrong number args - 1 */
try {
    new CairoImageSurface();
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 2 */
try {
    new CairoImageSurface(CairoFormat::ARGB32);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 3 */
try {
    new CairoImageSurface(CairoFormat::ARGB32, 1);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 4 */
try {
    new CairoImageSurface(CairoFormat::ARGB32, 1, 1, 1);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 1 */
try {
    new CairoImageSurface(array(), 1, 1);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 2 */
try {
    new CairoImageSurface(CairoFormat::ARGB32, array(), 1);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 3 */
try {
    new CairoImageSurface(CairoFormat::ARGB32, 1, array());
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
CairoImageSurface::__construct() expects exactly 3 parameters, 0 given
CairoImageSurface::__construct() expects exactly 3 parameters, 1 given
CairoImageSurface::__construct() expects exactly 3 parameters, 2 given
CairoImageSurface::__construct() expects exactly 3 parameters, 4 given
CairoImageSurface::__construct() expects parameter 1 to be long, array given
CairoImageSurface::__construct() expects parameter 2 to be long, array given
CairoImageSurface::__construct() expects parameter 3 to be long, array given