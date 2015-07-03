--TEST--
 new Cairo\Pattern [__construct method]
--EXTENSIONS--
eos_datastructures
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
?>
--FILE--
<?php
use Cairo\Pattern;
use Cairo\Exception;

try {
	$class = new Pattern;
} catch (Error $e) {
	echo $e->getMessage(), PHP_EOL;
}

class test extends Pattern {}

try {
	$class = new test;
} catch (Exception $e) {
	echo $e->getMessage(), PHP_EOL;
}

class test2 extends Pattern {
	public function __construct() {}
}
try {
	$pattern = new test2();
	$pattern->getStatus();
} catch (Exception $e) {
	echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
Cannot instantiate abstract class Cairo\Pattern
Cairo\Pattern cannot be constructed
Internal pattern object missing in test2, you must call parent::__construct in extended classes