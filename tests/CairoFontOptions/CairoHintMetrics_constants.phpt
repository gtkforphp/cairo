--TEST--
Cairo\HintMetrics class constants
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$constants = array(
	'METRICS_DEFAULT',
	'METRICS_ON',
	'METRICS_OFF',
	);

foreach($constants as $name) {
	var_dump(defined('Cairo\HintMetrics::' . $name));
}
?>
--EXPECT--
bool(true)
bool(true)
bool(true)