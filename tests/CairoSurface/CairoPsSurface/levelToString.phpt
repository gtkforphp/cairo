--TEST--
CairoPsSurface::levelToString() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!in_array('PS', Cairo::availableSurfaces())) die('skip - PS surface not available');
if(!method_exists('CairoPsSurface', 'levelToString')) die('skip - CairoPsSurface::levelToString not available');
?>
--FILE--
<?php
echo CairoPsSurface::levelToString(CairoPsLevel::LEVEL_2), PHP_EOL;

/* Wrong number args */
try {
    CairoPsSurface::levelToString();
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args 2 */
try {
    CairoPsSurface::levelToString(1, 1);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type */
try {
    CairoPsSurface::levelToString(array());
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
PS Level 2
CairoPsSurface::levelToString() expects exactly 1 parameter, 0 given
CairoPsSurface::levelToString() expects exactly 1 parameter, 2 given
CairoPsSurface::levelToString() expects parameter 1 to be long, array given