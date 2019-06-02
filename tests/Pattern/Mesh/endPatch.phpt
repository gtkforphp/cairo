--TEST--
Cairo\Pattern\Mesh->endPatch()
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

try {
    $pattern->endPatch();
} catch (Cairo\Exception $e) {
    echo $e->getMessage(), PHP_EOL;
}

$pattern = new Mesh();
$pattern->beginPatch();
$pattern->lineTo(5,5);
$pattern->endPatch();
var_dump($pattern->getPatchCount());

/* Total number of args needed = 9 */
try {
    $pattern->endPatch(1);
    trigger_error('endPatch with no args');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECT--
invalid operation during mesh pattern construction
long(1)
Cairo\Pattern\Mesh::endPatch() expects exactly 0 parameters, 1 given