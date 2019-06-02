--TEST--
Cairo\Pattern->setMatrix() method [using Solid]
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

$pattern = new Solid(1, 1, 1);

$matrix = new Matrix();

$pattern->setMatrix($matrix);
$matrix1 = $pattern->getMatrix();

var_dump($matrix === $matrix1);

$matrix2 = new Matrix(5, 5);
$pattern->setMatrix($matrix2);
$matrix1 = $pattern->getMatrix();

var_dump($matrix2 === $matrix1);

try {
    $pattern->setMatrix();
    trigger_error('Set matrix requires one arg');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

try {
    $pattern->setMatrix(1, 1);
    trigger_error('Set matrix requires only one arg');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

try {
    $pattern->setMatrix(1);
    trigger_error('Set matrix requires instanceof Matrix');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

?>
--EXPECT--
bool(true)
bool(true)
Cairo\Pattern::setMatrix() expects exactly 1 parameter, 0 given
Argument 1 passed to Cairo\Pattern::setMatrix() must be an instance of Cairo\Matrix, int given
Argument 1 passed to Cairo\Pattern::setMatrix() must be an instance of Cairo\Matrix, int given