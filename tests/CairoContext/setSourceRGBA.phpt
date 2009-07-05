--TEST--
CairoContext->setSourceRGBA() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$surface = new CairoImageSurface(CairoFormat::ARGB32, 50, 50);
var_dump($surface);

$context = new CairoContext($surface);
var_dump($context);

$context->setSourceRGBA(0.1, 0.1, 0.1, 0.5);

try {
    $context->setSourceRGBA("1", "1", "1", "0");
} catch (CairoException $e) {
    echo $e->getMessage();
}

try {
    $context->setSourceRGBA("1.0", "1.0", "1.0", "0.0");
} catch (CairoException $e) {
    echo $e->getMessage();
}

try {
    $context->setSourceRGBA("foo", "bar", "baz", "foo");
} catch (CairoException $e) {
    echo $e->getMessage();
}

?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
CairoContext::setSourceRGBA() expects parameter 1 to be double, string given
