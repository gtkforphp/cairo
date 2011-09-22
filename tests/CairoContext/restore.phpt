--TEST--
CairoContext->restore() method
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

$context->save();
$context->restore();

/* restore without save */
try {
    $context->restore();
    trigger_error('save requires only one arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args */
try {
    $context->restore('foo');
    trigger_error('save requires only one arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
cairo_restore() without matching cairo_save()
CairoContext::restore() expects exactly 0 parameters, 1 given
