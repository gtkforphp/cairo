--TEST--
Cairo\Surface\ImageFormat::strideForWidth() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!method_exists('Cairo\Surface\ImageFormat', 'strideForWidth')) die('skip - Cairo\Surface\ImageFormat::strideForWidth not available');
?>
--FILE--
<?php
echo Cairo\Surface\ImageFormat::strideForWidth(1, 5), PHP_EOL;

/* Wrong number args */
try {
    Cairo\Surface\ImageFormat::strideForWidth();
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args 2 */
try {
    Cairo\Surface\ImageFormat::strideForWidth(1);
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args 3 */
try {
    Cairo\Surface\ImageFormat::strideForWidth(1, 1, 1);
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type */
try {
    Cairo\Surface\ImageFormat::strideForWidth(array(), 1);
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type */
try {
    Cairo\Surface\ImageFormat::strideForWidth(1, array());
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
20
Cairo\Surface\ImageFormat::strideForWidth() expects exactly 2 parameters, 0 given
Cairo\Surface\ImageFormat::strideForWidth() expects exactly 2 parameters, 1 given
Cairo\Surface\ImageFormat::strideForWidth() expects exactly 2 parameters, 3 given
Cairo\Surface\ImageFormat::strideForWidth() expects parameter 1 to be int, array given
Cairo\Surface\ImageFormat::strideForWidth() expects parameter 2 to be int, array given