--TEST--
Cairo\Matrix->__construct() extended
--EXTENSIONS--
eos_datastructures
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
?>
--FILE--
<?php
use Cairo\Matrix;
use Cairo\Exception;

class Bad extends Matrix {
    public function __construct() {
    }
}

$fail = new Bad();

try {
    $fail->invert();
} catch (Exception $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECT--
invalid matrix (not invertible)