--TEST--
cairo_ps_level_to_string() function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!in_array('PS', cairo_available_surfaces())) die('skip - PS surface not available');
if(!function_exists('cairo_ps_level_to_string')) die('skip - cairo_ps_level_to_string not available');
?>
--FILE--
<?php
echo cairo_ps_level_to_string(CAIRO_PS_LEVEL_2), PHP_EOL;

// check number of args - should accept ONLY 1
cairo_ps_level_to_string();
cairo_ps_level_to_string(1, 1);

// check arg types, should be int
cairo_ps_level_to_string(array());
?>
--EXPECTF--
PS Level 2

Warning: cairo_ps_level_to_string() expects exactly 1 parameter, 0 given in %s on line %d

Warning: cairo_ps_level_to_string() expects exactly 1 parameter, 2 given in %s on line %d

Warning: cairo_ps_level_to_string() expects parameter 1 to be long, array given in %s on line %d