--TEST--
CairoFormat::strideForWidth() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!method_exists('CairoFormat', 'strideForWidth')) die('skip - CairoFormat::strideForWidth not available');
?>
--FILE--
<?php
echo CairoFormat::strideForWidth(1, 5), PHP_EOL;

/* Wrong number args */
try {
    CairoFormat::strideForWidth();
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args 2 */
try {
    CairoFormat::strideForWidth(1);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args 3 */
try {
    CairoFormat::strideForWidth(1, 1, 1);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type */
try {
    CairoFormat::strideForWidth(array(), 1);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type */
try {
    CairoFormat::strideForWidth(1, array());
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
20
CairoFormat::strideForWidth() expects exactly 2 parameters, 0 given
CairoFormat::strideForWidth() expects exactly 2 parameters, 1 given
CairoFormat::strideForWidth() expects exactly 2 parameters, 3 given
CairoFormat::strideForWidth() expects parameter 1 to be long, array given
CairoFormat::strideForWidth() expects parameter 2 to be long, array given