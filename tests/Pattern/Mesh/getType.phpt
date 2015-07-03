--TEST--
Cairo\Pattern->getType() method [using Solid]
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
$type = $pattern->getType();
var_dump($type instanceof Cairo\Pattern\Type);
var_dump($type == Cairo\Pattern\Type::SOLID);

try {
    $pattern->getType('foo');
    trigger_error('gettype requires no args');
} catch (TypeError $e) {
    echo $e->getMessage();
}
?>
--EXPECT--
bool(true)
bool(true)
Cairo\Pattern::getType() expects exactly 0 parameters, 1 given