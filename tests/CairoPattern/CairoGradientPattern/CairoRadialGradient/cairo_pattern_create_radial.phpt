--TEST--
cairo_pattern_create_radial function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$pattern = cairo_pattern_create_radial(0.5, 0.5, 0.25, 0.5, 0.5, 0.5);
var_dump($pattern);

?>
--EXPECTF--
object(CairoRadialGradient)#%d (0) {
}