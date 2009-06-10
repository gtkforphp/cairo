--TEST--
cairo_pattern_get_rgba function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$red = 0.8;
$green = 0.6;
$blue = 0.5;
$alpha = 0.7;

$pattern = cairo_pattern_create_rgba($red, $green, $blue, $alpha);
var_dump($pattern);

$values = cairo_pattern_get_rgba($pattern);
var_dump($values);
var_dump($red === $values['red']);
var_dump($green === $values['green']);
var_dump($blue === $values['blue']);
var_dump($alpha === $values['alpha']);

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// requires 1 arg
cairo_pattern_get_rgba();
cairo_pattern_get_rgba($pattern, 1);

// arg types is CairoPattern
cairo_pattern_get_rgba(1);
?>
--EXPECTF--
object(CairoSolidPattern)#%d (0) {
}
array(4) {
  ["red"]=>
  float(0.8)
  ["green"]=>
  float(0.6)
  ["blue"]=>
  float(0.5)
  ["alpha"]=>
  float(0.7)
}
bool(true)
bool(true)
bool(true)
bool(true)

Warning: cairo_pattern_get_rgba() expects exactly 1 parameter, 0 given in %s on line %d

Warning: cairo_pattern_get_rgba() expects exactly 1 parameter, 2 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_pattern_get_rgba() must be an instance of CairoSolidPattern, integer given

Warning: cairo_pattern_get_rgba() expects parameter 1 to be CairoSolidPattern, integer given in %s on line %d