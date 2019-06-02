--TEST--
Cairo\Surface\Ps::levelToString() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!in_array('PS', Cairo::availableSurfaces())) die('skip - PS surface not available');
if(!method_exists('Cairo\Surface\Ps', 'levelToString')) die('skip - Cairo\Surface\Ps::levelToString not available');
?>
--FILE--
<?php
echo Cairo\Surface\Ps::levelToString(Cairo\Surface\Ps\Level::LEVEL_2), PHP_EOL;

/* Wrong number args */
try {
    Cairo\Surface\Ps::levelToString();
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args 2 */
try {
    Cairo\Surface\Ps::levelToString(1, 1);
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type */
try {
    Cairo\Surface\Ps::levelToString(array());
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
PS Level 2
Cairo\Surface\Ps::levelToString() expects exactly 1 parameter, 0 given
Cairo\Surface\Ps::levelToString() expects exactly 1 parameter, 2 given
Cairo\Surface\Ps::levelToString() expects parameter 1 to be int, array given