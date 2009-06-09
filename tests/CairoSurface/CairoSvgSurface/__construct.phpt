--TEST--
new CairoSvgSurface [__construct() method ]
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!in_array('SVG', Cairo::availableSurfaces())) die('skip - SVG surface not available');
?>
--FILE--
<?php
$surface = new CairoSvgSurface(NULL, 50, 50);
var_dump($surface);

$surface = new CairoSvgSurface(dirname(__FILE__) . '/nametest.svg', 50, 50);
var_dump($surface);

$fp = fopen(dirname(__FILE__) . '/streamtest.svg', 'wb');
$surface = new CairoSvgSurface($fp, 50, 50);
var_dump($surface);

/* Wrong number args - 1 */
try {
    new CairoSvgSurface();
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 2 */
try {
    new CairoSvgSurface(NULL);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 3 */
try {
    new CairoSvgSurface(NULL, 1);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 4 */
try {
    new CairoSvgSurface(NULL, 1, 1, 1);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 1 */
try {
    new CairoSvgSurface(array(), 1, 1);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 2 */
try {
    new CairoSvgSurface(NULL, array(), 1);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 3 */
try {
    new CairoSvgSurface(NULL, 1, array());
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--CLEAN--
<?php
unlink(dirname(__FILE__) . '/nametest.svg');
unlink(dirname(__FILE__) . '/streamtest.svg');
?>
--EXPECTF--
object(CairoSvgSurface)#%d (0) {
}
object(CairoSvgSurface)#%d (0) {
}
object(CairoSvgSurface)#%d (0) {
}
CairoSvgSurface::__construct() expects exactly 3 parameters, 0 given
CairoSvgSurface::__construct() expects exactly 3 parameters, 1 given
CairoSvgSurface::__construct() expects exactly 3 parameters, 2 given
CairoSvgSurface::__construct() expects exactly 3 parameters, 4 given
CairoSvgSurface::__construct() expects parameter 1 to be null, a string, or a stream resource
CairoSvgSurface::__construct() expects parameter 2 to be double, array given
CairoSvgSurface::__construct() expects parameter 3 to be double, array given