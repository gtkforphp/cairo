--TEST--
Cairo\HintStyle class constants
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$constants = array(
	'STYLE_DEFAULT',
	'STYLE_NONE',
	'STYLE_SLIGHT',
	'STYLE_MEDIUM',
	'STYLE_FULL',
	);

foreach($constants as $name) {
	var_dump(defined('Cairo\HintStyle::' . $name));
}
?>
--EXPECT--
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)