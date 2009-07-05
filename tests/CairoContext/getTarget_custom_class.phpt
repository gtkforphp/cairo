--TEST--
CairoContext->getTarget() should return custom classes derived from CairoImageSurface
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
class TestSurface extends CairoImageSurface {
    function __construct($format, $width, $height) {
        parent::__construct($format, $width, $height);
    }
}

$t = new TestSurface(CairoFormat::ARGB32, 500, 500);
$c = new CairoContext($t);
var_dump($c->getTarget() instanceof TestSurface);
var_dump($c->getTarget() instanceof TestSurface);
unset($t);
var_dump($c->getTarget() instanceof TestSurface);
die; // PHP bug? get a memleak without this
?>
--EXPECTF--
bool(true)
bool(true)
bool(true)
