--TEST--
CairoWin32Fontface::__construct() function
--SKIPIF--
<?php
if(!extension_loaded('cairo'))
	die('skip - Cairo extension not available');
if(!class_exists('CairoWin32FontFace'))
	die('skip - CairoWin32FontFace class not available');
?>
--FILE--
<?php
$f_opts = array (
	'lfWeight' => CairoWin32FontWeight::BOLD,
	'lfFaceName' => 'Impact'
);

// Test with no params
$f = new CairoWin32FontFace;
var_dump($f);

// Test with all params
$f = new CairoWin32FontFace($f_opts);
var_dump($f);

// Test with incorrect param
try {
	$f = new CairoWin32FontFace('not an array');
} catch (TypeError $e) {
	echo $e->getMessage(), PHP_EOL;
}

// Test with too many params
try {
	$f = new CairoWin32FontFace($f_opts, '2nd param');
} catch (TypeError $e) {
	echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoWin32FontFace)#%d (0) {
}
object(CairoWin32FontFace)#%d (0) {
}
CairoWin32FontFace::__construct() expects parameter 1 to be array, string given
CairoWin32FontFace::__construct() expects at most 1 parameter, 2 given
