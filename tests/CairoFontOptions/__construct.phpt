--TEST--
new Cairo\FontOptions [ __construct() method ]
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$options = new Cairo\FontOptions();
var_dump($options);

/* Wrong number args */
try {
    new Cairo\FontOptions('foo');
    trigger_error('__construct requires no args');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\FontOptions)#%d (0) {
}
Cairo\FontOptions::__construct() expects exactly 0 parameters, 1 given