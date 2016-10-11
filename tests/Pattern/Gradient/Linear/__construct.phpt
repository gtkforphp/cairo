--TEST--
Cairo\Pattern\Gradient\Linear->__construct()
--EXTENSIONS--
eos_datastructures
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
?>
--FILE--
<?php
use Cairo\Pattern\Gradient\Linear;

$pattern = new Linear(1, 2, 3, 4);
var_dump($pattern);

/* Wrong number args - requires 4 */
try {
    new Linear();
    trigger_error('__construct with no args should fail');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 4 */
try {
    new Linear(1);
    trigger_error('__construct with 1 arg should fail');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 4 */
try {
    new Linear(1, 1);
    trigger_error('__construct with 2 args should fail');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 4 */
try {
    new Linear(1, 1, 1);
    trigger_error('__construct with 3 args should fail');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 4 */
try {
    new Linear(1, 1, 1, 1, 1);
    trigger_error('__construct with 5 args should fail');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 1 */
try {
    new Linear(array(), 1, 1, 1);
    trigger_error('__construct requires all doubles');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 2 */
try {
    new Linear(1, array(), 1, 1);
    trigger_error('__construct requires all doubles');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 3 */
try {
    new Linear(1, 1, array(), 1);
    trigger_error('__construct requires all doubles');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 4 */
try {
    new Linear(1, 1, 1, array());
    trigger_error('__construct requires all doubles');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Pattern\Gradient\Linear)#%d (0) {
}
Cairo\Pattern\Gradient\Linear::__construct() expects exactly 4 parameters, 0 given
Cairo\Pattern\Gradient\Linear::__construct() expects exactly 4 parameters, 1 given
Cairo\Pattern\Gradient\Linear::__construct() expects exactly 4 parameters, 2 given
Cairo\Pattern\Gradient\Linear::__construct() expects exactly 4 parameters, 3 given
Cairo\Pattern\Gradient\Linear::__construct() expects exactly 4 parameters, 5 given
Cairo\Pattern\Gradient\Linear::__construct() expects parameter 1 to be float, array given
Cairo\Pattern\Gradient\Linear::__construct() expects parameter 2 to be float, array given
Cairo\Pattern\Gradient\Linear::__construct() expects parameter 3 to be float, array given
Cairo\Pattern\Gradient\Linear::__construct() expects parameter 4 to be float, array given