--TEST--
new CairoPsSurface [__construct() method ]
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!in_array('PS', Cairo::availableSurfaces())) die('skip - PS surface not available');
?>
--FILE--
<?php
$surface = new CairoPsSurface(NULL, 50, 50);
var_dump($surface);

$surface = new CairoPsSurface(dirname(__FILE__) . '/nametest.ps', 50, 50);
var_dump($surface);

$fp = fopen(dirname(__FILE__) . '/streamtest.ps', 'wb');
$surface = new CairoPsSurface($fp, 50, 50);
var_dump($surface);

/* Wrong number args - 1 */
try {
    new CairoPsSurface();
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 2 */
try {
    new CairoPsSurface(NULL);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 3 */
try {
    new CairoPsSurface(NULL, 1);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 4 */
try {
    new CairoPsSurface(NULL, 1, 1, 1);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 1 */
try {
    new CairoPsSurface(array(), 1, 1);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 2 */
try {
    new CairoPsSurface(NULL, array(), 1);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 3 */
try {
    new CairoPsSurface(NULL, 1, array());
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--CLEAN--
<?php
unlink(dirname(__FILE__) . '/nametest.ps');
unlink(dirname(__FILE__) . '/streamtest.ps');
?>
--EXPECTF--
object(CairoPsSurface)#%d (0) {
}
object(CairoPsSurface)#%d (0) {
}
object(CairoPsSurface)#%d (0) {
}
CairoPsSurface::__construct() expects exactly 3 parameters, 0 given
CairoPsSurface::__construct() expects exactly 3 parameters, 1 given
CairoPsSurface::__construct() expects exactly 3 parameters, 2 given
CairoPsSurface::__construct() expects exactly 3 parameters, 4 given
CairoPsSurface::__construct() expects parameter 1 to be null, a string, or a stream resource
CairoPsSurface::__construct() expects parameter 2 to be double, array given
CairoPsSurface::__construct() expects parameter 3 to be double, array given