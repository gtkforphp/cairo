--TEST--
Cairo::statusToString() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$surface = new Cairo\Surface\Image(CAIRO_FORMAT_ARGB32, 50, 50);
var_dump($surface);

$context = new Cairo\Context($surface);
var_dump($context);

var_dump(Cairo::statusToString($context->status()));

/* Wrong number args */
try {
    Cairo::statusToString();
    trigger_error('Cairo::statusToString should take 1 argument');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args 2*/
try {
    Cairo::statusToString(1, 1);
    trigger_error('Cairo::statusToString should take 1 argument');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type*/
try {
    Cairo::statusToString(array());
    trigger_error('Cairo::statusToString arg 1 must be scalar (int)');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Surface\Image)#%d (0) {
}
object(Cairo\Context)#%d (0) {
}
string(21) "no error has occurred"
Cairo::statusToString() expects exactly 1 parameter, 0 given
Cairo::statusToString() expects exactly 1 parameter, 2 given
Cairo::statusToString() expects parameter 1 to be int, array given
