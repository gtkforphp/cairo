--TEST--
cairo_version() function
--SKIPIF--
<?php 

if(!extension_loaded('cairo')) die('skip ');

 ?>
--FILE--
<?php
echo is_numeric(cairo_version()) ? "OK" : "ERROR";
?>
--EXPECT--
OK