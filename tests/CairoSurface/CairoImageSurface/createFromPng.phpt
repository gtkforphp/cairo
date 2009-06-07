--TEST--
CairoImageSurface::createFromPng() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!in_array('PNG', cairo_available_surfaces())) die('skip - PNG support not available');
?>
--FILE--
<?php
$surface = CairoImageSurface::createFromPng(dirname(__FILE__) . '/red.png');
var_dump($surface);

$resource = fopen(dirname(__FILE__) . '/red.png', 'rw');
$surface = CairoImageSurface::createFromPng($resource);
var_dump($surface);
fclose($resource);

/* Wrong number args - 1 */
CairoImageSurface::createFromPng();

/* Wrong number args - 2 */
CairoImageSurface::createFromPng('', 1);

/* Wrong arg */
CairoImageSurface::createFromPng(array());
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoImageSurface)#%d (0) {
}

Warning: CairoImageSurface::createFromPng() expects exactly 1 parameter, 0 given in %s on line %d

Warning: CairoImageSurface::createFromPng() expects exactly 1 parameter, 2 given in %s on line %d

Warning: CairoImageSurface::createFromPng() expects parameter 1 to be a string or a stream resource in %s on line %d