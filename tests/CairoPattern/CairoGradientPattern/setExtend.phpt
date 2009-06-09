--TEST--
CairoGradientPattern->setExtend() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$pattern = new CairoLinearGradient(1, 2, 3, 4);
var_dump($pattern);

$pattern->setExtend(CairoExtend::REFLECT);

$extend = $pattern->getExtend();
var_dump($extend);
var_dump($extend == CairoExtend::REFLECT);

/* Total number of args needed = 1 */
try {
    $pattern->setExtend();
    trigger_error('setExtend with no args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
try {
    $pattern->setExtend(1, 1);
    trigger_error('setExtend with too many args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* arg must be int or castable to int */
try {
    $pattern->setExtend(array());
    trigger_error('Arg 1 must be int');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoLinearGradient)#%d (0) {
}
int(2)
bool(true)
CairoGradientPattern::setExtend() expects exactly 1 parameter, 0 given
CairoGradientPattern::setExtend() expects exactly 1 parameter, 2 given
CairoGradientPattern::setExtend() expects parameter 1 to be long, array given