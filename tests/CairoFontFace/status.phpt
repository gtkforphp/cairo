--TEST--
Cairo\FontFace->status() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
include(dirname(__FILE__) . '/create_toyfont.inc');
var_dump($fontface);

$status = $fontface->status();
var_dump($status);

var_dump($status == CairoStatus::SUCCESS);

/* Wrong number args */
try {
    $fontface->status('foo');
    trigger_error('status requires only one arg');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\FontFace\Toy)#%d (0) {
}
long(0)
bool(true)
Cairo\FontFace::status() expects exactly 0 parameters, 1 given