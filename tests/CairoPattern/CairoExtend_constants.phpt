--TEST--
CairoExtend class constants
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$constants = array(
	'NONE',
	'REPEAT',
	'REFLECT',
	'PAD',
	);

foreach($constants as $name) {
	var_dump(defined('CairoExtend::' . $name));
}
?>
--EXPECT--
bool(true)
bool(true)
bool(true)
bool(true)