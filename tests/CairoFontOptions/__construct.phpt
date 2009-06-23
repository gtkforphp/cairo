--TEST--
new CairoFontOptions [ __construct() method ]
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$options = new CairoFontOptions();
var_dump($options);

/* Wrong number args */
try {
    new CairoFontOptions('foo');
    trigger_error('__construct requires no args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoFontOptions)#%d (0) {
}
CairoFontOptions::__construct() expects exactly 0 parameters, 1 given