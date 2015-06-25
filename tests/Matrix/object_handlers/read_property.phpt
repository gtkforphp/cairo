--TEST--
Cairo\Matrix object read_property handler;
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
use Cairo\Matrix;

$matrix = new Matrix(1, 2, 3, 4, 5, 6);

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
float(3)
float(5)
float(2)
float(4)
float(6)
string(5) "fruit"