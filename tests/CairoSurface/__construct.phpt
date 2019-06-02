--TEST--
new Cairo\Surface [ __construct method ]
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
class test extends Cairo\Surface {}

class test2 extends Cairo\Surface {
	public function __construct() {}
}

try {
	$surface = new test();
	echo 'Attempting to use constructor should throw an exception';
} catch (TypeError $e) {
	echo $e->getMessage();
}

$surface = new test2();
$surface->finish();
echo 'First call to any method should throw a fatal error';
?>
--EXPECTF--
Cairo\Surface cannot be constructed
Fatal error: Internal surface object missing in test2 wrapper, you must call parent::__construct in extended classes in %s on line %d