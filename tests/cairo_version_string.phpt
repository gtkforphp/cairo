--TEST--
cairo_version_string() function
--SKIPIF--
<?php 

if(!extension_loaded('cairo')) die('skip ');

 ?>
--FILE--
<?php
echo preg_match('|\d\.\d\.\d|', cairo_version_string()) ? "OK" : "ERROR";
?>
--EXPECT--
OK