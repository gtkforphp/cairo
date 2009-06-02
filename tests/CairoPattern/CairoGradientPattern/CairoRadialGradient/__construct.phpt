--TEST--
new CairoRadialGradient [ __construct method ]
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$pattern = new CairoRadialGradient(0.5, 0.5, 0.25, 0.5, 0.5, 0.5);
var_dump($pattern);

?>
--EXPECTF--
object(CairoRadialGradient)#%d (0) {
}