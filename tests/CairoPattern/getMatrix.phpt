--TEST--
CairoPattern->getMatrix() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$pattern = new CairoSolidPattern(0.8, 0.6, 0.5);
var_dump($pattern);

var_dump($orig_matrix = $pattern->getMatrix());

$matrix = new CairoMatrix(5, 5);
var_dump($matrix);
var_dump($orig_matrix === $matrix);

$pattern->setMatrix($matrix);
var_dump($matrix1 = $pattern->getMatrix());
var_dump($matrix1 === $matrix);
var_dump($orig_matrix === $matrix);

try {
    $pattern->getMatrix('foo');
    trigger_error('get matrix requires no args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

die; // DO NOT REMOVE THIS - fixes issue in 5.3 with GC giving bogus memleak reports
?>
--EXPECTF--
object(CairoSolidPattern)#%d (0) {
}
object(CairoMatrix)#%d (0) {
}
object(CairoMatrix)#%d (0) {
}
bool(false)
object(CairoMatrix)#%d (0) {
}
bool(true)
bool(false)
CairoPattern::getMatrix() expects exactly 0 parameters, 1 given