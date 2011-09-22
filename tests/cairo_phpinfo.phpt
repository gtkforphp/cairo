--TEST--
cairo phpinfo information
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
ob_start();
phpinfo(INFO_MODULES);
$data = ob_get_clean();
$data = explode("\n\n", $data);
foreach($data as $key => $info) {
	if ($info === 'cairo') {
		break;
	}
}
$data = $data[$key + 1];
var_dump($data);
?>
--EXPECTF--
string(%d) "Cairo Graphics Library Bindings => enabled
                        compiled as %s module                        
Cairo Library Version => %s
Extension Version => %s
                        Surface Backends Available                        
Image Surface => %s
PNG Support => %s
PDF Surface => %s
PS Surface => %s
Xlib (X11, X.org) Surface => %s
Quartz (MacOSX) Surface => %s
SVG Surface => %s
Win32 Surface => %s
Recording Surface => %s
                         Font Backends Available                         
Freetype Fonts => %s
Quartz Fonts => %s
Win32 Fonts => %s
User Fonts => %s"
