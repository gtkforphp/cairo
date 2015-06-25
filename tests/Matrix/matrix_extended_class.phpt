--TEST--
extend Cairo\Matrix Class
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
use Cairo\Matrix;
use Cairo\Exception;

class test extends Matrix {}

class test2 extends Matrix {
	public function __construct() {}
}

$matrix = new Matrix();
var_dump($matrix);

$matrix = new test2();
$matrix->invert();
echo 'First call to any method should throw a fatal error';
?>
--EXPECTF--
object(Cairo\Matrix)#%d (0) {
}

Fatal error: Internal matrix object missing in test2 wrapper, you must call parent::__construct in extended classes in %s on line %d