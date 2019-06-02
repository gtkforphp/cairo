--TEST--
new Cairo\Context [ __construct() method ]
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$surface = new Cairo\Surface\Image(Cairo\Surface\ImageFormat::ARGB32, 50, 50);
var_dump($surface);

$context = new Cairo\Context($surface);
var_dump($context);

/* Wrong number args - 1 */
try {
    new Cairo\Context();
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 2 */
try {
    new Cairo\Context($surface, 10);
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 1 */
try {
    new Cairo\Context(1);
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Surface\Image)#%d (0) {
}
object(Cairo\Context)#%d (0) {
}
Cairo\Context::__construct() expects exactly 1 parameter, 0 given
Cairo\Context::__construct() expects exactly 1 parameter, 2 given
Argument 1 passed to Cairo\Context::__construct() must be an instance of Cairo\Surface, int given
