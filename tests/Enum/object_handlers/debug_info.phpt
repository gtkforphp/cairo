--TEST--
Cairo\Enum debug info handler;
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

$fruit = new Fruit(Fruit::Apple);
$fruit->property = 'foobar';
var_dump($fruit);
?>
--EXPECT--
object(Fruit)#1 (4) {
  ["test"]=>
  int(6)
  ["property"]=>
  string(6) "foobar"
  ["__elements"]=>
  array(4) {
    ["Apple"]=>
    int(1)
    ["Pear"]=>
    int(2)
    ["Orange"]=>
    int(3)
    ["Banana"]=>
    int(5)
  }
  ["__value"]=>
  int(1)
}