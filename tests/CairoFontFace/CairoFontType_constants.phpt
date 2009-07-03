--TEST--
CairoFontType class constants
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$constants = array(
	'TOY',
	'FT',
	'WIN32',
	);

$version = Cairo::version();
if($version > 10600) {
    $constants[] = 'QUARTZ';
}
if($version > 10800) {
    $constants[] = 'USER';
}
$error = false;
foreach($constants as $name) {
	if (!defined('CairoFontType::' . $name)) {
		$error = true;
		echo 'Missing Constant: CairoFontType::' . $name . "\n";
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