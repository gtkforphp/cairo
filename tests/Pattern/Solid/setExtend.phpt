--TEST--
Cairo\Pattern->setExtend() method [using Solid]
--EXTENSIONS--
eos_datastructures
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
?>
--FILE--
<?php
use Cairo\Pattern\Solid;

$pattern = new Solid(1, 1, 1);

$pattern->setExtend(Cairo\Extend::PAD);

$extend = $pattern->getExtend();
var_dump($extend == Cairo\Extend::PAD);

$pattern->setExtend(new Cairo\Extend('PAD'));
$extend = $pattern->getExtend();
var_dump($extend == Cairo\Extend::PAD);

/* Total number of args needed = 1 */
try {
    $pattern->setExtend();
    trigger_error('setExtend with no args');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
try {
    $pattern->setExtend(1, 1);
    trigger_error('setExtend with too many args');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* arg must be int or castable to int */
try {
    $pattern->setExtend(array());
    trigger_error('Arg 1 must be int');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* int must be in enum */
try {
    $pattern->setExtend(999);
    trigger_error('Arg 1 must be int');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
bool(true)
bool(true)
Cairo\Pattern::setExtend() expects exactly 1 parameter, 0 given
Cairo\Pattern::setExtend() expects exactly 1 parameter, 2 given
Cairo\Pattern::setExtend() expects parameter 1 to be int, array given
Value 999 provided is not a const in enum Cairo\Extend