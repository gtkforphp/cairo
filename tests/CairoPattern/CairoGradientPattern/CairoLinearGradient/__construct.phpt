--TEST--
new CairoLinearGradient [ __construct method ]
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$x0 = 1;
$x1 = 2;
$y0 = 3;
$y1 = 4;

$pattern = new CairoLinearGradient($x0, $y0, $x1, $y1);
var_dump($pattern);

?>
--EXPECTF--
object(CairoLinearGradient)#%d (0) {
}