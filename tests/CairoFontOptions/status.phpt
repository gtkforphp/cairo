--TEST--
CairoFontOptions->status() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$options = new CairoFontOptions();
var_dump($options);

$status = $options->status();
var_dump($status);
var_dump($status == CairoStatus::SUCCESS);

/* Wrong number args */
try {
    $options->status('foo');
    trigger_error('status requires no args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoFontOptions)#%d (0) {
}
int(0)
bool(true)
CairoFontOptions::status() expects exactly 0 parameters, 1 given