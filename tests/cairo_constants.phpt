--TEST--
cairo global constants registered
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
// cairo status constants
$cairo_status_constants = array(
	'CAIRO_STATUS_SUCCESS',
	'CAIRO_STATUS_NO_MEMORY',
	'CAIRO_STATUS_INVALID_RESTORE',
	'CAIRO_STATUS_INVALID_POP_GROUP',
	'CAIRO_STATUS_NO_CURRENT_POINT',
	'CAIRO_STATUS_INVALID_MATRIX',
	'CAIRO_STATUS_INVALID_STATUS',
	'CAIRO_STATUS_NULL_POINTER',
	'CAIRO_STATUS_INVALID_STRING',
	'CAIRO_STATUS_INVALID_PATH_DATA',
	'CAIRO_STATUS_READ_ERROR',
	'CAIRO_STATUS_WRITE_ERROR',
	'CAIRO_STATUS_SURFACE_FINISHED',
	'CAIRO_STATUS_SURFACE_TYPE_MISMATCH',
	'CAIRO_STATUS_PATTERN_TYPE_MISMATCH',
	'CAIRO_STATUS_INVALID_CONTENT',
	'CAIRO_STATUS_INVALID_FORMAT',
	'CAIRO_STATUS_INVALID_VISUAL',
	'CAIRO_STATUS_FILE_NOT_FOUND',
	'CAIRO_STATUS_INVALID_DASH',
	'CAIRO_STATUS_INVALID_DSC_COMMENT',
	'CAIRO_STATUS_INVALID_INDEX',
	'CAIRO_STATUS_CLIP_NOT_REPRESENTABLE',
);
if (cairo_version() >= 10600) {
	$cairo_status_constants = array_merge($cairo_status_constants,
		array(
			'CAIRO_STATUS_TEMP_FILE_ERROR',
			'CAIRO_STATUS_INVALID_STRIDE'
		)
	);
}
if (cairo_version() >= 10800)
{
	$cairo_status_constants = array_merge($cairo_status_constants,
		array(
			'CAIRO_STATUS_FONT_TYPE_MISMATCH',
			'CAIRO_STATUS_USER_FONT_IMMUTABLE',
			'CAIRO_STATUS_USER_FONT_ERROR',
			'CAIRO_STATUS_NEGATIVE_COUNT',
			'CAIRO_STATUS_INVALID_CLUSTERS',
			'CAIRO_STATUS_INVALID_SLANT',
			'CAIRO_STATUS_INVALID_WEIGHT',
		)
	);
}

$cairo_surface_type_constants = array(
	'CAIRO_SURFACE_TYPE_IMAGE',
	'CAIRO_SURFACE_TYPE_PDF',
	'CAIRO_SURFACE_TYPE_PS',
	'CAIRO_SURFACE_TYPE_XLIB',
	'CAIRO_SURFACE_TYPE_XCB',
	'CAIRO_SURFACE_TYPE_GLITZ',
	'CAIRO_SURFACE_TYPE_QUARTZ',
	'CAIRO_SURFACE_TYPE_WIN32',
	'CAIRO_SURFACE_TYPE_BEOS',
	'CAIRO_SURFACE_TYPE_DIRECTFB',
	'CAIRO_SURFACE_TYPE_SVG',
	'CAIRO_SURFACE_TYPE_OS2',
	'CAIRO_SURFACE_TYPE_WIN32_PRINTING',
	'CAIRO_SURFACE_TYPE_QUARTZ_IMAGE',
);

$cairo_content_constants = array(
	'CAIRO_CONTENT_COLOR',
	'CAIRO_CONTENT_ALPHA',
	'CAIRO_CONTENT_COLOR_ALPHA',
);

$surfaces = cairo_available_surfaces();

$cairo_image_format_constants = array(
	'CAIRO_FORMAT_ARGB32',
	'CAIRO_FORMAT_RGB24',
	'CAIRO_FORMAT_A8',
	'CAIRO_FORMAT_A1',
);

if (in_array('PS', $surfaces)) {
	// ps level constants
	$cairo_ps_version_constants = array(
		'CAIRO_PS_LEVEL_2',
		'CAIRO_PS_LEVEL_3',
	);
} else { $cairo_ps_version_constants = array(); }

if (in_array('SVG', $surfaces)) {
	// svg version constants
	$cairo_svg_version_constants = array(
		'CAIRO_SVG_VERSION_1_1',
		'CAIRO_SVG_VERSION_1_2',
	);
} else { $cairo_svg_version_constants = array(); }

// merge all the constants together
$constants = array_merge(
				$cairo_status_constants,
				$cairo_surface_type_constants,
				$cairo_content_constants,
				$cairo_image_format_constants,
				$cairo_ps_version_constants,
				$cairo_svg_version_constants);

$error = false;
foreach($constants as $name) {
	if (!defined($name)) {
		$error = true;
		echo 'Missing Constant: ' . $name . "\n";
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