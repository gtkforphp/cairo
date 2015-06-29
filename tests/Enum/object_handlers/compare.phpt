--TEST--
Cairo\Enum compare objects handler
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
    const Orange = 3;
    const Banana = 4;
}

$fruit1 = new Fruit(Fruit::Apple);
$fruit2 = new Fruit(Fruit::Pear);
$fruit3 = new Fruit(Fruit::Apple);

var_dump($fruit1 > $fruit2);
var_dump($fruit1 < $fruit2);
var_dump($fruit1 < 2);

var_dump($fruit1 == $fruit2);
var_dump($fruit1 == $fruit3);
var_dump($fruit1 === 1);
var_dump($fruit1 == 1);

?>
--EXPECT--
bool(false)
bool(true)
bool(true)
bool(false)
bool(true)
bool(false)
bool(true)