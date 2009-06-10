--TEST--
new CairoLinearGradient [ __construct method ]
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$pattern = new CairoLinearGradient(1, 2, 3, 4);
var_dump($pattern);

/* Wrong number args - requires 4 */
try {
    new CairoLinearGradient();
    trigger_error('CairoLinearGradient::__construct with no args should fail');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 4 */
try {
    new CairoLinearGradient(1);
    trigger_error('CairoLinearGradient::__construct with 1 arg should fail');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 4 */
try {
    new CairoLinearGradient(1, 1);
    trigger_error('CairoLinearGradient::__construct with 2 args should fail');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 4 */
try {
    new CairoLinearGradient(1, 1, 1);
    trigger_error('CairoLinearGradient::__construct with 3 args should fail');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 4 */
try {
    new CairoLinearGradient(1, 1, 1, 1, 1);
    trigger_error('CairoLinearGradient::__construct with 5 args should fail');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 1 */
try {
    new CairoLinearGradient(array(), 1, 1, 1);
    trigger_error('CairoLinearGradient::__construct requires all doubles');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 2 */
try {
    new CairoLinearGradient(1, array(), 1, 1);
    trigger_error('CairoLinearGradient::__construct requires all doubles');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 3 */
try {
    new CairoLinearGradient(1, 1, array(), 1);
    trigger_error('CairoLinearGradient::__construct requires all doubles');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 4 */
try {
    new CairoLinearGradient(1, 1, 1, array());
    trigger_error('CairoLinearGradient::__construct requires all doubles');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoLinearGradient)#%d (0) {
}
CairoLinearGradient::__construct() expects exactly 4 parameters, 0 given
CairoLinearGradient::__construct() expects exactly 4 parameters, 1 given
CairoLinearGradient::__construct() expects exactly 4 parameters, 2 given
CairoLinearGradient::__construct() expects exactly 4 parameters, 3 given
CairoLinearGradient::__construct() expects exactly 4 parameters, 5 given
CairoLinearGradient::__construct() expects parameter 1 to be double, array given
CairoLinearGradient::__construct() expects parameter 2 to be double, array given
CairoLinearGradient::__construct() expects parameter 3 to be double, array given
CairoLinearGradient::__construct() expects parameter 4 to be double, array given