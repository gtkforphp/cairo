--TEST--
CairoContext->appendPath() method
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

$path = $context->copyPath();
var_dump($path);

$context->appendPath($path);

/* Wrong number args - expects 1 */
try {
    $context->appendPath();
    trigger_error('appendPath requires 0 args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - expects 1 */
try {
    $context->appendPath($path, 1);
    trigger_error('appendPath requires 0 args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* incorrect args, expects cairopath*/
try {
    $context->appendPath(1);
    trigger_error('appendPath requires 0 args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
object(CairoPath)#%d (0) {
}
CairoContext::appendPath() expects exactly 1 parameter, 0 given
CairoContext::appendPath() expects exactly 1 parameter, 2 given
CairoContext::appendPath() expects parameter 1 to be CairoPath, integer given