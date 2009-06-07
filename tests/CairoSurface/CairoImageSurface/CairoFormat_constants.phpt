--TEST--
CairoFormat class constants
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$constants = array(
	'ARGB32',
	'RGB24',
	'A8',
	'A1',
);

$error = false;
foreach($constants as $name) {
	$constant = 'CairoFormat::' . $name;
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