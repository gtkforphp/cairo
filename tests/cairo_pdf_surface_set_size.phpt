--TEST--
cairo_pdf_surface_set_size() function
--SKIPIF--
<?php 

if(!extension_loaded('cairo')) die('skip ');

if(!function_exists('cairo_pdf_surface_set_size')) die('skip not compiled in (CAIRO_HAS_PDF_SURFACE)');

 ?>
--FILE--
<?php
echo 'OK'; // no test case for this function yet
?>
--EXPECT--
OK