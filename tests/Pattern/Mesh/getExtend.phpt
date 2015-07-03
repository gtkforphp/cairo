--TEST--
Cairo\Pattern->getExtend() method [using Solid]
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
$extend = $pattern->getExtend();

var_dump($extend == Cairo\Extend::PAD);

/* Total number of args needed = 0 */
try {
    $pattern->getExtend(1);
    trigger_error('getExtend with too many args');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECT--
bool(true)
Cairo\Pattern::getExtend() expects exactly 0 parameters, 1 given