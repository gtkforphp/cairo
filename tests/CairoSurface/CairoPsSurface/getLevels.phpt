--TEST--
CairoPsSurface::getLevels() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!in_array('PS', Cairo::availableSurfaces())) die('skip - PS surface not available');
if(!method_exists('CairoPsSurface', 'getLevels')) die('skip - CairoPsSurface::getLevels not available');

?>
--FILE--
<?php
var_dump(CairoPsSurface::getLevels());

/* Wrong number args */
try {
    CairoPsSurface::getLevels('foo');
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
array(2) {
  [0]=>
  int(0)
  [1]=>
  int(1)
}
CairoPsSurface::getLevels() expects exactly 0 parameters, 1 given