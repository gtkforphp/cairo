--TEST--
Cairo\Enum clone handler
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
    const Banana = 5;

    public $test = 6;
}

$fruit1 = new Fruit(Fruit::Apple);
$fruit1->property = 'foobar';
echo $fruit1, PHP_EOL;

$fruit2 = clone $fruit1;
echo $fruit2, PHP_EOL;

var_dump($fruit1 == $fruit2);
var_dump($fruit2->property == 'foobar');

$fruit2 = Fruit::Banana;
echo $fruit2, PHP_EOL;

var_dump($fruit1 == $fruit2);
?>
--EXPECT--
1
1
bool(true)
bool(true)
5
bool(false)