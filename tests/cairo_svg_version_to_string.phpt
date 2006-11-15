--TEST--
cairo_svg_version_to_string() function
--SKIPIF--
<?php 

if(!extension_loaded('cairo')) die('skip ');

if(!function_exists('cairo_svg_version_to_string')) die('skip not compiled in (CAIRO_HAS_SVG_SURFACE)');

 ?>
--FILE--
<?php
echo 'OK'; // no test case for this function yet
?>
--EXPECT--
OK