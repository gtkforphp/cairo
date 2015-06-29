--TEST--
Cairo\Enum->getName();
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
use Cairo\Enum;

class Fruit extends Enum {
    const Apple = 1;
    const Pear = 2;
}

$fruit1 = new Fruit(Fruit::Apple);
var_dump($fruit1->getName());

$fruit2 = new Fruit(Fruit::Pear);
var_dump($fruit2->getName());

// too many args
try {
     $fruit1->getName(1);
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
string(5) "Apple"
string(4) "Pear"
Cairo\Enum::getName() expects exactly 0 parameters, 1 given