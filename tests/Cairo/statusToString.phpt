--TEST--
Cairo::statusToString() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$surface = new CairoImageSurface(CAIRO_FORMAT_ARGB32, 50, 50);
var_dump($surface);

$context = new CairoContext($surface);
var_dump($context);

var_dump(Cairo::statusToString($context->status()));

Cairo::statusToString(array());

Cairo::statusToString();
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
string(7) "success"

Warning: Cairo::statusToString() expects parameter 1 to be long, array given in %s on line %d

Warning: Cairo::statusToString() expects exactly 1 parameter, 0 given in %s on line %d