--TEST--
cairo global constants registered
--SKIPIF--
<?php
die('skip - need to get final list of constants created');
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$constants = array();
foreach($constants as $name) {
	var_dump(defined($name));
}
?>
--EXPECTF--