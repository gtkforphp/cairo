--TEST--
new CairoRecordingSurface [__construct() method ]
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!in_array('RECORDING', Cairo::availableSurfaces())) die('skip - SVG surface not available');
?>
--FILE--
<?php
$surface = new CairoRecordingSurface(CairoContent::COLOR_ALPHA);
var_dump($surface);

$extents = array('x' => 0, 'y' => 0, 'width' => 400, 'height' => 400);
$surface = new CairoRecordingSurface(CairoContent::COLOR_ALPHA, $extents);
var_dump($surface);

/* Wrong number args - 1 */
try {
    new CairoRecordingSurface();
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 4 */
try {
    new CairoRecordingSurface(NULL, 1, 1, 1);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 1 */
try {
    new CairoRecordingSurface(array(), 1);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 2 */
try {
    new CairoRecordingSurface(NULL, 1);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoRecordingSurface)#%d (0) {
}
object(CairoRecordingSurface)#%d (0) {
}
CairoRecordingSurface::__construct() expects at least 1 parameter, 0 given
CairoRecordingSurface::__construct() expects at most 2 parameters, 4 given
CairoRecordingSurface::__construct() expects parameter 1 to be long, array given
CairoRecordingSurface::__construct() expects parameter 2 to be array, integer given
