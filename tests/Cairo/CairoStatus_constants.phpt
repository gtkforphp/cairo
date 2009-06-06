--TEST--
CairoStatus class constants
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$constants = array(
	'SUCCESS',
	'NO_MEMORY',
	'INVALID_RESTORE',
	'INVALID_POP_GROUP',
	'NO_CURRENT_POINT',
	'INVALID_MATRIX',
	'INVALID_STATUS',
	'NULL_POINTER',
	'INVALID_STRING',
	'INVALID_PATH_DATA',
	'READ_ERROR',
	'WRITE_ERROR',
	'SURFACE_FINISHED',
	'SURFACE_TYPE_MISMATCH',
	'PATTERN_TYPE_MISMATCH',
	'INVALID_CONTENT',
	'INVALID_FORMAT',
	'INVALID_VISUAL',
	'FILE_NOT_FOUND',
	'INVALID_DASH',
	'INVALID_DSC_COMMENT',
	'INVALID_INDEX',
	'CLIP_NOT_REPRESENTABLE',
);
if (Cairo::version() >= 10600) {
	$constants_16 = array(
		'TEMP_FILE_ERROR',
		'INVALID_STRIDE'
	);
	$constants = array_merge($constants, $constants_16);
}
if (Cairo::version() >= 10800)
{
	$constants_18 = array(
		'FONT_TYPE_MISMATCH',
		'USER_FONT_IMMUTABLE',
		'USER_FONT_ERROR',
		'NEGATIVE_COUNT',
		'INVALID_CLUSTERS',
		'INVALID_SLANT',
		'INVALID_WEIGHT',
	);
	$constants = array_merge($constants, $constants_18);
}

$error = false;
foreach($constants as $name) {
	$constant = 'CairoStatus::' . $name;
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