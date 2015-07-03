--TEST--
Cairo\Pattern->getFilter() method [using Solid]
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
$filter = $pattern->getFilter();

var_dump($filter == Cairo\Filter::GOOD);

/* Total number of args needed = 0 */
try {
    $pattern->getFilter(1);
    trigger_error('getFilter with too many args');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECT--
bool(true)
Cairo\Pattern::getFilter() expects exactly 0 parameters, 1 given