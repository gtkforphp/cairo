--TEST--
Cairo\Enum is abstract
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
use Cairo\Enum;

try {
    $item = new Enum;
} catch (Error $e) {
    echo $e->getMessage();
}

?>
--EXPECTF--
Cannot instantiate abstract class Cairo\Enum