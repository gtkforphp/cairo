--TEST--
CairoImageSurface::createForData() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$surface = CairoImageSurface::createForData('', CairoFormat::ARGB32, 50, 50);
var_dump($surface);

/* Wrong number args - 1 */
CairoImageSurface::createForData();

/* Wrong number args - 2 */
CairoImageSurface::createForData('');

/* Wrong number args - 3 */
CairoImageSurface::createForData('', CairoFormat::ARGB32);

/* Wrong number args - 4 */
CairoImageSurface::createForData('', CairoFormat::ARGB32, 1);

/* Wrong number args - 5 */
CairoImageSurface::createForData('', CairoFormat::ARGB32, 1, 1, 1, 1);

/* Wrong arg type 1 */
CairoImageSurface::createForData(array(), 1, 1, 1, 1);

/* Wrong arg type 2 */
CairoImageSurface::createForData('', array(), 1, 1, 1);

/* Wrong arg type 3 */
CairoImageSurface::createForData('', 1, array(), 1, 1);

/* Wrong arg type 4 */
CairoImageSurface::createForData('', 1, 1, array(), 1);

/* Wrong arg type 5 */
CairoImageSurface::createForData('', 1, 1, 1, array());

?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}

Warning: CairoImageSurface::createForData() expects at least 4 parameters, 0 given in %s on line %d

Warning: CairoImageSurface::createForData() expects at least 4 parameters, 1 given in %s on line %d

Warning: CairoImageSurface::createForData() expects at least 4 parameters, 2 given in %s on line %d

Warning: CairoImageSurface::createForData() expects at least 4 parameters, 3 given in %s on line %d

Warning: CairoImageSurface::createForData() expects at most 5 parameters, 6 given in %s on line %d

Warning: CairoImageSurface::createForData() expects parameter 1 to be string, array given in %s on line %d

Warning: CairoImageSurface::createForData() expects parameter 2 to be long, array given in %s on line %d

Warning: CairoImageSurface::createForData() expects parameter 3 to be long, array given in %s on line %d

Warning: CairoImageSurface::createForData() expects parameter 4 to be long, array given in %s on line %d

Warning: CairoImageSurface::createForData() expects parameter 5 to be long, array given in %s on line %d