--TEST--
new Cairo\Surface\Recording [__construct() method ]
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!in_array('RECORDING', Cairo::availableSurfaces())) die('skip - SVG surface not available');
?>
--FILE--
<?php
$surface = new Cairo\Surface\Recording(Cairo\Surface\Content::COLOR_ALPHA);
var_dump($surface);

$extents = array('x' => 0, 'y' => 0, 'width' => 400, 'height' => 400);
$surface = new Cairo\Surface\Recording(Cairo\Surface\Content::COLOR_ALPHA, $extents);
var_dump($surface);

/* Wrong number args - 1 */
try {
    new Cairo\Surface\Recording();
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 4 */
try {
    new Cairo\Surface\Recording(NULL, 1, 1, 1);
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 1 */
try {
    new Cairo\Surface\Recording(array(), 1);
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 2 */
try {
    new Cairo\Surface\Recording(NULL, 1);
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Surface\Recording)#%d (0) {
}
object(Cairo\Surface\Recording)#%d (0) {
}
Cairo\Surface\Recording::__construct() expects at least 1 parameter, 0 given
Cairo\Surface\Recording::__construct() expects at most 2 parameters, 4 given
Cairo\Surface\Recording::__construct() expects parameter 1 to be int, array given
Cairo\Surface\Recording::__construct() expects parameter 2 to be array, int given
