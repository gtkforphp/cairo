--TEST--
cairo_pattern_create_linear function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$pattern = cairo_pattern_create_linear(1,2,3,4);
var_dump($pattern);

?>
--EXPECTF--
object(CairoLinearGradient)#%d (0) {
}