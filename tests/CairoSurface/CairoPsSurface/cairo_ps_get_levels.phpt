--TEST--
cairo_ps_get_levels() function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!in_array('PS', cairo_available_surfaces())) die('skip - PS surface not available');
if(!function_exists('cairo_ps_get_levels')) die('skip - cairo_ps_get_levels not available');
?>
--FILE--
<?php
var_dump(cairo_ps_get_levels());

cairo_ps_get_levels('foo');
?>
--EXPECTF--
array(2) {
  [0]=>
  int(0)
  [1]=>
  int(1)
}

Warning: cairo_ps_get_levels() expects exactly 0 parameters, 1 given in %s on line %d