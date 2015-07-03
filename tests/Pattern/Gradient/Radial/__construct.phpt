--TEST--
new Cairo\Pattern\Gradient\Radial [ __construct method ]
--EXTENSIONS--
eos_datastructures
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
?>
--FILE--
<?php
use Cairo\Pattern\Gradient\Radial;

$pattern = new Radial(0.5, 0.5, 0.25, 0.5, 0.5, 0.5);
var_dump($pattern);

/* Wrong number args - requires 6 */
try {
    new Radial();
    trigger_error('CairoRadialGradient::__construct with no args should fail');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 6 */
try {
    new Radial(1);
    trigger_error('CairoRadialGradient::__construct with 1 arg should fail');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 6 */
try {
    new Radial(1, 1);
    trigger_error('CairoRadialGradient::__construct with 2 args should fail');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 6 */
try {
    new Radial(1, 1, 1);
    trigger_error('CairoRadialGradient::__construct with 3 args should fail');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 6 */
try {
    new Radial(1, 1, 1, 1);
    trigger_error('CairoRadialGradient::__construct with 4 args should fail');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 6 */
try {
    new Radial(1, 1, 1, 1, 1);
    trigger_error('CairoRadialGradient::__construct with 5 args should fail');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 6 */
try {
    new Radial(1, 1, 1, 1, 1, 1, 1);
    trigger_error('CairoRadialGradient::__construct with 7 args should fail');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 1 */
try {
    new Radial(array(), 1, 1, 1, 1, 1);
    trigger_error('CairoRadialGradient::__construct requires all doubles');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 2 */
try {
    new Radial(1, array(), 1, 1, 1, 1);
    trigger_error('CairoRadialGradient::__construct requires all doubles');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 3 */
try {
    new Radial(1, 1, array(), 1, 1, 1);
    trigger_error('CairoRadialGradient::__construct requires all doubles');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 4 */
try {
    new Radial(1, 1, 1, array(), 1, 1);
    trigger_error('CairoRadialGradient::__construct requires all doubles');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 5 */
try {
    new Radial(1, 1, 1, 1, array(), 1);
    trigger_error('CairoRadialGradient::__construct requires all doubles');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 6 */
try {
    new Radial(1, 1, 1, 1, 1, array());
    trigger_error('CairoRadialGradient::__construct requires all doubles');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Pattern\Gradient\Radial)#%d (0) {
}
Cairo\Pattern\Gradient\Radial::__construct() expects exactly 6 parameters, 0 given
Cairo\Pattern\Gradient\Radial::__construct() expects exactly 6 parameters, 1 given
Cairo\Pattern\Gradient\Radial::__construct() expects exactly 6 parameters, 2 given
Cairo\Pattern\Gradient\Radial::__construct() expects exactly 6 parameters, 3 given
Cairo\Pattern\Gradient\Radial::__construct() expects exactly 6 parameters, 4 given
Cairo\Pattern\Gradient\Radial::__construct() expects exactly 6 parameters, 5 given
Cairo\Pattern\Gradient\Radial::__construct() expects exactly 6 parameters, 7 given
Cairo\Pattern\Gradient\Radial::__construct() expects parameter 1 to be float, array given
Cairo\Pattern\Gradient\Radial::__construct() expects parameter 2 to be float, array given
Cairo\Pattern\Gradient\Radial::__construct() expects parameter 3 to be float, array given
Cairo\Pattern\Gradient\Radial::__construct() expects parameter 4 to be float, array given
Cairo\Pattern\Gradient\Radial::__construct() expects parameter 5 to be float, array given
Cairo\Pattern\Gradient\Radial::__construct() expects parameter 6 to be float, array given