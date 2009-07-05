--TEST--
CairoContext->textPath() method
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

$context->textPath('foobar');

/* Wrong number args 1 */
try {
    $context->textPath();
    trigger_error('textPath requires one arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args 1 */
try {
    $context->textPath('foo', 1);
    trigger_error('textPath requires only one arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type */
try {
    $context->textPath(array());
    trigger_error('textPath requires one arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
CairoContext::textPath() expects exactly 1 parameter, 0 given
CairoContext::textPath() expects exactly 1 parameter, 2 given
CairoContext::textPath() expects parameter 1 to be string, array given