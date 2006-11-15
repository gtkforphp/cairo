--TEST--
cairo_status_to_string() function
--SKIPIF--
<?php 

if(!extension_loaded('cairo')) die('skip ');

 ?>
--FILE--
<?php
echo 'OK'; // no test case for this function yet
?>
--EXPECT--
OK