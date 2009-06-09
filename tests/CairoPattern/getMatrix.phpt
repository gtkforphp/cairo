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

var_dump($pattern->getMatrix());

$matrix = new CairoMatrix();
var_dump($matrix);

$pattern->setMatrix($matrix);
var_dump($pattern->getMatrix());

try {
    $pattern->setMatrix();
    trigger_error('Set matrix requires one arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

try {
    $pattern->setMatrix(1, 1);
    trigger_error('Set matrix requires only one arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

try {
    $pattern->setMatrix(1);
    trigger_error('Set matrix requires instanceof Cairomatrix');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoSolidPattern)#%d (0) {
}
object(CairoMatrix)#%d (0) {
}
object(CairoMatrix)#%d (0) {
}
object(CairoMatrix)#%d (0) {
}
CairoPattern::setMatrix() expects exactly 1 parameter, 0 given
CairoPattern::setMatrix() expects exactly 1 parameter, 2 given
CairoPattern::setMatrix() expects parameter 1 to be CairoMatrix, integer given