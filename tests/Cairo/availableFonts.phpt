--TEST--
Cairo::availableFonts() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$fonts = Cairo::availableFonts();
var_dump(is_array($fonts));
var_dump($fonts[0]);

/* Wrong number args */
try {
    Cairo::availableFonts('foo');
    trigger_error('Cairo::availableFonts should take no arguments');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
bool(true)
string(%d) %s
Cairo::availableFonts() expects exactly 0 parameters, 1 given