--TEST--
CairoPatternType class constants
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$constants = array(
	'SOLID',
	'SURFACE',
	'LINEAR',
	'RADIAL',
	);

foreach($constants as $name) {
	var_dump(defined('CairoPatternType::' . $name));
}
?>
--EXPECT--
bool(true)
bool(true)
bool(true)
bool(true)