--TEST--
cairo_ps_surface_dsc_comment() function
--SKIPIF--
<?php 

if(!extension_loaded('cairo')) die('skip ');

if(!function_exists('cairo_ps_surface_dsc_comment')) die('skip not compiled in (CAIRO_HAS_PS_SURFACE)');

 ?>
--FILE--
<?php
echo 'OK'; // no test case for this function yet
?>
--EXPECT--
OK