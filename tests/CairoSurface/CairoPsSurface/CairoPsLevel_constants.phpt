--TEST--
Cairo\Surface\Ps\Level class constants
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!in_array('PS', Cairo::availableSurfaces())) die('skip - PS surface not available');
?>
--FILE--
<?php
$constants = array(
	'LEVEL_2',
	'LEVEL_3',
);

$error = false;
foreach($constants as $name) {
	$constant = 'Cairo\Surface\Ps\Level::' . $name;
	if (!defined($constant)) {
		$error = true;
		echo 'Missing Constant: ' . $constant . "\n";
	}
}
if (!$error) {
	echo "No missing constants, checked " . sizeof($constants) . "!\n";
}
echo "Done\n";
?>
--EXPECTF--
No missing constants, checked %d!
Done