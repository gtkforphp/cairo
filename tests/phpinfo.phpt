--TEST--
cairo extension phpinfo information
--EXTENSIONS--
eos_datastructures
--SKIPIF--
<?php
include __DIR__ . '/skipif.inc';
?>
--FILE--
<?php
$ext = new ReflectionExtension('cairo');
$ext->info();
?>
--EXPECTF--
cairo

Cairo Graphics Library Bindings => enabled
                        compiled as %s module                        
Cairo Library Version => 1.%d.%d
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
User Fonts => %s
