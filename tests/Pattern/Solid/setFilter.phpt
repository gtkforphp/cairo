--TEST--
Cairo\Pattern->setFilter() method [using Solid]
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

$pattern->setFilter(Cairo\Filter::GOOD);
$filter = $pattern->getFilter();
var_dump($filter == Cairo\Filter::GOOD);

$pattern->setFilter(new Cairo\Filter('FAST'));
$filter = $pattern->getFilter();
var_dump($filter == Cairo\Filter::FAST);

/* Total number of args needed = 1 */
try {
    $pattern->setFilter();
    trigger_error('setFilter with no args');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
try {
    $pattern->setFilter(1, 1);
    trigger_error('setFilter with too many args');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* arg must be int or castable to int */
try {
    $pattern->setFilter(array());
    trigger_error('Arg 1 must be int');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* int must be in enum */
try {
    $pattern->setFilter(999);
    trigger_error('Arg 1 must be int');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
bool(true)
bool(true)
Cairo\Pattern::setFilter() expects exactly 1 parameter, 0 given
Cairo\Pattern::setFilter() expects exactly 1 parameter, 2 given
Cairo\Pattern::setFilter() expects parameter 1 to be int, array given
Value 999 provided is not a const in enum Cairo\Filter