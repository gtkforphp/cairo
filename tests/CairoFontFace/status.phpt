--TEST--
CairoFontFace->status() method
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
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoToyFontFace)#%d (0) {
}
int(0)
bool(true)
CairoFontFace::status() expects exactly 0 parameters, 1 given