--TEST--
cairo_font_options_create() function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$options = cairo_font_options_create();
var_dump($options);

// check number of args - should accept 0
cairo_font_options_create(1);
?>
--EXPECTF--
object(CairoFontOptions)#%d (0) {
}

Warning: cairo_font_options_create() expects exactly 0 parameters, 1 given in %s on line %d