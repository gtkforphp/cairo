--TEST--
Cairo\Pattern->getMatrix() method [using Solid]
--EXTENSIONS--
eos_datastructures
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
?>
--FILE--
<?php
use Cairo\Pattern\Solid;
use Cairo\Matrix;

// create a new matrix, it comes out identical even after refcount unsets
$pattern = new Solid(1, 1, 1);
$matrix1 = $pattern->getMatrix();

$matrix2 = new Matrix(5, 5);
$pattern->setMatrix($matrix2);
$matrix3 = $pattern->getMatrix();

var_dump($matrix2 == $matrix3);
var_dump($matrix1 === $matrix3);

try {
    $pattern->getMatrix('foo');
    trigger_error('get matrix requires no args');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECT--
bool(true)
bool(false)
Cairo\Pattern::getMatrix() expects exactly 0 parameters, 1 given