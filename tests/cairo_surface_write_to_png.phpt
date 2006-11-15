--TEST--
cairo_surface_write_to_png() function
--SKIPIF--
<?php 

if(!extension_loaded('cairo')) die('skip ');

if(!function_exists('cairo_surface_write_to_png')) die('skip not compiled in (CAIRO_HAS_PNG_FUNCTIONS)');

 ?>
--FILE--
<?php
echo 'OK'; // no test case for this function yet
?>
--EXPECT--
OK