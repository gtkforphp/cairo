--TEST--
CairoContext->pushGroupWithContent() method
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

$context->pushGroupWithContent(CairoContent::COLOR);

/* Wrong number args - needs 1 */
try {
    $context->pushGroupWithContent();
    trigger_error('pushGroupWithContent requires one arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - needs 1 */
try {
    $context->pushGroupWithContent(1, 1);
    trigger_error('pushGroupWithContent requires only one arg');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type, needs int */
try {
    $context->pushGroupWithContent(array());
    trigger_error('pushGroupWithContent arg one must be int');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
CairoContext::pushGroupWithContent() expects exactly 1 parameter, 0 given
CairoContext::pushGroupWithContent() expects exactly 1 parameter, 2 given
CairoContext::pushGroupWithContent() expects parameter 1 to be long, array given