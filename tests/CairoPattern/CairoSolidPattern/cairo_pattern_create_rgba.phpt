--TEST--
cairo_pattern_create_rgba function
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

// requires 4 args
cairo_pattern_create_rgba();
cairo_pattern_create_rgba(1);
cairo_pattern_create_rgba(1, 1);
cairo_pattern_create_rgba(1, 1, 1);
cairo_pattern_create_rgba(1, 1, 1, 1, 1);

// arg types are all double
cairo_pattern_create_rgba(array(), 1, 1, 1);
cairo_pattern_create_rgba(1, array(), 1, 1);
cairo_pattern_create_rgba(1, 1, array(), 1);
cairo_pattern_create_rgba(1, 1, 1, array());
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

Warning: cairo_pattern_create_rgba() expects exactly 4 parameters, 0 given in %s on line %d

Warning: cairo_pattern_create_rgba() expects exactly 4 parameters, 1 given in %s on line %d

Warning: cairo_pattern_create_rgba() expects exactly 4 parameters, 2 given in %s on line %d

Warning: cairo_pattern_create_rgba() expects exactly 4 parameters, 3 given in %s on line %d

Warning: cairo_pattern_create_rgba() expects exactly 4 parameters, 5 given in %s on line %d

Warning: cairo_pattern_create_rgba() expects parameter 1 to be double, array given in %s on line %d

Warning: cairo_pattern_create_rgba() expects parameter 2 to be double, array given in %s on line %d

Warning: cairo_pattern_create_rgba() expects parameter 3 to be double, array given in %s on line %d

Warning: cairo_pattern_create_rgba() expects parameter 4 to be double, array given in %s on line %d