--TEST--
Cairo\Matrix object write_property handler
--EXTENSIONS--
eos_datastructures
--SKIPIF--
<?php
include __DIR__ . '/../../skipif.inc';
?>
--FILE--
<?php
use Cairo\Matrix;

$matrix = new Matrix(9, 9, 9, 9, 9, 9);

$matrix->xx = 1;
$matrix->xy = 2;
$matrix->x0 = 3;
$matrix->yx = 4;
$matrix->yy = 5;
$matrix->y0 = 6;

var_dump($matrix->xx);
var_dump($matrix->xy);
var_dump($matrix->x0);
var_dump($matrix->yx);
var_dump($matrix->yy);
var_dump($matrix->y0);

$matrix->banana = 'fruit';
var_dump($matrix->banana);

?>
--EXPECT--
float(1)
float(2)
float(3)
float(4)
float(5)
float(6)
string(5) "fruit"