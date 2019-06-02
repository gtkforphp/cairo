--TEST--
Cairo\Surface\Ps::getLevels() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!in_array('PS', Cairo::availableSurfaces())) die('skip - PS surface not available');
if(!method_exists('Cairo\Surface\Ps', 'getLevels')) die('skip - Cairo\Surface\Ps::getLevels not available');

?>
--FILE--
<?php
var_dump(Cairo\Surface\Ps::getLevels());

/* Wrong number args */
try {
    Cairo\Surface\Ps::getLevels('foo');
    trigger_error('We should bomb here');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
array(2) {
  [0]=>
  long(0)
  [1]=>
  long(1)
}
Cairo\Surface\Ps::getLevels() expects exactly 0 parameters, 1 given