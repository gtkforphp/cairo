--TEST--
 new Cairo\Pattern\Gradient [__construct method]
--EXTENSIONS--
eos_datastructures
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
?>
--FILE--
<?php
use Cairo\Pattern\Gradient;
use Cairo\Exception;

try {
	$class = new Gradient;
} catch (Error $e) {
	echo $e->getMessage(), PHP_EOL;
}

class test extends Gradient {}

try {
	$class = new test;
} catch (Exception $e) {
	echo $e->getMessage(), PHP_EOL;
}

class test2 extends Gradient {
	public function __construct() {}
}
try {
	$pattern = new test2();
	$pattern->getStatus();
} catch (Exception $e) {
	echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECT--
Cannot instantiate abstract class Cairo\Pattern\Gradient
Cairo\Pattern cannot be constructed
Internal pattern object missing in test2, you must call parent::__construct in extended classes