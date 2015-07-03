--TEST--
Cairo\Rectangle read_property handler
--EXTENSIONS--
eos_datastructures
--SKIPIF--
<?php
include __DIR__ . '/../../skipif.inc';
?>
--FILE--
<?php
use Cairo\Rectangle;

$rect = new Rectangle(1, 2, 3, 4);

var_dump($rect->x);
var_dump($rect->y);
var_dump($rect->width);
var_dump($rect->height);

$rect->banana = 'fruit';
var_dump($rect->banana);

?>
--EXPECT--
int(1)
int(2)
int(3)
int(4)
string(5) "fruit"