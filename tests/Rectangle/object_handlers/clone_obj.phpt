--TEST--
Cairo\Rectangle clone handler
--EXTENSIONS--
eos_datastructures
--SKIPIF--
<?php
include __DIR__ . '/../../skipif.inc';
?>
--FILE--
<?php
use Cairo\Rectangle;

$rect = new Rectangle(5);
$copy = clone $rect;
$copy->x = 9;

var_dump($rect->x);
var_dump($copy->x);

class testing extends Rectangle {}

$testing = new testing(6);
$copy = clone $testing;
var_dump(get_class($copy));
var_dump($copy->x);

?>
--EXPECT--
int(5)
int(9)
string(7) "testing"
int(6)