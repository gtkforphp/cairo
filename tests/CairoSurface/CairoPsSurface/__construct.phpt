--TEST--
new Cairo\Surface\Ps [__construct() method ]
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!in_array('PS', Cairo::availableSurfaces())) die('skip - PS surface not available');
?>
--FILE--
<?php
$surface = new Cairo\Surface\Ps(NULL, 50, 50);
var_dump($surface);

$surface = new Cairo\Surface\Ps(dirname(__FILE__) . '/nametest.ps', 50, 50);
var_dump($surface);

$fp = fopen(dirname(__FILE__) . '/streamtest.ps', 'wb');
$surface = new Cairo\Surface\Ps($fp, 50, 50);
var_dump($surface);

/* Wrong number args - 1 */
try {
    new Cairo\Surface\Ps();
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 2 */
try {
    new Cairo\Surface\Ps(NULL);
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 3 */
try {
    new Cairo\Surface\Ps(NULL, 1);
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 4 */
try {
    new Cairo\Surface\Ps(NULL, 1, 1, 1);
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 1 */
try {
    new Cairo\Surface\Ps(array(), 1, 1);
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 2 */
try {
    new Cairo\Surface\Ps(NULL, array(), 1);
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 3 */
try {
    new Cairo\Surface\Ps(NULL, 1, array());
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--CLEAN--
<?php
unlink(dirname(__FILE__) . '/nametest.ps');
unlink(dirname(__FILE__) . '/streamtest.ps');
?>
--EXPECTF--
object(Cairo\Surface\Ps)#%d (0) {
}
object(Cairo\Surface\Ps)#%d (0) {
}
object(Cairo\Surface\Ps)#%d (0) {
}
Cairo\Surface\Ps::__construct() expects exactly 3 parameters, 0 given
Cairo\Surface\Ps::__construct() expects exactly 3 parameters, 1 given
Cairo\Surface\Ps::__construct() expects exactly 3 parameters, 2 given
Cairo\Surface\Ps::__construct() expects exactly 3 parameters, 4 given
Cairo\Surface\Ps::__construct() expects parameter 1 to be null, a string, or a stream resource
Cairo\Surface\Ps::__construct() expects parameter 2 to be float, array given
Cairo\Surface\Ps::__construct() expects parameter 3 to be float, array given