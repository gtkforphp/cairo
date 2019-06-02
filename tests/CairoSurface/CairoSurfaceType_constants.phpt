--TEST--
Cairo\SurfaceType class constants
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$constants = array(
	'IMAGE',
	'PDF',
	'PS',
	'XLIB',
	'XCB',
	'GLITZ',
	'QUARTZ',
	'WIN32',
	'BEOS',
	'DIRECTFB',
	'SVG',
	'OS2',
	'WIN32_PRINTING',
	'QUARTZ_IMAGE',
);

$error = false;
foreach($constants as $name) {
	$constant = 'Cairo\SurfaceType::' . $name;
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