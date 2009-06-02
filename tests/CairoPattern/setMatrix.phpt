--TEST--
CairoPattern->setMatrix() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$pattern = new CairoSolidPattern(0.8, 0.6, 0.5);
var_dump($pattern);

$matrix = new CairoMatrix();
var_dump($matrix);

$pattern->setMatrix($matrix);

try {
    $pattern->setMatrix();
} catch (CairoException $e) {
    echo $e->getMessage();
}

?>
--EXPECTF--
object(CairoSolidPattern)#%d (0) {
}
object(CairoMatrix)#%d (0) {
}
CairoPattern::setMatrix() expects exactly 1 parameter, 0 given