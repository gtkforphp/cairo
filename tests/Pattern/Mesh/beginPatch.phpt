--TEST--
Cairo\Pattern\Mesh->beginPatch()
--EXTENSIONS--
eos_datastructures
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
?>
--FILE--
<?php
use Cairo\Pattern\Mesh;

$pattern = new Mesh();

$pattern->beginPatch();
var_dump($pattern->getPatchCount());

// we have to do stuff here
$pattern->lineTo(5,5);
$pattern->endPatch();

$pattern->beginPatch();
var_dump($pattern->getPatchCount());

try {
    $pattern->beginPatch();
} catch (Cairo\Exception $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Total number of args needed = 9 */
try {
    $pattern->beginPatch(1);
    trigger_error('beginPatch with no args');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECT--
long(0)
long(1)
invalid operation during mesh pattern construction
Cairo\Pattern\Mesh::beginPatch() expects exactly 0 parameters, 1 given